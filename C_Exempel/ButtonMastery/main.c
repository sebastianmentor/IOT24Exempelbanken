#include <avr/io.h>
#include <avr/interrupt.h>
#include "millis.h"  // Inkludera Zak Kemble's millis-bibliotek

#define GREEN_BUTTON_PIN  (1 << PD7)  // Pin 7
#define RED_BUTTON_PIN    (1 << PB0)  // Pin 8
#define GREEN_LED_PIN     (1 << PB2)  // Pin 10
#define RED_LED_PIN       (1 << PB3)  // Pin 11

#define DEBOUNCE_TIME 50  // 50 ms debounce

volatile uint8_t greenLedState = 0;
volatile uint8_t redLedState = 0;
volatile uint8_t lastStateGreenButton = 1;
volatile uint8_t trueStateOfGreenButton = 1;
volatile uint32_t lastDebounceTime = 0;

void init_ports() {
    DDRD &= ~GREEN_BUTTON_PIN; // Pin 7 som ingång
    PORTD |= GREEN_BUTTON_PIN; // Aktivera pull-up
    
    DDRB &= ~RED_BUTTON_PIN; // Pin 8 som ingång
    PORTB |= RED_BUTTON_PIN; // Aktivera pull-up

    DDRB |= GREEN_LED_PIN | RED_LED_PIN; // Pin 10 och 11 som utgångar
}

uint8_t read_button(uint8_t pin, volatile uint8_t *port) {
    return (*port & pin) ? 1 : 0;
}

void toggle_led(uint8_t pin, volatile uint8_t *port) {
    *port ^= pin; // XOR för att växla tillstånd
}

int main(void) {
    init_ports();
    millis_init(); // Initiera Zak Kemble's millis
    sei(); // Aktivera globala avbrott

    while (1) {
        // Hantering av knapp utan debounce (röd knapp)
        if (!read_button(RED_BUTTON_PIN, &PINB)) { // Om röd knapp är tryckt
            while (!read_button(RED_BUTTON_PIN, &PINB)); // Vänta tills knappen släpps
            redLedState ^= 1; // Växla tillstånd
            if (redLedState) {
                PORTB |= RED_LED_PIN;
            } else {
                PORTB &= ~RED_LED_PIN;
            }
        }

        // Hantering av grön knapp med debounce
        uint8_t currentStateGreenButton = read_button(GREEN_BUTTON_PIN, &PIND);
        
        if (currentStateGreenButton != lastStateGreenButton) {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
            if (currentStateGreenButton != trueStateOfGreenButton) {
                trueStateOfGreenButton = currentStateGreenButton;
                if (!currentStateGreenButton) { // Om knapp tryckt
                    greenLedState ^= 1;
                    if (greenLedState) {
                        PORTB |= GREEN_LED_PIN;
                    } else {
                        PORTB &= ~GREEN_LED_PIN;
                    }
                }
            }
        }
        lastStateGreenButton = currentStateGreenButton;
    }
}
