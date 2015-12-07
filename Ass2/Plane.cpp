#include "Plane.h"

#define BOARD_SIZE 32

Plane::Plane(Vector3f norm, Point c, GLfloat w, GLfloat len, Vector3f a, Vector3f d, Vector3f s, int shine): SceneObject(c, a, d, s, shine) {

	normal.x = norm.x;
	normal.y = norm.y;
	normal.z = norm.z;
	width = w;
	length = len;
	if (normal.x == 0)
	{
		right = Vector3f(1, 0, 0);
		up = Vector3f::crossProduct(right, normal);
	}
	else if (normal.y == 0)
	{
		up = Vector3f(0, 1, 0);
		right = Vector3f::crossProduct(up, normal);
	}
	else if (normal.z == 0)
	{
		right = Vector3f(0, 0, 1);
		up = Vector3f::crossProduct(right, normal);
	}
	
}

void Plane::findIntersection(Intersection* inter, Ray& ray) {
	GLfloat infinity = std::numeric_limits<float>::infinity();
	Vector3f rayDirection = ray.vector;
	float a = Vector3f::dotProduct(rayDirection,normal);
	if (a > 0) {
		return;
	}
	else {
		ray.length = Vector3f::dotProduct(normal, ((center - ray.source) / Vector3f::dotProduct(normal, ray.vector)));
		inter->position = ray.source + (ray.length * ray.vector);
		inter->distance = ray.length;
		if (Vector3f::dotProduct(ray.vector, normal) < 0)
			inter->normal = normal;
		else
			inter->normal = -normal;
		inter->obj = this;
	}
}

Vector3f Plane::calcAmbientColor(Scene* scene, Intersection* inter) {

	GLint location;
	Vector3f botleft;
	botleft = center - ((width / 2) * right) + ((length / 2) * up);
	location = (GLint)fabs((Vector3f::dotProduct((inter->position - botleft), right)) / (width / BOARD_SIZE));
	location += (GLint)fabs((Vector3f::dotProduct((inter->position - botleft), up)) / (length / BOARD_SIZE));
	location = location % 2;
	return ((!location * Vector3f(0, 0, 0)) + (location * scene->ambient->RGB)) * Ka;
}

Vector3f Plane::getNormalAt(Vector3f point) {
	return normal;
}

Plane::~Plane() {

}