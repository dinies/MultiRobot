// Created by Dinies on 19/11/2018.

#include "Environment.hpp"
namespace MultiRobot {

  Environment::Environment( Drawer &t_drawer,
      const std::vector<Gaussian> &t_eventDistribs,
      const int t_x_units, const int t_y_units,
      const double t_precDiscret):
    m_drawer( t_drawer),
    m_eventDistribs( t_eventDistribs),
    m_x_units( t_x_units),
    m_y_units( t_y_units),
    m_precisionDiscretization( t_precDiscret)
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

    m_eventValues = computeEventValues();    
 
  }

  std::vector< std::vector< double>> Environment::computeEventValues(){
    std::vector< std::vector< double>> values;    
    const int numOfColumns = m_x_units*m_precisionDiscretization;
    values.reserve( numOfColumns);
    const double xIncrement = m_x_units/ m_precisionDiscretization;
    double currX = 0;
    for (int i = 0; i < numOfColumns ; ++i){
      values.push_back( computeEventColumn(currX ));
      currX += xIncrement;
    }
 
  };


  std::vector< double> Environment::computeEventColumn( const double t_xValue){
    std::vector< double> values;    
    const int numOfRows = m_y_units*m_precisionDiscretization;
    values.reserve( numOfRows);
    const double yIncrement = m_y_units/ m_precisionDiscretization;
    double currY = 0;
    for (int i = 0; i < numOfRows; ++i){
      Eigen::Vector2d currPoint( t_xValue, currY);
      double currValue = 0;
      for ( int j = 0; j < m_eventDistribs.size(); ++J){
        currValue += m_eventDistribs.at(j).;
      }

      double eventValue
      values.push_back( computeEventColumn(eventValue));
      currY += yIncrement;
    }


  }

  void Environment::drawEventDistribs(){
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
