#ifndef R_K_METHOD_H
#define R_K_METHOD_H

#include "Type.h"

class RotationRHS {
    Eigen::Matrix3d J_;
    Eigen::Vector3d M_;
    Eigen::Matrix3d JInv_;

public:
    RotationRHS(const Eigen::Matrix3d &J, const Eigen::Vector3d &M) : J_(J), M_(M), JInv_(J.inverse()) {
    }

    using ArgType = double;
    using VecType = Eigen::Vector<double, 7>;

    struct State {
        VecType x;
        ArgType t;
    };

    VecType operator()(const ArgType &/*t*/, const VecType &Vec) const {
        const Eigen::Quaterniond q(Vec[0], Vec[1], Vec[2], Vec[3]);
        const Eigen::Quaterniond w_quat(0, Vec[4], Vec[5], Vec[6]);

        const Eigen::Quaterniond q_deriv = q * w_quat;
        const Eigen::Vector3d param = M_ - Vec.segment<3>(4).cross((J_ * Vec.segment<3>(4)));
        const Eigen::Vector3d w_deriv = JInv_ * param;

        return VecType{
            0.5 * q_deriv.w(), 0.5 * q_deriv.x(), 0.5 * q_deriv.y(), 0.5 * q_deriv.z(),
            w_deriv(0), w_deriv(1), w_deriv(2)
        };
    }

    static void normalize(VecType &v) {
        const Eigen::Vector<double, 4> quat = v.segment<4>(0) / v.segment<4>(0).norm();
        v.segment<4>(0) = quat;
    }
};

template<typename Callable>
typename Callable::VecType RK4Step(const Callable &f,
                                   const typename Callable::State &state,
                                   const double step) {
    const auto k1 = f(state.t, state.x);
    const auto k2 = f(state.t + step / 2, state.x + (step / 2) * k1);
    const auto k3 = f(state.t + step / 2, state.x + (step / 2) * k2);
    const auto k4 = f(state.t + step, state.x + step * k3);
    typename Callable::VecType r{state.x + step / 6 * (k1 + 2 * (k2 + k3) + k4)};

    f.normalize(r);

    return r;
}

template<typename Callable>
std::vector<typename Callable::State> RK4(
    const Callable &f, const typename Callable::State &state,
    const typename Callable::ArgType &tEnd,
    const double step) {
    std::vector<typename Callable::State> solution{state};
    while (solution.back().t <= tEnd) {
        solution.push_back({RK4Step(f, solution.back(), step), solution.back().t + step});
    }
    return solution;
}

#endif //R_K_METHOD_H
