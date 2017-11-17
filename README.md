# ESP8266-RCWL0516

This is an ESP8266 project that uses a RCWL0516 microwave presence sensor. The code is capable of detecting the state of the sensor by utilizing either polling or interrupts. The circuit also utilizes *opto-coupling* to isolate the sensor from the ESP8266.

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

When `interr - ACTIVE` is seen the on-board LED will be lit. And when `interr - IDLE` is seen the LED will be off. And `ACTIVE` will indicate that something has triggered the sensor.

## The Circuit

Parts Used :

* RCWL-0516 microwave presence sensor
* ESP8266 NodeMCU v1.0
* NTE3042 Opto-coupler (*or equivalent*)
* 100k resistor
* 4.7k resistor
* Two individual power sources - 
    * 5v power supply to power the sensor
    * 5v supply to power the ESP8266, I used the board's USB connection.
* A solderless bread board
* Bread board jumper wires
* Lead-free solder

Miscellaneous/Optional Parts :

* 5 pin solder-in header, I used a right-angle 5 pin header.
* Male/Female jumper wires, for connecting the sensor to the rest of the circuit.
* Housing/case for the RCWL-0516. I used an old CF memory card case that I modified slightly to contain the board.
* Mini clamps, used for holding the CF card case and standing it up vertically.

Tools Used :

* Small needle-nose pliers
* Small wire cutter
* Voltmeter
* Soldering iron

*Component sources will be listed near the end of this document.*

### Schematic

Here's a basic schematic of the circuit - 

<p align="center">
  <img src="./mdimg/schem-01.png" alt="Circuit Schematic" txt="Circuit Schematic" style="border: 2px solid black;width:400px"/>
</p>

The output of the opto-coupler is wired as *open collector*, which explains the need for a pull-up resistor to bring the voltage up when the sensor is inactive (*idle*). The use of the inverted logic has an advantage, the input value on `D2` can be used directly to turn the LED on or off. 

| Sensor Output | Opto Output | Active State Value | LED |
|:-------------:|:-----------:|:------------------:|:---:|
|      3.3v     |     GND     |          0         |  ON |
|      GND      |     OPEN    |          1         | OFF |

### Assembling the Parts

**IMAGE OF PARTS LAID OUT**

* RCWL-0516
* 5 pin header

If you are using a *male* header on the sensor it's likely you'll have to cut the length you need from a larger header. Use the small wire cutter and place the cutting edge in the small groove between the pins.

**IMAGE OF CUTTING PIN HEADER**


### Finished Breadboard

<p align="center">
  <img src="./mdimg/bb-01.png" alt="NTE 6 pin IC package" txt="NTE 6 pin IC package" style="border: 2px solid black;width:400px"/>
</p>

**NOTES :** The NTE3042 chips I used didn't have the typical pin 1 markings. Most IC's will have a small dimple or a printed dot on the top corner that marks pin 1. However the NTE3042 chips have the left edge (*looking down*) corner removed. And unfortunately the resulting notch is very small and difficult to see without magnification. Here's a diagram that might provide a better description :

<p align="center">
  <img src="./mdimg/ic-6-pin-all-nte.png" alt="NTE 6 pin IC package" txt="NTE 6 pin IC package" style="border: 2px solid black"/>
</p>

So you might be wondering "*why the NTE3042?*". Well I happened to be in a local electronics store and it was the *only* opto-coupler they had in stock. And I didn't want to wait for an online order to be delivered, and at about $2 each I figured "why not?". And I was lucky that day, the part worked perfectly for this project.

I recommend that you use at least 12 to 18 inches of wire to connect the sensor to the bread board. And keep it separated from the NodeMCU. I've read that the radio frequency used by the sensor (*in the gigahertz range*) conflicts with the 2.4Ghz signal used by the WiFi on the NodeMCU board.

### RCWL0516 Details

The RCWL-0516 sensors are relatively inexpensive. I found them online at 5 for about $10 ($2 each). When they arrived they needed to be "snapped apart". It's typical for smaller electronic boards to be manufactured this way. It makes them easier to assemble. There may also be a small piece to snap off where the connection holes are.

