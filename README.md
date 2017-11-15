# ESP8266-RCWL0516

This is an ESP8266 project that uses a RCWL0516 microwave presence sensor. The code is capable of detecting the state of the sensor by utilizing either polling or interrupts. The circuit utilizes *opto-coupling* to isolate the sensor from the ESP8266.

# History

The RCWL-0516 is a sensor that I wanted to try out. I intend to use it in applications where I wanted to sense the presence of a person or an animal (like my dog!) and trigger an event or action. I initially investigated the use of a PIR, but they are incapable of sensing through barriers such as glass or a wooden door.

In addition to the use of the RCWL-0516 I also wanted to experiment with opto-coupling the sensor output to the ESP8266 GPIO.

I also wanted to investigate polling vs interrupts on the ESP8266. The sketch in this repository is capable of using either method for detecting changes on an input.

# Running the Application

The code is not dependent on the type of the sensor. It could be used with any sensor or switch that is capable of producing a logic `1` or `0` on an input of the ESP8266. The only modifications the *might* be necessary are - 

* Modifying the input pin, the currently used pin is set with `#define SENSOR_PIN D2` in the sketch file.
* Modifying the polarity of whether the input is "active" or "idle". The circuit (*as described below*) and code assumes that the sensor is "active" when the input is "low".

Use the Arduino IDE to build and download the sketch to the ESP8266. If the circuit (*described below*) is used the expected output in the console is - 

```
interr - ACTIVE
interr - IDLE
```

When `interr - ACTIVE` is seen the on-board LED will be lit. And when `interr - IDLE` is seen the LED will be off.

## The Circuit

Parts Needed :

* RCWL-0516 microwave presence sensor
* ESP8266 NodeMCU v1.0
* NTE3042 Opto-coupler (*or equivalent*)
* 100k resistor
* 4.7k resistor
* 5v power supply to power the sensor and input of the opto-coupler
* 5v supply to power the ESP8266 and the output of the opto-coupler
* Solderless bread board

Miscellaneous/Option Parts :

* 5 pin solder-in header, I used a right-angle pin header.
* Male/Female jumper wires
* Housing/case for the RCWL-0516. I used an old CF memory card case that I modified slightly to contain the board.
* Mini clamps, used for holding the CF card case and standing it up vertically.

*Component sources will be listed near the end of this document.*

### Schematic

### Finished Breadboard

<p align="center">
  <img src="./mdimg/bb-01.png" alt="NTE 6 pin IC package" txt="NTE 6 pin IC package" style="border: 2px solid black;width:400px"/>
</p>

**NOTES :** The NTE3042 chips I used didn't have the typical pin 1 markings. Most IC's will have a small dimple on the top that marks pin 1. However the NTE3042 chips have the left edge (*looking down*) corner removed. And unfortunately the resulting notch is very small and difficult to see without magnification. Here's a diagram that might provide a better description :

<p align="center">
  <img src="./mdimg/ic-6-pin-all-nte.png" alt="NTE 6 pin IC package" txt="NTE 6 pin IC package" style="border: 2px solid black"/>
</p>

### RCWL0516 Details

### Testing the Circuit

## Download & Run

# Code Details

# Component Sources

## Component Data Sheets

# Build Details

# Recommended Reading
