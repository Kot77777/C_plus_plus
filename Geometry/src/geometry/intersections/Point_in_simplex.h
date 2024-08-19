#ifndef GEOMETRY_POINT_IN_SIMPLEX_H
#define GEOMETRY_POINT_IN_SIMPLEX_H
#include "geometry/primitives/Simplex.h"
#include "geometry/primitives/Matrix.h"

template <std::size_t N>
Matrix<N, N> swap(const Matrix<N, N>& basis, const Vector<N> r, const std::size_t i)
{
	Matrix<N, N> matrix_;
	for (std::size_t j = 0; j < N; ++j) {
		if (i != j) {matrix_[j] = basis[j];}
		else {matrix_[j] = r[0];}
	}

	return matrix_;
}

template <std::size_t N>
bool point_in_simplex(const Point<N>& point, const Simplex<N>& simplex)
{
	std::array<Vector<N>, N> basis;

	for (std::size_t i = 0; i < N; ++i)
	{
		basis[i] = simplex.data_[i+1] - simplex.data_[0];

	}

	const Matrix<N, N> basis_vector{basis};
	const Vector<N> r = point - simplex.data_[0];

	std::array<double, N> determinants;
	const double det = determinant(basis_vector);

	for (std::size_t i = 0; i < N; ++i)
	{
		determinants[i] = determinant(swap(basis_vector, r, i));
	}

	std::array<double, N> x;
	double total = 0;
	for (std::size_t i = 0; i < N; ++i)
	{
		if (determinants[i] / det < 0) {return false;}
		total += determinants[i] / det;
	}

	return total <= 1 ? true : false;
}

#endif
