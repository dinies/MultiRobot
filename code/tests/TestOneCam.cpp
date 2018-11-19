// Created by Edoardo Ghini on 19/11/2018.

#include <gtest/gtest.h>
#include "../src/AgentManager.hpp"
#include "../src/Camera.hpp"
#include "../src/Environment.hpp"
#include "../src/utils/Drawer.hpp"

using namespace testing;
namespace MultiRobot{



  TEST( OneCamTest, simple){
    Drawer drawer( 40);

    std::vector<Eigen::Vector2d> eventDistribs; 
    eventDistribs.push_back( Eigen::Vector2d(3,3));
    
    Environment env( drawer, eventDistribs);

    Camera cam( env);

    std::vector<Camera> cams; 
    cams.push_back(cam);

    AgentManager agentMan( env, cams);

    agentMan.cycle();
    
  }
}



