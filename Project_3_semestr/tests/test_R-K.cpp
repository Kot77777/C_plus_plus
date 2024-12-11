#include "gtest/gtest.h"
#include <fstream>
#include "RK4.h"
#include <cmath>

Eigen::Vector3d Eiler_test(const RotationRHS::State &state, const Eigen::Matrix3d &J) {
    const double A = J(0, 0);
    const double B = J(1, 1);
    const double C = J(2, 2);
    const double p = state.x(4), q = state.x(5), r = state.x(6);
    const double K = sqrt(A * A * p * p + B * B * q * q + C * C * r * r);
    const double T_2 = sqrt(A * p * p + B * q * q + C * r * r);
    const double cos_theta = C * r / K;
    const double psi_dir = (T_2 - C * r * r) / (A * sqrt(1 - cos_theta * cos_theta));
    const double phi_dir = r - psi_dir * cos_theta;

    return Eigen::Vector3d{cos_theta, psi_dir, phi_dir};
}

double Lagrang_test(const RotationRHS::State &state, const Eigen::Matrix3d &J, const double F, const double l) {
    const double A = J(0, 0);
    const double C = J(2, 2);
    const Eigen::Vector3d w = state.x.segment<3>(4);
    const Eigen::Quaterniond quat(state.x(0), state.x(1), state.x(2), state.x(3));
    const Eigen::Quaterniond l_quat(0, 0, 0, l);
    const Eigen::Quaterniond l_I_quat = Eigen::Quaterniond{quat * l_quat} * quat.conjugate();
    const Eigen::Vector3d l_I{l_I_quat.x(), l_I_quat.y(), l_I_quat.z()};

    return 0.5 * w.dot(J * w) + F * l_I.dot(Eigen::Vector3d{0, 0, 1});
    //return A * sin(euler_angles(1)) * (p * sin(euler_angles(2)) + q * cos(euler_angles(2))) + C*r*cos(euler_angles(2));
    //return r;
}

TEST(MOVEMENT, CREATE_MOVEMENT) {
    const double A = 2;
    const double B = 2;
    const double C = 1;
    Eigen::Matrix3d J;
    J << A, 0, 0,
            0, B, 0,
            0, 0, C;
    //const Eigen::Vector3d M(1/1.41,0 , 0);
    const double F = 0.01;
    const double l = 1;
    const RotationRHS rhs{J, F, l};

    const RotationRHS::State state{{cos(std::numbers::pi / 8), -sin(std::numbers::pi / 8), 0, 0, 0, -1, 1}, 0};
    //const auto ang_correct = Eiler_test(state, J);
    const double Energy_correct = Lagrang_test(state, J, F, l);
    double dt = 0.1;
    /*std::ofstream f("step_dif.txt");
    std::ofstream f_out("output.txt");
    auto solution = RK4(rhs, state, 20, dt);

    for (const auto &i: solution) {
        f_out << i.x(0) << " " << i.x(1) << " " << i.x(2) << " " << i.x(3) << '\n';
    }*/
    std::ofstream f("step_dif_lagr.txt");
    for (int i = 0; i != 10; ++i) {
        double large = 0;
        auto solution = RK4(rhs, state, 20, dt);

        for (const auto &j: solution) {
            if (abs(Lagrang_test(j, J, F, l) - Energy_correct) > large)
                large = abs(Lagrang_test(j, J, F, l) - Energy_correct);
        }

        f << dt << " " << large << '\n';
        dt /= 2;
    }
}
