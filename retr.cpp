#pragma once
#include "stdafx.h"

#include <windows.h>
#include <math.h>
#include <vector>
#define inf 1e10

struct color {
	unsigned int  
};
class colorRGB {
public:
	unsigned int  R;
	unsigned G;
	unsigned B;

	explicit colorRGB() {
		R = 255;
		B = 255;
		G = 255;
	}

	colorRGB(unsigned const R, unsigned const G, unsigned const B) 
		: R(R), G(G), B(B) {};
	
	~colorRGB() {};

	colorRGB operator *(double const k) {
		R = (unsigned) k * R;
		G = (unsigned) k * ;
		B *= k;
		if (R < 0) R = 0;
		else if (R > 255) return 
	}
};

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

	vec3 &operator +(vec3 const &other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	double  operator *(const vec3 &other) {
		return (x * other.x + y * other.y + z * other.z);
	}

	vec3 &operator *(double d) {
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
		return (*this * (1 / l));
	}

};

class light {
public:
	double intensity = 0;
	virtual double computeLighting(vec3 const &Point, vec3 const &Normal) { return 0; };
};

class ambientLight : public light {
public:
	ambientLight(const double &intensity) {
		this->intensity = intensity;
	}

	double computeLighting(vec3 const &Point, vec3 const &Normal) { 
		return intensity; 
	};
	~ambientLight() {};
};

class pointLight : public light {	
	
	vec3 position;

public:
	pointLight(const double &intensity, const vec3 &position) : position(position) {
		this->intensity = intensity;
	}

	double computeLighting(vec3 const &Point, vec3 const &Normal) {
		vec3 L;
		L = position - Point;

		double Normal_dot_L = L * Normal;
		if (Normal_dot_L > 0)
			return intensity * Normal_dot_L / L.len();
		else return 0;
	}
	~pointLight() {};
};

class directionalLight : public light {

	vec3 direction;

public:
	directionalLight(const double &intensity, const vec3 &direction) : direction(direction) {
		this->intensity = intensity;
	}

	double computeLighting(vec3 const &Point, vec3 const &Normal) {
		double Normal_dot_L = direction * Normal;
		if (Normal_dot_L > 0)
			return intensity * Normal_dot_L / direction.len();
		else return 0;
	}

	~directionalLight() {};
};



class object {
public:
	COLORREF color;
	vec3 position;

	virtual bool Intersect(vec3 const &start, vec3 const &direction, double *t) { return false; };
};

class Sphere: public object {
	
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

COLORREF TraceRay(const vec3 &start, vec3 &direction, std::vector<object*> &scene, std::vector<light*> &lightning) {

	double *t = new double[2];
	t[0] = inf, t[1] = inf;

	double closest_t = inf;
	size_t closest_object = -1;

	for (size_t i = 0; i < scene.size(); i++) {

		if (scene[i]->Intersect(start, direction, t))
			if (t[0] < closest_t) {
				closest_object = i;
				closest_t = t[0];
			}
			else if  (t[1] < closest_t) {
				closest_object = i;
				closest_t = t[1];
			}
	}

	if (closest_object == -1) return RGB(255, 255, 255);

	vec3 intersectPoint = direction * closest_t + start;
	vec3 Normal;
	Normal = intersectPoint - scene[closest_object]->position;
	Normal.normalize();

	double totalIntensity = 0;

	for (size_t i = 0; i < lightning.size(); i++) {
		totalIntensity += lightning[i]->computeLighting(intersectPoint, Normal);
	}

	
	return scene[closest_object]->color * totalIntensity;
};

void Draw_Scene(HDC hdc) {
	
	int imageWigth = 640,
		imageHeight = 640,
		screenDistanse = 640;

	vec3 O = vec3(0, 0, 0);

	std::vector<object*> scene;
	
	scene.push_back(&Sphere(vec3(0, imageHeight, 3 * screenDistanse), 640, RGB(255, 0, 0)));
	scene.push_back(&Sphere(vec3(2 * imageWigth, 0, 4 * screenDistanse), 640, RGB(0, 255, 0)));
	scene.push_back(&Sphere(vec3(- 2 * imageWigth, 0, 4 * screenDistanse), 640, RGB(0, 0, 255)));

	std::vector<light*> lighting;

	lighting.push_back(&ambientLight(0.2));
	lighting.push_back(&pointLight(0.6, vec3(2 * imageWigth, 2 * imageHeight, 0)));
	lighting.push_back(&directionalLight(0.2, vec3(imageWigth, 4 * imageHeight, 4 * screenDistanse)));


	for (int i = 0; i < imageWigth; ++i)
	{
		for (int j = 0; j < imageHeight; ++j)
		{
			double x = i - imageWigth / 2;
			double y = j - imageHeight / 2;
			vec3 D = vec3(x, y, screenDistanse);
			D.normalize();

			SetPixel(hdc, i, j, TraceRay(O, D, scene, lighting));
		}
	}
return;
};
