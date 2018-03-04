#pragma once
#include "vec3.h"
#include "texture.h"
//»сточники света
class Light {
public:
	double intensity = 0;
	Colour colour = Colour(255, 255, 255);
	//computeLighting вычисл€ет вклад данного источника 
	//в освещение рассматриваемой точки
	//(интенсивность света источника в данной точке)
	virtual double computeLighting(Vec3 const &point, Vec3 const &normal) {
		double total_intensity = 0;
		Vec3 L = -this->getDirection(point).normalize();; //Ќаправление, обратное направлению светового луча
		double cos = L * normal; // осинус угла между лучем света и нормалью к поверхности

		if (cos > 0) //≈сли угол (-pi/2, pi/2) считаем интенсивность
			total_intensity += intensity * cos;

		return total_intensity;
	}

	virtual Vec3 getDirection(Vec3 const &point) const { return Vec3(0, 0, 0); }
};

//ќкружающее освещение
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

//“очечный источник
class Point_Light : public Light {

	Vec3 position;

public:
	Point_Light(const double &intensity, const Vec3 &position) : position(position) {
		this->intensity = intensity;
	}

	//double computeLighting(Vec3 const &point, Vec3 const &normal);

	Vec3 getDirection(Vec3 const &point) const {
		return (point - position);
	}

	~Point_Light() {};
};

//Ќаправленный источник
class Directional_Light : public Light {

	Vec3 direction;

public:
	Directional_Light(const double &intensity, const Vec3 &direction) : direction(direction) {
		this->intensity = intensity;
	}

	//double computeLighting(Vec3 const &point, Vec3 const &normal);

	Vec3 getDirection(Vec3 const &point) const {
		return direction;
	}

	~Directional_Light() {};
};
