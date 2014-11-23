#include "Algorithm.h"

using namespace std;


int main(int argc, char** argv)
{
	
	pcl::visualization::PCLVisualizer viewer("PCL Viewer");
	Algorithm obiekt(&viewer);
	cout << endl << "1. Play without algorithm" << endl << "2. Play with algorithm" << endl ;

	int a;
	cin >> a;
	if (a == 1) {
		obiekt.playFromFile("sample-pokoj.oni", 1);
	}
	if (a == 2) {
		obiekt.playFromFile("sample-pokoj.oni", 2);
	}

	cin >> a;
	return 0;

}