#include "Scene.h"
#include "Camera.h"


Scene::Scene() {

}

Scene::Scene(Point center, Vector3f up, GLfloat w, GLfloat x, GLfloat y, Light* light, Camera* cam) {

	screenCenter.x = center.x;
	screenCenter.y = center.y;
	screenCenter.z = center.z;

	upVector.x = up.x;
	upVector.y = up.y;
	upVector.z = up.z;
	upVector.normalize();

	toVector.fromTo(screenCenter, cam->center);
	toVector.normalize();
	rightVector = Vector3f::crossProduct(upVector, toVector);

	width = w;

	Rx = x;
	Ry = y;
	printf("!@ %d %d %d !@", width, Rx, Ry);
	ambient = light;
	camera = cam;


}

void Scene::addLight(Light* light) {
	lights.push_back(light);
}

void Scene::addObject(SceneObject* object) {
	objects.push_back(object);
}


Scene::~Scene() {

}

