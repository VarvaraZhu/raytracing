#pragma once
#include "stdafx.h"

#include <math.h>

class Vec3
{
	double x;
	double y;
	double z;

public:
	explicit Vec3() {};
	Vec3(const double x, const double y, const double z) :
		x(x), y(y), z(z) {};

	Vec3(Vec3 const &other) {
		x = other.x;
		y = other.y;
		z = other.z;
	};

	~Vec3() {};

	Vec3 &operator =(Vec3 const &other);
	Vec3 &operator -=(Vec3 const &other);
	Vec3 &operator +=(Vec3 const &other);
	Vec3 &operator *=(double d);
	Vec3 &operator -() const;

	Vec3 operator -(Vec3 const &other);
	Vec3 operator +(Vec3 const &other);
	Vec3 operator *(double d) const;
	double operator *(const Vec3 &other) const;

	double len() const {
		return sqrt((*this) * (*this));
	}

	Vec3 normalize() {
		(*this) *= (1 / this->len());
		return *this;
	}
};

