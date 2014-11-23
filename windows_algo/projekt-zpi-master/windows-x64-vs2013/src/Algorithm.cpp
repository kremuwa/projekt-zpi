#include "Algorithm.h"

using namespace std;

// definitions of global variables

boost::mutex cloud_mutex;
int person_nr = 0;
bool new_cloud_available_flag = false;
pcl::people::GroundBasedPeopleDetectionApp<PointT> people_detector;
Eigen::VectorXf ground_coeffs;
static unsigned count = 0;
static double last = pcl::getTime();
vector<Eigen::Vector4f> centroids_prev;
vector<Eigen::Vector4f> centroids_curr;
int empty_in_row = 0;
float min_confidence = -1.5;
pcl::Grabber* interface;

bool flag1 = true;
bool flag2 = false;

boost::function<void(const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f;
// definitions of global functions

void cloud_cb_(const PointCloudT::ConstPtr &callback_cloud, PointCloudT::Ptr& cloud,
	bool* new_cloud_available_flag)
{
	cloud_mutex.lock();    // for not overwriting the point cloud from another thread
	*cloud = *callback_cloud;
	*new_cloud_available_flag = true;
	cloud_mutex.unlock();
}

void pp_callback(const pcl::visualization::PointPickingEvent& event, void* args)
{
	struct callback_args* data = (struct callback_args *)args;
	if (event.getPointIndex() == -1)
		return;
	PointT current_point;
	event.getPoint(current_point.x, current_point.y, current_point.z);
	data->clicked_points_3d->points.push_back(current_point);
	// Draw clicked points in red:
	pcl::visualization::PointCloudColorHandlerCustom<PointT> red(data->clicked_points_3d, 255, 0, 0);
	data->viewerPtr->removePointCloud("clicked_points");
	data->viewerPtr->addPointCloud(data->clicked_points_3d, red, "clicked_points");
	data->viewerPtr->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 10, "clicked_points");
	std::cout << current_point.x << " " << current_point.y << " " << current_point.z << std::endl;
}

int if_same_person(vector<Eigen::Vector4f> centroids, Eigen::Vector3f person, float thresold)
{
	cout << "aktualna liczba ludzi: " << person_nr << endl;

	for (int i = 0; i<centroids.size(); i++)
	{
		cout << "Roznice w koordynatach: " << endl << abs(centroids[i][0] - person[0]) << " " << abs(centroids[i][1] - person[1]) << " " << abs(centroids[i][2] - person[2]);
		cout << endl << "porowanie a: ";
		cout << abs(centroids[i][0] - person[0]);
		cout << endl << "porownanie b: ";
		cout << abs(centroids[i][1] - person[1]);
		cout << endl << "porownanie c: ";
		cout << abs(centroids[i][2] - person[2]);
		cout << endl;

		if (abs(centroids[i][0] - person[0]) < thresold && abs(centroids[i][1] - person[1]) < thresold && abs(centroids[i][2] - person[2]) < thresold)
		{
			cout << "znalazlem pasujaca osobe";
			return int(centroids[i][3]);
		}
		else return ++person_nr;
	}
	return ++person_nr;
}

// definicje funkcji klasy Algorithm

Algorithm::Algorithm(pcl::visualization::PCLVisualizer *_viewer) {

	svm_filename = "trainedLinearSVMForPeopleDetectionWithHOG.yaml";
	
	viewer = _viewer;
	
	min_height = 1.3;
	max_height = 2.3;
	dist = 0.2;
	voxel_size = 0.06;
	rgb_intrinsics_matrix << 525, 0.0, 319.5, 0.0, 525, 239.5, 0.0, 0.0, 1.0; // Kinect RGB camera intrinsics
	
	new_cloud_available_flag = false;

};


void Algorithm::playFromKinect()
{
	// playing from Kinect is equivalent to playing from file with no filepath

	playFromFile();
}




