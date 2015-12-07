#include "Spher.h"



Spher::Spher(Vector3f c, GLfloat r, Vector3f a, Vector3f d, Vector3f s, int shine): SceneObject(c, a, d, s, shine) {
	radius = r;
}
Vector3f Spher::getNormalAt(Vector3f point) {
	Point normal = (point - center);
	normal.normalize();
	return normal;
}

void Spher::findIntersection(Intersection* inter, Ray& ray) {
	GLfloat infinity = std::numeric_limits<float>::infinity();
	float root;
	float a = 1; // normalized 
	float b = (2 * (ray.source.x - center.x)*ray.vector.x) + (2 * (ray.source.y - center.y)*ray.vector.y) + (2 * (ray.source.z - center.z)*ray.vector.z);
	float c = pow(ray.source.x - center.x, 2) + pow(ray.source.y - center.y, 2) + pow(ray.source.z - center.z, 2) - radius*radius;
	float discriminant = b*b - 4*a*c;
	if (discriminant < 0) {
		// the ray didnt intersect with the spher
		return;
	}
	else {
		//the first root 
		float root1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.000001; // 0.000001 help with accurcy some how 
		if (root1 > 0) {
			// the first root is the smallest positive root 
			root = root1;
		}
		else {
			// the second root is the smallest positive root 
			root = ((-1 * b + sqrt(discriminant)) / 2) - 0.000001;
		}
		ray.length = root;
		inter->position = ray.source + (ray.length * ray.vector);
		inter->distance = ray.length;
		inter->normal = getNormalAt(inter->position);
		inter->normal.normalize();
		inter->obj = this;
	}

}

Vector3f Spher::calcAmbientColor(Scene* scene, Intersection* inter) {
	return  scene->ambient->RGB * Ka;
}

Spher::~Spher() {

}