#pragma once
#include "Vector3f.h"
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "glut.h"
#include "Vector3f.h"

using namespace std;
typedef Vector3f Point;


class Ray{
public:
	Point source;	// P0
	Point vector;	// V  = (P - P0)/|(P - P0)|
	GLfloat length;  // t

	Ray();
	Ray(Point s, Vector3f v, GLfloat len);

	~Ray();
};

