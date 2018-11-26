add_library( mainSources
  AgentManager.cpp
  Camera.cpp
  Environment.cpp
  Gaussian.cpp
  utils/Drawer.cpp
  utils/MyMath.cpp
  )

target_include_directories(
  mainSources PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  )
