// Created by Dinies on 19/11/2018.

#include "AgentManager.hpp"
namespace MultiRobot {
  AgentManager::AgentManager( Environment & t_env, std::vector<Camera> &t_cameras):
    m_env( t_env),
    m_cameras( t_cameras)
  {};

  void  AgentManager::cycle(){
    for ( int i= 0; i<= 100; ++i){
      for( int j = 0; j<= m_cameras.size()-1; ++j){
        Camera &cam = m_cameras.at(j);
        cam.evolve();
        m_env.drawEventDistribs();
        m_env.showImg();
      }
      //TODO
    };

  }
}





