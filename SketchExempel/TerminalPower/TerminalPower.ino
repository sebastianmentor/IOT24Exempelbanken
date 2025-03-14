const int ledOne = 9;   // LED 1 kopplad till pin 9
const int ledTwo = 10;  // LED 2 kopplad till pin 10
String inputString = ""; // För att lagra inkommande strängar
bool stringComplete = false; // Indikator för färdig inmatning

void setup() {
    pinMode(ledOne, OUTPUT);
    pinMode(ledTwo, OUTPUT);
    Serial.begin(115200); // Startar seriell kommunikation
    Serial.println("Ange kommando (L1 on/off, L2 on/off):");
}

void loop() {
    if (Serial.available() > 0) { // Kolla om data finns i bufferten
        String input = Serial.readStringUntil('\n'); // Läs in data fram till ny rad
        input.trim(); // Tar bort eventuella extra mellanslag och radbrytningar
        
        if (input.equalsIgnoreCase("L1 on")) {
            digitalWrite(ledOne, HIGH);
            Serial.println("LED 1 är tänd!");
        } 
        else if (input.equalsIgnoreCase("L1 off")) {
            digitalWrite(ledOne, LOW);
            Serial.println("LED 1 är släckt!");
        } 
        else if (input.equalsIgnoreCase("L2 on")) {
            digitalWrite(ledTwo, HIGH);
            Serial.println("LED 2 är tänd!");
        } 
        else if (input.equalsIgnoreCase("L2 off")) {
            digitalWrite(ledTwo, LOW);
            Serial.println("LED 2 är släckt!");
        } 
        else {
            Serial.println("Okänt kommando! Använd 'L1 on/off' eller 'L2 on/off'");
        }
    }
}
