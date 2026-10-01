#pragma once
#include <cmath>
#include <string>
#include "raylib.h"

class function
{
protected:
	float _a = 0.0f;
	float _b = 0.0f;
	float _c = 0.0f;
	Color _color = VIOLET;
public:
	virtual float create(float x, float y) const = 0;
	virtual string formula() const = 0;

	float getA() const {
		return _a;
	}
	float getB() const {
		return _b;
	}
	float getC() const {
		return _c;
	}
	Color getColor() const {
		return _color;
	}

	void setA(float a) {
		_a = a;
	}
	void setB(float b) {
		_b = b;
	}
	void setC(float c) {
		_c = c;
	}
	void setColor(Color color) {
		_color = color;
	}


	virtual ~function() = default;
};

class LinearFunction : public function {
public:
	LinearFunction(float a = 1.0f, float b = 1.0f, float c = 0.0f) {
		_a = a;
		_b = b;
		_c = c;
	}
	float create(float x, float y) const{
		return _a * x + _b * y + _c; // - y
	}
	string formula() const {
		return "z = a*x + b*y + c";
	}

};

class EllipticParaboloid : public function {
public:
	EllipticParaboloid(float a = 1.0f, float b = 1.0f, float c = 0.0f) {
		_a = a;
		_b = b;
		_c = c;
	}
	float create(float x, float y) const{
		return _a * (x * x) + _b * (y * y) + _c; // - y
	}
	string formula() const {
		return "z = a*x² + b*y² + c";
	}
};

class Saddle : public function {
public:
	Saddle(float a = 1.0f, float b = 1.0f, float c = 1.0f) {
		_a = a;
		_b = b;
		_c = c;
	}
	float create(float x, float y) const{
		return _c * ((x * x) / (_a * _a) - (y * y) / (_b * _b)); // - y
	}
	string formula() const {
		return "z = c*(x²/a² - y²/b²)";
	}
};

class Conus : public function {
public:
	Conus(float a = 1.0f, float b = 1.0f, float c = 1.0f) {
		_a = a;
		_b = b;
		_c = c;
	}
	float create(float x, float y) const{
		return _c * sqrt(abs(_a) * (x * x) + abs(_b) * (y * y)); // - y
	}
	string formula() const {
		return "z = c*sqrt(a*x² + b*y²)";
	}

};

class GaussBell : public function {
public:
	GaussBell(float a = 1.0f, float b = 1.0f, float c = 1.0f) {
		_a = a;
		_b = b;
		_c = c;
	}
	float create(float x, float y) const{
		return _c * std::exp(-(_a * (x * x) + _b * (y * y))); // - y
	}
	string formula() const {
		return "z = c*(e^-(a*x² + b*y²))";
	}
};

class LinearWave : public function {
public:
	LinearWave(float a = 1.0f, float b = 1.0f, float c = 0.0f) {
		_a = a;
		_b = b;
		_c = c;
	}
	float create(float x, float y) const {
		return sin(_a * x + _b * y) + _c; // - y
	}
	string formula() const {
		return "z = sin(a*x + b*y) + c";
	}
};

class RadialWaves : public function {
public:
	RadialWaves(float a = 1.0f, float b = 1.0f, float c = 0.0f) {
		_a = a;
		_b = b;
		_c = c;
	}
	float create(float x, float y) const {
		return cos(_a * _b * sqrt(x * x + y * y)) + _c; // - y
	}
	string formula() const {
		return "z = cos(a*b*sqrt(x² + y²)) + c";
	}
};
