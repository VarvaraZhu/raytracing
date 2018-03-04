#pragma once
#include "stdafx.h"
#include "objects.h"
#include "texture.h"

Colour Object::reflectedColour(Vec3 const &direction, Vec3 const &point, Light const *light) const {
	Vec3 L = -light->getDirection(point);
	Vec3 V = -direction;
	Vec3 N = this->buildNormal(point);
	Vec3 R = N * 2 * (N * L) - L;
	R.normalize(), V.normalize();
	double cos = R * V;
	if (cos > 0)
		return ((*light).colour - object_colour) * pow(cos, specular) * (*light).intensity;

	else return (Colour(0, 0, 0));
}
/*
double Object::reflectedColour(Vec3 const &direction, Vec3 const &point, Light const *light) {
	Vec3 L = -light->getDirection(point);
	Vec3 V = -direction;
	Vec3 N = this->buildNormal(point);
	Vec3 R = N * 2 * (N * L) - L;
	R.normalize(), V.normalize();
	double cos = R * V;
	if (cos > 0)
		return pow(cos, specular) * (*light).intensity;

	else return 0;
}
*/
bool Sphere::intersect(Vec3 const &start, Vec3 const &direction, double &t0, double &t1) const {

	//Решается уравнение (direction * t - position)^2 = radius2 
	double
		a = direction * direction,
		b = -(position * direction),
		c = position * position - radius2,
		D = b * b - c * a;

	if (D < 0)
		return FALSE;

	double d = sqrt(D);

	t0 = (-b - d) / a;
	t1 = (-b + d) / a;

	return TRUE;
}


