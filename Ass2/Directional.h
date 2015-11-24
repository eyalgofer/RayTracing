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

class Directional : public Light {
public: 
	Directional();
	~Directional();

	Vector3f direction;



};