void Algorithm::playFromFile(string filename)
{

	PointCloudT::Ptr cloud(new PointCloudT);
	
	interface = new pcl::OpenNIGrabber(filename);
	f = boost::bind(&cloud_cb_, _1, cloud, &new_cloud_available_flag);
	interface->registerCallback(f);
	interface->start();

	// Wait for the first frame:

	while (!new_cloud_available_flag)
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	new_cloud_available_flag = false;
	cloud_mutex.lock();    // for not overwriting the point cloud

	// Display pointcloud:
	pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb(cloud);
	viewer->addPointCloud<PointT>(cloud, rgb, "input_cloud");
	viewer->setCameraPosition(0, 0, -2, 0, -1, 0, 0);

	// Add point picking callback to viewer:
		
	callback_args cb_args;
	PointCloudT::Ptr clicked_points_3d(new PointCloudT);
	cb_args.clicked_points_3d = clicked_points_3d;
	cb_args.viewerPtr = pcl::visualization::PCLVisualizer::Ptr(viewer);
	viewer->registerPointPickingCallback(pp_callback, (void*)&cb_args);

	cout << "Kliknij w 3 punkty na podlodze trzymajac wcisniety SHIFT";
	viewer->addText("Kliknij w 3 punkty na podlodze trzymajac wcisniety SHIFT", 250, 300, 20, 1, 1, 1);
	viewer->addText("Nastepnie nacisnij klawisz Q", 250, 250, 20, 1, 1, 1);

	// Spin until 'Q' is pressed:
	viewer->spin();
	std::cout << "Gotowe." << std::endl;

	cloud_mutex.unlock();

	// Ground plane estimation:
	ground_coeffs.resize(4);
	std::vector<int> clicked_points_indices;
	for (unsigned int i = 0; i < clicked_points_3d->points.size(); i++)
		clicked_points_indices.push_back(i);
	pcl::SampleConsensusModelPlane<PointT> model_plane(clicked_points_3d);
	model_plane.computeModelCoefficients(clicked_points_indices, ground_coeffs);
	std::cout << "Ground plane: " << ground_coeffs(0) << " " << ground_coeffs(1) << " " << ground_coeffs(2) << " " << ground_coeffs(3) << std::endl;

	// Create classifier for people detection:  
	pcl::people::PersonClassifier<pcl::RGB> person_classifier;
	person_classifier.loadSVMFromFile(svm_filename);   // load trained SVM

	// People detection app initialization:
   // people detection object
	people_detector.setVoxelSize(voxel_size);                        // set the voxel size
	people_detector.setIntrinsics(rgb_intrinsics_matrix);            // set RGB camera intrinsic parameters
	people_detector.setClassifier(person_classifier);                // set person classifier
	//	  people_detector.setHeightLimits(min_height, max_height);         // set person height limits
	people_detector.setPersonClusterLimits(min_height, max_height, 0.1, 8.0); // set person height limits

	// For timing:
	

	// Main loop:
	mainLoop(viewer, cloud, dist);



		/*	while (true)
	{
		if (new_cloud_available_flag && cloud_mutex.try_lock())    // if a new cloud is available
		{
			new_cloud_available_flag = false;

			// Perform people detection on the new cloud:
			std::vector<pcl::people::PersonCluster<PointT> > clusters;   // vector containing persons clusters
			people_detector.setInputCloud(cloud);
			people_detector.setGround(ground_coeffs);                    // set floor coefficients
			people_detector.compute(clusters);                           // perform people detection

			ground_coeffs = people_detector.getGround();                 // get updated floor coefficients


			// Draw cloud and people bounding boxes in the viewer:
			viewer->removeAllPointClouds();
			viewer->removeAllShapes();
			
			pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb(cloud);
			viewer->addPointCloud<PointT>(cloud, rgb, "input_cloud");
			
			unsigned int k = 0;

			
			centroids_curr.clear();

			for (std::vector<pcl::people::PersonCluster<PointT> >::iterator it = clusters.begin(); it != clusters.end(); ++it)
			{
				if (it->getPersonConfidence() > min_confidence)             // draw only people with confidence above a threshold
				{
					Eigen::Vector3f centroid_coords; //vector containing persons centroid coordinates

					centroid_coords = it->getCenter(); // calculate centroid coordinates

					int person_on_screen; // person number displayed on screen

					person_on_screen = if_same_person(centroids_prev, centroid_coords, dist); // check if current person existed in prev frame

					// add coordinates to vector containing people from current frame

					float x = centroid_coords[0]; // extract x coordinate of centroid
					float y = centroid_coords[1]; // extract y coordinate of centroid
					float z = centroid_coords[2]; // extract z coorfinate of centroid

					PointT pp;
					pp.getVector3fMap() = it->getCenter();

					Eigen::Vector4f centroid_coords_person;
					centroid_coords_person[0] = x;
					centroid_coords_person[1] = y;
					centroid_coords_person[2] = z;
					centroid_coords_person[3] = (float)person_on_screen;
					centroids_curr.push_back(centroid_coords_person);

					// draw theoretical person bounding box in the PCL viewer:
					it->drawTBoundingBox(*viewer, k); // draw persons bounding box

					cout << "tesst";
					//creating text to display near person box
					string tekst = "person ";

					string Result;

					ostringstream convert;

					convert << person_on_screen;

					Result = convert.str();

					tekst = tekst + Result;

					viewer->addText3D(tekst, pp, 0.08); // display text
					k++;

					cout << "-------------";
				}
			}

			if (k == 0)
			{
				empty_in_row++;
				cout << "Rmpty in a row: " << empty_in_row;
			}
			else empty_in_row = 0;

			if (empty_in_row == 3) {
				cout << "Czyszcze wektor przechowujacy dane o postaciach";
				centroids_prev.clear();
			}

			if (k > 0)centroids_prev = centroids_curr;

			std::cout << k << " people found" << std::endl;
			viewer->spinOnce();

			cloud_mutex.unlock();

		}
	}*/
}

