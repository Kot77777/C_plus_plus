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

	ScopedPointer p{new S(4)};
	//std::cout << p->x << std::endl;


	int b = 5, c = 0;
	int &a = b;
	int *d = &b;

	int *&g = d;


	int *f = &a;

	std::cout << &a << " " << &b <<  " " << &d << " " <<  &g << " " << f << std::endl;

	int x[5];
	//&x == x;
	int (*z)[5] = &x;
	std::cout << *x << " " << x << " " << &(x[5]) << std::endl;
	std::cout << z << " " << **z ;

	int l = 1;
	int &k = l;



	/*std::array<std::array<double, 3>, 1> matrix1 = {{{1, 2, 3}}};
	//Matrix<1, 3> matrix_1{matrix1};
	Vector<3> vec{matrix1};
	std::cout << vec.x() << std::endl;*/
	
	std::array<std::array<double, 3>, 3> matrix2 = {{{3, 2, 5}, {7, 8, 6}, {11, 3, 6}}};
	Matrix<3, 3> matrix_2{matrix2};

	std::cout << matrix_2 << std::endl;

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
