#ifndef R_K_METHOD_H
#define R_K_METHOD_H

#include "Type.h"

class RotationRHS {
    Eigen::Matrix3d J_;
    Eigen::Matrix3d JInv_;
    double F_;
    double l_;

public:
    RotationRHS(const Eigen::Matrix3d &J, const double F, const double l) : J_(J), JInv_(J.inverse()), F_(F), l_(l) {
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

        const Eigen::Vector3d l_I = adjoint_EI(Eigen::Vector3d{0, 0, l_}, q);
        const Eigen::Vector3d mg_I{0, 0, -F_};
        const Eigen::Vector3d M_I = l_I.cross(mg_I);
        const Eigen::Vector3d M = adjoint_IE(M_I, q);

        const Eigen::Quaterniond q_deriv = q * w_quat;
        const Eigen::Vector3d param = M - Vec.segment<3>(4).cross((J_ * Vec.segment<3>(4)));
        const Eigen::Vector3d w_deriv = JInv_ * param;

        return VecType{
            0.5 * q_deriv.w(), 0.5 * q_deriv.x(), 0.5 * q_deriv.y(), 0.5 * q_deriv.z(),
            w_deriv(0), w_deriv(1), w_deriv(2)
        };
    }

    static Eigen::Vector3d adjoint_EI(const Eigen::Vector3d& v_E, const Eigen::Quaterniond& q) {
        const Eigen::Quaterniond v_quat(0, v_E[0], v_E[1], v_E[2]);
        const Eigen::Quaterniond v_I =  Eigen::Quaterniond{q * v_quat} * q.conjugate();
        return Eigen::Vector3d{v_I.x(), v_I.y(), v_I.z()};
    }

    static Eigen::Vector3d adjoint_IE(const Eigen::Vector3d& v_I, const Eigen::Quaterniond& q) {
        const Eigen::Quaterniond v_quat(0, v_I[0], v_I[1], v_I[2]);
        const Eigen::Quaterniond v_E =  Eigen::Quaterniond{q.conjugate() * v_quat} * q;
        return Eigen::Vector3d{v_E.x(), v_E.y(), v_E.z()};
    }

    static void normalize(VecType &v){
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
