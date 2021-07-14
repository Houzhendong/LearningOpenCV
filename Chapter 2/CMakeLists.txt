cmake_minimum_required(VERSION 3.8)

project("Chapter2")
add_executable(${PROJECT_NAME} main.cpp)

find_package( OpenCV REQUIRED )

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )