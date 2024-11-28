#include "gtest/gtest.h"
#include <fstream>
#include "RK4.h"
#include <cmath>

Eigen::Vector3d angel(const RotationRHS::State& state, const Eigen::Matrix3d& J) {
    const double A = J(0, 0);
    const double B = J(1, 1);
    const double C = J(2, 2);
    const double p = state.x(4), q = state.x(5), r = state.x(6);
    const double K = sqrt(A*A*p*p + B*B*q*q + C*C*r*r);
    const double T_2 = sqrt(A*p*p + B*q*q + C*r*r);
    const double cos_theta = C * r / K;
    const double psi_dir = (T_2 - C*r*r) / (A * sqrt(1 - cos_theta*cos_theta));
    const double phi_dir = r - psi_dir*cos_theta;
    
    return Eigen::Vector3d{cos_theta, psi_dir, phi_dir};
}

TEST(MOVEMENT, CREATE_MOVEMENT) {
    const double A = 2;
    const double B = 2;
    const double C = 1;
    Eigen::Matrix3d J;
    J << A, 0, 0,
            0, B, 0,
            0, 0, C;
    const Eigen::Vector3d M(0, 0, 0);
    const RotationRHS rhs{J, M};

    const RotationRHS::State state{{1, 0, 0, 0, 1, 0, 1}, 0};
    const auto ang_0 = angel(state, J);

    const auto solution = RK4(rhs, state, 10, 0.1);

    std::ofstream f("output.txt", std::ios::app);
    for (const auto &i: solution) {
        Eigen::Quaterniond q(i.x(0), i.x(1), i.x(2), i.x(3));

        auto ang = angel(i, J);
        EXPECT_NEAR(ang(0), ang_0(0), 0.00001);
        EXPECT_NEAR(ang(1), ang_0(1), 0.00001);
        EXPECT_NEAR(ang(2), ang_0(2), 0.00001);

        f << i.x(0) << " " << i.x(1) << " " << i.x(2)
                << " " << i.x(3) << " " << i.x(4) << " " << i.x(5)
                << " " << i.x(6) << '\n';
    }
}
