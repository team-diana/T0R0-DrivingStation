# t0r0-gui-cameras

A GUI to display cameras from T0-R0 rover.

# Dependencies installation
### QT5
  Dowload and install components from <a href="https://download.qt.io/official_releases/qt/5.10/5.10.1/">here</a>

<code>cd Download  </code> <br> <code>chmod +x qt-opensource-linux-x64-5.10.1.run</code> <br> <code>./qt-opensource-linux-x64-5.10.1.run </code>  <br>

<h> Follow the instruction, and PIN the checkbox "QT 5.10.1" </h>

### GStreamer
Run the following commands
```
apt-get install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools
```
```
sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
```
```
sudo apt-get install libqt5glib-2.0-0 libqt5gstreamer-1.0-0 libqt5gstreamer-dev libqt5gstreamerquick-1.0-0 libqt5gstreamerui-1.0-0 libqt5gstreamerutils-1.0-0
```

# Compile from command line
```
cd /<path>/build
cmake ..
make gui_cameras
```

# Launch from Command-Line
```
cd /<path>/build
./bin/gui_cameras
```

# Use Makefile to update project from Git & Compile & Launch it

Create a Makefile with the following content. Substitute \<path\> with the path of your t0r0-gui-cameras folder accordingly
```
all:	 update	compile	show

update:
	cd /<path>/ && git pull origin master

compile:
	cd /<path>/build && cmake .. && make gui_cameras

show:
	cd /<path>/build && ./bin/gui_cameras
```
Run Makefile using <code>make</code>.

*tested on Ubuntu 16.04LTS with ROS Kinetic*
