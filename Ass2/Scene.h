#pragma once

#include <vector>
#include "Light.h"
#include "SceneObject.h"
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "glut.h"
#include "Vector3f.h"
#include "Camera.h"
#include "Spher.h"
#include "Plane.h"


using namespace std;
typedef Vector3f Point;

class Scene {

public:

	Scene();
	Scene(Point center, Vector3f up, GLfloat w, GLfloat x, GLfloat y, Light* light, Camera* cam);
	~Scene();
	void addLight(Light* light);
	void addObject(SceneObject* object);


	Point screenCenter;
	Vector3f upVector;
	Vector3f toVector;
	Vector3f rightVector;
	GLfloat width;
	GLfloat Rx, Ry;
	Light* ambient;
	Camera* camera;
	vector<Light*> lights;
	vector<SceneObject*> objects; // planes and sphers 

};


