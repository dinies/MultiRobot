add_library( mainSources
  AgentManager.cpp
  Camera.cpp
  Environment.cpp
  utils/Drawer.cpp
  )

target_include_directories(
  mainSources PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  )
