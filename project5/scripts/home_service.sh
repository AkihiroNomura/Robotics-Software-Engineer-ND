#!/bin/sh
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/map/crayon_office.world" &
sleep 10
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/map/map.yaml" &
sleep 10
xterm  -e  "rosrun rviz rviz -d /home/workspace/catkin_ws/src/rvizConfig/homeServiceRobot.rviz" &
sleep 10
xterm  -e  "rosrun add_markers add_markers" &
sleep 3
xterm  -e  "rosrun pick_objects pick_objects"