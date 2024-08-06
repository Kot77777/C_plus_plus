#ifndef GEOMETRY_SIMPLEX_H
#define GEOMETRY_SIMPLEX_H
#include <array>
#include "Matrix.h"

template<std::size_t N>
struct Simplex {

    std::array<Point<N>, N + 1> data_;

};

#endif
