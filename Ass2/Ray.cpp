#include "Ray.h"

typedef Vector3f Point;

Ray::Ray(){
	source = Point();
	vector = Point();
	length = 0;
}

Ray::Ray(Point s, Vector3f v, GLfloat len) {
	source = s;
	vector = v;
	length = len;
}


Ray::~Ray(){
}
