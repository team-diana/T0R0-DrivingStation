cmake_minimum_required(VERSION 2.8.11)

project(t0r0_gui_cameras)

add_compile_options(-fPIC)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(catkin REQUIRED COMPONENTS roscpp)
include_directories(${catkin_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})

catkin_package()

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

#Resource files: images, etc.
qt5_add_resources(RESOURCES  "resources.qrc")

add_executable(gui_cameras ${HEADER_FILES} ${SOURCE_FILES} ${RESOURCES})
target_link_libraries(gui_cameras Qt5Core Qt5Widgets Qt5Gui ${catkin_LIBRARIES})

