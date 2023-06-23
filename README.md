# Medication Reminder System

This project is a medication reminder system that helps users manage their medication schedule and doses. The system utilizes an Arduino board, an RTC (Real-Time Clock) module, a keypad, and an LCD display.

## Features

- Set morning, lunch, and night doses with customizable time and quantity.
- Choose between regular or personalized dosage schedules.
- Personalize dosage schedule for each day of the week.
- Display remaining doses for each day on an LCD screen.
- Add and remove doses from the schedule.

## Hardware Requirements

- Arduino board
- RTC module (DS3231)
- Keypad
- LCD display (I2C compatible)

## Software Libraries

- RTClib: Library for accessing and controlling the RTC module.
- Wire: Arduino's built-in library for I2C communication.
- LiquidCrystal_I2C: Library for controlling LCD displays using I2C communication.
- Keypad: Library for interfacing with matrix keypads.

## Circuit Connection

The hardware components should be connected as follows:

- RTC module:
  - SDA pin to Arduino A4 pin
  - SCL pin to Arduino A5 pin
  - VCC pin to 5V
  - GND pin to GND

- LCD display:
  - SDA pin to Arduino A4 pin
  - SCL pin to Arduino A5 pin
  - VCC pin to 5V
  - GND pin to GND

- Keypad:
  - Connect each keypad pin to its corresponding Arduino pin.

## Guide 

- Connect the Arduino board to your computer and upload the code.

- Make sure all the hardware components are properly connected.

- The LCD display will show the current day and the remaining doses for that day.

- Use the keypad to navigate through the menu and set the desired dosage schedule.

- Press the 'A' key to set the morning dose, 'B' for lunch dose, and 'C' for night dose.

- Use the keypad to enter the desired time and quantity for each dose.

- Press the '#' key to confirm and move to the next dose.

- To personalize the dosage schedule, press the 'B' key and follow the on-screen instructions.

- To add or remove doses, follow the on-screen instructions and use the keypad to enter the required information.

- The LCD display will continuously show the current day and the remaining doses for that day.

## Contributing

Contributions to this project are welcome. If you have any suggestions, bug reports, or feature requests, please open an issue or submit a pull request.

