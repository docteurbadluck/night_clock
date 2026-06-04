#!/bin/bash

ITERATIONS=100
DEVICE=/dev/ttyS0
LOGFILE="stress_$(date +%Y%m%d_%H%M%S).log"
BOOT_WAIT=5
CAT_PID=""

init() {
    stty -F "$DEVICE" 115200 raw -echo
    cat "$DEVICE" >> "$LOGFILE" &
    CAT_PID=$!
    echo "=== boot stress test: $ITERATIONS iterations ==="
    echo "log : $LOGFILE"
}

run_reboots() {
    for i in $(seq 1 $ITERATIONS); do
        openocd -f interface/raspberrypi-swd.cfg -f target/rp2350.cfg \
            -c "init; reset run; exit" 2>/dev/null
        printf "[%3d/%d]\r" "$i" "$ITERATIONS"
        sleep "$BOOT_WAIT"
    done
    echo ""
}

print_results() {
    local fail_led fail_prox fail_rtc fail_screen total percent
    fail_led=$(grep -c "ERROR: LED" "$LOGFILE")
    fail_prox=$(grep -c "ERROR: Proximity" "$LOGFILE")
    fail_rtc=$(grep -c "ERROR: RTC" "$LOGFILE")
    fail_screen=$(grep -c "ERROR: Screen" "$LOGFILE")
    total=$((fail_led + fail_prox + fail_rtc + fail_screen))
    percent=$(awk "BEGIN {printf \"%.1f\", $total * 100 / $ITERATIONS}")

    echo "=== résultats ==="
    printf "LED not responding    : %d/%d\n" "$fail_led"    "$ITERATIONS"
    printf "Proximity not respond : %d/%d\n" "$fail_prox"   "$ITERATIONS"
    printf "RTC not responding    : %d/%d\n" "$fail_rtc"    "$ITERATIONS"
    printf "Screen not responding : %d/%d\n" "$fail_screen" "$ITERATIONS"
    printf "Taux d'échec total    : %s%%\n"  "$percent"
    echo "log complet : $LOGFILE"
}

cleanup() {
    kill "$CAT_PID" 2>/dev/null
    stty -F "$DEVICE" sane 115200
}

trap cleanup EXIT

init
run_reboots
print_results
