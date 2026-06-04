#!/bin/sh

build_and_flash() {
    cd ~/pico/theo/C++/night_clock/build && cmake .. -DSTART_TIME="$(date +%H:%M:%S)" && ninja || return 1

    openocd -f interface/raspberrypi-swd.cfg -f target/rp2350.cfg \
        -c "program /home/raspi1/pico/theo/C++/night_clock/build/night_clock.elf verify reset exit" || return 1
}

if build_and_flash; then
    sleep 1
    clear
    stty -F /dev/ttyS0 115200
    cat /dev/ttyS0
fi
