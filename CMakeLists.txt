cmake_minimum_required(VERSION 4.2)

project(ROBOTCONTROLLER CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(SDL3 REQUIRED)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

file(GLOB SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
)

target_sources(${PROJECT_NAME}
  PRIVATE
    controller.cc
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    SDL3::SDL3
)

set(VIRTUAL_ROBOT_PROJECT_NAME ${PROJECT_NAME}_VIRTUALROBOT)

add_executable(${VIRTUAL_ROBOT_PROJECT_NAME})

target_include_directories(${VIRTUAL_ROBOT_PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_sources(${VIRTUAL_ROBOT_PROJECT_NAME}
  PRIVATE
    virtualrobot.cc
)
