// Deklarering knappar
int greenButton = 7;
int redButton = 8;

// Deklarering lysdioder
int greenLed = 10;
int redLed = 11;

// Deklarerar tillstånd för lysdioderna
int greenLedState = LOW; // Tillstånd för lysdioden om den är på eller av
int redLedState = LOW; // Tillstånd för lysdioden om den är på eller av

// Debounce
int debounceTime = 50; // sätter studstiden till 50 millisekunder
int trueStateOfGreenButton = HIGH; // vi använder intern pullup så den är från start satt till hög
int currentStateGreenButton = HIGH; // placeholder för att läsa knappens tillstånd
int lastStateGreenButton = HIGH; //
unsigned long lastDebounceTime = 0; // till för att hålla koll på när knappen ändrades sist

void setup() {
  // konfigurering av knappar
  pinMode(greenButton, INPUT_PULLUP); // Använder inbyggda pull-up konfigureringen 
  pinMode(redButton, INPUT_PULLUP); // Använder inbyggda pull-up konfigureringen

  // konfigurering av lysdioder
  pinMode(greenLed, OUTPUT); 
  pinMode(redLed, OUTPUT);

}

void loop() {
  // ---------------------------------- //
  // Hantering av knapp utan studsskydd //
  // ---------------------------------- //

  int currentStateRedButton = digitalRead(redButton);

  if (currentStateRedButton == LOW){
    redLedState = !redLedState;
    digitalWrite(redLed, redLedState);
  }

  // ----------------------------------- //
  // Hantering av knappar med studsskydd //
  // ----------------------------------- //

  int currentStateGreenButton = digitalRead(greenButton);
  
  if (currentStateGreenButton != lastStateGreenButton){
    lastDebounceTime = millis();
  }
  if (millis() - lastDebounceTime > debounceTime) {
    
    if (currentStateGreenButton != trueStateOfGreenButton){
      trueStateOfGreenButton=currentStateGreenButton;

      if (currentStateGreenButton == LOW) {
        greenLedState = !greenLedState;
      }
    }
  }
  digitalWrite(greenLed, greenLedState);
  lastStateGreenButton = currentStateGreenButton;
}
