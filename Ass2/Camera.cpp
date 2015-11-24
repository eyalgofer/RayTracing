#include "Camera.h"


Camera::Camera() {

}

Camera::Camera(Point c) {
	center.x = c.x;
	center.y = c.y;
	center.z = c.z;
}

Camera::~Camera() {

}