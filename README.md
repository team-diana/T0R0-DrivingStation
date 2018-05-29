# T0-R0 Driving Station GUI

A GUI to display cameras from T0-R0 rover

# Dependencies installation
### QT5
  Dowload and install components from <a href="https://download.qt.io/official_releases/qt/5.10/5.10.1/">here</a>

<code>cd Download  </code> <br> <code>chmod +x qt-opensource-linux-x64-5.10.1.run</code> <br> <code>./qt-opensource-linux-x64-5.10.1.run </code>  <br>

<h> Follow the instruction, and PIN the checkbox "QT 5.10.1" </h>

### LibVLC

Run the following commands
```
sudo apt-get install vlc
```
```
sudo apt-get install libvlc-dev libvlccore-dev
```

### VLC-Qt

- A wrapper of LibVLC for Qt.

Run the following commands
```
sudo add-apt-repository ppa:ntadej/tano
```
```
sudo apt update
```
```
sudo apt-get install libvlc-qt-core2 libvlc-qt-widgets2 libvlc-qt-dbg libvlc-qt-dev
```

## Compile and Run

### With Makefile

Change to main project directory and run Makefile using <code>make</code>

### Compile from command line
```
cd /<path>/build
cmake ..
make gui_drivingstation
```

### Launch from Command-Line
```
cd /<path>/build
./bin/gui_drivingstation
```

### Use Makefile to update project from Git, Compile & Launch it

Create a Makefile with the following content. Substitute \<path\> with the path of your t0r0-gui-cameras folder accordingly
```
all:	 update	compile	show

update:
	cd /<path>/ && git pull origin master

compile:
	cd /<path>/build && cmake .. && make gui_drivingstation

run:
	cd /<path>/build && ./bin/gui_drivingstation
```
