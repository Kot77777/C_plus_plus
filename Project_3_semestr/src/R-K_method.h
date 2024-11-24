#ifndef R_K_METHOD_H
#define R_K_METHOD_H
#include "State.h"

struct Callable {
    const Eigen::Matrix3d J;
    const Eigen::Vector3d M;
    const Eigen::Matrix3d J_inv = J.inverse();

    using ArgType = double;
    using VecType = Eigen::Vector<double, 7>;

    VecType operator()(const VecType& Vec) const {
        const Eigen::Quaterniond q(Vec[0], Vec[1], Vec[2], Vec[3]);
        const Eigen::Quaterniond q_norm = q.normalized();
        const Eigen::Quaterniond w_quat(0, Vec[4], Vec[5], Vec[6]);

        const Eigen::Quaterniond q_deriv = q_norm * w_quat;
        const Eigen::Vector3d param = M - Vec.segment<3>(4).cross((J * Vec.segment<3>(4)));
        const Eigen::Vector3d w_deriv = J_inv * param;

        VecType vec(7);
        vec << 0.5 * q_deriv.w(), 0.5 * q_deriv.x(), 0.5 * q_deriv.y(), 0.5 * q_deriv.z(),
               w_deriv[0], w_deriv[1], w_deriv[2];

        return vec;
    }
};

template<typename T>
State_R_K integrate_step(const T& f,
                         const State_R_K& y,
                         const double step)
{
    const Eigen::Vector<double, 7> k1 = f(y.cond);
    const Eigen::Vector<double, 7> k2 = f(y.cond + step * k1 / 2);
    const Eigen::Vector<double, 7> k3 = f(y.cond + step * k2 / 2);
    const Eigen::Vector<double, 7> k4 = f(y.cond + step * k3);

    const Eigen::Vector<double, 7> update_cond = y.cond + step / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
    const double updatedTime = y.time + step;

    return {update_cond, updatedTime};
}

State_full_R_K solut_R_K(const double end_time,
                         const double step,
                         const State_R_K& cond_0,
                         const Eigen::Matrix3d& J,
                         const Eigen::Vector3d& M)
{
    std::vector<State_R_K> solution;
    const Callable f{J, M};
    const State_R_K cond_i = integrate_step<Callable>(f, cond_0, step);
    solution.push_back(cond_i);
    while(solution.back().time <= end_time) {
        solution.push_back(integrate_step<Callable>(f, solution.back(), step));
    }
    return {solution};
}

#endif //R_K_METHOD_H
