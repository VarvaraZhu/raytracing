#pragma once
#include "stdafx.h"

#include <windows.h>
#include <math.h>
#include <vector>
#define inf 1e10

//���� �������
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

// ������ / ����� � ���������� ������������
class vec3 {

	double x;
	double y;
	double z;

public:

	explicit vec3() {};

	//�����������
	vec3(const double x, const double y, const double z) :
		x(x), y(y), z(z) {};

	//���������� �����������
	vec3(vec3 const &other){
		x = other.x;
		y = other.y;
		z = other.z;
	};

	//����������
	~vec3() {};
	
	vec3 &operator =(vec3 const &other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	//������� �������������� ���������

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

	vec3 operator -() const {
		vec3 new_vec3 = vec3(*this);
		new_vec3.x = -x;
		new_vec3.y = -y;
		new_vec3.y = -y;
		return new_vec3;
	}

	//�������� �������������� ���������
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

	vec3 operator *(double d) const {
		vec3 new_vec3 = vec3(*this);
		new_vec3 *= d;
		return new_vec3;
	}

	//��������� ��������� 
	double operator *(const vec3 &other) const {
		return (x * other.x + y * other.y + z * other.z);
	}

	//���������� ����� �������
	double len() const {
		return sqrt((*this) * (*this));
	}

	//���������� �������
	vec3 normalize() {
		(*this) *= (1 / this->len());
		return *this;
	}
};

//��������� �����
class light {
public:
	double intensity = 0;
	//computeLighting ��������� ����� ������� ��������� 
	//� ��������� ��������������� �����
	//(������������� ����� ��������� � ������ �����)
	virtual double computeLighting(vec3 const &Point, vec3 const &Normal, vec3 const &reviewDirection, const int specular) { return 0; };
};

//���������� ���������
class ambientLight : public light {
public:
	ambientLight(const double &intensity) {
		this->intensity = intensity;
	}

	double computeLighting(vec3 const &Point, vec3 const &Normal, vec3 const &reviewDirection, const int specular) {
		return intensity; 
	};
	~ambientLight() {};
};

//�������� ��������
class pointLight : public light{	
	
	vec3 position; 

public:
	pointLight(const double &intensity, const vec3 &position) : position(position) {
		this->intensity = intensity;
	}

	double computeLighting(vec3 const &Point, vec3 const &Normal, vec3 const &reviewDirection, const int specular) {
		
		double totalIntensity = 0;

		vec3 L = (position - Point).normalize(); //�����������, �������� ����������� ��������� ����
		double cos = L * Normal; //������� ���� ����� ����� ����� � �������� � �����������

		if (cos > 0) //���� ���� (-pi/2, pi/2) ������� �������������
			totalIntensity += intensity * cos;

		if (specular != -1) {
			vec3 reflectedRay = Normal * 2 * cos - L;
			double cos_rev = reflectedRay * reviewDirection;
			if (cos_rev > 0)
				totalIntensity += intensity * pow(cos_rev / reflectedRay.len() / reviewDirection.len(), specular);
		}
		return totalIntensity;
	}
	~pointLight() {};
};

//������������ ��������
class directionalLight : public light {

	vec3 direction;

public:
	directionalLight(const double &intensity, const vec3 &direction) : direction(direction) {
		this->intensity = intensity;
	}

	double computeLighting(vec3 const &Point, vec3 const &Normal, vec3 const &reviewDirection, const int specular) {
		// ������� - �������, ������� cos ������ ���� �������������
		double totalIntensity = 0;
		double cos =  -(direction * Normal) / direction.len();
		if (cos > 0)
			totalIntensity += intensity * cos;

		if (specular != -1) {
			vec3 reflectedRay = Normal * 2 * cos + direction;
			double cos_rev = reflectedRay * reviewDirection;
			if (cos_rev > 0)
				totalIntensity += intensity * pow(cos_rev / reflectedRay.len() / reviewDirection.len(), specular);
		}
		return totalIntensity;
	}

	~directionalLight() {};
};

class object {
public:
	colour objColour; //���� �������
	int specular = -1;
	vec3 position; //����� �������
	//����������, ������������ �� ������ ������ � ������� ����� 
	virtual bool Intersect(vec3 const &start, vec3 const &direction, double *t) { return false; };
};

class Sphere: public object {
	
private:
	double radius, radius2;

public:

