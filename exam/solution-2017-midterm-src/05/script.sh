#!/bin/bash
T=$1
while true
do
    sleep $(expr $T / 1000)
    echo 0 > /sys/class/leds/beaglebone:green:usr3/brightness
    sleep $(expr $T / 1000)
    echo 255 > /sys/class/leds/beaglebone:green:usr3/brightness
done
