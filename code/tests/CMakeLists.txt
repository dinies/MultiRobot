add_executable(
  TestOneCam
  TestOneCam.cpp
  Starter.cpp
  )
target_link_libraries(
  TestOneCam
  PUBLIC gtest_main
  PUBLIC gmock_main
  PUBLIC mainSources
  PUBLIC ${OpenCV_LIBS}
 )

add_test(
  NAME TestOneCam
  COMMAND TestOneCam
  )

add_executable(
  TestCentrQuant
  TestCentrQuant.cpp
  Starter.cpp
  )
target_link_libraries(
  TestCentrQuant
  PUBLIC gtest_main
  PUBLIC gmock_main
  PUBLIC mainSources
  PUBLIC ${OpenCV_LIBS}
 )

add_test(
  NAME TestCentrQuant
  COMMAND TestCentrQuant
  )


add_executable(
  TestDrawVoronoi
  TestDrawVoronoi.cpp
  Starter.cpp
  )
target_link_libraries(
  TestDrawVoronoi
  PUBLIC gtest_main
  PUBLIC gmock_main
  PUBLIC mainSources
  PUBLIC ${OpenCV_LIBS}
 )

add_test(
  NAME TestDrawVoronoi
  COMMAND TestDrawVoronoi
  )


