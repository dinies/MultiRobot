// Created by Edoardo Ghini on 28/11/2018.

#include <gtest/gtest.h>
#include "../src/AgentManager.hpp"
#include "../src/Camera.hpp"
#include "../src/Environment.hpp"
#include "../src/utils/Drawer.hpp"

using namespace testing;
namespace MultiRobot{



  TEST( OneCamTest, simple){
    Drawer drawer( 100);

    Eigen::Vector2d center1(4, 7);
    Gaussian distrib1( 1, center1);
    std::vector<Gaussian> eventDistribs; 
    eventDistribs.push_back( distrib1);
    
    Environment env( drawer, eventDistribs);

    Eigen::Vector2d p( 3, 3);
    Eigen::Vector2d v( -2.0, -1.0);



    double alpha = M_PI/6;
    double sigma = 2;
    double R = 7;
    double kappa =3;
    Eigen::Matrix2d K_v;
    K_v <<
      1,0,
      0,1;
    double K_alpha = 1;

    Eigen::Vector2d leftDownVoronoi( 2, 2);
    Eigen::Vector2d upRightVoronoi( 8, 8);
    double delta_t = 0.1;
     
    Camera cam( env, p, v,alpha, sigma, R,
        kappa, K_v, K_alpha, leftDownVoronoi,
        upRightVoronoi, delta_t);


    cam.drawMassAndCentroidalPersp();
    env.showImg();
    cv::waitKey();
    
  }
}


