#pragma once
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "glut.h"
#include "Vector3f.h"

typedef Vector3f Point;
using namespace std; 


class Camera {
public:
	Point center;
	Camera();
	Camera(Point c);
	~Camera();

};