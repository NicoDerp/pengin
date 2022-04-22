cmake_minimum_required(VERSION 3.17)

project(pengin)

add_executable(${PROJECT_NAME} src/glad.c main.cpp src/window.cpp include/window.h)

target_link_libraries(${PROJECT_NAME} GL dl glfw)
