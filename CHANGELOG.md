# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.6.1] - 2018-08-31
###Fixes
- Program could hang while waiting for TCP connection.

## [0.6.0] - 2018-08-30
### Added
- Graphical widgets for input peripherals.
- Input peripherals for mobility (gamepad) are remapped to improve precision and control.

### Changed
- Update TCP library

## [0.5.3] - 2018-08-05
### Added
- Graphical output elements for gamepad and joystick

## [0.5.2] - 2018-07-26
### Changed
- Gamepad and Joystick now share the same library

### Fixes
- Gamepad and Joystick may be exchanged

## [0.5.1] - 2018-07-26
### Added
- New graphical elements (still in development)

### Changed
- GStreamer pipeline: to handle PointGray cameras
- Reimplemented joystick library

### Fixes
- Unreliable handling of HID peripherals

## [0.5.0] - 2018-07-26
### Added
- New TCP Handler library
- TCP Handler is now a QThread

## [0.4] - 2018-07-10
### Added
- Input Map for Joystick and Gamepad --> "inputmapping.h"
- Sending Gamepad L3 R3 through TCP ports (converted to uint16)
- TcpServerSimulator Tool inside 'Tool' folder
- IO mapping function for Gamepad and Joystick
- Library Updater tool

### Changed
- Using Joystick library also for Gamepad

### Removed
- QGamepad library

### Fixes
- When initializing MainWindow constructor, the initialization of TCP ports of the Gamepad
	was sent uin8_t instead of uint16_t.

## [0.3] - 2018-07-01
### Added
- QtCreator Support
- qmake file

### Removed
- File 'atom-build-yml'
