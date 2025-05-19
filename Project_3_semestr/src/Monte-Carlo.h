#pragma once

#include <random>
#include <vector>


constexpr double R1 = 7e6;
constexpr double mu = 3.986e14;
static const double omega = std::sqrt(mu / (R1 * R1 * R1));
static const double V1 = std::sqrt(mu / R1);


struct cond
{
  std::vector<double> R1_ = {R1, 0, 0};
  std::vector<double> R2_;
  std::vector<double> V1_ = {0, V1, 0};
  std::vector<double> V2_ = {0, V1, 0};
  std::vector<double> delta_r;
  std::vector<double> delta_v;

  cond(const std::vector<double> R2)
      : R2_(R2)
  {
    V2_[0] -= omega * (R2_[1] - R1_[1]);
    V2_[1] += omega * (R2_[0] - R1_[0]);

    delta_r = 
    {
      R2_[0] - R1_[0],
      R2_[1] - R1_[1],
      R2_[2] - R1_[2]
    };

    delta_v =
    {
      V2_[0] - V1_[0],
      V2_[1] - V1_[1],
      V2_[2] - V2_[2]
    };
  }
};


struct random_init_cond
{
public:
  random_init_cond(const double sigma_delta_R,
                   const size_t init_condition_arr_size)
      : sigma_delta_R_(sigma_delta_R),
        init_condition_arr_size_(init_condition_arr_size),
        gen_(std::random_device{}()) {}

  std::vector<cond> Get_init_cond() const
  {
    std::vector<cond> init_cond(init_condition_arr_size_);

    for (size_t i = 0; i < init_condition_arr_size_; ++i)
    {
      std::vector<double> R2 = generate_normal_randoms(sigma_delta_R_, 3);
      R2[0] += R1;

      cond c(R2);
      init_cond[i] = c;
    }

    return init_cond;
  }

private:
  double sigma_delta_R_;
  size_t init_condition_arr_size_;
  mutable std::mt19937 gen_;

  std::vector<double> generate_normal_randoms(double sigma, size_t vector_size) const
  {
    std::normal_distribution<> dist(0.0, sigma);
    std::vector<double> vec(vector_size);

    for (size_t i = 0; i < vector_size; ++i) 
    {
      vec[i] = dist(gen_);
    }

    return vec;
  }
};
