#pragma once
class texture
{
public:
	texture() {};
	~texture() {};
};

struct Colour{

	 int R;
	 int G;
	 int B;

	 Colour(const int R = 0,  const int G = 0, const int B = 0) :
		 R(R), G(G), B(B) {};

	 ~Colour() {};

	 Colour &operator +=(Colour const &other);
	 Colour &operator *=(double const k);
	 Colour operator *(double k);
};
