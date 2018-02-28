#include "stdafx.h"
#include "lights.h"

double Point_Light::computeLighting(Vec3 const &point, Vec3 const &normal) {

	double total_intensity = 0;

	Vec3 L = (position - point).normalize(); //�����������, �������� ����������� ��������� ����
	double cos = L * normal; //������� ���� ����� ����� ����� � �������� � �����������

	if (cos > 0) //���� ���� (-pi/2, pi/2) ������� �������������
		total_intensity += intensity * cos;

	return total_intensity;
}

double Directional_Light::computeLighting(Vec3 const &point, Vec3 const &normal) {
	// ������� - �������, ������� cos ������ ���� �������������
	double total_intensity = 0;
	double cos = -(direction * normal) / direction.len();

	if (cos > 0)
		total_intensity += intensity * cos;

	return total_intensity;
}
