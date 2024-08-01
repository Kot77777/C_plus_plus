#ifndef GEOMETRY_MATRIX_H
#define GEOMETRY_MATRIX_H
#include <array>

template<std::size_t N, std::size_t M>
class Matrix
{
	std::array<std::array<double,  M>, N> matrix_;
public:

	Matrix() = default;
	Matrix(const std::array<std::array<double,  M>, N>& matrix) : matrix_(matrix){}

	double operator()(const std::size_t i, const std::size_t j) const {return matrix_[i][j];}
	double& operator()(const std::size_t i, const std::size_t j) {return matrix_[i][j];}
	
	const double x(const std::size_t i) const
	{
		static_assert(M > 0);
		return matrix_(i, 0);
	}

	double& x(const std::size_t i)
	{
		static_assert(M > 0);
                return matrix_(i, 0);
	}

	const double y(const std::size_t i) const
        {
                static_assert(M > 1);
                return matrix_(i, 1);
        }

        double& y(const std::size_t i)
        {
                static_assert(M > 1);
                return matrix_(i, 1);
        }

	const double z(const std::size_t i) const
        {
                static_assert(M > 2);
                return matrix_(i, 2);
        }

        double& z(const std::size_t i)
        {
                static_assert(M > 2);
                return matrix_(i, 2);
        }
};

template <std::size_t N>
using Vector = Matrix<1, N>;

template<std::size_t N, std::size_t M>
Matrix<N, M> operator+(const Matrix<N, M>& matrix_1, const Matrix<N, M>& matrix_2)
{
	Matrix<N, M> matrix;
	for (std::size_t i; i < N; ++i)
	{
		for(std::size_t j; j < M; ++j)
		{
			matrix(i, j) = matrix_1(i, j) + matrix_2(i, j);
		}
	}

	return matrix;
}

template<std::size_t N, std::size_t M>
Matrix<N, M> operator-(const Matrix<N, M>& matrix_1, const Matrix<N, M>& matrix_2)
{
        Matrix<N, M> matrix;
        for (std::size_t i; i < N; ++i)
        {
                for(std::size_t j; j < M; ++j)
                {
                        matrix(i, j) = matrix_1(i, j) - matrix_2(i, j);
                }
        }

        return matrix;
}

template<std::size_t N, std::size_t M>
Matrix<N, M> operator+(const Matrix<N, M>& matrix_)
{
        Matrix<N, M> matrix;
        for (std::size_t i; i < N; ++i)
        {
                for(std::size_t j; j < M; ++j)
                {
                        matrix(i, j) = -matrix_(i, j);
                }
        }

        return matrix;
}

template<std::size_t N, std::size_t M>
Matrix<N, M> operator*(const Matrix<N, M>& matrix_, const double c)
{
        Matrix<N, M> matrix;
        for (std::size_t i; i < N; ++i)
        {
                for(std::size_t j; j < M; ++j)
                {
                        matrix(i, j) = matrix_(i, j) * c;
                }
        }

        return matrix;
}

template<std::size_t N, std::size_t M>
Matrix<N, M> operator*(const double c, const Matrix<N, M>& matrix_)
{
        return matrix_ * c;
}

template<std::size_t N, std::size_t M, std::size_t K>
Matrix<N, M> operator*(const Matrix<N, K>& matrix_1, const Matrix<K, M>& matrix_2)
{
	Matrix<N, M> matrix;

	for(std::size_t i = 0; i < N; ++i)
	{
		for(std::size_t j = 0; j < M; ++j)
		{
			matrix(i, j) = 0;
			for(std::size_t k = 0; k < K; ++k)
			{
				matrix(i, j) += matrix_1(i, k) * matrix_2(k, j); 
			}
		}
	}

	return matrix;
}

template<std::size_t N, std::size_t M>
Matrix<M, N> transposition(const Matrix<N, M>& matrix_)
{
	Matrix<M, N> matrix;
	for(std::size_t i = 0; i < M; ++i)
	{
		for(std::size_t j = 0; j < N; ++j)
		{
			matrix[i][j] = matrix_[j][i];
		} 
	}
	
	return matrix;
}

template<std::size_t N>
Matrix<N-1, N-1> minor(const std::size_t i, const Matrix<N, N>& matrix)
{
	Matrix<N-1, N-1> minor_;
	for(std::size_t j = 0, z = 0; j < N; ++j)
	{
		for(std::size_t k = 1; k < N; ++k)
		{	
			if (j != i) {minor_(z, k - 1) = matrix(j, k);}
			else {
			z--;
			break;}	
		}
		z++;
	} 
	
	return minor_;
}

int pow_minus1(const std::size_t i)
{
    int result = 1;
    for(std::size_t j = 0; j < i; j++)
    {
        result *= -1;
    }

    return result;
}

template<std::size_t N>
double determinant(const Matrix<N, N>& matrix)
{
	
	double total = 0;
	for(std::size_t i = 0; i < N; ++i)
	{
		total += pow_minus1(i) * matrix(i, 0) * determinant(minor(i, matrix));

	}
	
	return total;
}

template<>
inline double determinant<1>(const Matrix<1, 1>& matrix)
{
	return matrix(0, 0);
}






#endif