**IMAGE OF BOARDS TOGETHER**

So you may have to separate them. It's not difficult but I recommend being careful. It's easiest if you have a sturdy hold on two adjacent boards and then gently bend at the edge where they're attached to each other.

For my purposes I decided that I wanted a 5 pin *right angle* pin header on the board. In my opinion it's a better option compared to soldering wires directly to the board.

**IMAGE OF BOARD WITH AND WITHOUT HEADER**

My next step was to find a way where I could either mount the board onto something or enclose it in some type of container. So after rummaging through my bits and pieces I found an old CF memory card case. And as it turns out it needed only minor modifications and the board with the connector fit it perfectly.

**IMAGE OF CASE, DETAILS OF MOD, AND WITH BOARD INSIDE**

Now that I had the sensor in a case I needed a way to stand it up or attach it to something. For attaching it to a window or a door *painter's tape* works very well. For standing it upright on a table I used some platic mini-clamps that I found a local tool supply store.

**IMAGE OF SENSOR WITH CLAMPS & ATTACHED WIRES**

### Testing the Circuit

Although I've had luck with the 5 sensors I bought I've read reviews where other have had problems. For example, I read a few reviews stated that the board output would be at 5v when the sensor was activated. However it's supposed to be 3.3v! And that was enough reason for me to use the opto-coupler and test the circuit before connecting it to my NodeMCU.

Testing was simple and only required the use of a voltmeter. First I tested the RCWL-0516 independantly and verified that it's output pin produced either 3.3v (*approximately*) or it would be at `gnd`. Then I assembled the opto-couple portion of the circuit with the sensor attached. Trial and error and some guessing helped me determine that I needed a 100k pull-up resistor to 3.3v on the connection between the NTE3042 (*opto-coupler*) and the NodeMCU.

## Download & Run

Assuming that you've assembled and tested the circuit it's time to try out the code! After the sketch has been compiled and downloaded the on-board LED of the NodeMCU *might* be lit when the program starts. If so just wait about 5 to 10 seconds and it should turn off. When it turns off the sensor has not detected any presence.

Please keep in mind that the sensor is quite sensitive. And a minor amount of movement within its range will activate it. 

When the LED is off try waving your hand in front of the sensor (*the side with the components*) and the LED should light up and you should see `interr - ACTIVE` on the IDE console. Wait about 5 to 10 seconds and the LED should turn off and `interr - IDLE` will be seen on the console.

# Code Details

There are two methods of state-change detection in this sketch :

* Polled - The input pin is read in the loop() function and if the current input state doesn't match the last changed state then announce the change and save the state.
* Interrupt - There are two methods used here for invoking an input interrupt when the input state changes :
    * Interrupt on a Level, toggle between levels on subsequent level changes.
    * Interrupt on Change

## Polling for State Change

## Interrupt on State Change

### The Need for Debouncing



# Component Sources



# Build Details


# Future Modifications

* [DCH010505S Miniature, 1W, 3kVDC Isolated DCDC Converters](http://www.ti.com/product/dch010505s?qgpn=dch010505s)
* [DCH010505SN7 Texas Instruments Power Supplies - Board Mount DigiKey](https://www.digikey.com/products/en?keywords=DCH010505S)


# Links and References

## NodeMCU

* [NodeMCU Dev Kit](https://github.com/nodemcu/nodemcu-devkit-v1.0)
* [NodeMCU Documentation](https://nodemcu.readthedocs.io/en/master/)

## Interrupts

* [Arduino - AttachInterrupt](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)
* [Gammon Forum Electronics Microprocessors Interrupts](http://gammon.com.au/interrupts)
* [ESP8266 External interrupts techtutorialsx](https://techtutorialsx.com/2016/12/11/esp8266-external-interrupts/)

## RCWL-0516

* [Wiring the RCWL0516 Auto Induction Doppler Microwave Radar with ESP826632Arduino](http://www.14core.com/wiring-the-rcwl0516-auto-induction-doppler-microwave-radar-with-esp826632arduino/)
* [RCWL-0516 information](https://github.com/jdesbonnet/RCWL-0516)



