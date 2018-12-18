// Created by Dinies on 19/11/2018.

#include "AgentManager.hpp"
using namespace cv;

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
    };
  }

  void  AgentManager::cycleWithVideo( std::string t_fileName, double t_fps){
    
    bool isColor = true;
    VideoWriter writer;
    int codec = VideoWriter::fourcc( 'X','V','I','D');
    Size drawingSize = m_env.getDrawingSize();
    writer.open(t_fileName, codec, t_fps, drawingSize, isColor);

    if (!writer.isOpened()){
      std::cerr << "Couldn't open the video writer\n";
    }
    

    for ( int i= 0; i<= 100; ++i){
      for( int j = 0; j<= m_cameras.size()-1; ++j){
        Camera &cam = m_cameras.at(j);
        cam.evolve();
        m_env.drawEventDistribs();
        writer.write( m_env.getCurrDrawing());
        m_env.showImg();
      }
    };
 

  }
}





