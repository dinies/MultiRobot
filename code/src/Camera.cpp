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
    m_radius = 3;
  }



  Eigen::Vector2d Camera::generateInput(){
    //TODO
    return Eigen::Vector2d(0.00, 0.08);
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


    cv::Point2d pointCamCenter( m_p(0), m_p(1));
    const double angleLeftViewCone = theta + m_alpha;
    const double offMapRange = 150;

    Eigen::Vector2d leftOffRangePoint(offMapRange, 0.0);
    MyMath::rotate2D( leftOffRangePoint, angleLeftViewCone);
    cv::Point2d pLeftOff(m_p(0)+leftOffRangePoint(0),
        m_p(1)+leftOffRangePoint(1));
    pointVec.push_back(pLeftOff); 
    
    pointVec.push_back(pointCamCenter);

    Eigen::Vector2d leftNearPoint(m_radius, 0.0);
    MyMath::rotate2D( leftNearPoint, angleLeftViewCone);
    cv::Point2d pLeftNear(m_p(0)+leftNearPoint(0),
        m_p(1)+leftNearPoint(1));
    pointVec.push_back(pLeftNear);

    double curr_angle(theta + M_PI/2);
    double angle_offset( M_PI/3);
    for (int i = 0; i < 4; ++i) {
      Eigen::Vector2d currPoint(m_radius, 0.0);
      MyMath::rotate2D( currPoint, curr_angle );
      cv::Point2d p(m_p(0)+currPoint(0), m_p(1)+currPoint(1));
      pointVec.push_back(p);
      curr_angle += angle_offset;
    }

    const double angleRightViewCone = theta - m_alpha;
    Eigen::Vector2d rightNearPoint(m_radius, 0.0);
    MyMath::rotate2D( rightNearPoint, angleRightViewCone);
    cv::Point2d pRightNear(m_p(0)+rightNearPoint(0),
        m_p(1)+rightNearPoint(1));
    pointVec.push_back(pRightNear);

    pointVec.push_back(pointCamCenter);

    Eigen::Vector2d rightOffRangePoint(offMapRange, 0.0);
    MyMath::rotate2D( rightOffRangePoint, angleRightViewCone);
    cv::Point2d pRightOff(m_p(0)+rightOffRangePoint(0),
        m_p(1)+rightOffRangePoint(1));
    pointVec.push_back(pRightOff);  

    return pointVec;
  };


  void Camera::draw(){
    if ( m_drawingPoints.size() > 0){
    m_env.drawCam( m_drawingPoints, m_p, true);
    }
    m_drawingPoints = computePointsCameraDrawing();
    m_env.drawCam( m_drawingPoints, m_p,false);
  }

}



