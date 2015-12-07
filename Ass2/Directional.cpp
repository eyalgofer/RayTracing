#include "Directional.h"

Directional::Directional() {

}

Directional::Directional(Vector3f RGB, Vector3f dir ) : Light(RGB) {
	direction.x = dir.x;
	direction.y = dir.y;
	direction.z = dir.z;
	direction.normalize();

}

Directional::~Directional() {

}

Vector3f Directional::calcDiffuseSpeculareColor(Scene* scene, Ray& ray, Ray& lightRay, Intersection* inter) {

	Vector3f L = -direction;
	L.normalize();
	Vector3f V = -ray.vector;
	Vector3f R = direction - (2 * inter->normal * (Vector3f::dotProduct(direction, inter->normal)));
	R.normalize();
	Vector3f color = inter->obj->Kd*Vector3f::dotProduct(inter->normal,L) + inter->obj->Ks*pow(Vector3f::dotProduct(V,R), inter->obj->shininess);
	return color*RGB;
}

void Directional::constructRayToLight(Ray& lightRay, Intersection* inter) {

	lightRay.vector = -direction;
	lightRay.source = inter->position;
	lightRay.length = numeric_limits<float>::infinity();
}

string Directional::getName() {
	return "Directional";
}