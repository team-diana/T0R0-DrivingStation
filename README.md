# T0-R0 Driving Station GUI

A GUI to display cameras from T0-R0 rover

## Dependencies installation

### QT5
  Download and install components from <a href="https://download.qt.io/official_releases/qt/5.10/5.10.1/">here</a>

```
cd Download
chmod +x qt-opensource-linux-x64-5.10.1.run
./qt-opensource-linux-x64-5.10.1.run
```

<h> Follow the instruction, and PIN the checkbox "QT 5.10.1" </h>

### GStreamer
Run the following commands
```
sudo apt install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools
```
```
sudo apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libqt5gstreamer-dev
```


## Compile and Run
Directly inside of QtCreator

## Note - Known Issues
Connect Joystick before Gamepad otherwise they can be misinterpreted.
