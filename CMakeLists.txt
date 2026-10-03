cmake_minimum_required(VERSION 4.2)

project(PS4CONTROLLER CXX)

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
    main.cc
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    SDL3::SDL3
)
