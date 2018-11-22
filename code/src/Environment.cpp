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


    m_colors.white = {255,255,255};
    m_colors.green = {0,255,20};
    m_colors.dark_red = {20,0,255};
    m_colors.milk= {227,246,253};
    m_colors.lightBlue= {210,139,38};
    m_colors.fadedLightBlue= {255,207,130};
    m_colors.lightOrange = {0,164,216};
    m_colors.darkBrown = {1,83,109};
 
  }

  void drawEventDistribs(){
    //TODO implement
  };

  void Environment::drawCam(
      const std::vector< cv::Point2d> &t_points,
      const Eigen::Vector2d &t_camCenter,
      const bool t_deletingFlag){

    cv::Scalar color;
    if (t_deletingFlag){
      color= m_colors.milk;
    }else{
      color= m_colors.dark_red;
    }

    m_drawer.drawSegmentSeries(m_drawing, t_points, color);
  };


  void Environment::showImg(){
    cv::imshow("Environment",m_drawing);
    cv::waitKey(50);
   };

}
