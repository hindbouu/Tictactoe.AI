# Copyright (c) 2025 Nathan Greenfield. All rights reserved

# Require CMAKE 3.12 or higher
cmake_minimum_required(VERSION 3.12)

# If you create new headers/cpp files, add them to these list!
set(HEADER_FILES
    catch.hpp
    catch_reporter_github.hpp
)

set(SOURCE_FILES
    catch.cpp
	studentTests.cpp
)

# Where any include files are
include_directories("../src")

# Don't change this
add_executable(tests ${SOURCE_FILES})

# Link main vs the source library
target_link_libraries(tests src)
