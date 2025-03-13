int pot1 = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pot1, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pot1Value = analogRead(pot1);
  Serial.println(pot1Value);
  delay(100);
}
