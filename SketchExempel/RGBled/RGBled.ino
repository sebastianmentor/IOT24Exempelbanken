const int pinR = 11;
const int pinG = 10;
const int pinB = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
}

void brightenLed(int pwmPin) {
    for (int brightness = 0; brightness <= 255; brightness++) {
        analogWrite(pwmPin, brightness);
        delay(2); // Vänta 2 millisekunder mellan varje ökning
    }
}

void dimLed(int pwmPin) {
    for (int brightness = 255; brightness >= 0; brightness--) {
        analogWrite(pwmPin, brightness);
        delay(2); // Vänta 2 millisekunder mellan varje minskning
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  brightenLed(pinR);
  dimLed(pinR);
  brightenLed(pinG);
  dimLed(pinG);
  brightenLed(pinB);
  dimLed(pinB);


  brightenLed(pinR);
  brightenLed(pinG);
  brightenLed(pinB);
  dimLed(pinR);
  dimLed(pinG);
  dimLed(pinB);
}
