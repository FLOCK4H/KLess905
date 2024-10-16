# KLess905

Jammer device for 433.92Mhz frequency, a frequency on which many car key fobs (European) and IoT devices operate.
When jamming radio controlled home weather station you may observe that the temperature does not change at all, furthermore, car keys tend to become useless after split second, the garage won't open, and neither will gate. 

> [!NOTE]
> NRF905 can operate on 433/868/915Mhz, which means that **all these frequencies can be jammed by NRF905**

# Usage

Project is written in pure **Arduino C**, no libraries are needed.

There's no need to clone this repository, simply:

1. Download Arduino IDE: [Arduino](https://www.arduino.cc/en/software)
2. Open Arduino IDE, create new sketch `File->New Sketch`
3. Open preferences `File->Preferences`
4. Add your board's manager URL (you can find online by searching `Arduino for "YourBoard"`
For ESP32 -> https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
6. Connect NRF905 to your board

Needed pins are:
- VCC
- TXEN
- CE
- PWR
- MISO
- MOSI
- SCK
- CSN
- 1x GND (2nd GND not needed, but also ok)

![image](https://github.com/user-attachments/assets/48a8b711-81ff-4226-8d18-879a299ed2f5)

6. Copy `KLess905.ino` contents, paste them into the sketch
7. Modify GPIO pin references to yours
8. Press Compile & Upload
9. Next time you power your board, the NRF will jam the 433.92Mhz frequency
10. Use it responsibly!

**Range: 2 meters from the remote control pointed directly, and being very close to the receiver. Effective jamming range is about 10m around, receiving (correct & full) signal in the way where jamming occurs is impossible.**

> [!CAUTION]
> Project was made for educational purposes, any use outside of that context may result in legal consequences, jamming is illegal in most countries. Always assert permission to perform penetration testing!
