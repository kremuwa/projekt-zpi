#include "Algorithm.h"

using namespace std;


int main(int argc, char** argv)
{
	
	pcl::visualization::PCLVisualizer viewer("PCL Viewer");
	Algorithm obiekt(&viewer);
	cout << endl << "1. Play" << endl << "2. Play from kinect" << endl << "3. Play from file" << endl;

	int a;
	cin >> a;

	if (a == 2) {
		obiekt.playFromKinect();
	}
	if (a == 3) {
		obiekt.playFromFile("sample-pokoj.oni");
	}

	cin >> a;
	return 0;

}