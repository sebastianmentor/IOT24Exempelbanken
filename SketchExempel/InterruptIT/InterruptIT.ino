const int buttonPin = 2;  // Interrupt pin
const int ledPin = 8;     // LED pin
volatile bool ledState = false;  // Variabel som kan ändras i ISR

void toggleLED() {
    ledState = !ledState;  // Växla LED-status
    digitalWrite(ledPin, ledState);
}

void setup() {
    pinMode(buttonPin, INPUT_PULLUP); // Aktivera intern pull-up motstånd
    pinMode(ledPin, OUTPUT);
    
    // Koppla interrupt till funktionen toggleLED vid fallande signal
    attachInterrupt(digitalPinToInterrupt(buttonPin), toggleLED, FALLING);
}

void loop() {
    // Huvudloopen gör inget - LED styrs av interrupt
}
