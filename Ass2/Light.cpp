#include "Light.h"

Light::Light() {
	RGB.x = 0;
	RGB.y = 0;
	RGB.z = 0;
}

Light::Light(Vector3f rgb) {
	RGB.x = rgb.x;
	RGB.y = rgb.y;
	RGB.z = rgb.z;
}

Light::~Light() {

}


