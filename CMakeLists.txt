cmake_minimum_required(VERSION 2.8)
PROJECT (name)
# Add OpenCV libraray
find_package(OpenCV REQUIRED core imgproc highgui calib3d videostab xfeatures2d aruco)
message(STATUS ${OpenCV_LIBS})


INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_library(ARUCO_LOC relocalize_aruco.cpp)
target_link_libraries(ARUCO_LOC ${OpenCV_LIBS})
