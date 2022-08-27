


# SmartHandController-HD
> My personal version of an OnStep Telescope hand controller with higher resolution LCD, nicer graphics and easier control.

## Table of Contents
- [SmartHandController-HD](#smarthandcontroller-hd)
  - [Table of Contents](#table-of-contents)
  - [General Information](#general-information)
  - [Features](#features)
  - [Project Status](#project-status)
  - [Photos](#photos)
  - [Setup](#setup)
  - [Acknowledgements](#acknowledgements)
  - [Contact](#contact)
<!-- * [License](#license) -->


## General Information
Although i'm a big fan of the OnStep project and the SmartHandController, I do not like the small dinky unintuitive OLED that is used in the official SmartHandController.
With the available processing power, something 'cleaner' should be possible. So this project includes:
- A SmartHandController variant with high resolution screen, a 240 x 240 pixels CG9A01 1.28" round LCD in my case (why? because i had one left over, and i like the aestethic) 
- (more and different screens should theoretically be possible in the future?)
- A nice graphical UI built with LVGL
- Fully compatible with OnStep 4.x and X, loosely based on the original SHC code.
<!-- You don't have to answer all the questions - just the ones relevant to your project. -->


## Features
List the ready features here:
- A SmartHandController variant with high resolution screen, a 240 x 240 pixels CG9A01 1.28" round LCD in my case (why? because i had one left over, and i like the aestethic) 
- (more and different screens should theoretically be possible in the future?)
- A nice graphical UI built with LVGL
- Fully compatible with OnStep 4.x and X, loosely based on the original SHC code.
- Running on an ESP32-C3-12F (Might change to ESP32S3 later on, for classic bluetooth connection)
- 7 buttons utilizing just 4 I/O pins through WaynePlexing. (programming boot mode is done via the home button)

## Project Status
Project is: _in progress and non-functional as of yet_!
- [x] Prototype hardware
- [x] Initial project setup
- [x] Graphical UI
  - [x] Basic navigation
  - [ ] Design menu structure
  - [ ] Implement menu structure
- [ ] Telescope Communication
  - [ ] Basic control
  - [ ] Settings




## Photos
The initial prototype looks like this.
<!--![Example screenshot](img\prototype-front.jpg) -->
<img src="img\prototype-screen.jpg" alt="drawing" height="500" width="500"/>
<img src="img\prototype-iso.jpg" alt="drawing" height="500" width="500"/>
<!-- If you have screenshots you'd like to share, include them here. -->



## Setup
This project is a complete PlatformIO project. So if you're familiar with that, just import it in PlatformIO and you should be good to go.
But i have to stress! this project is not functional yet!

## Acknowledgements
This project would be impossible without:
- The great work over at [OnStep](https://onstep.groups.io/g/main/wiki) and their [github](https://github.com/hjd1964/OnStep)
- Principle and code partially based off of [SmartHandController](https://github.com/hjd1964/SmartHandController)
- UI is made with [LVGL](https://github.com/lvgl/lvgl)


## Contact
Created by [@flynerdpl](https://www.flynerd.pl/) - feel free to contact me!


<!-- Optional -->
<!-- ## License -->
<!-- This project is open source and available under the [... License](). -->

<!-- You don't have to include all sections - just the one's relevant to your project -->