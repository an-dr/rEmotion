cmake_minimum_required(VERSION 3.15)
project(remotion_demo_app)

set(CMAKE_CXX_STANDARD 17)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Config: CppLinuxSerial
set(BUILD_TESTS
    OFF
    CACHE BOOL "Build tests"
)

# Add abcmake
include(../ab.cmake)

register_components(
    ${CMAKE_CURRENT_LIST_DIR}/..
)

add_main_component(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE CppLinuxSerial::CppLinuxSerial)
target_link_libraries(${PROJECT_NAME} PRIVATE libv4l2cpp)
target_link_components( ${PROJECT_NAME} NAME remotion_ctrl )
