#include <iostream>
#include "Plane.h"
using namespace std;

void Plane::set(float x, float y, float z, float d)
{
	plane.x = x;
	plane.y = y;
	plane.z = z;
	plane.d = d;
}
Plane::Plane()
{
	set(1, 1, 1, 1);
}

Plane::Plane(float x_, float y_, float z_, float d_)
{
	set(x_, y_, z_, d_);

}

Plane::Plane(Vec3 normal, Vec3 p)
{

	set(normal.x, normal.y, normal.z, -p.Dot(normal));
}
Plane::Plane(Vec3 normal, float _d)
{

	set(normal.x, normal.y, normal.z, _d);
}
Plane::Plane(const Vec3& v0, const Vec3& v1, const Vec3& v2)
{
	Vec3 e1 = v1 - v0;
	Vec3 e2 = v2 - v0;
	Vec3 normal = e1.Cross(e2);
	normal.Normalize();
	float d = -normal.Dot(v0);
	set(normal.x, normal.y, normal.z, d);
	print();

}



void Plane::print()
{
	cout << "Ax+By+CZ+ D=0" << endl;
	printf("%f", plane.y);
	cout << "A: " << plane.x << endl;
	cout << "B: " << plane.y << endl;
	cout << "C: " << plane.z << endl;
	cout << "D: " << plane.d << endl;

}

Vec3 Plane::intersectionPoint(Ray ray)
{
	Vec3 N(plane.x, plane.y, plane.z);
	float D = plane.d;
	Vec3 V = ray.dir;
	Vec3 S = ray.start;
	float t;
	float dot = N.Dot(V);

	if (abs(dot) <= 0.0001)
	{
		//If line lies in the plane
		float distance = N.Dot(S) + D;

		if (distance <= 0.00001)
		{
			printf("\nLine lies in plane.\n");
		}
		else { printf("\nNo intersection\n"); }
		//No intersection
	}
	else {
		t = -(D + N.Dot(S)) / (N.Dot(V));
		return ray.currentPosition(t);
	}
	return Vec3(NULL, NULL, NULL);
}