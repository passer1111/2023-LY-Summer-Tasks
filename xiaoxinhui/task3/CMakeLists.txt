cmake_minimum_required(VERSION 3.22)
project(run)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(main main.cpp model.cpp)
target_link_libraries(main
	${OpenCV_LIBS}	
)
