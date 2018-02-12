#pragma once
#include "stdafx.h"

#include <windows.h>
#include <math.h>
#include <vector>
#define inf 1e10

class vec3 {

public:
	double x;
	double y;
	double z;

	explicit vec3() {};
	vec3(const double x, const double y, const double z) : 
					x(x), y(y), z(z) {};
	~vec3() {};

	vec3 &operator -(vec3 const &other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	double operator *(const vec3 &other) {
		return (x * other.x + y * other.y + z * other.z);
	}

	vec3 operator *(double d) {
		x *= d;
		y *= d;
		z *= d;
		return *this;
	}

	double len() {
		return sqrt((*this) * (*this));
	}

	vec3 normalize() {
		double l = this->len();
		return (*this * (1/l));
	}
	
};

class object {
public:
	COLORREF color;
	vec3 position;
public:
	virtual bool Intersect(vec3 const &start, vec3 const &direction, double *t) { return false; };
};

class Sphere: public object {

//class Sphere {
	
private:
	double radius, radius2;

public:

	Sphere(const vec3 &centre, const double &radius, const COLORREF &color = RGB(0, 0, 0)) :
		radius(radius), radius2(radius * radius) {
		this->color = color;
		this->position = centre;
	};

	~Sphere() {};

public:
	bool Intersect(vec3 const &start, vec3 const &direction, double *t) {

		vec3 CS = position - start;
		double
			b = CS * direction,
			c = CS * CS - radius2,
			D = b * b - c;

		if (D < 0)
			return FALSE;
		
		double d = sqrt(D);
		
		t[0] = -b - d;
		t[1] = -b + d;
		return TRUE;
	}
};

COLORREF TraceRay(const vec3 &start, const vec3 &direction, std::vector<object*> &scene) {

	const Sphere* sphere = NULL;
	double *t = new double[2];
	double t_near = inf;
	double t0 = inf, t1 = inf;
	COLORREF tempcolor = RGB(255, 255, 255);

	for (size_t i = 0; i < scene.size(); i++) {
		double t0 = inf, t1 = inf;
		if (scene[i]->Intersect(start, direction, t)) 
			tempcolor = scene[i]->color;
	}
	return tempcolor;
};

void Draw_Scene(HDC hdc) {
	
	vec3 O = vec3(0, 0, 0); 
	std::vector<object*> scene;
	//std::vector<Sphere> scene;

	scene.push_back(&Sphere(vec3(10, 10, 100), 10, RGB(255, 0, 0)));
	scene.push_back(&Sphere(vec3(30, 30, 100), 30, RGB(0, 255, 0)));
	scene.push_back(&Sphere(vec3(100, 100, 100), 100, RGB(0, 0, 255)));

	int imaheWigth = 640,
		imageHeight = 640;

	for (int i = 0; i < imaheWigth; ++i)
	{
		for (int j = 0; j < imageHeight; ++j)
		{
			vec3 D = vec3(i, j, 1000);
			D.normalize();
			SetPixel(hdc, i, j, TraceRay(O, D, scene));
		}
	}
return;
};
