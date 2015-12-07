#pragma once
#include <iostream>
#include "Vector3f.h"
#include "glut.h"


class Ray;
class Intersection;
class Scene;

using namespace std;


class SceneObject {
public:

	SceneObject(Vector3f c, Vector3f a, Vector3f d, Vector3f s, GLfloat sh);
	virtual ~SceneObject();
	virtual void findIntersection(Intersection* inter, Ray& ray) = 0;
	virtual Vector3f calcAmbientColor(Scene* scene, Intersection* inter) = 0;
	virtual Vector3f getNormalAt(Vector3f point) = 0;

	Vector3f center;
	Vector3f Ka;
	Vector3f Kd;
	Vector3f Ks;
	int shininess;

};