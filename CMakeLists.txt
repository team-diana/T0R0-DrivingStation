cmake_minimum_required(VERSION 2.8.11)

project(t0r0_gui_drivingstation)

# deprecated: catkin
#find_package(catkin REQUIRED COMPONENTS roscpp)
#include_directories(${catkin_INCLUDE_DIRS})
#include_directories(include ${catkin_INCLUDE_DIRS})
#
#catkin_package()

add_compile_options(-fPIC)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#DEPRECATED: Gstreamer
#find_package(Qt5GStreamer REQUIRED)
#include_directories(${QTGSTREAMER_INCLUDES})
#add_definitions(${QTGSTREAMER_DEFINITIONS})
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${QTGSTREAMER_FLAGS}")

# LIBVLC #
find_package(VLCQt REQUIRED COMPONENTS Core Qml Widgets)

#Qt5
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})

#C++ code
file(GLOB HEADER_FILES "src/*.h")
file(GLOB SOURCE_FILES "src/*.cpp")
#DELETE ME:
#set(SOURCE_FILES src/main.cpp src/player.cpp src/mediapp.cpp)
#set(HEADER_FILES src/player.h src/mediapp.h)

#UI files
file(GLOB UIS "*.ui" "src/*.ui")

#Resource files: images, etc.
qt5_add_resources(RESOURCES  "resources.qrc")

#change compile output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(gui_drivingstation ${HEADER_FILES} ${SOURCE_FILES} ${RESOURCES} ${UIS})
target_link_libraries(gui_drivingstation Qt5Core Qt5Widgets Qt5Gui
  VLCQtCore VLCQtWidgets VLCQtQml # LIBVLC and LIBVLCQt wrapper
)
