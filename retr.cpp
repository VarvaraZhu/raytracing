#pragma once
#include "stdafx.h"

#include <windows.h>
#include <math.h>
#include <vector>

#define inf 1e10

#include "vec3.h"
#include "texture.h"
#include "objects.h"
#include "lights.h"


//Функция, определяющая цвет пикселя 
Colour traceRay(const Vec3 &start, Vec3 &direction,  std::vector<Object* > &scene, std::vector<Light*> &lightning) {

	// ray = start + t * direction
	double t0 = inf, t1 = inf;
	// Значения t, соответствующие точкам пересечения луча с объектом
	

	size_t closest_object = -1; // Номер ближайшего объекта
	double closest_t = inf;		// Соответствует ближайшей к экрану точке пересечения

	for (size_t i = 0; i < scene.size(); i++) {

		if (scene[i]->intersect(start, direction, t0, t1))
			if (t0 < closest_t && t0 > 1) {
				closest_object = i;
				closest_t = t0;
			}

			else if  (t1 < closest_t && t1 > 1) {
				closest_object = i;
				closest_t = t1;
			}
	}

	if (closest_object == -1) return Colour(255, 255, 255);

	//Вычислем координаты точки пересечения
	Vec3 intersect_point = (direction * closest_t + start);
	//Строим ВНЕШНЮЮ нормаль к сфере

	Vec3 normal = scene[closest_object]->buildNormal(intersect_point);
	//Суммарная интенсивность от всех источников света в данной точке
	double total_intensity = 0;
	Colour reflected_colour = Colour(0, 0, 0); 

	for (size_t i = 0; i < lightning.size(); i++) {
		total_intensity += lightning[i]->computeLighting(intersect_point, normal);
		if (scene[closest_object]->specular != -1)
			//total_intensity += scene[closest_object]->reflectedColour(direction, intersect_point, lightning[i]);

			reflected_colour += scene[closest_object]->reflectedColour(direction, intersect_point, lightning[i]);
	}

	return (scene[closest_object]->object_colour * total_intensity +  reflected_colour);
};

void drawScene(HDC hdc) {
	
	//Размеры окна, расстояние от начала координат до плоскости экрана
	int image_wigth = 640,
		image_height = 640,
		screen_distanse = 640;

	//Задаем начало координат
	Vec3 O = Vec3(0, 0, 0);

	//Добавляем в пространство объекты
	 std::vector<Object*> scene;
	

	scene.push_back(&Sphere(Vec3(0, image_height, 3 * screen_distanse), 640, 500, Colour(255, 0, 0)));
	scene.push_back(&Sphere(Vec3(2 * image_wigth, 0, 4 * screen_distanse), 640, 500, Colour(0, 255, 0)));
	scene.push_back(&Sphere(Vec3(- 2 * image_wigth, 0, 4 * screen_distanse), 640, 10, Colour(0, 0, 255)));
	scene.push_back(&Sphere(Vec3(0, 5001 * image_height, 0), 5000 * image_height, 2000, Colour(255, 255, 0)));

	//Добавляем в пространство источники света
	std::vector<Light*> lighting;

	lighting.push_back(&Ambient_Light(0.2));
	lighting.push_back(&Point_Light(0.6, Vec3(2 * image_wigth,  - image_height, 0)));
	lighting.push_back(&Directional_Light(0.2, Vec3(image_wigth, - 4 * image_height, 4 * screen_distanse)));

	for (int i = 0; i < image_wigth; ++i)
	{
		for (int j = 0; j < image_height; ++j)
		{
			//Переход из СК экрана в координатное пространство
			double x = i - image_wigth / 2; 
			double y = j - image_height / 2;
			
			Vec3 D = Vec3(x, y, screen_distanse); //Луч из точки наблюдения в пиксель

			Colour temp_colour = traceRay(O, D, scene, lighting);
			SetPixel(hdc, i, j, RGB(temp_colour.R, temp_colour.G, temp_colour.B));
		}
	}

	return;
};
