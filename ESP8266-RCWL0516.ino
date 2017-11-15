/* ************************************************************************ */
/*
    Detects the state of an input and announces new states in the console
    window.

    This code could be used with any of the GPIO pins as long as their 
    configured as inputs.

    There are two methods of state-change detection in this sketch :

        * Polled - The input pin is read in the loop() function and if the
          current input state doesn't match the last changed state then 
          announce the change and save the state.

        * Interrupt - There are two methods used here for invoking an
          input interrupt when the input state changes :

            * Interrupt on Change
            * Interrupt on a Level, toggle between levels on subsequent
              level changes.
*/
// change as necessary
#define SERIAL_BAUD 115200

// The pin and LED states
#define SENSOR_PIN D2
#define LED_BUILTIN_ON false
#define LED_BUILTIN_OFF true

/*
    You can choose between polled or interrupt driven
    sensor state-change detection.

    Good info on interrupts - 

        http://gammon.com.au/interrupts
*/
//#define POLLED
//  - OR -
#define INTERR
// this will enable interrupt on change instead of 
// interrupt on level (low vs high)
//#define INTERR_CHG

#ifdef POLLED
#ifdef INTERR
There can be only one
#endif
#endif

/* ************************************************************************ */
/*
    Two variables are needed when polling the sensor's current state. Each
    pass through loop() will read the sensor state and compare it against
    the last state that was saved when there was a transition of the sensor
    state.
*/
#ifdef POLLED
bool state;
bool lastState;
#endif

/* ************************************************************************ */
/*
    Gotta start somewhere...
*/
void setup()
{
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println();

    setUpIO();

#ifdef POLLED
    // initialize the states...
    state = false;
    lastState = false;
#endif

#ifdef INTERR
#ifdef INTERR_CHG
    // attach an interrupt handler to run when the input changes
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sensorHandler, CHANGE);
#else
    // attach an interrupt handler to run when the input is going low
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sensorHandlerActive, FALLING);
#endif
#endif
}

/*
    Set up the GPIO pins as needed...
*/
void setUpIO()
{
    // set up the built-in LED for use...
    pinMode(LED_BUILTIN, OUTPUT);
    // turn off the on-board LED
    digitalWrite(LED_BUILTIN, LED_BUILTIN_OFF);

    // set up the pin to read the sensor state
    // NOTE: An external pull-up resistor was used in
    // the circuit where this sketch was developed.
    pinMode(SENSOR_PIN, INPUT);
}

#ifdef INTERR
/* ************************************************************************ */
#ifdef INTERR_CHG
/*
    A single interrupt handler for "change" on the input pin.
*/
void sensorHandler()
{
    bool state = digitalRead(SENSOR_PIN);
    // indicate the new sensor state - active
    setLED(state);
}
#else  // INTERR_CHG
/*
    The ESP8266 only allows one handler per pin. That is why each handler
    attaches the opposite handler before returning.
*/
void sensorHandlerActive()
{
    // indicate the new sensor state - active
    setLED(LED_BUILTIN_ON);
    // attach an interrupt handler to run when the input is going high
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sensorHandlerIdle, RISING);
}

void sensorHandlerIdle()
{
    // indicate the new sensor state - idle
    setLED(LED_BUILTIN_OFF);
    // attach an interrupt handler to run when the input is going low
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sensorHandlerActive, FALLING);
}
#endif // INTERR_CHG
/*
*/
void setLED(bool state)
{
    digitalWrite(LED_BUILTIN, state);

    // sensor indicates active when it pulls
    // the input to 0.
    Serial.println("interr - " + String(state ? "IDLE" : "ACTIVE"));
}
#endif // INTERR

void loop()
{
#ifdef POLLED
    // read the state of the sensor and see if it 
    // matches the last known state
    if((state = digitalRead(SENSOR_PIN)) != lastState)
    {
        // no match, change the state of the LED
        digitalWrite(LED_BUILTIN, state);

        // remember this state as the last
        lastState = state;

        // sensor indicates active when it pulls
        // the input to 0.
        Serial.println("polled - " + String(state ? "IDLE" : "ACTIVE"));
    }
    yield();
    delay(500);
#endif
}
