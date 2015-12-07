#pragma once
#include "Light.h"
#include "SceneObject.h"
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "glut.h"
#include "Vector3f.h"
#include "Ray.h"
#include "Scene.h"
#include "Intersection.h"

class SceneObject;
class Scene;
class Intersection;


typedef Vector3f Point;
using namespace std;

class Plane : public SceneObject {

public: 


	Plane(Vector3f norm,Point c, GLfloat w, GLfloat len, Vector3f Ka, Vector3f Kd, Vector3f Ks,int shininess);
	~Plane();
	void findIntersection(Intersection* inter, Ray& ray);
	Vector3f calcAmbientColor(Scene* scene, Intersection* inter);
	Vector3f getNormalAt(Vector3f point);

	Vector3f normal;
	Vector3f right;
	Vector3f up;
	GLfloat width;
	GLfloat length;

};