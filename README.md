# Antenna Stepper Controller

Arduino/PlatformIO project for driving an antenna mount with stepper motors.

The project goal is to control antenna azimuth and elevation with two stepper
motors, each driven by a TMC2209 driver. The current firmware in `src/main.cpp`
is a safe single-motor test program: it drives one TMC2209 in STEP/DIR mode,
moves the motor from position `0` to `4000` steps, then returns to `0` in a
loop.

## Hardware Target

- Arduino Uno
- 1 stepper motor currently tested
- 1 TMC2209 stepper driver currently tested
- Future target: 2 stepper motors and 2 TMC2209 drivers for azimuth/elevation

## Current Pinout

The current firmware uses one driver:

| Signal | Arduino Uno Pin |
| --- | --- |
| DIR | `2` |
| STEP | `3` |
| ENABLE | `4` |

`ENABLE` is driven `LOW` in `setup()` to enable the TMC2209 driver.

## Current Firmware Behavior

On boot, the Arduino:

1. Enables the stepper driver.
2. Starts the serial port at `9600` baud.
3. Configures AccelStepper with:
   - Max speed: `1000` steps/second
   - Acceleration: `500` steps/second^2
4. Resets the current motor position to `0`.
5. Repeatedly:
   - Moves to `4000` steps.
   - Waits 1 second.
   - Moves back to `0`.
   - Waits 1 second.

Serial messages are printed during each movement so the behavior can be checked
with the PlatformIO serial monitor.

## Software Requirements

- PlatformIO
- Arduino framework for AVR
- `AccelStepper` library

The dependency is declared in `platformio.ini`:

```ini
lib_deps =
    waspinator/AccelStepper
```

## Build

From the project root:

```bash
pio run
```

## Upload to the Arduino Uno

Connect the Arduino Uno over USB, then run:

```bash
pio run -t upload
```

## Serial Monitor

The firmware uses `9600` baud:

```bash
pio device monitor -b 9600
```

## Project Structure

```text
.
|-- README.md
|-- platformio.ini
`-- src
    `-- main.cpp
```

## Roadmap

- Add the second TMC2209 driver.
- Add a second AccelStepper instance.
- Assign dedicated STEP/DIR/ENABLE pins for azimuth and elevation.
- Replace the current back-and-forth test loop with antenna positioning logic.
