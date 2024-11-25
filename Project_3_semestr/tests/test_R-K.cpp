#include "gtest/gtest.h"
#include <fstream>
#include "RK4.h"


TEST(MOVEMENT, CREATE_MOVEMENT) {
    const double A = 1;
    const double C = 1;
    Eigen::Matrix3d J;
    J << A, 0, 0,
            0, A, 0,
            0, 0, C;
    const Eigen::Vector3d M(0, 0, 0);
    const RotationRHS rhs{J, M};

    const RotationRHS::State state{{1, 0, 0, 0, 0, 0, 1 / 1.41}, 0};
    const auto solution = RK4(rhs, state, 10, 0.1);

    std::ofstream f("output.txt", std::ios::app);
    for (const auto &i: solution) {
        f << i.x(0) << " " << i.x(1) << " " << i.x(2)
                << " " << i.x(3) << " " << i.x(4) << " " << i.x(5)
                << " " << i.x(6) << '\n';
    }
}
