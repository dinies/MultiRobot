// Created by Edoardo Ghini on 21/12/2018.

#include <gtest/gtest.h>
#include "../src/AgentManager.hpp"
#include "../src/Camera.hpp"
#include "../src/Environment.hpp"
#include "../src/utils/Drawer.hpp"

using namespace testing;
namespace MultiRobot{



  TEST( OneCamTest, full){
    Drawer drawer( 100);

    cv::Scalar blue = {255,204,0};
    cv::Scalar green= {0,204,0};
    cv::Scalar red= {0,51,204};
    cv::Scalar yellow= {0,204,255};





    Eigen::Vector2d center1(8.0, 8.0);
    Eigen::Vector2d center2(8.0, 2.0);
    Eigen::Vector2d center3(8.0, 4.0);
    Eigen::Vector2d center4(3.0, 7.0);

    Gaussian distrib1( 1/9, center1);
    Gaussian distrib2( 1/2, center2);
    Gaussian distrib3( 1/2, center3);
    Gaussian distrib4( 1, center4);
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

    Eigen::Vector2d camLeftDownVoronoiFirstP( 0, 5);
    Eigen::Vector2d camLeftDownVoronoiSecondP( 5, 10);

    Eigen::Vector2d camRightDownVoronoiFirstP( 0, 0);
    Eigen::Vector2d camRightDownVoronoiSecondP( 10, 10);


    Eigen::Vector2d camRightUpVoronoiFirstP( 5, 0);
    Eigen::Vector2d camRightUpVoronoiSecondP( 10, 5);


    Eigen::Vector2d camLeftUpVoronoiFirstP( 5, 5);
    Eigen::Vector2d camLeftUpVoronoiSecondP( 10, 10);


    double delta_t = 0.1;
     
    Camera camLeftDown( env, p1, v1, alpha, sigma, R,
        kappa, K_v, K_alpha, camLeftDownVoronoiFirstP,
        camLeftDownVoronoiSecondP, delta_t, red);

    Camera camRightDown( env, p2, v2, alpha, sigma, R,
        kappa, K_v, K_alpha, camRightDownVoronoiFirstP,
        camRightDownVoronoiSecondP, delta_t, blue);

    Camera camRightUp( env, p3, v3, alpha, sigma, R,
        kappa, K_v, K_alpha, camRightUpVoronoiFirstP,
        camRightUpVoronoiSecondP, delta_t, green);

    Camera camLeftUp( env, p4, v4, alpha, sigma, R,
        kappa, K_v, K_alpha,camLeftUpVoronoiFirstP,
        camLeftUpVoronoiSecondP, delta_t, yellow);


    std::vector<Camera> cams; 
    cams.push_back(camLeftDown);
    cams.push_back(camRightDown);
    cams.push_back(camRightUp);
    cams.push_back(camLeftUp);

    AgentManager agentMan( env, cams);

    double fps = 60.0;
    std::string videopath  = "../videos/FullMultiEvent.avi";
    //agentMan.cycleWithVideo(videopath, fps);
    agentMan.cycle();
  }
}



