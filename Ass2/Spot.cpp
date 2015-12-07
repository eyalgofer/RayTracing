#include "Spot.h"

Spot::Spot() {

}

Spot::Spot(Vector3f RGB, Vector3f dir, Vector3f pos, GLfloat cutoff) : Light(RGB) {

	direction.x = dir.x;
	direction.y = dir.y;
	direction.z = dir.z;
	direction.normalize();

	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	cutoffAngle = cutoff;

	
}

Spot::~Spot() {

}

Vector3f Spot::calcDiffuseSpeculareColor(Scene* scene, Ray& ray, Ray& lightRay, Intersection* inter) {
	Vector3f intensity = Vector3f(0, 0, 0);
	Vector3f Lspot = inter->position - position;
	Lspot.normalize();
	Vector3f Dspot = direction;
	Dspot.normalize();
	GLfloat theta = acos(Vector3f::dotProduct(Lspot, Dspot))*180.0 / M_PI;
	if (theta > cutoffAngle)
		return intensity;

	intensity = Vector3f::dotProduct(Dspot, Lspot)*RGB;
	Vector3f L = -Lspot;
	L.normalize();
	Vector3f V = -ray.vector;
	V.normalize();
	Vector3f R = direction - (2 * inter->normal * (Vector3f::dotProduct(direction, inter->normal)));
	R.normalize();
	Vector3f color = inter->obj->Kd*Vector3f::dotProduct(inter->normal, L) + inter->obj->Ks*pow(Vector3f::dotProduct(V, R), inter->obj->shininess);
	return color*intensity;

}

void Spot::constructRayToLight(Ray& lightRay, Intersection* inter) {
	lightRay.vector = position - inter->position;
	lightRay.source = inter->position;
	lightRay.length = lightRay.vector.getLength();
}

string Spot::getName() {
	return "Spot";
}