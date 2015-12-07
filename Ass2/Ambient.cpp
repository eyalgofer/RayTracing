#include "Ambient.h"
#include "Light.h"

Ambient::Ambient() {

}

Ambient::Ambient(Vector3f rgb) :Light(rgb) {


}

Ambient::~Ambient() {

}





Vector3f Ambient::calcDiffuseSpeculareColor(Scene* scene, Ray& ray, Ray& lightRay, Intersection* inter) {
	return Vector3f(0, 0, 0);
}

void Ambient::constructRayToLight(Ray& lightRay, Intersection* inter) {
	lightRay.length = 0;
	lightRay.source = Vector3f(0, 0, 0);
	lightRay.vector = Vector3f(0, 0, 0);
}

string Ambient::getName() {
	return "Ambient";
}