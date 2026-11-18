# OLED Pixel Art Display — SSD1306

This project is intended to draw a 128×64 bitmap on an SSD1306 I²C OLED and animate it sliding in from the right after reset. The currently confirmed firmware file targets an STM32 Blue Pill.

## Current repository status — build blockers

The checked-in files do not currently support the complete Arduino Uno workflow described in the older README:

- `STM32_BluePill/STM32_BluePill.ino` is present and is the firmware file inspected for this review.
- The documented `Arduino_Uno_FY.ino` was not found at the repository root or under `Arduino_Uno/` during this review.
- The STM32 sketch includes `../../assets/image_bitmap.h`, but the referenced bitmap header and `assets/image_bitmap.h` were not found in the checked-in paths inspected. The sketch relies on `myImage`, `IMG_WIDTH`, and `IMG_HEIGHT` from that header, so it is not buildable from the confirmed files as they currently stand.

The firmware was deliberately left unchanged. Restore the intended bitmap header and correct its include path, and restore the Uno sketch if that target is still supported, before treating this repository as a buildable project.

## Confirmed STM32 hardware and wiring

| OLED connection | STM32 Blue Pill connection |
|---|---|
| SDA | PB7, as noted in the sketch comments |
| SCL | PB6, as noted in the sketch comments |
| VCC | **3.3 V only** |
| GND | GND |

The source configures a 128×64 display and I²C address `0x3C`. Confirm your OLED module's controller, address, and wiring before powering it. Do not apply 5 V to the OLED VCC; the checked-in STM32 sketch explicitly specifies 3.3 V only.

## Required software

- Arduino IDE
- STM32duino board support for the STM32 Blue Pill target
- Adafruit SSD1306 library
- Adafruit GFX Library
- `Wire`, provided by the selected board core

## Intended animation

The STM32 sketch calls `Wire.begin()`, initializes the SSD1306 display, and halts in a loop if display initialization fails. Its slide-in routine draws the bitmap at decreasing x positions from the screen width to zero, stepping by four pixels with a 15 ms delay, then redraws it at the origin. The image remains on screen until reset. The bitmap dimensions and data are expected from the missing header, so the animation cannot be built from the confirmed checkout yet.

## Build and upload status

Do not treat the current checkout as ready to upload. After the missing bitmap header and include path have been repaired in a future code change:

1. Install Arduino IDE, STM32duino board support, Adafruit SSD1306, and Adafruit GFX.
2. Open `STM32_BluePill/STM32_BluePill.ino`.
3. Select the correct STM32 Blue Pill board variant and serial port for your hardware.
4. Compile before connecting the OLED; resolve missing-header or board-core errors first.
5. Wire the OLED using the 3.3 V table above and upload only after the sketch compiles.

The earlier Arduino Uno upload steps are not currently actionable because the documented Uno sketch was not found at the checked paths. No firmware compilation, upload, or physical OLED test was performed during this review.

## Troubleshooting after the missing files are restored

- **Blank OLED:** verify SDA/SCL, common ground, supply voltage, and the configured I²C address (`0x3C`).
- **Compilation fails on `image_bitmap.h`:** the required bitmap header is absent from the confirmed checkout or the include path does not point to it.
- **Display initialization halts:** the source enters an infinite loop if `display.begin()` fails; check wiring, power, controller compatibility, and address.

## License

No root `LICENSE` file was found during this review. Confirm and add the intended license before redistributing the project.

---

## Maintenance & Audit

- **Audit date:** 18 November 2026
- **Documentation status:** README reviewed and audit record updated on this date.
- **Scope and evidence:** Documentation review of the README and `STM32_BluePill/STM32_BluePill.ino`; the documented Uno sketch and bitmap-header paths were checked and not found at the expected locations.
- **Code and tests:** No firmware was changed; no compile, upload, or hardware test was performed.
- **Maintenance baseline:** Documentation status recorded through 18 November 2026; recheck the missing bitmap header, include path, and intended Uno target when the repository changes.
