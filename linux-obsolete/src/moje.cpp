#include <pcl/console/parse.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/people/ground_based_people_detection_app.h>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

class Algorithm
{
    pcl::visualization::PCLVisualizer *displayer;
    public:Algorithm(pcl::visualization::PCLVisualizer*)
    {
        cout<<"witam w konstruktorze";
    }






};

int main()
{
    cout<<"Siemano23";
    Algorithm dupa = new Algorithm(new pcl::visualization::PCLVisualizer());

};


