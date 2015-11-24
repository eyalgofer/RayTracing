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

using namespace std;
typedef Vector3f Point;

class Scene {

public:

	Scene();
	Scene(Point center, Vector3f up, int w, int x, int y, Light* light, Camera* cam);
	~Scene();
	void addLight(Light* light);
	void addObject(SceneObject* object);

	Point screenCenter;
	Vector3f upVector;
	Vector3f toVector;
	Vector3f rightVector;
	int width;
	int Rx, Ry;
	Light* ambient;
	Camera* camera;
	vector<Light*> lights;
	vector<SceneObject*> objects; // planes and sphers 

};


