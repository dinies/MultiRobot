// Created by Dinies on 19/11/2018.
#pragma once
#include <unistd.h>
#include "opencv2/opencv.hpp"


namespace MultiRobot{

  typedef cv::Mat_< cv::Vec3b > RGBImage;

  class Drawer {


  private:
    double m_scale;
  public:
    Drawer(const double scale);

    void drawHollowPoligon(
        const RGBImage &t_drawing,
        const std::vector< cv::Point2d> &t_consecPoints,
        const cv::Scalar &t_color );

    void drawPatch(
        RGBImage &t_drawing,
        const cv::Point2d &t_point,
        const cv::Scalar &t_color);

    void drawLine(
        const RGBImage &t_drawing,
        const cv::Point2d &t_firstP,
        const cv::Point2d &t_secondP,
        const cv::Scalar &t_color);

    cv::Point2d convertFrowWorldToImg(
        const RGBImage &t_drawing,
        const cv::Point2d &t_point);

    bool isInsideBoundaries(
        const RGBImage &t_drawing,
        const cv::Point2d &t_point);
  };
}
