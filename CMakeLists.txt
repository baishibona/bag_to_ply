cmake_minimum_required(VERSION 2.8.3)
project(bag_to_ply)

set(octomap_DIR "/opt/ros/indigo/share/octomap")
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -O3")


## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  pcl_ros
  roscpp
  std_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES turtlebot_exploration_3d
#  CATKIN_DEPENDS geometry_msgs octomap_msgs octomap_ros octomap_server pcl_ros roscpp std_msgs actionlib move_base_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  include/
)

## Declare a cpp executable
add_executable(save_ply                     src/save_ply.cpp)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes

## Specify libraries to link a library or executable target against

target_link_libraries(save_ply
  ${catkin_LIBRARIES}
)

