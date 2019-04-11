cmake_minimum_required(VERSION 3.10.2)
project(GameRecorder)
add_library(GameRecorder SHARED
   src/Recorder.cpp)
#target_link_libraries(GameRecorder xcb)
