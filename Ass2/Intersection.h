#pragma once
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "glut.h"
#include "Vector3f.h"
#include "SceneObject.h"

class SceneObject;

class Intersection {
public:
	Intersection();
	Intersection(Vector3f position, GLfloat distance);
	Intersection& operator= (const Intersection& inter);
	~Intersection();

	SceneObject* obj;
	Vector3f position;
	GLfloat distance;
	Vector3f normal;

};

