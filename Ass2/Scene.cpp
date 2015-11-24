#include "Scene.h"
#include "Camera.h"

Scene::Scene() {

}

Scene::Scene(Point center, Vector3f up, int w, int x, int y, Light* light, Camera* cam) {

	screenCenter.x = center.x;
	screenCenter.y = center.y;
	screenCenter.z = center.z;

	upVector.x = upVector.x;
	upVector.y = upVector.y;
	upVector.z = upVector.z;
	upVector.normalize();



	width = w;
	Rx = x;
	Ry = y;
	ambient = light;
	camera = cam;

	toVector.fromTo(screenCenter, camera->center);
	toVector.normalize();

}

void Scene::addLight(Light* light) {
	lights.push_back(light);
}

void Scene::addObject(SceneObject* object) {
	objects.push_back(object);
}

Scene::~Scene() {

}

