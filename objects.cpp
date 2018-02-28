#pragma once
#include "stdafx.h"
#include "objects.h"
#include "texture.h"


bool Sphere::intersect(Vec3 const &start, Vec3 const &direction, double *t) {

	//Решается уравнение (direction * t - position)^2 = radius2 
	double
		a = direction * direction,
		b = -(position * direction),
		c = position * position - radius2,
		D = b * b - c * a;

	if (D < 0)
		return FALSE;

	double d = sqrt(D);

	t[0] = (-b - d) / a;
	t[1] = (-b + d) / a;

	return TRUE;
}




