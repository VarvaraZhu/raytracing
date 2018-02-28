#pragma once
#include "vec3.h"
#include "texture.h"
//��������� �����
class Light {
public:
	double intensity = 0;
	//computeLighting ��������� ����� ������� ��������� 
	//� ��������� ��������������� �����
	//(������������� ����� ��������� � ������ �����)
	virtual double computeLighting(Vec3 const &point, Vec3 const &normal) { return 0; };
};

//���������� ���������
class Ambient_Light : public Light {
public:
	Ambient_Light(const double &intensity) {
		this->intensity = intensity;
	}

	double computeLighting(Vec3 const &point, Vec3 const &normal) {
		return intensity;
	};
	~Ambient_Light() {};
};

//�������� ��������
class Point_Light : public Light {

	Vec3 position;

public:
	Point_Light(const double &intensity, const Vec3 &position) : position(position) {
		this->intensity = intensity;
	}

	double computeLighting(Vec3 const &point, Vec3 const &normal);
	~Point_Light() {};
};

//������������ ��������
class Directional_Light : public Light {

	Vec3 direction;

public:
	Directional_Light(const double &intensity, const Vec3 &direction) : direction(direction) {
		this->intensity = intensity;
	}

	double computeLighting(Vec3 const &point, Vec3 const &normal);
	~Directional_Light() {};
};
