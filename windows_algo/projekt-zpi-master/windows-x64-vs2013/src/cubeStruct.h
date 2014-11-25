#ifndef CUBE_STRUCT_H
#define CUBE_STRUCT_H

#include <string>
using namespace std;

typedef struct {
	string name;
	double x_min;
	double x_max;
	double y_min;
	double y_max;
	double z_min;
	double z_max;
} cubeStruct;


#endif CUBE_STRUCT_H