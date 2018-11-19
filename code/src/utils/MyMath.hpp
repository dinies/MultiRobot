// Created by dinies on 03/07/2018.

//Collection of static functions and useful types to perform geometric computations
#pragma once

#include <unistd.h>
#include <vector>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace MultiRobot{
  class MyMath{

  public:
    // static Eigen::Isometry2d v2t(const std::vector<double> &t_vec);
    // static std::vector<double> t2v(const Eigen::Isometry2d& t_transf);

    static Eigen::Isometry2d v2t(const Eigen::Vector3d &t_vec);
    static Eigen::Vector3d t2v(const Eigen::Isometry2d& t_transf);

    static void rotate2D( Eigen::Vector2d &t_point, const double t_angle_rad );

    static std::vector<double> vecSum(const std::vector<double> &t_first,const std::vector<double> &t_second);

    static std::vector<double> vecMultEleWise(const std::vector<double> &t_first,const std::vector<double> &t_second);

    static double boxMinusAngleRad(const double t_ref,const double t_actual);
    static double boxPlusAngleRad(const double t_ref,const double t_actual);
    static double computeAvg(const double t_prevAvg,const int t_numEntries,const double t_newValue);
  };
}
