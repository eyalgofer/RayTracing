#pragma once
#include "Light.h"
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "glut.h"
#include "Vector3f.h"
#include "Intersection.h"
#include "Ray.h"

typedef Vector3f Point;
using namespace std;

class Spot : public Light {
public:
	Spot();
	Spot(Vector3f RGB, Vector3f direction, Vector3f position, GLfloat cutoffAngle);
	~Spot();
	Vector3f calcDiffuseSpeculareColor(Scene* scene, Ray& ray, Ray& lightRay, Intersection* inter);
	void constructRayToLight(Ray& lightRay,Intersection* inter);
	string getName();
	Vector3f direction;
	Vector3f position;
	GLfloat cutoffAngle;

};