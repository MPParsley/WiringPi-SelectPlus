# WiringPi-SelectPlus
Send the QH-832AC doorbell signal from a Raspberry Pi.

## Introduction
This script is based on the blog post "[QH-832AC Door-bell modding](https://arduinodiy.wordpress.com/2015/03/02/qh-832ac-door-bell-moddinghttps://arduinodiy.wordpress.com/2015/03/02/qh-832ac-door-bell-modding)".

## Hardware
You'll need:
- [QH-832AC Doorbell from Quhwa](http://www.quhwa.com/Auto-learning-Code-Chimes-QH-832AC-g-72.html).
- [433 MHz RF transmitter, like this one](https://iprototype.nl/products/components/communications/rf-transmitter-434mhz)

## Installation
- [Install WiringPi](http://wiringpi.com/download-and-install/)
  - sudo apt-get install git-core
  - sudo apt-get update
  - sudo apt-get upgrade
  - git clone git://git.drogon.net/wiringPi
  - cd wiringPi
  - git pull origin
  - cd wiringPi
  - ./build
- Install WiringPi-SelectPlus doorbell:
  - git clone git://github.com/MPParsley/WiringPi-SelectPlus
  - cd WiringPi-SelectPlus
  - sudo g++ -o Ring ring.cpp -I/usr/local/include -L/usr/local/lib -lwiringPi

## Configuration
You can change the settings in the "config.ini" file:
- gpio: WiringPi Pin number (See http://wiringpi.com/pins/).
- timing: Pause in between rings (in microseconds).
- black, white: # Bell codes for respectively black and white doorbell.

## Testing
You can check if wiringPi’s installation succeeded by running the gpio command:
- gpio -v
- gpio readall

Run the Ring binary to test your doorbell setup using the "black" or "white" commandline argument:
- ./Ring black # To ring the black doorbell once.
- ./Ring white # To ring the white doorbell once.
- ./Ring black black white # To ring the black doorbell twice and the white doorbell once.

Note: make sure to ring once immediately after plugging in the doorbell to "pair" the device.
