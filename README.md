 OLED Pixel Art Display — Arduino Uno
 
Display a pixel art image on an SSD1306 OLED with a smooth right-to-left slide-in animation on every reset.
 
---
 
## Preview
 
```
┌─────────────────────────────┐
│  ┌──────────────────────┐   │
│  │  your bit map            │   │
│  └──────────────────┘   │   │
│            └─┘           │   │
└─────────────────────────────┘
        SSD1306 OLED
```
 
---
 
## Hardware Required
 
| Component | Quantity |
|---|---|
| Arduino Uno | 1 |
| SSD1306 OLED Display (128×64, I2C) | 1 |
| Jumper Wires | 4 |
 
---
 
## Wiring
 
| OLED Pin | Arduino Uno Pin |
|---|---|
| VCC | 3.3V or 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |
 
---
 
## Libraries
 
Install both via Arduino IDE — Sketch → Include Library → Manage Libraries:
 
- **Adafruit SSD1306**
- **Adafruit GFX Library**
 
---
 
## How to Flash
 
1. Open `Arduino_Uno_FY.ino` in Arduino IDE.
2. Connect the Arduino Uno via USB.
3. Select board: **Tools → Board → Arduino Uno**.
4. Select the correct port: **Tools → Port → COMx** (Windows) or **/dev/ttyUSB0** (Linux/Mac).
5. Click **Upload**.
 
---
 
## How It Works
 
On every reset or power-on, the sketch runs `setup()` which triggers the slide-in animation.
 
The image bitmap is stored as a 1024-byte array in flash memory using `PROGMEM`. Each byte encodes 8 horizontal pixels, MSB first. The 128×64 image is drawn using `drawBitmap()` from the Adafruit GFX library.
 
The animation works by drawing the bitmap at a decreasing x-offset:
 
```cpp
for (int x = 128; x >= 0; x -= 4) {
    display.clearDisplay();
    display.drawBitmap(x, 0, myImage, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    display.display();
    delay(15);
}
```
 
The image starts fully off-screen to the right at x = 128 and moves left in steps of 4 pixels with a 15ms delay per frame. Total animation time is approximately 500ms. Once the image reaches x = 0 it stays displayed until the next reset. `loop()` is intentionally empty.
 
---
 
## Customizing the Image
 
To use your own image:
 
1. Resize it to exactly **128 × 64 pixels** in any image editor.
2. Open [image2cpp](https://javl.github.io/image2cpp/) in a browser.
3. Use these settings:
   - Canvas size: `128 x 64`
   - Invert image: **ON** if your image has dark content on a light background
   - Code format: `Arduino code`
   - Draw mode: `Horizontal — 1 bit per pixel`
4. Click **Generate code** and copy the array.
5. Replace the `myImage[]` array in the sketch with the copied output.
 
---
 
## Adjusting Animation Speed
 
| Parameter | Effect |
|---|---|
| Increase step size (e.g. `x -= 8`) | Faster slide |
| Decrease step size (e.g. `x -= 2`) | Slower, smoother slide |
| Increase `delay(15)` | Slower slide |
| Decrease `delay(15)` | Faster slide |
 
---
 
## Troubleshooting
 
| Symptom | Fix |
|---|---|
| Blank screen | Check SDA→A4, SCL→A5 wiring |
| Wrong I2C address | Change `0x3C` to `0x3D` in the sketch |
| Image looks inverted | Swap `WHITE` to `BLACK` in both `drawBitmap()` calls |
| Compilation error | Confirm both Adafruit libraries are installed |
 
---
 
## License
 
MIT — free to use, modify, and distribute.
## For more info or help please contact Carmodbhai@gmaol.com


---

## Skills & technologies

`Arduino/C++`


## Repository structure

Key files and folders (not exhaustive):

- `README.md`
- `STM32_BluePill/STM32_BluePill.ino`


## Maintenance & Audit

- **Audit date:** 11 November 2026
- **Documentation status:** README reviewed and audit record added on this date.
- **Scope and evidence:** This is a documentation-level maintenance pass. It does not establish that source code compiles, dependencies are current, security has been tested, or hardware/runtime behavior has been verified.
- **Code and tests:** No new functional code changes or test results are claimed by this README update. Run project-specific build, test, and hardware/runtime checks before relying on the project.
- **Maintenance baseline:** Documentation status recorded through 11 November 2026; revisit setup instructions, dependencies, known limitations, and tests when the project changes.
