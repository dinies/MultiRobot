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
    m_drawing.create( 1000,1000 );
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

  std::vector< std::vector< discretePoint>> Environment::computeEventValues(){
    std::vector< std::vector< discretePoint>> values;    
    const int numOfColumns = m_x_units*m_precisionDiscretization;
    values.reserve( numOfColumns);
    const double xIncrement =  1.0/m_precisionDiscretization;
    double currX = 0.0;
    for (int i = 0; i < numOfColumns ; ++i){
      values.push_back( computeEventColumn(currX ));
      currX += xIncrement;
    }
    return values;
  };


  std::vector< discretePoint> Environment::computeEventColumn(
      const double t_xValue){
    std::vector< discretePoint> values;    
    const int numOfRows = m_y_units*m_precisionDiscretization;
    values.reserve( numOfRows);
    const double yIncrement = 1.0/m_precisionDiscretization;
    double currY = 0.0;
    for (int i = 0; i < numOfRows; ++i){

      double currValue = 0;
      for ( int j = 0; j < m_eventDistribs.size(); ++j){
        currValue += m_eventDistribs.at(j).eval( t_xValue, currY);
      }
  
      discretePoint point( t_xValue,currY,currValue/m_eventDistribs.size());
      values.push_back( point );
      currY += yIncrement;
    }
    return values;
  }

  void Environment::drawPointEventDistrib( const discretePoint &t_point){
    cv::Scalar color = getColorTemperature(
        t_point.eventProbability,
        m_colors.fadedLightBlue,
        m_colors.darkBrown);
    m_drawer.drawPatch(m_drawing, t_point.coords, color );
  }

  

  void Environment::drawColumnDistribSerial(
      const std::vector<discretePoint> &t_columnValues){

    for ( int j = 0; j < t_columnValues.size(); ++j){
        discretePoint point = t_columnValues.at(j);
        drawPointEventDistrib( point);
     }
   
  }

  // MultiThreading implementation based on lib 
  // https://github.com/deepsea-inria/pasl/tree/edu
//  void Environment::drawColumnDistribParallel_rec(
//     const std::vector<discretePoint> &t_columnValues,
//     const int lo,
//   const int hi){
//   int n = hi - lo;
//   if (n == 0) {
//   } else if ( n==1){
//     drawPointEventDistrib( t_columnValues.at(lo));
//   }else{
//     int mid = (int) floor( (lo + hi)/2);
//     fork2( [&] {
//       drawColumnDistribParallel_rec( t_columnValues, lo, mid);
//     }, [&] {
//       drawColumnDistribParallel_rec( t_columnValues, mid, hi);
//     });
//   }
// }
  
  void Environment::drawEventDistribs(){

    for (int i = 0; i < m_eventValues.size(); ++i){
      std::vector<discretePoint> columnValues= m_eventValues.at(i); 
      drawColumnDistribSerial( columnValues);
   }
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



   void Environment::drawDot(
       const cv::Point2d &t_point,
       const cv::Scalar &t_color){

     m_drawer.drawPatch(m_drawing,t_point , t_color );
   }
      

   void Environment::drawMass(
       const double t_value,
       const cv::Point2d &t_point,
       const cv::Scalar &t_minColor,
       const cv::Scalar &t_maxColor){

     cv::Scalar color = getColorTemperature(
        t_value,
        t_minColor,
        t_maxColor);

     m_drawer.drawPatch(m_drawing,t_point , color );

    }

   void Environment::drawCentroidalPerspective(
       const cv::Point2d &t_start,
       const cv::Point2d &t_end,
       const cv::Scalar &t_color){

     m_drawer.drawLine( m_drawing,t_start,t_end,t_color);

   }

 


  void Environment::showImg(){
    cv::imshow("Environment",m_drawing);
    cv::waitKey(5);
   };


  cv::Scalar Environment::getColorTemperature( 
      const double t_temp,
      const cv::Scalar &t_minColor,
      const cv::Scalar &t_maxColor){
    
    double rangeGreen = t_maxColor(0) - t_minColor(0);
    double rangeRed = t_maxColor(1) - t_minColor(1);
    double rangeBlue = t_maxColor(2) - t_minColor(2);
    cv::Scalar newColor  = {
      t_minColor(0) + (rangeGreen * t_temp),
      t_minColor(1) + (rangeRed* t_temp),
      t_minColor(2) + (rangeBlue* t_temp)};
    return newColor;
  }


}
