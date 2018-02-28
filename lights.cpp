#include "stdafx.h"
#include "lights.h"

double Point_Light::computeLighting(Vec3 const &point, Vec3 const &normal) {

	double total_intensity = 0;

	Vec3 L = (position - point).normalize(); //Ќаправление, обратное направлению светового луча
	double cos = L * normal; // осинус угла между лучем света и нормалью к поверхности

	if (cos > 0) //≈сли угол (-pi/2, pi/2) считаем интенсивность
		total_intensity += intensity * cos;

	return total_intensity;
}

double Directional_Light::computeLighting(Vec3 const &point, Vec3 const &normal) {
	// Ќормаль - внешн€€, поэтому cos должен быть отрицательный
	double total_intensity = 0;
	double cos = -(direction * normal) / direction.len();

	if (cos > 0)
		total_intensity += intensity * cos;

	return total_intensity;
}
