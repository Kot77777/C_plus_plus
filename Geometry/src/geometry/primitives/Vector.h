#ifndef GEOMETRY_VECTOR_H
#define GEOMETRY_VECTOR_H
#include <iostream>
#include <array>

template<std::size_t n>
class Vector
{
	std::array<double, n> data_;
public:
	Vector(const std::array<double, n>& data) : data_{data} {};

	double operator[](const std::size_t index) const;
	
	const std::array<double, n>& data() const;

	const double x() const;
	const double y() const;
	const double z() const;
};

template<std::size_t d>
double dot(const Vector<d>& v1, const Vector<d>& v2);

template<std::size_t d>
Vector<d> operator+(const Vector<d>& v1, const Vector<d>& v2);

template<std::size_t d>
Vector<d> operator-(const Vector<d>& v1, const Vector<d>& v2);

template<std::size_t d>
Vector<d> operator-(const Vector<d>& v1);

template<std::size_t d>
Vector<d> operator*(const Vector<d>& v1, const double c);

template<std::size_t d>
Vector<d> operator*(const double c, const Vector<d>& v1);

template<std::size_t d>
double det(std::array<Vector<d>, d>& matrix);

#endif
