cmake_minimum_required(VERSION 3.22)

project(Calculation VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)

find_package(Qt6 COMPONENTS REQUIRED
  Core
)

add_library(${PROJECT_NAME}
  SHARED
  calculation.h
  calculation.cc
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${PROJECT_NAME}
  PUBLIC
  cxx_std_17
)

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE
  -Wall
  -Werror
  -Wpedantic
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${Qt6Core_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  Qt6::Core
)
