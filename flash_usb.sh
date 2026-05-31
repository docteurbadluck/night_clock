#!/bin/sh

#Ne fonctionne que si usb is enable in CMakeLists !
build_and_flash() {
    cd ~/pico/theo/C++/night_clock/build && cmake .. -G Ninja -DSTART_TIME="$(date +%H:%M:%S)" && ninja || return 1
    picotool reboot -f -u
    sleep 2
    picotool load -f -v ~/pico/theo/C++/night_clock/build/night_clock.uf2 || return 1
    picotool reboot
}

if build_and_flash; then
    sleep 3
    clear
    cat /dev/ttyACM0
fi
