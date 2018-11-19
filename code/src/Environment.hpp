// Created by Dinies on 19/11/2018.

#pragma once
#include <unistd.h>
#include <Eigen/Core>
#include "utils/Drawer.hpp"

namespace MultiRobot {

  class Environment {
    private:
    Drawer m_drawer;
    std::vector<Eigen::Vector2d> m_eventDistribs; //TODO 
    int m_x_units;
    int m_y_units;
    RGBImage m_drawing;
    //use a different parametrization to use gaussians


    public:
    Environment( Drawer &t_drawer,
        const std::vector<Eigen::Vector2d> &t_eventDistribs,
        const int t_x_units = 100, const int t_y_units = 100);

    void drawEventDistribs();
    void showImg();

  };
}

      


