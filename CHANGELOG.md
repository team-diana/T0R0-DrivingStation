# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Added
- Input Map for Joystick and Gamepad --> "inputmapping.h"
- Sending Gamepad L3 R3 through TCP ports (converted to uint16)
- TcpServerSimulator Tool inside 'Tool' folder
- IO mapping function for Gamepad and Joystick

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
