#include <iostream>
#include "Plane.h"
using namespace std;

void Plane::set(float x, float y, float z, float d)
{
	plane.x = x;
	plane.y = y;
	plane.z = z;
	plane.w = d;
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
	cout << "D: " << plane.w << endl;

}

