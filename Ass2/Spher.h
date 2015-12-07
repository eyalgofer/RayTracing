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
#include "Intersection.h"
#include "Scene.h"



class SceneObject;
class Scene;
class Intersection;

typedef Vector3f Point;
using namespace std;

class Spher : public SceneObject {
public:

	Spher(Vector3f center, GLfloat radius, Vector3f Ka, Vector3f Kd, Vector3f Ks, int shininess);
	~Spher();
	void findIntersection(Intersection* inter, Ray& ray);
	Vector3f calcAmbientColor(Scene* scene, Intersection* inter);
	Vector3f getNormalAt(Vector3f point);



	GLfloat radius;



};