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


using namespace std;

class Directional : public Light {
public: 
	Directional();
	Directional(Vector3f RGB, Vector3f direction);
	~Directional();
	Vector3f calcDiffuseSpeculareColor(Scene* scene, Ray& ray, Ray& lightRay, Intersection* inter);
	void constructRayToLight(Ray& lightRay, Intersection* inter);
	string getName();

	Vector3f direction;



};