void mainLoop(pcl::visualization::PCLVisualizer *viewer, PointCloudT::Ptr cloud, float dist)
{
	while (true)
	{
		
		if (new_cloud_available_flag && cloud_mutex.try_lock())    // if a new cloud is available
		{
			new_cloud_available_flag = false;

			// Perform people detection on the new cloud:
			std::vector<pcl::people::PersonCluster<PointT> > clusters;   // vector containing persons clusters
			people_detector.setInputCloud(cloud);
			people_detector.setGround(ground_coeffs);                    // set floor coefficients
			people_detector.compute(clusters);                           // perform people detection

			ground_coeffs = people_detector.getGround();                 // get updated floor coefficients


			// Draw cloud and people bounding boxes in the viewer:
			viewer->removeAllPointClouds();
			viewer->removeAllShapes();

			pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb(cloud);
			viewer->addPointCloud<PointT>(cloud, rgb, "input_cloud");

			unsigned int k = 0;
			
			centroids_curr.clear();

			for (std::vector<pcl::people::PersonCluster<PointT> >::iterator it = clusters.begin(); it != clusters.end(); ++it)
			{
				if (it->getPersonConfidence() > min_confidence)             // draw only people with confidence above a threshold
				{
					Eigen::Vector3f centroid_coords; //vector containing persons centroid coordinates

					centroid_coords = it->getCenter(); // calculate centroid coordinates

					int person_on_screen; // person number displayed on screen

					person_on_screen = if_same_person(centroids_prev, centroid_coords, dist); // check if current person existed in prev frame

					// add coordinates to vector containing people from current frame

					float x = centroid_coords[0]; // extract x coordinate of centroid
					float y = centroid_coords[1]; // extract y coordinate of centroid
					float z = centroid_coords[2]; // extract z coorfinate of centroid

					PointT pp;
					pp.getVector3fMap() = it->getCenter();

					Eigen::Vector4f centroid_coords_person;
					centroid_coords_person[0] = x;
					centroid_coords_person[1] = y;
					centroid_coords_person[2] = z;
					centroid_coords_person[3] = (float)person_on_screen;
					centroids_curr.push_back(centroid_coords_person);

					// draw theoretical person bounding box in the PCL viewer:
					it->drawTBoundingBox(*viewer, k); // draw persons bounding box

					cout << "tesst";
					//creating text to display near person box
					string tekst = "person ";

					string Result;

					ostringstream convert;

					convert << person_on_screen;

					Result = convert.str();

					tekst = tekst + Result;

					viewer->addText3D(tekst, pp, 0.08); // display text
					k++;

					cout << "-------------";
				}
			}

			if (k == 0)
			{
				empty_in_row++;
				cout << "Empty in a row: " << empty_in_row;
			}
			else empty_in_row = 0;

			if (empty_in_row == 3) {
				cout << "Czyszcze wektor przechowujacy dane o postaciach";
				centroids_prev.clear();
			}

			if (k > 0)centroids_prev = centroids_curr;

			std::cout << k << " people found" << std::endl;
			viewer->spinOnce();

			cloud_mutex.unlock();
		}
	}
}

void Algorithm::stopPlaying()
{

}

void Algorithm::startAlgorithm()
{
	algorithmEnabled = true;

	// maybe some variables needs to be initialized here?
}

void Algorithm::stopAlgorithm()
{
	algorithmEnabled = false;

	// here we should also clear some variables needed to start the algorithm again
}

void Algorithm::startRecording(string PCDfilepath, string TRJfilepath)
{

}

void Algorithm::stopRecording()
{

}

void Algorithm::setMinConf(float a)
{
	min_confidence = a;
}

void Algorithm::setMinHeight(float a)
{
	min_height = a;
}

void Algorithm::setMaxHeight(float a)
{
	max_height = a;
}

void Algorithm::setDist(float a)
{
	dist = a;
}