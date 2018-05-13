# t0r0-gui-cameras

A GUI to display cameras from T0-R0 rover.

# Compile from command line
```
cd /<path>/catkin_ws/ && catkin_make
```

# Launch from Command-Line
```
rosrun t0r0_gui_cameras gui_cameras
```

# Use Makefile to update project from Git & Compile & Launch it

Create a Makefile with the following content. Substitute \<path\> with the path of your Catkin Workspace accordingly
```
all:	 update	compile	show

update:
	cd /<path>/catkin_ws/src/t0r0-gui-cameras && git pull origin master

compile:
	cd /<path>/catkin_ws	&& catkin_make

show:
	rosrun t0r0_gui_cameras gui_cameras
```

*tested on Ubuntu 16.04LTS with ROS Kinetic*
