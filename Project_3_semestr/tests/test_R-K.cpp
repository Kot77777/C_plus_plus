#include "gtest/gtest.h"
#include <fstream>
#include "R-K_method.h"


TEST(MOVEMENT, CREATE_MOVEMENT)
{
    const double A = 1;
    const double C = 1;
    Eigen::Matrix3d J;
    J << A, 0, 0,
         0, A, 0,
         0, 0, C;
    const Eigen::Vector3d M(0, 0, 0);

    const State_R_K y_0{{0.7, 0.7, 0, 0, 0, 0, 1/1.41}, 0};
    const State_full_R_K solution = solut_R_K(10, 0.1, y_0, J, M);

    std::ofstream f("output.txt", std::ios::app);
    for (const auto & i : solution.solution) {
        std::cout << i.cond(0) << " " << i.cond(1) << " " << i.cond(2)
                  << " " << i.cond(3) << " " << i.cond(4) << " " << i.cond(5)
                  << " " << i.cond(6) << '\n';
    }
    f.close();
}
