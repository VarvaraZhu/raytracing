#pragma once
#include "stdafx.h"

#include <windows.h>
#include <math.h>
#include <vector>
#define inf 1e10

//Цвет объекта
struct colour{

	 int R;
	 int G;
	 int B;

	 colour(const int R = 0,  const int G = 0, const int B = 0) :
		 R(R), G(G), B(B) {};

	 ~colour() {};

	 colour &operator +=(colour const &other) {
		 R += other.R;
		 G += other.G;
		 B += other.B;

		 if (R > 255) R = 255;
		 if (G > 255) G = 255;
		 if (B > 255) B = 255;

		 return *this;
	 }

	 colour &operator *=(double const k) {
		 R = (int)(k * R);
		 G = (int)(k * G);
		 B = (int)(k * B);

		 if (R > 255) R = 255;
		 if (G > 255) G = 255;
		 if (B > 255) B = 255;

		 return *this;
	 }

	 colour operator *(double k) {

		 colour new_colour = colour();
		 new_colour.R = (int)(R * k);
		 new_colour.G = (int)(G * k);
		 new_colour.B = (int)(B * k);

		 return new_colour;
	 }
};

// вектор / точка в трехмерном пространстве
class vec3 {

	double x;
	double y;
	double z;

public:

	explicit vec3() {};

	//Конструктор
	vec3(const double x, const double y, const double z) :
		x(x), y(y), z(z) {};

	//Коструктор копирования
	vec3(vec3 const &other){
		x = other.x;
		y = other.y;
		z = other.z;
	};

	//Деструктор
	~vec3() {};
	
	vec3 &operator =(vec3 const &other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	//Унарные арифметические операторы
	vec3 &operator -=(vec3 const &other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3 &operator +=(vec3 const &other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3 &operator *=(double d) {
		x *= d;
		y *= d;
		z *= d;
		return *this;
	}

	//Бинарные арифметические операторы
	vec3 operator -(vec3 const &other) {
		vec3 new_vec3 = vec3(*this);
		new_vec3 -= other;
		return new_vec3;
	}

	vec3 operator +(vec3 const &other) {
		vec3 new_vec3 = vec3(*this);
		new_vec3 += other;
		return new_vec3;
	}

	vec3 operator *(double d) {
		vec3 new_vec3 = vec3(*this);
		new_vec3 *= d;
		return new_vec3;
	}

	//Скалярное умножение 
	double operator *(const vec3 &other) {
		return (x * other.x + y * other.y + z * other.z);
	}

	//Вычисление длины вектора
	double len() {
		return sqrt((*this) * (*this));
	}

	//Нормировка вектора
	vec3 normalize() {
		(*this) *= (1 / this->len());
		return *this;
	}
};

//Источники света
class light {
public:
	double intensity = 0;
	//computeLighting вычисляет вклад данного источника 
	//в освещение рассматриваемой точки
	//(интенсивность света источника в данной точке)
	virtual double computeLighting(vec3 const &Point, vec3 const &Normal) { return 0; };
};

//Окружающее освещение
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

//Точечный источник
class pointLight : public light{	
	
	vec3 position; 

public:
	pointLight(const double &intensity, const vec3 &position) : position(position) {
		this->intensity = intensity;
	}

	double computeLighting(vec3 const &Point, vec3 const &Normal) {
		
		vec3 L = (position - Point).normalize(); //Направление светового луча

		double cos = L * Normal; //Косинус угла между лучем света и нормалью к поверхности

		if (cos > 0) //Если угол (-pi/2, pi/2) считаем интенсивность
			return (intensity * cos);

		else return 0;
	}

	~pointLight() {};
};

//Направленный источник
class directionalLight : public light {

	vec3 direction;

public:
	directionalLight(const double &intensity, const vec3 &direction) : direction(direction) {
		this->intensity = intensity;
	}

	double computeLighting(vec3 const &Point, vec3 const &Normal) {
		double cos = direction * Normal / direction.len();
		if (cos > 0)
			return intensity * cos;
		else return 0;
	}

	~directionalLight() {};
};

class object {
public:
	colour objColour;
	vec3 position;

	virtual bool Intersect(vec3 const &start, vec3 const &direction, double *t) { return false; };
};

class Sphere: public object {
	
private:
	double radius, radius2;

public:

	Sphere(const vec3 &centre, const double &radius, const colour &Colour = colour(0, 0, 0)) :
		radius(radius), radius2(radius * radius) {
		this->objColour = Colour;
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

colour TraceRay(const vec3 &start, vec3 &direction, std::vector<object*> &scene, std::vector<light*> &lightning) {

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

	if (closest_object == -1) return colour(255, 255, 255);

	vec3 intersectPoint = direction * closest_t + start;
	vec3 Normal = intersectPoint - scene[closest_object]->position;
	Normal.normalize();

	double totalIntensity = 0;

	for (size_t i = 0; i < lightning.size(); i++) {
		totalIntensity += lightning[i]->computeLighting(intersectPoint, Normal);
	}

	return (scene[closest_object]->objColour * totalIntensity);
};

void Draw_Scene(HDC hdc) {
	
	int imageWigth = 640,
		imageHeight = 640,
		screenDistanse = 640;

	vec3 O = vec3(0, 0, 0);

	std::vector<object*> scene;
	
	scene.push_back(&Sphere(vec3(0, imageHeight, 3 * screenDistanse), 640, colour(255, 0, 0)));
	scene.push_back(&Sphere(vec3(2 * imageWigth, 0, 4 * screenDistanse), 640, colour(0, 255, 0)));
	scene.push_back(&Sphere(vec3(- 2 * imageWigth, 0, 4 * screenDistanse), 640, colour(0, 0, 255)));

	std::vector<light*> lighting;

	lighting.push_back(&ambientLight(0.2));
	lighting.push_back(&pointLight(0.6, vec3(2 * imageWigth, imageHeight, 0)));
	lighting.push_back(&directionalLight(0.2, vec3(imageWigth, 4 * imageHeight, 4 * screenDistanse)));

	for (int i = 0; i < imageWigth; ++i)
	{
		for (int j = 0; j < imageHeight; ++j)
		{
			double x = i - imageWigth / 2;
			double y = j - imageHeight / 2;
			vec3 D = vec3(x, y, screenDistanse);
			D.normalize();
			colour tempColour = TraceRay(O, D, scene, lighting);
			SetPixel(hdc, i, j, RGB(tempColour.R, tempColour.G, tempColour.B));
		}
	}
return;
};
