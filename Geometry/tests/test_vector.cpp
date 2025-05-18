#include "gtest/gtest.h"
#include "geometry/primitives/Matrix.h"
#include "geometry/intersections/Point_in_simplex.h"

class S {
	int x;
public:

	S(const int x_) : x(x_){}
	//int& operator*() {return x;}

	int& operator->() {return x;}
	const int operator->() const {return x;}
};
class ScopedPointer {
	S *ptr_;
public:
	ScopedPointer(S *ptr = nullptr) : ptr_(ptr){}
	~ScopedPointer(){delete ptr_;}

	//S& operator*() {return *ptr_;}
	//const S& operator*() const {return *ptr_;}

	S* operator->() {return ptr_;}
	const S* operator->() const {return  ptr_;}
};


TEST(VECTOR, CREATE_VECTOR)
{

	std::array<std::array<double, 3>, 3> matrix2 = {{{3, 2, 5}, {7, 8, 6}, {11, 3, 6}}};
	Matrix<3, 3> matrix_2{matrix2};

	std::array<std::array<double, 3>, 1> point1 = {{{2, 2, 6}}};
	Point<3> point1_{point1};

	std::array<std::array<double, 3>, 1> pointA = {{{0, 0, 0}}};
	Point<3> pointA_{pointA};

	//std::array<std::array<double, 3>, 1> pointB = ;
	Point<3> pointB_{{{{0, 5, 0}}}};

	std::array<std::array<double, 3>, 1> pointC = {{{5, 0, 0}}};
	Point<3> pointC_{pointC};

	std::array<std::array<double, 3>, 1> pointD = {{{0, 0, 5}}};
	Point<3> pointD_{pointD};

	Simplex<3> ploskost{{pointA_, pointB_, pointC_, pointD_}};

	ASSERT_EQ(determinant<3>(matrix_2), -197);
	ASSERT_EQ(point_in_simplex(point1_, ploskost), 0);
}
