# Night Clock

<img width="400" height="446" alt="showcase" src="https://github.com/user-attachments/assets/dec2e177-5023-448b-905f-f24ea9784bf1" />

<img width="2505" height="1822" alt="IMG_20260604_141542099_MFNR~2" src="https://github.com/user-attachments/assets/27befef9-3e25-40a8-90ad-199b31f5424d" />

<img width="2855" height="2397" alt="IMG_20260604_143532136_MFNR" src="https://github.com/user-attachments/assets/ff9cd25e-e5ad-4c8e-83bd-ac992a46a71d" />

A clock built on a Raspberry Pi Pico 2 W which, displays time on an OLED screen and automatically controls a LED stripe based on proximity detection. The entire system runs off a single power supply.

## Hardware
| Component | Role |
|---|---|
| Raspberry Pi Pico 2 W | MCU |
| SSD1306 128×32 | OLED display |
| HW-84 (DS1307) | Real-time clock |
| HC-SR04 | Proximity sensor |
| IRLZ44N + LED strip (12V) | PWM-controlled backlight |
| LM2596 buck converter | 12V → 5V for the Pico (single supply system) |
| 3× 1Ω shunt resistor | LED current measurement via ADC |

## Architecture

Clean layered architecture — drivers depend only on abstract interfaces, making each layer independently testable.

```
0_orchestration/   — init, main loop, self-tests
1_domain/          — business logic, Context, Time
2_usecases/        — UpdateTime, DisplayTime, DetectProx, StartLight
3_interface/       — abstract interfaces (Clock, Screen, PWM, ProxDetector)
4_drivers/         — SSD1306, RTC_HW84, HC-SR04, pico_pwm
```

## Self-Test & Stress Test

Every boot runs a `selfTest()` on each component. The RTC writes and reads back a time to verify I2C. The LED measures actual current through a shunt resistor to detect wiring faults.

`stress_test.sh` automates 100 reboots via OpenOCD (SWD) and reports per-component failure rates.

demo  
https://github.com/user-attachments/assets/da2e25bb-6378-472a-8790-5f3e0d6c1971


## Schematic
[output.pdf](https://github.com/user-attachments/files/28601989/output.pdf)

## Build & Flash

```bash
./flash_swd.sh   # via SWD (Raspberry Pi GPIO)
./flash_usb.sh   # via USB
```

Both scripts inject the current time at compile time via `-DSTART_TIME`.

## Dependencies

- [Pico SDK](https://github.com/raspberrypi/pico-sdk)
- [pico-ssd1306](https://github.com/daschr/pico-ssd1306)
