
bool state;
bool lastState;

void setup()
{
    Serial.begin(115200);

    // let's blink the LED from within loop()
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, false);
    state = false;
    lastState = false;

    pinMode(D2, INPUT);
}


void loop()
{
    if((state = digitalRead(D2)) != lastState)
    {
        digitalWrite(LED_BUILTIN, state);
        lastState = state;

        // sensor is indicates active when it pulls
        // the input to 0.
        Serial.println(state ? "IDLE" : "ACTIVE");
    }
    delay(500);
}
