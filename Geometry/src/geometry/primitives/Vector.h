#ifndef GEOMETRY_VECTOR_H
#define GEOMETRY_VECTOR_H
#include <iostream>
#include <array>

template<std::size_t n>
class Vector
{
	std::array<double, n> data_;
public:

	Vector() = default;
	Vector(const std::array<double, n>& data) : data_{data} {};

	double operator[](const std::size_t index) const {return data_[index];}
	double& operator[](const std::size_t index) {return data_[index];}
	
	const std::array<double, n>& data() const {return data_;}

	const double x() const
	{
		static_assert(n > 0);
		return data_[0];
	}
	
	double& x()
	{
		static_assert(n > 0);
		return data_[0];
	}
	
	const double y() const
	{
		static_assert(n > 1);
		return data_[1];
	}
	
	double& y()
	{
		static_assert(n > 1);
		return data_[1];
	}
	
	const double z() const
	{
		static_assert(n > 2);
        	return data_[2];
	}
	
	double& z()
	{
		static_assert(n > 2);
        	return data_[2];
	}
};

template<std::size_t d>
double dot(const Vector<d>& v1, const Vector<d>& v2)
{
	double dot = 0;
	for (std::size_t i = 0; i < d; ++i)
	{
		dot += v1[i] * v2[i];
	}
	return dot;
}

template<std::size_t d>
Vector<d> operator+(const Vector<d>& v1, const Vector<d>& v2) 
{
	Vector<d> result;
	for (std::size_t i = 0; i < d; ++i)
	{
		result[i] = v1[i] + v2[i];
	}
	return result;
}

template<std::size_t d>
Vector<d> operator-(const Vector<d>& v1, const Vector<d>& v2)
{
	Vector<d> result;
        for (std::size_t i = 0; i < d; ++i)
        {
                result[i] = v1[i] - v2[i];
        }
        return result;
}

template<std::size_t d>
Vector<d> operator-(const Vector<d>& v1)
{
	Vector<d> result;
        for (std::size_t i = 0; i < d; ++i)
        {
                result[i] = -v1[i];
        }
        return result;
}

template<std::size_t d>
Vector<d> operator*(const Vector<d>& v1, const double c)
{
	Vector<d> result;
        for (std::size_t i = 0; i < d; ++i)
        {
                result[i] = v1[i] * c;
        }
        return result;
}

template<std::size_t d>
Vector<d> operator*(const double c, const Vector<d>& v1)
{
	return v1 * c;
}

template<std::size_t n>
void swap(std::array<Vector<n>, n>& matrix, const std::size_t i, const std::size_t j)
{
        Vector<n> a = matrix[i];
        matrix[i] = matrix[j];
        matrix[j] = a;
}


template<std::size_t d>
double determinant(std::array<Vector<d>, d>& matrix)
{
        double det_ = 1;
        for (std::size_t i = 0; i < d; ++i)
        {
                bool A = false;
                for (std::size_t j = i; j < d; ++j)
                {
                        if (matrix[j][i] != 0)
                        {
                                A = true;
                                if (i != j) {swap(matrix, i, j);}
                                if ((i + j) % 2 != 0) {det_ *= -1;} 

                                det_ *= matrix[i][i];
                                matrix[i] = matrix[i] * (1 / matrix[i][i]);
                                
                                for (std::size_t k = i; k < d; ++k)
                                {
                                        if (k == i)
                                        {
                                                continue;
                                        }
                                        matrix[k] = matrix[k] - matrix[i]*matrix[k][i];
                                }

                                break;
                        }

                }

        if (!A) {return 0;}
        }

        return det_;
}

#endif
