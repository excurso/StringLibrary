###############################################################################
# StringLibrary - A C++ library extending the functionality of the STL strings
# Copyright (C) 2019-2020 Waldemar Zimpel <hspp@utilizer.de>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.
###############################################################################


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
