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


  class Environment {
    private:
    Drawer m_drawer;
    std::vector<Gaussian> m_eventDistribs;

    int m_x_units;
    int m_y_units;
    RGBImage m_drawing;
    colors m_colors;
    int m_precisionDiscretization;

    std::vector< std::vector< double>>  m_eventValues;

    
 

    public:
    Environment( Drawer &t_drawer,
        const std::vector<Gaussian> &t_eventDistribs,
        const int t_x_units = 10, const int t_y_units = 10,
        const double t_precDiscret = 20);


    std::vector< std::vector< double>> computeEventValues();
    std::vector< double> computeEventColumn(const double t_xValue);

    void drawEventDistribs();

    void drawCam(
        const std::vector< cv::Point2d> &t_points,
        const Eigen::Vector2d &t_camCenter,
        const bool t_deletingFlag);

    void showImg();

  };
}

      


