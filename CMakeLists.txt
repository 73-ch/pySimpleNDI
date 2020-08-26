cmake_minimum_required(VERSION 3.16)
project(simplendi)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(pybind)

find_package(NDI REQUIRED)

file(GLOB INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

pybind11_add_module(simplendi MODULE ${SOURCES})

target_include_directories(simplendi PRIVATE ${NDI_INCLUDE_DIR})
target_link_directories(simplendi PRIVATE ${NDI_LIBRARY_DIR})
target_link_libraries(simplendi PRIVATE pybind11::module ${NDI_LIBS})

source_group("" FILES ${SOURCES} ${INCLUDES})