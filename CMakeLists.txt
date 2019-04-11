cmake_minimum_required(VERSION 3.10.2)
project(GameRecorder)
add_library(GameRecorder SHARED
   src/Recorder.cpp
   src/utils.cpp)
#target_link_libraries(GameRecorder xcb)
