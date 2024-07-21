cmake_minimum_required(VERSION 3.15)
project(remotion_ctrl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# Config: microlog
add_definitions(-DULOG_HIDE_FILE_STRING)
add_definitions(-DULOG_SHORT_LEVEL_STRINGS)
add_definitions(-DULOG_USE_COLOR)

# Config: CppLinuxSerial
set(BUILD_TESTS
    OFF
    CACHE BOOL "Build tests"
)

# Add abcmake
include(ab.cmake)


add_component(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE CppLinuxSerial::CppLinuxSerial)
target_link_libraries(${PROJECT_NAME} PRIVATE libv4l2cpp)
# target_link_components(
    # ${PROJECT_NAME} NAME SceneReaderWebcam visioner_interfaces visioner_app
    # microlog
# )

# Install
# file(GLOB examples "${CMAKE_CURRENT_LIST_DIR}/../../img/examples/*")
# install(FILES ${examples} DESTINATION ./input)

# # Tests
# enable_testing()
# find_package(GTest) 

# add_executable(
#     utest
#     tests/stubs/Remotion.cpp
#     tests/test_basic/test_basic.cpp
# )
# target_link_libraries(
#     utest
#     GTest::gtest_main
# )

# include(GoogleTest)
# gtest_discover_tests(utest)
