#include "RK4_relate.h"
#include "gtest/gtest.h"
#include "perevod.h"
#include "Monte-Carlo.h"
#include <fstream>

TEST(RK, RK) {
    const double mu = 3.986e14;
    const double rho = 7e6;
    const double N = 6;
    const double velocity = std::sqrt(mu / rho);
    const double w = std::sqrt(mu / rho / rho / rho);
    const double sigma_delta_R = 50;

    const random_init_cond c{sigma_delta_R, 500};
    auto condition = c.Get_init_cond();

    // const Eigen::Vector3d r_otn_0{1, 1, 1};
    // const Eigen::Vector3d v_otn_0{0, 0, 0};
    //
    // const Eigen::Vector3d r1_0{rho, 0, 0};
    // const Eigen::Vector3d v1_0{0, velocity, 0};
    //
    // const Eigen::Vector3d r2_0{r1_0(0) + r_otn_0(0), r1_0(1) + r_otn_0(1), r1_0(2) + r_otn_0(2)};
    // const Eigen::Vector3d v2_0{v1_0(0) - w * r_otn_0(1), v1_0(1) + w * r_otn_0(0), v1_0(2)};

    const double dt = 1;

    const RotationRHS_1 rhs_1{w};
    const RotationRHS_2 rhs_2{mu};
    const RotationRHS_2 rhs_3{mu};

    std::vector<double> norma_eps{};

    for (auto &cond: condition) {
        RotationRHS_1::State state_1{
            {
                cond.delta_r[0], cond.delta_r[1], cond.delta_r[2], cond.delta_v[0], cond.delta_v[1], cond.delta_v[2]
            },
            0
        };

        RotationRHS_2::State state_2{
            {
                cond.R1_[0], cond.R1_[1], cond.R1_[2], cond.V1_[0], cond.V1_[1], cond.V1_[2]
            },
            0
        };

        RotationRHS_2::State state_3{
            {
                cond.R2_[0], cond.R2_[1], cond.R2_[2], cond.V2_[0], cond.V2_[1], cond.V2_[2]
            },
            0
        };

        std::vector<Eigen::Vector3d> solution_ISO_in_e{};

        auto solution_NISO = RK4_NISO(rhs_1, state_1, 3600 * N, dt);
        auto solution_ISO = RK4_ISO(rhs_2, rhs_3, state_2, state_3, 3600 * N, dt);

        for (int i = 0; i < solution_ISO[0].size(); ++i) {
            Eigen::Vector3d r1 = solution_ISO[0][i].x.segment<3>(0);
            Eigen::Vector3d v1 = solution_ISO[0][i].x.segment<3>(3);
            Eigen::Vector3d r2 = solution_ISO[1][i].x.segment<3>(0);

            Eigen::Vector3d r_otn = r2 - r1;
            const Eigen::Vector3d e1{r1 / r1.norm()};
            const Eigen::Vector3d e3{r1.cross(v1) / r1.cross(v1).norm()};
            const Eigen::Vector3d e2{e3.cross(e1)};
            Eigen::Matrix3d A_mat;
            A_mat << e1, e2, e3;

            Eigen::Vector3d r_otn_e = A_mat.transpose() * r_otn;
            solution_ISO_in_e.push_back(r_otn_e);
        }

        Eigen::Vector3d eps = Eigen::Vector3d{
            solution_ISO_in_e.back().x() - solution_NISO.back().x.x(),
            solution_ISO_in_e.back().y() - solution_NISO.back().x.y(),
            solution_ISO_in_e.back().z() - solution_NISO.back().x.z()
        };
        norma_eps.push_back(eps.norm());
    }

    // std::ofstream data_NISO("data_NISO.txt");
    // std::ofstream data_ISO("data_ISO.txt");
    //
    //
    // for (int i = 0; i < solution_ISO[0].size(); ++i) {
    //     data_ISO << solution_ISO_in_e[i](0) << " " << solution_ISO_in_e[i](1) << " " << solution_ISO_in_e[i](2) << '\n';
    //     data_NISO << solution_NISO[i].x(0) << " " << solution_NISO[i].x(1) << " " << solution_NISO[i].x(2) << '\n';
    // }

    std::ofstream data("data.txt");

    for (int i = 0; i < norma_eps.size(); ++i) {
        data << condition[i].delta_r_norm << " " << norma_eps[i] << '\n';
    }
}
