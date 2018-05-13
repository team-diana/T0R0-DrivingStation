cmake_minimum_required(VERSION 2.8.11)

project(t0r0_gui_cameras)

add_compile_options(-fPIC)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(catkin REQUIRED COMPONENTS roscpp)
include_directories(${catkin_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})

catkin_package()

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})

set(HEADER_FILES src/window.h)
set(SOURCE_FILES src/main.cpp src/window.cpp)

add_executable(gui_cameras ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(gui_cameras Qt5Core Qt5Widgets Qt5Gui ${catkin_LIBRARIES})
