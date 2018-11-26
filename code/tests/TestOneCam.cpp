// Created by Edoardo Ghini on 19/11/2018.

#include <gtest/gtest.h>
#include "../src/AgentManager.hpp"
#include "../src/Camera.hpp"
#include "../src/Environment.hpp"
#include "../src/utils/Drawer.hpp"

using namespace testing;
namespace MultiRobot{



  TEST( OneCamTest, simple){
    Drawer drawer( 100);

    Eigen::Vector2d center1(5, 7);
    Gaussian distrib1( 1, center1);
    std::vector<Gaussian> eventDistribs; 
    eventDistribs.push_back( distrib1);
    
    Environment env( drawer, eventDistribs);

    Eigen::Vector2d p( 5, 5);
    Eigen::Vector2d v( 1.0, 0.0);

    Camera cam( env, p, v);

    std::vector<Camera> cams; 
    cams.push_back(cam);

    AgentManager agentMan( env, cams);

    agentMan.cycle();
    
  }
}



