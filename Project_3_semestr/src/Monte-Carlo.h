#pragma once

#include <random>
#include <vector>
#include "Type.h"


struct cond
{
  std::vector<double> R1;
  std::vector<double> R2;
  std::vector<double> V;

  cond() : R1(2), R2(3), V(3) {}
};


// we need sigma for R1, delta_R and V, not for R1, R2 and V
struct random_init_cond
{
public:
  random_init_cond(const double sigma_delta_R,
                   const size_t init_condition_arr_size)
      : sigma_delta_R_(sigma_delta_R),
        init_condition_arr_size_(init_condition_arr_size) {}
    
  std::vector<cond> Get_init_cond(double R1, double omega) const
  {
    std::vector<cond> init_cond(init_condition_arr_size_);

    for (size_t i = 0; i < init_condition_arr_size_; ++i)
    {
      cond c;
      c.R1 = std::vector<double> {R1, 0, 0};

      c.R2 = generate_normal_randoms(sigma_delta_R_, 3);
      for (size_t j = 0; j < 2; ++j) { c.R2[j] += c.R1[j]; }

      double mu = 3.986e14;
      c.V = std::vector<double> {0, std::sqrt(mu / R1), 0};

      init_cond[i] = c;
    }

    return init_cond;
  }


private:
  double sigma_delta_R_;
  size_t init_condition_arr_size_;

  std::vector<double> generate_normal_randoms(const double sigma, const size_t vector_size) const
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0.0, std::sqrt(sigma));

    std::vector<double> random_numbers(vector_size);

  for (size_t i = 0; i < vector_size; ++i) { random_numbers[i] = d(gen); }

  return random_numbers;
  }
};
