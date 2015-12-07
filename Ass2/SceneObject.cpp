#include "SceneObject.h"

SceneObject::SceneObject(Vector3f c, Vector3f a, Vector3f d, Vector3f s, GLfloat sh)
{
	center.x = c.x;
	center.y = c.y;
	center.z = c.z;
	Ka.x = a.x;
	Ka.y = a.y;
	Ka.z = a.z;
	Kd.x = d.x;
	Kd.y = d.y;
	Kd.z = d.z;
	Ks.x = s.x;
	Ks.y = s.y;
	Ks.z = s.z;
	shininess = sh;

}


SceneObject::~SceneObject()
{
}