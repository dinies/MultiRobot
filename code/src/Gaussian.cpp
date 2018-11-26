// Created by Dinies on 23/11/2018.

#include "Gaussian.hpp"
namespace MultiRobot{

  Gaussian::Gaussian(
      const double t_expFactor,
      const Eigen::Vector2d &t_center ):
    m_expFactor( t_expFactor),
    m_center( t_center)
  {};

  double Gaussian::eval( const double t_x, const double t_y){
    return computeDistrib( t_x, m_center(0)) * computeDistrib( t_y, m_center(1));
  };
    
  double Gaussian::computeDistrib( const double t_x, const double t_center){
     return std::exp( - std::pow( std::abs( t_x - t_center) , 2));
  }

}
