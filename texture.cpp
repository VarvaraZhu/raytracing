#include "stdafx.h"
#include "texture.h"


Colour& Colour::operator+=(Colour const &other) {
	R += other.R;
	G += other.G;
	B += other.B;

	R = min(R, 255);
	G = min(G, 255);
	B = min(B, 255);

	return *this;
}

Colour& Colour::operator *=(double const k) {
	R = (int)(k * R);
	G = (int)(k * G);
	B = (int)(k * B);

	R = min(R, 255);
	G = min(G, 255);
	B = min(B, 255);

	return *this;
}

Colour Colour::operator *(double k) {

	Colour new_colour = Colour();
	new_colour.R = (int)(R * k);
	new_colour.G = (int)(G * k);
	new_colour.B = (int)(B * k);

	R = min(R, 255);
	G = min(G, 255);
	B = min(B, 255);

	return new_colour;
}