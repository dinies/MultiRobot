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

add_executable(
  TestFull
  TestFull.cpp
  Starter.cpp
  )
target_link_libraries(
  TestFull
  PUBLIC gtest_main
  PUBLIC gmock_main
  PUBLIC mainSources
  PUBLIC ${OpenCV_LIBS}
 )

add_test(
  NAME TestFull
  COMMAND TestFull
  )


add_executable(
  TestFullSlanted
  TestFullSlanted.cpp
  Starter.cpp
  )
target_link_libraries(
  TestFullSlanted
  PUBLIC gtest_main
  PUBLIC gmock_main
  PUBLIC mainSources
  PUBLIC ${OpenCV_LIBS}
 )

add_test(
  NAME TestFullSlanted
  COMMAND TestFullSlanted
  )


add_executable(
  TestFullAlterned
  TestFullAlterned.cpp
  Starter.cpp
  )
target_link_libraries(
  TestFullAlterned
  PUBLIC gtest_main
  PUBLIC gmock_main
  PUBLIC mainSources
  PUBLIC ${OpenCV_LIBS}
 )

add_test(
  NAME TestFullAlterned
  COMMAND TestFullAlterned
  )


