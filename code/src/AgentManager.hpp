// Created by Dinies on 19/11/2018.

#pragma once
#include <unistd.h>
#include "Environment.hpp"
#include "Camera.hpp"

namespace MultiRobot {
  class AgentManager{

    private:
      Environment m_env;
      std::vector<Camera> m_cameras;

    public:
      AgentManager( Environment & t_env, std::vector<Camera> &t_cameras);

      void cycle();
  };
}
