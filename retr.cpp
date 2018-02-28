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

//�������, ������������ ���� ������� 
Colour traceRay(const Vec3 &start, Vec3 &direction, std::vector<Object*> &scene, std::vector<Light*> &lightning) {

	// ray = start + t * direction
	double *t = new double[2]; 
	// �������� t, ��������������� ������ ����������� ���� � ��������
	t[0] = inf, t[1] = inf;

	size_t closest_object = -1; // ����� ���������� �������
	double closest_t = inf;		// ������������� ��������� � ������ ����� �����������

	for (size_t i = 0; i < scene.size(); i++) {

		if (scene[i]->intersect(start, direction, t))
			if (t[0] < closest_t && t[1] > 1) {
				closest_object = i;
				closest_t = t[0];
			}

			else if  (t[1] < closest_t && t[1] > 1) {
				closest_object = i;
				closest_t = t[1];
			}
	}

	if (closest_object == -1) return Colour(255, 255, 255);

	//�������� ���������� ����� �����������
	Vec3 intersect_point = ((direction * closest_t) + start);
	//������ ������� ������� � �����
	Vec3 normal = (intersect_point - scene[closest_object]->position).normalize();

	//��������� ������������� �� ���� ���������� ����� � ������ �����
	double total_intensity = 0;

	Vec3 review_direction = Vec3();
	review_direction = -direction;
	for (size_t i = 0; i < lightning.size(); i++) {
		total_intensity += lightning[i]->computeLighting(intersect_point, normal);
	}

	return (scene[closest_object]->objColour * total_intensity);
};

void drawScene(HDC hdc) {
	
	//������� ����, ���������� �� ������ ��������� �� ��������� ������
	int image_wigth = 640,
		image_height = 640,
		screen_distanse = 640;

	//������ ������ ���������
	Vec3 O = Vec3(0, 0, 0);

	//��������� � ������������ �������
	std::vector<Object*> scene;
	
	scene.push_back(&Sphere(Vec3(0, image_height, 3 * screen_distanse), 640, 500, Colour(255, 0, 0)));
	scene.push_back(&Sphere(Vec3(2 * image_wigth, 0, 4 * screen_distanse), 640, 500, Colour(0, 255, 0)));
	scene.push_back(&Sphere(Vec3(- 2 * image_wigth, 0, 4 * screen_distanse), 640, 10, Colour(0, 0, 255)));
	scene.push_back(&Sphere(Vec3(0, 5001 * image_height, 0), 5000 * image_height, 1000, Colour(255, 255, 0)));

	//��������� � ������������ ��������� �����
	std::vector<Light*> lighting;

	lighting.push_back(&Ambient_Light(0.2));
	lighting.push_back(&Point_Light(0.6, Vec3(2 * image_wigth,  - image_height, 0)));
	lighting.push_back(&Directional_Light(0.2, Vec3(image_wigth, - 4 * image_height, 4 * screen_distanse)));

	for (int i = 0; i < image_wigth; ++i)
	{
		for (int j = 0; j < image_height; ++j)
		{
			//������� �� �� ������ � ������������ ������������
			double x = i - image_wigth / 2; 
			double y = j - image_height / 2;
			//vec3 D = vec3(x, y, screenDistanse).normalize(); //��� �� ����� ���������� � �������
			Vec3 D = Vec3(x, y, screen_distanse); //��� �� ����� ���������� � �������

			Colour temp_colour = traceRay(O, D, scene, lighting);
			SetPixel(hdc, i, j, RGB(temp_colour.R, temp_colour.G, temp_colour.B));
		}
	}
return;
};
