// Created by Dinies on 23/11/2018.

#include "Gaussian.hpp"
namespace MultiRobot{

  Gaussian::Gaussian(
      const double t_expFactor,
      const Eigen::Vector2d &t_center ):
    m_expFactor( t_expFactor),
    m_center( t_center)
  {};

  //TODO change the api params not a vector but two doubles and also the return will be the aggregate of the x and y values
  Eigen::Vector2d  Gaussian::eval( Eigen::Vector2d &t_point ){
    Eigen::Vector2d result(
        computeDistrib( t_point(0), m_center(0)),
        computeDistrib( t_point(1), m_center(1))
        );
    return result;
  };
    
  double Gaussian::computeDistrib( const double t_x, const double t_center){
     return std::exp( - std::pow( std::abs( t_x - t_center) , 2));
  }

}
