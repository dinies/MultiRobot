// Created by Dinies on 19/11/2018.

#include "Environment.hpp"
namespace MultiRobot {

  Environment::Environment( Drawer &t_drawer,
      const std::vector<Eigen::Vector2d> &t_eventDistribs,
      const int t_x_units, const int t_y_units):
    m_drawer( t_drawer),
    m_eventDistribs( t_eventDistribs),
    m_x_units( t_x_units),
    m_y_units( t_y_units)
  {
    m_drawing.create( 1250,1250 );
    m_drawing= cv::Vec3b(227, 246, 253);
    cv::namedWindow("Environment");
    cv::moveWindow("Environment", 40, 40);
  }

  void drawEventDistribs(){
    //TODO implement
  };
 

  void Environment::showImg(){
    cv::imshow("Environment",m_drawing);
    cv::waitKey(1);
   };

}
