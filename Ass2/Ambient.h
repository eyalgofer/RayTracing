#pragma once
#include "Light.h"
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "glut.h"
#include "Vector3f.h"
#include "Ray.h"


using namespace std;

class Ambient : public Light {
public:
	Ambient();
	Ambient(Vector3f rgb);
	~Ambient();
	Vector3f calcDiffuseSpeculareColor(Scene* scene, Ray& ray, Ray& lightRay, Intersection* inter);
	void constructRayToLight(Ray& lightRay, Intersection* inter);
	string getName();

};