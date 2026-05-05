# Antenna Stepper Controller

Arduino/PlatformIO project for driving an antenna mount with stepper motors.

The project goal is to control antenna azimuth and elevation with two stepper
motors, each driven by a TMC2209 driver. The current firmware in `src/main.cpp`
is a safe two-motor test program: it drives both TMC2209s in STEP/DIR mode,
moves each motor to a target position, then returns to `0` in a loop.

## Hardware Target

- Arduino Uno
- 2 stepper motors (stepper1 = elevation, stepper2 = azimuth)
- 2 TMC2209 stepper drivers

## Pinout

### stepper1 — Elevation

| Signal | Arduino Uno Pin |
| --- | --- |
| DIR | `2` |
| STEP | `3` |
| ENABLE | `4` |

### stepper2 — Azimuth

| Signal | Arduino Uno Pin |
| --- | --- |
| DIR | `7` |
| STEP | `6` |
| ENABLE | `5` |

`ENABLE` est mis à `LOW` dans `setup()` pour activer chaque driver TMC2209.

## Current Firmware Behavior

On boot, the Arduino:

1. Enables both stepper drivers.
2. Starts the serial port at `9600` baud.
3. Configures stepper1 (elevation) with:
   - Max speed: `1000` steps/second
   - Acceleration: `500` steps/second^2
4. Configures stepper2 (azimuth) with:
   - Max speed: `300` steps/second
   - Acceleration: `100` steps/second^2
5. Resets both motor positions to `0`.
6. Repeatedly:
   - Moves stepper1 to `4000` steps, then waits for stepper2 to reach `200` steps.
   - Waits 1 second.
   - Returns stepper1 to `0`, then returns stepper2 to `0`.
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

- Replace the current back-and-forth test loop with real antenna positioning logic.
- Drive both motors concurrently (non-blocking `run()` calls) instead of sequentially.
