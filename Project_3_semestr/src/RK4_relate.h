#ifndef RK4_RELATE_H
#define RK4_RELATE_H

#include "Type.h"

class RotationRHS_1 {
    double w_;

public:
    RotationRHS_1(const double w) : w_(w) {
    }

    using ArgType = double;
    using VecType = Eigen::Vector<double, 6>;

    struct State {
        VecType x;
        ArgType t;
    };

    VecType operator()(const ArgType &/*t*/, const VecType &Vec) const {
        const Eigen::Vector3d r = Vec.segment<3>(0);
        const Eigen::Vector3d v = Vec.segment<3>(3);

        const double accel_x = 2 * w_ * v(1) + 3 * w_ * w_ * r(0);
        const double accel_y = -2 * w_ * v(0);
        const double accel_z = -w_ * w_ * r(2);

        return VecType{v(0), v(1), v(2), accel_x, accel_y, accel_z};
    }
};

class RotationRHS_2 {
    double mu_;

public:
    RotationRHS_2(const double mu) : mu_(mu) {
    }

    using ArgType = double;
    using VecType = Eigen::Vector<double, 6>;

    struct State {
        VecType x;
        ArgType t;
    };

    VecType operator()(const ArgType &/*t*/, const VecType &Vec) const {
        const Eigen::Vector3d r = Vec.segment<3>(0);
        const Eigen::Vector3d v = Vec.segment<3>(3);

        const Eigen::Vector3d accel = -mu_ * r / (r.norm() * r.norm() * r.norm());

        return VecType{v(0), v(1), v(2), accel(0), accel(1), accel(2)};
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

    return r;
}

template<typename Callable>
std::vector<typename Callable::State> RK4_NISO(
    const Callable &f, const typename Callable::State &state,
    const typename Callable::ArgType &tEnd,
    const double step) {
    std::vector<typename Callable::State> solution{state};
    while (solution.back().t <= tEnd) {
        solution.push_back({RK4Step(f, solution.back(), step), solution.back().t + step});
    }
    return solution;
}

template<typename Callable>
std::array<std::vector<typename Callable::State>, 2> RK4_ISO(
    const Callable &f1, const Callable &f2, const typename Callable::State &state1, const typename Callable::State &state2,
    const typename Callable::ArgType &tEnd,
    const double step) {
    std::vector<typename Callable::State> solution1{state1};
    std::vector<typename Callable::State> solution2{state2};
    while (solution1.back().t <= tEnd) {
        solution1.push_back({RK4Step(f1, solution1.back(), step), solution1.back().t + step});
        solution2.push_back({RK4Step(f2, solution2.back(), step), solution2.back().t + step});
    }
    return {solution1, solution2};
}

#endif //RK4_RELATE_H
