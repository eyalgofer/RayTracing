#pragma once
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "glut.h"
#include "Vector3f.h"


class Scene;
class Intersection;
class Ray;
using namespace std;


class Light {

public:
	Vector3f RGB;

	Light();
	Light(Vector3f rgb);
	~Light();
	virtual Vector3f calcDiffuseSpeculareColor(Scene* scene, Ray& ray, Ray& lightRay, Intersection* inter) = 0;
	virtual void constructRayToLight(Ray& lightRay,Intersection* inter) = 0;
	virtual string getName() = 0;

};