#ifndef STATE_H
#define STATE_H
#include "/home/kostya/Repositories/RocketC-/project/eigen/Eigen/Dense"

struct State_R_K {
    Eigen::Vector<double, 7> cond;
    double time;

    State_R_K(const Eigen::Vector<double, 7>& initial_cond, double initial_time)
        : cond(initial_cond), time(initial_time) {}
};

struct State_full_R_K {
    std::vector<State_R_K> solution;
};

#endif //STATE_H
