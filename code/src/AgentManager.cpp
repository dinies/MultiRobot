// Created by Dinies on 19/11/2018.

#include "AgentManager.hpp"
namespace MultiRobot {
  AgentManager::AgentManager( Environment & t_env, std::vector<Camera> &t_cameras):
    m_env( t_env),
    m_cameras( t_cameras)
  {};

  void  AgentManager::cycle(){
    for ( int i= 0; i<= 100; ++i){
      std::cout << " cycle step \n";
      m_env.showImg();
    }
    //TODO
  };

}




