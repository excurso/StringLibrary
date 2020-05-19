cmake_minimum_required(VERSION 3.5)

project(String LANGUAGES CXX)

if (NOT TARGET Container)
	add_subdirectory(../ContainerLibrary/ ContainerLibrary/)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(String
	src/String.cpp
	src/String.h
)

target_link_libraries(String LINK_PUBLIC Container)
target_compile_definitions(String PRIVATE STRING_LIBRARY)
