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
    m_radius = 1;
  }



  Eigen::Vector2d Camera::generateInput(){
    //TODO
    return Eigen::Vector2d(0, -0.01);
  }

  void Camera::updateState(const Eigen::Vector2d & t_deltaState ){
    m_v = m_v + t_deltaState;
  }

  void Camera::evolve(){

    updateState( generateInput() );
    draw();
  };

  std::vector< cv::Point2d> Camera::computePointsCameraDrawing(){

    std::vector< cv::Point2d> pointVec;
    pointVec.reserve(6);
    double theta = atan2( m_v(1), m_v(0));

    double curr_angle(M_PI/6 + theta);
    double angle_offset( M_PI/3);
    for (int i = 0; i < 6; ++i) {
      Eigen::Vector2d currPoint(m_radius, 0.0);
      MyMath::rotate2D( currPoint, curr_angle );
      cv::Point2d p(m_p(0)+currPoint(0), m_p(1)+currPoint(1));
      pointVec.push_back(p);
      curr_angle += angle_offset;
    }
    return pointVec;
  };


  void Camera::draw(){
    std::vector< cv::Point2d> drawingPoints = computePointsCameraDrawing();
    m_env.drawCam( drawingPoints, m_p);
    //TODO
  }

}



