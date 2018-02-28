#include "stdafx.h"

#include "vec3.h"


Vec3& Vec3::operator=(Vec3 const &other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	//”нарные арифметические операторы

Vec3& Vec3::operator-=(Vec3 const &other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

Vec3& Vec3::operator +=(Vec3 const &other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

Vec3& Vec3::operator *=(double d) {
		x *= d;
		y *= d;
		z *= d;
		return *this;
	}

Vec3& Vec3::operator -() const {
		Vec3 new_vec3 = Vec3(*this);
		new_vec3.x = -x;
		new_vec3.y = -y;
		new_vec3.z = -z;
		return new_vec3;
	}

	//Ѕинарные арифметические операторы
Vec3 Vec3::operator -(Vec3 const &other) {
		Vec3 new_vec3 = Vec3(*this);
		new_vec3 -= other;
		return new_vec3;
	}

Vec3 Vec3::operator +(Vec3 const &other) {
		Vec3 new_vec3 = Vec3(*this);
		new_vec3 += other;
		return new_vec3;
	}

Vec3 Vec3::operator *(double d) const {
		Vec3 new_vec3 = Vec3(*this);
		new_vec3 *= d;
		return new_vec3;
	}

	//—кал€рное умножение 
double Vec3::operator *(const Vec3 &other) const {
		return (x * other.x + y * other.y + z * other.z);
	}

