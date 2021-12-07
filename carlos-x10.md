# NEW-X Automation Board Software Developer's Guide

> NOTE: All software development instructions are tested under Linux (Ubuntu 21.04) and MacOS (Big Sur).


## Power Supply

Safe input voltage range is,

* DC 15V -- 30V
* AC 12V -- 24V

## Pinmap

### Directly wired to ESP32-WROVER

Symbol | Pin | Description
-------|-----|------------
UART3_TX | 33 | TX for RS485
UART3_RX | 12 | RX for RS485
UART3_EN | 13 | RS485 enabled on H, disabled on L
UART2_TX | 4 | TX for Tuya module
UART2_RX | 15 | RX for Tuya module
INTR_0 | 25 | Interrupt from U6, MCP23017
INTR_1 | 26 | Interrupt from U7, MCP23017
INTR_2 | 27 | Interrupt from U8, MCP23017
PSENSE_1 | 36 | Analog voltage sensing of power input 1
PSENSE_2 | 39 |  Analog voltage sensing of power input 2
IR_0 | 34 | Digital IO for 3-pin sensor port
IR_1 | 35 | Digita IO of 4-pin sensor port
IR_2 | 32 | Digita IO of 4-pin sensor port
RFDATA | 14 | Digital IO of 433MHz RF receiver

### U6, MCP23017

Symbol | Pin | Description
-------|-----|------------
RELAY_0 | 0 | Digital Output for Relay
RELAY_1 | 1 | Digital Output for Relay
RELAY_2 | 2 | Digital Output for Relay
RELAY_3 | 3 | Digital Output for Relay
RELAY_4 | 4 | Digital Output for Relay
RELAY_5 | 5 | Digital Output for Relay
RELAY_6 | 6 | Digital Output for Relay
RELAY_7 | 7 | Digital Output for Relay
RELAY_8 | 8 | Digital Output for Relay
RELAY_9 | 9 | Digital Output for Relay
RELAY_10 | 10 | Digital Output for Relay
RELAY_11 | 11 | Digital Output for Relay

### U7, MCP23017

Symbol | Pin | Description
-------|-----|------------
IN_0 | 0 | DIgital Input via photocoupler
IN_1 | 1 | DIgital Input via photocoupler
IN_2 | 2 | DIgital Input via photocoupler
IN_3 | 3 | DIgital Input via photocoupler
IN_4 | 4 | DIgital Input via photocoupler
IN_5 | 5 | DIgital Input via photocoupler
IN_6 | 6 | DIgital Input via photocoupler
IN_7 | 7 | DIgital Input via photocoupler
IN_8 | 8 | DIgital Input via photocoupler
IN_9 | 9 | DIgital Input via photocoupler
IN_10 | 10 | DIgital Input via photocoupler
IN_11 | 11 | DIgital Input via photocoupler
IN_14 | 14 | DIgital Input via photocoupler
IN_15 | 15 | DIgital Input via photocoupler
IN_16 | 16 | DIgital Input via photocoupler
IN_17 | 17 | DIgital Input via photocoupler

### U8, MCP23017

Symbol | Pin | Description
-------|-----|------------
BUZZER | 0 | Digital Output of Buzzer
LOGOLED_R | 1 | Digital Output for Logo LED Red
LOGOLED_G | 2 | Digital Output for Logo LED Green
LOGOLED_B | 3 | Digital Output for Logo LED Blue
LOGOLED_W | 4 | Digital Output for Logo LED White
IN_12 | 8 | Digital Input via photocoupler
IN_13 | 9 | Digital Input via photocoupler
SW_1 | 10 | Digital Input of tacktile switch
SW_2 | 11 | Digital Input of tacktile switch
SW_3 | 12 | Digital Input of tacktile switch
SW_4 | 13 | Digital Input of tacktile switch

## USB Serial Programming

1. Power on the board.
2. Connect the board to computer via USB.
3. Check if the USB-Serial adapter is recognized. Run `lsusb` command on shell to see if the "CH340" is present.
4. Install [Arduino IDE](https://www.arduino.cc/en/software).
5. Install [ESP32 Support](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html) on Arduino.
6. Create and edit `blink.ino` on Arduino IDE.
7. Select "ESP32 Wrover Dev Module" from Arduino's Tools menu.
8. Select the present serial port from Arduino's Tools menu. On Linux, it is named like `/dev/ttyUSB0`.
9. Upload sketch and test if all run successfully.

```c
/* NEW-X Automation Spike: Blinking TX LED */

#define UART3_TX 33

void setup() {
    pinMode(UART3_TX, OUTPUT);
}

void loop() {
    digitalWrite(UART3_TX, HIGH);
    delay(500);
    digitalWrite(UART3_RX, HIGH);
    delay(500);
}
```


## IO Expander Driving

There are many ways to accomplish this. Here's just one method tested working.

1. Install [Adafruit MCP23017](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library) library on Arduino via Library manager.
2. Include and use `Adafruit_MCP23X17.h` header file, as MCP23017 is used on board.
3. After uploading the following sketch, test if the Relays are working.

```c
/* NEW-X Automation Spike: IO Expander */

#include <Wire.h>
#include <Adafruit_MCP23X17.h>

/*  U6, MCP23017, 0x20 */
Adafruit_MCP23X17 u6;

void test_relays() {
   for (int i = 0; i < 12; i++) {
        u6.digitalWrite(i, HIGH);
        delay(800);
        u6.digitalWrite(i, LOW);
    }
}

void setup() {
    u6.begin_I2C(0x20);
}

void loop() {
    test_relays();
}
```

For more information, see the `spike.ino` source code.


## Ethernet Communication

The board is using W5500 SPI Ethernet controller chip.

1. Install [Ethernet Library](https://www.arduino.cc/en/Reference/Ethernet) via Arduino Labrary Manager.
2. Upload the `spike-eth.ino` sketch.
3. Open the serial terminal and set the baurdrate as 115200, watch the logs.

For more information, see the source code of `spike-eth.ino` and examples of [Ethernet Library](https://www.arduino.cc/en/Reference/Ethernet)
