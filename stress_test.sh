#!/bin/bash

ITERATIONS=100
DEVICE=/dev/ttyS0
LOGFILE="stress_$(date +%Y%m%d_%H%M%S).log"
BOOT_WAIT=5

cleanup() {
    kill "$CAT_PID" 2>/dev/null
    stty -F "$DEVICE" sane 115200
}
trap cleanup EXIT

stty -F "$DEVICE" 115200 raw -echo

cat "$DEVICE" >> "$LOGFILE" &
CAT_PID=$!

echo "=== boot stress test: $ITERATIONS iterations ==="
echo "log : $LOGFILE"

for i in $(seq 1 $ITERATIONS); do
    openocd -f interface/raspberrypi-swd.cfg -f target/rp2350.cfg \
        -c "init; reset run; exit" 2>/dev/null
    printf "[%3d/%d]\r" "$i" "$ITERATIONS"
    sleep "$BOOT_WAIT"
done

kill "$CAT_PID" 2>/dev/null
stty -F "$DEVICE" sane
echo ""

FAIL_LED=$(grep -c "ERROR: LED" "$LOGFILE")
FAIL_PROX=$(grep -c "ERROR: Proximity" "$LOGFILE")
FAIL_RTC=$(grep -c "ERROR: RTC" "$LOGFILE")
FAIL_SCREEN=$(grep -c "ERROR: Screen" "$LOGFILE")
TOTAL_FAIL=$((FAIL_LED + FAIL_PROX + FAIL_RTC + FAIL_SCREEN))
PERCENT=$(awk "BEGIN {printf \"%.1f\", $TOTAL_FAIL * 100 / $ITERATIONS}")

echo "=== résultats ==="
printf "LED not responding    : %d/%d\n" "$FAIL_LED"    "$ITERATIONS"
printf "Proximity not respond : %d/%d\n" "$FAIL_PROX"   "$ITERATIONS"
printf "RTC not responding    : %d/%d\n" "$FAIL_RTC"    "$ITERATIONS"
printf "Screen not responding : %d/%d\n" "$FAIL_SCREEN" "$ITERATIONS"
printf "Taux d'échec total    : %s%%\n"  "$PERCENT"
echo "log complet : $LOGFILE"
