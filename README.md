Indoor air quality matters more than ever — especially CO₂ levels, which strongly affect concentration, fatigue, and overall comfort. I wanted a compact, always-on desktop gadget that gives at-a-glance feedback using both a small OLED screen and a glowing LED ring.

This project combines the Infineon PAS CO₂ sensor, an ESP32-C3 Super Mini, a 0.96" OLED, and a 12-pixel NeoPixel ring, all inside a custom 3D-printed enclosure. It runs entirely from USB power and updates every 5 seconds.

Perfect for your desk, workshop, classroom, or even next to your gaming setup.

Setting up the CO₂ desktop display is straightforward. You’ll prepare the firmware in the Arduino IDE, flash the ESP32-C3, wire all components, and finally assemble the 3D-printed enclosure.

1. Install the Arduino IDE & ESP32 Board Package
Download and install the latest Arduino IDE.

Open Preferences → Additional Boards Manager URLs and add:

https://espressif.github.io/arduino-esp32/package_esp32_index.json

Go to Tools → Board Manager, search ESP32, and install “esp32 by Espressif Systems.”

2. Install Required Libraries
In Sketch → Include Library → Manage Libraries, install:

Adafruit SSD1306

Adafruit GFX

Adafruit NeoPixel

pas-co2-ino (Infineon PAS CO₂ sensor library)

After these are installed, restart the IDE if needed.

3. Flashing the ESP32-C3 Super Mini
Connect the ESP32-C3 Super Mini via USB-C.

Select the correct COM port under Tools → Port.

Set Board: ESP32C3 Super Mini

Click Upload and wait for flashing to complete.

Some C3 boards require pressing the BOOT button during the first upload; afterwards, it works automatically.

4. Wiring Everything Together
All modules in this build are powered directly from the ESP32-C3's 5V pin.
Only GND is shared across all components.

OLED (SSD1306, I2C)

VCC → 5V

GND → GND

SDA → GPIO 8

SCL → GPIO 9

Infineon PAS CO₂ sensor (I2C)

VCC → 5V

GND → GND

SDA → GPIO 8

SCL → GPIO 9

(Both sensors share the same I2C bus.)

LED NeoPixel Ring

5V → 5V

GND → GND

DIN → GPIO 3

Double-check that the LED ring’s arrow points away from DIN.

5. Printing the 3D Case
Print both case parts in PLA:

Bottom shell

Top lid with OLED window

Ensure the OLED opening prints cleanly so the display can slide into place.

6. Final Assembly
Place the electronics inside the bottom part:

ESP32-C3

CO₂ sensor

Glue the LED ring into the slot.

Slide the OLED into the front window of the lid — it should fit snugly along the printed rails.

Apply a small amount of glue to the lid perimeter and press it onto the bottom shell.

Route the USB-C cable through the rear opening and plug it into the ESP32-C3.

And voilà , once powered, the OLED should show boot messages and the LED ring will light up immediately.
