#pragma once
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "glut.h"
#include "Vector3f.h"


using namespace std;


class Light {

public:
	Vector3f RGB;

	Light();
	Light(Vector3f rgb);
	~Light();

};