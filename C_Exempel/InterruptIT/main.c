#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BUTTON_PIN PD2  // Knapp på PD2 (INT0)
#define LED_PIN PB0     // Lysdiod på PB0 (pin 8)

volatile uint8_t ledState = 0;  // LED-status

ISR(INT0_vect) {
    _delay_ms(50);  // Debounce-skydd (50 ms)
    if (!(PIND & (1 << BUTTON_PIN))) {  // Kontrollera om knappen verkligen är nere
        ledState = !ledState;
        if (ledState)
            PORTB |= (1 << LED_PIN);  // Slå på LED
        else
            PORTB &= ~(1 << LED_PIN); // Slå av LED
    }
}

void setup() {
    // Ställ in knappen (PD2) som ingång och aktivera intern pull-up
    DDRD &= ~(1 << BUTTON_PIN);  // Ingång
    PORTD |= (1 << BUTTON_PIN);  // Intern pull-up

    // Ställ in LED (PB0) som utgång
    DDRB |= (1 << LED_PIN);
    PORTB &= ~(1 << LED_PIN); // Se till att LED är av i början

    // Ställ in extern interrupt på INT0 (fallande flank)
    EICRA |= (1 << ISC01);  // ISC01 = 1, ISC00 = 0 → Fallande signal
    EIMSK |= (1 << INT0);   // Aktivera INT0

    sei(); // Aktivera globala interrupts
}

int main(void) {
    setup();
    while (1) {
        // Huvudloopen gör inget - all logik hanteras i ISR
    }
}
