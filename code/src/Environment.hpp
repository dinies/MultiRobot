// Created by Dinies on 19/11/2018.

#pragma once
#include <unistd.h>
#include <Eigen/Core>
#include "utils/Drawer.hpp"
#include "Gaussian.hpp"

namespace MultiRobot {

  typedef struct colors_tag{
    cv::Scalar green;
    cv::Scalar white;
    cv::Scalar dark_red;
    cv::Scalar milk;
    cv::Scalar lightBlue;
    cv::Scalar fadedLightBlue;
    cv::Scalar lightOrange;
    cv::Scalar darkBrown;
  }colors;

  typedef struct discretePoint_tag{
    cv::Point2d coords;
    double eventProbability;
    discretePoint_tag(
        double t_xCoord = 0,
        double t_yCoord = 0,
        double t_eventProb =0):
      coords( t_xCoord, t_yCoord),
      eventProbability( t_eventProb)
    {}
  }discretePoint;




  class Environment {
    private:
    Drawer m_drawer;
    std::vector<Gaussian> m_eventDistribs;

    int m_x_units;
    int m_y_units;
    RGBImage m_drawing;
    colors m_colors;
    int m_precisionDiscretization;

    std::vector< std::vector< discretePoint>>  m_eventValues;

    
 

    public:
    Environment( Drawer &t_drawer,
        const std::vector<Gaussian> &t_eventDistribs,
        const int t_x_units = 10, const int t_y_units = 10,
        const double t_precDiscret = 20);


    std::vector< std::vector< discretePoint>> computeEventValues();
    std::vector< discretePoint> computeEventColumn(const double t_xValue);

    void drawEventDistribs();

    void drawCam(
        const std::vector< cv::Point2d> &t_points,
        const Eigen::Vector2d &t_camCenter,
        const bool t_deletingFlag);

    void showImg();

    cv::Scalar getColorTemperature( 
      const double t_temp,
      const cv::Scalar &t_minColor,
      const cv::Scalar &t_maxColor);



  };
}

      


