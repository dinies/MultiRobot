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
    double m_sigma;
    double m_R;
    double m_kappa;
    Eigen::Matrix2d m_K_v;
    double m_K_alpha;
    Eigen::Vector2d m_lowLeftEdgeVoronoi;
    Eigen::Vector2d m_upRightEdgeVoronoi;
    double m_delta_t;
    double m_curr_t;
   double m_massVoronoiCell;
    Eigen::Vector2d m_centroidalPerspective;
    double m_radius;
    std::vector< cv::Point2d> m_drawingPoints;

    public:

    Camera(Environment & t_env,
        const Eigen::Vector2d &t_p = Eigen::Vector2d::Zero(),
        const Eigen::Vector2d &t_v = Eigen::Vector2d::Zero(),
        const double t_alpha= 0.2,
        const double t_sigma= 0.1,
        const double t_R = 3,
        const double t_kappa= 1,
        const Eigen::Matrix2d t_K_v = Eigen::Matrix2d::Identity(),
        const double t_K_alpha = 0,
        const Eigen::Vector2d t_lowLeftEdgeVoronoi= Eigen::Vector2d::Zero(),
        const Eigen::Vector2d t_upRightEdgeVoronoi= Eigen::Vector2d::Zero(),
        const double t_delta_t = 0.01
        );





    bool isInsideVoronoi( const double t_xCoord, const double t_yCoord );

    double computeCentroidalAperture();

    double computeCentroidalAngleOfView(
      const double t_centrAperture);

    void computeMassAndCentroidalPersp();

    Eigen::Vector3d generateInput();


    void updateState(const Eigen::Vector3d &t_deltaState );

    void evolve();
    void evolveDummy();

    std::vector< cv::Point2d> computePointsCameraDrawing();

    void draw();
    void drawMassAndCentroidalPersp();
    void drawVoronoi();

  };
}