	Sphere(const vec3 &centre, const double radius, const int specular, const colour &Colour = colour(0, 0, 0)) :
		radius(radius), radius2(radius * radius) {
		this->objColour = Colour;
		this->position = centre;
		this->specular = specular;
	};

	~Sphere() {};

public:
	bool Intersect(vec3 const &start, vec3 const &direction, double *t) {
		
		//�������� ��������� (direction * t - position)^2 = radius2 
		double
			a = direction * direction,
			b = - (position * direction),
			c = position * position - radius2,
			D = b * b - c * a;

		if (D < 0)
			return FALSE;
		
		double d = sqrt(D);
		
		t[0] = (-b - d) / a;
		t[1] = (-b + d) / a;
		return TRUE;
	}
};

//�������, ������������ ���� ������� 
colour TraceRay(const vec3 &start, vec3 &direction, std::vector<object*> &scene, std::vector<light*> &lightning) {

	// Ray = start + t * direction
	double *t = new double[2]; 
	// �������� t, ��������������� ������ ����������� ���� � ��������
	t[0] = inf, t[1] = inf;

	size_t closest_object = -1; //����� ���������� �������
	double closest_t = inf;		//������������� ��������� � ������ ����� �����������

	
	for (size_t i = 0; i < scene.size(); i++) {

		if (scene[i]->Intersect(start, direction, t))
			if (t[0] < closest_t && t[1] > 1) {
				closest_object = i;
				closest_t = t[0];
			}

			else if  (t[1] < closest_t && t[1] > 1) {
				closest_object = i;
				closest_t = t[1];
			}
	}

	if (closest_object == -1) return colour(255, 255, 255);

	//�������� ���������� ����� �����������
	vec3 intersectPoint = ((direction * closest_t) + start);
	//������ ������� ������� � �����
	vec3 Normal = (intersectPoint - scene[closest_object]->position).normalize();

	//��������� ������������� �� ���� ���������� ����� � ������ �����
	double totalIntensity = 0;

	//vec3 reviewDirection = vec3();
	//reviewDirection = -direction;
	for (size_t i = 0; i < lightning.size(); i++) {
		totalIntensity += lightning[i]->computeLighting(intersectPoint, Normal, -direction, scene[closest_object]->specular);
	}

	return (scene[closest_object]->objColour * totalIntensity);
};

void Draw_Scene(HDC hdc) {
	
	//������� ����, ���������� �� ������ ��������� �� ��������� ������
	int imageWigth = 640,
		imageHeight = 640,
		screenDistanse = 640;

	//������ ������ ���������
	vec3 O = vec3(0, 0, 0);

	//��������� � ������������ �������
	std::vector<object*> scene;
	
	scene.push_back(&Sphere(vec3(0, imageHeight, 3 * screenDistanse), 640, 500, colour(255, 0, 0)));
	scene.push_back(&Sphere(vec3(2 * imageWigth, 0, 4 * screenDistanse), 640, 500, colour(0, 255, 0)));
	scene.push_back(&Sphere(vec3(- 2 * imageWigth, 0, 4 * screenDistanse), 640, 10, colour(0, 0, 255)));
	scene.push_back(&Sphere(vec3(0, 5001 * imageHeight, 0), 5000 * imageHeight, 1000, colour(255, 255, 0)));

	//��������� � ������������ ��������� �����
	std::vector<light*> lighting;

	lighting.push_back(&ambientLight(0.2));
	lighting.push_back(&pointLight(0.6, vec3(2 * imageWigth,  - imageHeight, 0)));
	lighting.push_back(&directionalLight(0.2, vec3(imageWigth, - 4 * imageHeight, 4 * screenDistanse)));

	for (int i = 0; i < imageWigth; ++i)
	{
		for (int j = 0; j < imageHeight; ++j)
		{
			//������� �� �� ������ � ������������ ������������
			double x = i - imageWigth / 2; 
			double y = j - imageHeight / 2;
			//vec3 D = vec3(x, y, screenDistanse).normalize(); //��� �� ����� ���������� � �������
			vec3 D = vec3(x, y, screenDistanse); //��� �� ����� ���������� � �������

			colour tempColour = TraceRay(O, D, scene, lighting);
			SetPixel(hdc, i, j, RGB(tempColour.R, tempColour.G, tempColour.B));
		}
	}
return;
};
