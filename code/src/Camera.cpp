// Created by Dinies on 19/11/2018.

#include "Camera.hpp"
namespace MultiRobot {

  Camera::Camera( Environment & t_env,
      const Eigen::Vector2d &t_p,
      const Eigen::Vector2d &t_v,
      const double t_alpha ):
    m_env( t_env),
    m_p( t_p),
    m_v( t_v),
    m_alpha( t_alpha)
  {
  }



  Eigen::Vector2d Camera::generateInput(){
    //TODO
    return Eigen::Vector2d(0.1, 0.1);
  }

  void Camera::updateState(const Eigen::Vector2d & t_deltaState ){
    m_v = m_v + t_deltaState;
  }

  void Camera::draw(){
    //TODO
  }

}



