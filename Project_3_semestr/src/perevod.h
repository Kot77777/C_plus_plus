#ifndef PEREVOD_H
#define PEREVOD_H

Eigen::Vector3d adjoint_EI(const Eigen::Vector3d &v_E, const Eigen::Quaterniond &q) {
    const Eigen::Quaterniond v_quat(0, v_E[0], v_E[1], v_E[2]);
    const Eigen::Quaterniond v_I = Eigen::Quaterniond{q * v_quat} * q.conjugate();
    return Eigen::Vector3d{v_I.x(), v_I.y(), v_I.z()};
}

Eigen::Vector3d adjoint_IE(const Eigen::Vector3d &v_I, const Eigen::Quaterniond &q) {
    const Eigen::Quaterniond v_quat(0, v_I[0], v_I[1], v_I[2]);
    const Eigen::Quaterniond v_E_1 = q.conjugate() * v_quat;
    const Eigen::Quaterniond v_E = v_E_1 * q;
    return Eigen::Vector3d{v_E.x(), v_E.y(), v_E.z()};
}

#endif //PEREVOD_H
