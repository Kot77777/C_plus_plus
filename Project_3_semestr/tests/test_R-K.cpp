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
    const Eigen::Vector3d w = state.x.segment<3>(4);
    const Eigen::Quaterniond quat(state.x(0), state.x(1), state.x(2), state.x(3));
    const Eigen::Quaterniond l_quat(0, 0, 0, l);
    const Eigen::Quaterniond l_I_quat = Eigen::Quaterniond{quat * l_quat} * quat.conjugate();
    const Eigen::Vector3d l_I{l_I_quat.x(), l_I_quat.y(), l_I_quat.z()};

    return 0.5 * w.dot(J * w) + F * l_I.dot(Eigen::Vector3d{0, 0, 1});
}

TEST(MOVEMENT, CREATE_MOVEMENT) {
    const double A = 2;
    const double B = 3;
    const double C = 4;
    Eigen::Matrix3d J;
    J << A, 0, 0,
            0, B, 0,
            0, 0, C;
    const double F = 0.01;
    const double l = 1;
    const double mu = 3.986e14;
    const double rho = 7e6;
    const double velocity = std::sqrt(mu / rho);
    const RotationRHS rhs{J, F, l, mu};

    const Eigen::Vector3d r0{rho, 0, 0};
    const Eigen::Vector3d v0{0, velocity, 0};
    const Eigen::Vector3d e1{r0 / r0.norm()};
    const Eigen::Vector3d e3{r0.cross(v0) / r0.cross(v0).norm()};
    const Eigen::Vector3d e2{e3.cross(e1)};
    Eigen::Matrix3d A_mat;
    A_mat << e1, e2, e3;
    const Eigen::Quaterniond q0(A_mat);
    const Eigen::Vector3d w0 = A_mat.transpose() * r0.cross(v0) / (r0.norm() * r0.norm()) + Eigen::Vector3d{0.0001, 0.0001, 0.0001};

    const RotationRHS::State state{
        {
            q0.w(), q0.x(), q0.y(), q0.z(), w0(0), w0(1), w0(2), rho, 0, 0, 0, velocity, 0
        }, 0};

    double dt = 0.2;

    std::ofstream f_quat("output_quat.txt");
    auto solution = RK4(rhs, state, 7200, dt);

    for (int i = 0; i < solution.size(); i+=100) {
        f_quat << solution[i].x(0) << " " << solution[i].x(1) << " " << solution[i].x(2) << " " << solution[i].x(3) << '\n';
    }

    std::ofstream f_coord("output_coord.txt");
    for (int i = 0; i < solution.size(); i+=100) {
        f_coord << solution[i].x(7) << " " << solution[i].x(8) << " " << solution[i].x(9) << '\n';
    }

    // ТЕСТИРОВАНИЕ СЛУЧАЯ ЛАГРАНЖА И ЭЙЛЕРА

    //const auto ang_correct = Eiler_test(state, J);
    //const double Energy_correct = Lagrang_test(state, J, F, l);

    /*std::ofstream f("step_dif_lagr.txt");
    for (int i = 0; i != 10; ++i) {
        double large = 0;
        auto solution = RK4(rhs, state, 20, dt);

        for (const auto &j: solution) {
            if (abs(Lagrang_test(j, J, F, l) - Energy_correct) > large)
                large = abs(Lagrang_test(j, J, F, l) - Energy_correct);
        }

        f << dt << " " << large << '\n';
        dt /= 2;
    }*/
}
