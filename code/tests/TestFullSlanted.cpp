// Created by Edoardo Ghini on 05/12/2018.

#include <gtest/gtest.h>
#include "../src/AgentManager.hpp"
#include "../src/Camera.hpp"
#include "../src/Environment.hpp"
#include "../src/utils/Drawer.hpp"

using namespace testing;
namespace MultiRobot{


  TEST( OneCamTest, fullSlanted){
    Drawer drawer( 100);

    cv::Scalar white = {255,255,255};
    cv::Scalar green = {0,255,20};
    cv::Scalar dark_red = {20,0,255};
    cv::Scalar milk= {227,246,253};
    cv::Scalar lightBlue= {210,139,38};
    cv::Scalar fadedLightBlue= {255,207,130};
    cv::Scalar lightOrange = {0,164,216};
    cv::Scalar darkBrown = {1,83,109};


    Eigen::Vector2d centerDown(5.0, 2.0);
    Eigen::Vector2d centerRight(8.0, 5.0);
    Eigen::Vector2d centerUp(5.0, 8.0);
    Eigen::Vector2d centerLeft(2.0, 5.0);

    Gaussian distrib1( 1, centerDown);
    Gaussian distrib2( 1, centerRight);
    Gaussian distrib3( 1, centerUp);
    Gaussian distrib4( 1, centerLeft);
    std::vector<Gaussian> eventDistribs; 

    eventDistribs.push_back( distrib1);
    eventDistribs.push_back( distrib2);
    eventDistribs.push_back( distrib3);
    eventDistribs.push_back( distrib4);
    
    Environment env( drawer, eventDistribs);

    Eigen::Vector2d p1( 0.5, 0.5);
    Eigen::Vector2d v1( 1.0, 0.0);

    Eigen::Vector2d p2( 9.5, 0.5);
    Eigen::Vector2d v2( 0.0, 1.0);

    Eigen::Vector2d p3( 9.5, 9.5);
    Eigen::Vector2d v3( -1.0, 0.0);

    Eigen::Vector2d p4( 0.5, 9.5);
    Eigen::Vector2d v4( 0.0, -1.0);


    double alpha = M_PI/6;
    double sigma = 2;
    double R = 7;
    double kappa =3;
    Eigen::Matrix2d K_v;
    K_v <<
      1,0,
      0,1;
    double K_alpha = 1;

    Eigen::Vector2d downVoronoiFirstP( 5, 0);
    Eigen::Vector2d downVoronoiSecondP( 10, 5);
    Eigen::Vector2d rightVoronoiFirstP( 5, 5);
    Eigen::Vector2d rightVoronoiSecondP( 10, 10);
    Eigen::Vector2d upVoronoiFirstP( 0, 5);
    Eigen::Vector2d upVoronoiSecondP( 5, 10);
    Eigen::Vector2d leftVoronoiFirstP( 0, 0);
    Eigen::Vector2d leftVoronoiSecondP( 5, 5);

    double delta_t = 0.1;
     
    Camera camLeftDown( env, p1, v1, alpha, sigma, R,
        kappa, K_v, K_alpha, rightVoronoiFirstP,
        rightVoronoiSecondP, delta_t,green);

    Camera camRightDown( env, p2, v2, alpha, sigma, R,
        kappa, K_v, K_alpha, upVoronoiFirstP,
        upVoronoiSecondP, delta_t, lightOrange);


    Camera camRightUp( env, p3, v3, alpha, sigma, R,
        kappa, K_v, K_alpha, leftVoronoiFirstP,
        leftVoronoiSecondP, delta_t, lightBlue);


    Camera camLeftUp( env, p4, v4, alpha, sigma, R,
        kappa, K_v, K_alpha,downVoronoiFirstP,
        downVoronoiSecondP, delta_t,darkBrown);


    std::vector<Camera> cams; 
    cams.push_back(camLeftDown);
    cams.push_back(camRightDown);
    cams.push_back(camRightUp);
    cams.push_back(camLeftUp);

    AgentManager agentMan( env, cams);

    double fps = 60.0;
    std::string videopath  = "../videos/FullSlanted.avi";
    agentMan.cycleWithVideo(videopath,fps);
    
  }
}



