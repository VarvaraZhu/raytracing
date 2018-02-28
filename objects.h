#pragma once
#include "texture.h"
#include "vec3.h"

class Object {
public:
	Colour objColour; //Цвет объекта
	int specular = -1;
	Vec3 position; //Центр объекта
	
				   //Определяет, пересекается ли данный объект с текущим лучем 
	virtual bool intersect(Vec3 const &start, Vec3 const &direction, double *t) { return false; };
};


class Sphere : public Object {

private:
	double radius, radius2;

public:

	Sphere(const Vec3 &centre, const double radius, const int specular, const Colour &Colour = Colour(0, 0, 0)) :
		radius(radius), radius2(radius * radius) {
		this->objColour = Colour;
		this->position = centre;
		this->specular = specular;
	};

	~Sphere() {};

public:
	bool intersect(Vec3 const &start, Vec3 const &direction, double *t);
};


