// Created by Dinies on 19/11/2018.

#pragma once
#include <unistd.h>
#include "Environment.hpp"
#include "utils/MyMath.hpp"

namespace MultiRobot {
  class Camera {
    private:

    Environment m_env;
    Eigen::Vector2d m_p;//position
    Eigen::Vector2d m_v;//optical axis direction
    double m_alpha; //angle of view (zoom level)
    double m_radius;
    public:

    Camera(Environment & t_env,
        const Eigen::Vector2d &t_p = Eigen::Vector2d::Zero(),
        const Eigen::Vector2d &t_v = Eigen::Vector2d::Zero(),
        const double t_alpha= 0.2);

    Eigen::Vector2d generateInput();

    void updateState(const Eigen::Vector2d & t_deltaState );

    void evolve();

    std::vector< cv::Point2d> computePointsCameraDrawing();

    void draw();

  };
}


