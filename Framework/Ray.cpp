#include "Ray.h"

Ray::Ray(Vec3 start_, Vec3 dir_)
{
	start = start_;
	dir = dir_;
}

Vec3 Ray::currentPosition(float t)
{
	Vec3 p;
	p.x = start.x + t * dir.x;
	p.y = start.y + t * dir.y;
	p.z = start.z + t * dir.z;

	return p;

}
