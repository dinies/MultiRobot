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


