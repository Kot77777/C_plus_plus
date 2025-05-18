#include "RK4_relate.h"
#include "gtest/gtest.h"
#include "perevod.h"
#include <fstream>

TEST(RK, RK) {
    const double mu = 3.986e14;
    const double rho = 7e6;
    const double velocity = std::sqrt(mu / rho);
    const double w = std::sqrt(mu / rho / rho / rho);

    const Eigen::Vector3d r_otn_0{10, 10, 10};
    const Eigen::Vector3d v_otn_0{0.1, 0.1, 0.1};

    const Eigen::Vector3d r1_0{rho, 0, 0};
    const Eigen::Vector3d v1_0{0, velocity, 0};

    const Eigen::Vector3d r2_0{r1_0(0) + r_otn_0(0), r1_0(1) + r_otn_0(1), r1_0(2) + r_otn_0(2)};
    const Eigen::Vector3d v2_0{v1_0(0) + v_otn_0(0), v1_0(1) + v_otn_0(1), v1_0(2) + v_otn_0(2)};

    const RotationRHS_1 rhs_1{w};

    const RotationRHS_1::State state_1{
        {
            r_otn_0(0), r_otn_0(1), r_otn_0(2), v_otn_0(0), v_otn_0(1), v_otn_0(2)
        },
        0
    };

    const RotationRHS_2 rhs_2{mu};

    const RotationRHS_2::State state_2{
            {
                r1_0(0), r1_0(1), r1_0(2), v1_0(0), v1_0(1), v1_0(2)
            },
            0
        };

    const RotationRHS_2 rhs_3{mu};

    const RotationRHS_2::State state_3{
                {
                    r2_0(0), r2_0(1), r2_0(2), v2_0(0), v2_0(1), v2_0(2)
                },
                0
            };

    const double dt = 1;

    std::ofstream data_NISO("data_NISO.txt");
    std::ofstream data_ISO("data_ISO.txt");
    auto solution_NISO = RK4_NISO(rhs_1, state_1, 3600 * 24, dt);
    auto solution_ISO = RK4_ISO(rhs_2, rhs_3, state_2, state_3, 3600 * 24, dt);

    std::vector<Eigen::Vector3d> solution_ISO_in_e{};

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

    for (int i = 0; i < solution_ISO[0].size(); ++i) {
        data_ISO <<  solution_ISO_in_e[i](0) << " " << solution_ISO_in_e[i](1) << " " << solution_ISO_in_e[i](2) << '\n';
        data_NISO <<  solution_NISO[i].x(0) << " " << solution_NISO[i].x(1) << " " << solution_NISO[i].x(2) << '\n';
    }
}
