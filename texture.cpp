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

Colour Colour::operator *(double k) const {

	Colour new_colour = Colour();
	new_colour.R = (int)(R * k);
	new_colour.G = (int)(G * k);
	new_colour.B = (int)(B * k);

	new_colour.R = min(new_colour.R, 255);
	new_colour.G = min(new_colour.G, 255);
	new_colour.B = min(new_colour.B, 255);

	return new_colour;
}

Colour Colour::operator +(Colour const &other) const {

	Colour new_colour = Colour();
	new_colour.R = R + other.R;
	new_colour.G = G + other.G;
	new_colour.B = B + other.B;

	new_colour.R = min(new_colour.R, 255);
	new_colour.G = min(new_colour.G, 255);
	new_colour.B = min(new_colour.B, 255);

	return new_colour;
}

Colour Colour::operator -(Colour const &other) const {

	Colour new_colour = Colour();
	new_colour.R = R - other.R;
	new_colour.G = G - other.G;
	new_colour.B = B - other.B;

	new_colour.R = max(new_colour.R, 0);
	new_colour.G = max(new_colour.G, 0);
	new_colour.B = max(new_colour.B, 0);

	return new_colour;
}