# *************************************************************************
#
# Copyright (c) 2024 Andrei Gramakov. All rights reserved.
#
# This file is licensed under the terms of the MIT license.
# For a copy, see: https://opensource.org/licenses/MIT
#
# site:    https://agramakov.me
# e-mail:  mail@agramakov.me
#
# *************************************************************************

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
project(app_main)

find_package(GTest) 

enable_testing()

add_executable(
    utest
    test_basic.cpp
)
target_link_libraries(
    utest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utest)
