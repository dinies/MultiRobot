// Created by Dinies on 23/11/2018.

#pragma once
#include <unistd.h>
#include <Eigen/Core>

namespace MultiRobot {


  class Gaussian{
    private:

    double m_expFactor;
    Eigen::Vector2d m_center;

    public:
    Gaussian( const double t_expFactor, const Eigen::Vector2d &t_center );

    double eval( const double t_x, const double t_y);

    double computeDistrib( const double t_x, const double t_center);
  };
}

      


