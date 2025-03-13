int onboardLed = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(onboardLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(onboardLed, HIGH);
  delay(1000);
  digitalWrite(onboardLed, LOW);
  delay(1000);
}
