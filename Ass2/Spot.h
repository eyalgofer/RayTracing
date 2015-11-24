#pragma once
#include "Light.h"
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "glut.h"
#include "Vector3f.h"


using namespace std;

class Spot : public Light {
public:
	Spot();
	~Spot();

	Vector3f direction;
	GLfloat cutoffAngle;

};