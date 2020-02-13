cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0042 NEW)
project(wrapDeformer)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)