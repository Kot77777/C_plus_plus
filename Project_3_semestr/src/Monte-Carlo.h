#pragma once

#include <random>
#include <vector>
#include "Type.h"


struct cond
{
  std::vector<double> R1;
  std::vector<double> R2;
  std::vector<double> V;

  cond() : R1(3), R2(3), V(3) {}
};

// we need sigma for R1, delta_R and V, not for R1, R2 and V
struct random_init_cond
{
public:
  random_init_cond(const double sigma_R1,
                   const double sigma_delta_R,
                   const double sigma_V,
                   const size_t init_condition_arr_size)
      : sigma_R1_(sigma_R1), sigma_delta_R_(sigma_delta_R),
        sigma_V_(sigma_V), init_condition_arr_size_(init_condition_arr_size) {}
    
  std::vector<cond> Get_init_cond() const
  {
    std::vector<cond> init_cond(init_condition_arr_size_);

    for (size_t i = 0; i < init_condition_arr_size_; ++i)
    {
      cond c;
      c.R1 = generate_normal_randoms(sigma_R1_);

      c.R2 = generate_normal_randoms(sigma_delta_R_);
      for (size_t j = 0; j < 3; ++j) { c.R2[j] += c.R1[j]; }

      c.V = generate_normal_randoms(sigma_V_);

      init_cond[i] = c;
    }

    return init_cond;
  }


private:
  double sigma_R1_;
  double sigma_delta_R_;
  double sigma_V_;
  size_t init_condition_arr_size_;

  std::vector<double> generate_normal_randoms(const double sigma) const
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0.0, std::sqrt(sigma));

    std::vector<double> random_numbers;

  for (size_t i = 0; i < 3; ++i) { random_numbers.push_back(d(gen)); }

  return random_numbers;
  }
};
