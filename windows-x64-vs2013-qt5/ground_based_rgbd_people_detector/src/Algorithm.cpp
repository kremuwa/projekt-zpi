#include "Algorithm.h"

using namespace std;

// definitions of global variables

boost::mutex cloud_mutex;

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


// definicje funkcji klasy Algorithm

Algorithm::Algorithm() {

	svm_filename = "trainedLinearSVMForPeopleDetectionWithHOG.yaml";
	
	min_confidence = -1.5;
	min_height = 1.3;
	max_height = 2.3;
	dist = 0.3;

	isStopped = true;
	isJustStopped = false;
	isAlgorithmEnabled = false;
	isAlgorithmJustEnabled = false;
	isRecordingEnabled = false;
	isRecordingJustEnabled = false;

	person_nr = 0;
	
	/*voxel_size = 0.06;
	rgb_intrinsics_matrix << 525, 0.0, 319.5, 0.0, 525, 239.5, 0.0, 0.0, 1.0; // Kinect RGB camera intrinsics

	cloud = PointCloudT::Ptr(new PointCloudT());
	f = boost::bind(&cloud_cb_, _1, cloud, &new_cloud_available_flag);

	new_cloud_available_flag = false;

	viewer = NULL;*/
};

void Algorithm::run()
{
	qDebug() << QThread::currentThreadId();

	int i = 1;
		
	while (true)
	{
		i++;

		// TODO mutex dla isStopped!

		if (isStopped)
		{
			if (!(i % 100000000))
				qDebug() << isStopped;

			continue;
		}

		// this sections starts when user clicks the "Start Algorithm" button

		qDebug() << "wystartowalo";

		// internal parameters

		float voxel_size = 0.06;
		Eigen::Matrix3f rgb_intrinsics_matrix;
		rgb_intrinsics_matrix << 525, 0.0, 319.5, 0.0, 525, 239.5, 0.0, 0.0, 1.0; // Kinect RGB camera intrinsics

		// create new viewer

		viewer = new pcl::visualization::PCLVisualizer("Detection Algorithm");
		viewer->setCameraPosition(0, 0, -2, 0, -1, 0, 0);

		// Add point picking callback to viewer (for later)

		struct callback_args cb_args;
		PointCloudT::Ptr clicked_points_3d(new PointCloudT);
		cb_args.clicked_points_3d = clicked_points_3d;
		cb_args.viewerPtr = pcl::visualization::PCLVisualizer::Ptr(viewer);
		viewer->registerPointPickingCallback(pp_callback, (void*)&cb_args);

		// Read Kinect live stream / ONI file

		PointCloudT::Ptr cloud(new PointCloudT);
		bool new_cloud_available_flag = false;
		pcl::OpenNIGrabber* interface = new pcl::OpenNIGrabber(currentFile);
		boost::function<void(const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f =
			boost::bind(&cloud_cb_, _1, cloud, &new_cloud_available_flag);
		interface->registerCallback(f);
		interface->start();

		// For timing

		static unsigned count = 0;
		static double last = pcl::getTime();

		// preparing variables

		vector<Eigen::Vector4f> centroids_prev;
		vector<Eigen::Vector4f> centroids_curr;
		int empty_in_row = 0;

		vector<pair<string, PeopleClusterT > > bboxes;

		pcl::people::PersonClassifier<pcl::RGB> person_classifier; // Create classifier for people detection

		pcl::people::GroundBasedPeopleDetectionApp<PointT> people_detector;    // people detection object

		Eigen::VectorXf ground_coeffs;

		// Main loop

		while (true)
		{
			if (new_cloud_available_flag && cloud_mutex.try_lock())    // if a new cloud is available
			{
				new_cloud_available_flag = false;

				if (isAlgorithmJustEnabled)
				{

					// so that this if is run only once after starting the algorithm

					isAlgorithmJustEnabled = false;

					// remove previously chosen points

					clicked_points_3d->points.clear();
					
					// Spin until 'Q' is pressed:

					viewer->spin();

					// Ground plane estimation:

					ground_coeffs.resize(4);
					std::vector<int> clicked_points_indices;
					for (unsigned int i = 0; i < clicked_points_3d->points.size(); i++)
						clicked_points_indices.push_back(i);
					pcl::SampleConsensusModelPlane<PointT> model_plane(clicked_points_3d);
					model_plane.computeModelCoefficients(clicked_points_indices, ground_coeffs);
					
					// load trained SVM

					person_classifier.loadSVMFromFile(svm_filename);

					// People detection app initialization:

					people_detector.setVoxelSize(voxel_size);									// set the voxel size
					people_detector.setIntrinsics(rgb_intrinsics_matrix);						// set RGB camera intrinsic parameters
					people_detector.setClassifier(person_classifier);							// set person classifier
					people_detector.setPersonClusterLimits(min_height, max_height, 0.1, 8.0);	// set person height limits

					// initialize the number for first detected person

					person_nr = 0;

					centroids_prev.clear();
					centroids_curr.clear();

				}

				// Draw cloud and people bounding boxes in the viewer:

				viewer->removeAllPointClouds();
				viewer->removeAllShapes();

				pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb(cloud);
				viewer->addPointCloud<PointT>(cloud, rgb, "input_cloud");

				unsigned int k = 0;
				
				if (!isAlgorithmJustEnabled  && isAlgorithmEnabled)
				{

					// Perform people detection on the new cloud:
					std::vector<pcl::people::PersonCluster<PointT> > clusters;   // vector containing persons clusters
					people_detector.setInputCloud(cloud);
					people_detector.setGround(ground_coeffs);                    // set floor coefficients
					people_detector.compute(clusters);                           // perform people detection

					ground_coeffs = people_detector.getGround();                 // get updated floor coefficients
					
					centroids_curr.clear();
					bboxes.clear();

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

							//creating text to display near person box
							

							string tekst = "person ";

							string Result;

							ostringstream convert;

							convert << person_on_screen;

							Result = convert.str();

							tekst = tekst + Result;

							viewer->addText3D(tekst, pp, 0.08); // display text
							k++;

							qDebug() << "mark 10";
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

					cout << " liczba elementow wektora w miejscu b: " << centroids_curr.size() << endl;
					std::cout << k << " people found" << std::endl;
				
					if (isRecordingJustEnabled)
					{

						// so that this clause is run only once

						isRecordingJustEnabled = false;

						myWriter.startWriting(currentTRJdir, currentPCDdir);

					}

					if (isRecordingEnabled)
					{

						//recorder.write(cloud, );

					}
				}

				viewer->spinOnce();

				cloud_mutex.unlock();

			}
			
			if (isJustStopped)
			{

				interface->stop(); // stop grabbing the frames
				
				viewer->close(); // close the visualizer

				break;

			}

		}
		
	}

}

void Algorithm::playFromKinect()
{
	// playing from Kinect is equivalent to playing from file with no filepath

	playFromFile();
}

void Algorithm::playFromFile(string filename)
{

	isAlgorithmEnabled = false;
	isAlgorithmJustEnabled = false;
	isRecordingEnabled = false;
	isRecordingJustEnabled = false;

	currentFile = filename;

	// this will make the video play

	qDebug() << "ustawiam isstopped na false";

	isStopped = false;
	isJustStopped = false;

}

void Algorithm::stopPlaying()
{

	isStopped = true;
	isJustStopped = true;

}

void Algorithm::startAlgorithm()
{

	isAlgorithmEnabled = true;

	isAlgorithmJustEnabled = true;

}

void Algorithm::stopAlgorithm()
{

	isAlgorithmEnabled = false;

	// here we should also clear some variables needed to start the algorithm again
}

void Algorithm::startRecording(string PCDfilepath, string TRJfilepath)
{

	isRecordingEnabled = true;
	isRecordingJustEnabled = true;

}

void Algorithm::stopRecording()
{

	isRecordingEnabled = false;

}

void Algorithm::playTrajectory()
{

}

void Algorithm::pauseTrajectory()
{

}

void Algorithm::stopTrajectory()
{

}

void Algorithm::jumpToTrajectory(int offset)
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

int Algorithm::if_same_person(vector<Eigen::Vector4f> centroids, Eigen::Vector3f person, float thresold)
{

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
	}
	return ++person_nr;
}