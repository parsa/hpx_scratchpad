cmake_minimum_required(VERSION 3.3)

project(bcast)

find_package(HPX REQUIRED)

add_hpx_executable(bcast
  SOURCES bcast.cpp
  COMPONENT_DEPENDENCIES iostreams)
