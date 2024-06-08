cmake_minimum_required(VERSION 3.15)
project(remotion_demo_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

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
include(../ab.cmake)

register_components(
    ${CMAKE_CURRENT_LIST_DIR}/..
#     ${CMAKE_CURRENT_LIST_DIR}/../common_components/visioner_interfaces
#     ${CMAKE_CURRENT_LIST_DIR}/../common_components/visioner_app
#     ${CMAKE_CURRENT_LIST_DIR}/../common_components/SceneReaderWebcam
)

add_main_component(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
# target_link_libraries(${PROJECT_NAME} PRIVATE CppLinuxSerial::CppLinuxSerial)
target_link_components(
    ${PROJECT_NAME} NAME remotion_ctrl
    # microlog
)

# Install
# file(GLOB examples "${CMAKE_CURRENT_LIST_DIR}/../../img/examples/*")
# install(FILES ${examples} DESTINATION ./input)