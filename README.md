# Blinky using freeRTOS
## Description
This code is just a simple blinky program made with tasks in freeRTOS.

## Hardware
The connections are showed at the diagram below:
```
ESP32      Hardware      Config
---------------------------------
PIN14      RED_LED       OUTPUT
PIN26      YELLOW_LED    OUTPUT
PIN25      PUSH_BUTTON   INPUT_PULLUP
```

## Working principle
Working principle is simple. The red LED is blinking every 1 second and yellow LED is blinking every 
1/4 second, but only if you press and hold the button.\
For this purpose I have created 2 tasks pinned to core 0. They are responsible for handling diodes.
The while loop in app_main() is responsible for handling button input (changing the value of global variable, yhat is controlling yellow diode task).




##
Author: Mateusz Szpot \
Date: 14.02.2025
