cmake_minimum_required(VERSION 2.8)
project( gabor_preprocess )
set(OpenCV_DIR /home/pradeep/Desktop/opencv_buildd/opencv)
find_package( OpenCV REQUIRED )
add_executable( gabor_preprocess gabor_preprocess.cpp)
target_link_libraries( gabor_preprocess ${OpenCV_LIBS} )