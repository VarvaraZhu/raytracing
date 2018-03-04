#pragma once
#include "texture.h"
#include "vec3.h"
#include "lights.h"

class Object {
public:
	Colour object_colour; //Цвет объекта
	int specular = -1;
	Vec3 position; //Центр объекта
	
				   //Определяет, пересекается ли данный объект с текущим лучем 
	virtual bool intersect(Vec3 const &start, Vec3 const &direction, double &t0, double &t1) const { return false; };
	virtual Vec3 buildNormal(Vec3 const& point) const { return Vec3(0, 0, 0); }
	Colour reflectedColour(Vec3 const &direction, Vec3 const &point, Light const *light) const;
	//double reflectedColour(Vec3 const &direction, Vec3 const &point, Light const *light);

};


class Sphere : public Object {

private:
	double radius, radius2;

public:

	Sphere(const Vec3 &centre, const double radius, const int specular, const Colour &Colour = Colour(0, 0, 0)) :
		radius(radius), radius2(radius * radius) {
		this->object_colour = Colour;
		this->position = centre;
		this->specular = specular;
	};

	~Sphere() {};

	bool intersect(Vec3 const &start, Vec3 const &direction, double &t0, double &t1) const;
	Vec3 buildNormal(Vec3 const& point) const {
		return (point - position).normalize();
	}
};


