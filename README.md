# t0r0-gui-cameras

A GUI to display cameras from T0-R0 rover.

# Dependencies installation
  Dowload and install components from <a href="https://download.qt.io/official_releases/qt/5.10/5.10.1/">here</a>

<code>cd Download  </code> <br> <code>chmod +x qt-opensource-linux-x64-5.10.1.run</code> <br> <code>./qt-opensource-linux-x64-5.10.1.run </code>  <br>

<h> Follow the instruction, and PIN the checkbox "QT 5.10.1" </h>

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
Run
```
make
```

*tested on Ubuntu 16.04LTS with ROS Kinetic*
