
#include "Intersection.h"

Intersection::Intersection() {
	GLfloat infinity = std::numeric_limits<float>::infinity();
	obj = NULL;
	position = Vector3f(0, 0, 0);
	distance = infinity;
	normal = Vector3f(0, 0, 0);
	// TODO Auto-generated constructor stub

}

Intersection::~Intersection() {
	// TODO Auto-generated destructor stub
}

Intersection::Intersection(Vector3f pos, GLfloat dis) {
	obj = NULL;
	position = pos;
	distance = dis;
	normal = Vector3f(0, 0, 0);
}

Intersection& Intersection::operator = (const Intersection& inter)
{
	obj = inter.obj;
	position = Vector3f(inter.position);
	distance = inter.distance;
	normal = Vector3f(inter.normal);

	return (*this);
};

