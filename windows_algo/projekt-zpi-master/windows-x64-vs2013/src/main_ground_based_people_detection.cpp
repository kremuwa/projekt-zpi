#include "Algorithm.h"

using namespace std;


int main(int argc, char** argv)
{
	
	pcl::visualization::PCLVisualizer viewer("PCL Viewer");
	Algorithm obiekt(&viewer);
	cout << endl << "1. Play without algorithm" << endl << "2. Play with algorithm" << end "3. Play with recording" << endl;

	int a;
	cin >> a;
	if (a == 1) {
		obiekt.playFromFile("sample-pokoj.oni", 1);
	}
	if (a == 2) {
		obiekt.playFromFile("sample-pokoj.oni", 2);
	}

	if (a == 3){
		obiekt.playFromFile("sample-pokoj.oni", 3);
	}

	cin >> a;
	return 0;

}