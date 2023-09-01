cmake_minimum_required(VERSION 3.20)
project(clion_opencv)

set(CMAKE_CXX_STANDARD 14)

add_executable(clion_opencv main.cpp)
set(OpenCV_DIR D:/opencv/mingw-build/install)
find_package(OpenCV REQUIRED)
target_link_libraries(clion_opencv ${OpenCV_LIBS})
