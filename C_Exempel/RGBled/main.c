#include <avr/io.h>
#include <util/delay.h>

#define PIN_R PB3  // OC2A (Pin 11 på Arduino Uno)
#define PIN_G PB2  // OC1B (Pin 10 på Arduino Uno)
#define PIN_B PB1  // OC1A (Pin 9 på Arduino Uno)

void init_pwm() {
    // **Konfigurera Timer2 för Fast PWM (8-bit)**
    TCCR2A = (1 << WGM21) | (1 << WGM20) | (1 << COM2A1); // Fast PWM, 8-bit
    TCCR2B = (1 << CS21);  // Prescaler 8 (ökar PWM-frekvensen)
    
    // **Sätt Pin 11 som utgång**
    DDRB |= (1 << PIN_R);

    // **Konfigurera Timer1 för Fast PWM (10-bit)**
    TCCR1A = (1 << WGM11) | (1 << WGM10) | (1 << COM1B1); // Fast PWM, 10-bit
    TCCR1B = (1 << WGM12) | (1 << CS11);  // Prescaler 8

    // **Sätt Pin 10 som utgång**
    DDRB |= (1 << PIN_G);

    // **Konfigurera Timer1 för Fast PWM (10-bit)**
    TCCR1A = (1 << WGM11) | (1 << WGM10) | (1 << COM1A1); // Fast PWM, 10-bit
    TCCR1B = (1 << WGM12) | (1 << CS11);  // Prescaler 8

    // **Sätt Pin 9 som utgång**
    DDRB |= (1 << PIN_B);
}

void pulse_red_led() {
    // Öka ljusstyrkan
    for (uint8_t brightness = 0; brightness < 255; brightness++) {
        OCR2A = brightness;
        _delay_ms(4);
    }
    
    // Minska ljusstyrkan
    for (uint8_t brightness = 255; brightness > 0; brightness--) {
        OCR2A = brightness;
        _delay_ms(4);
    }
}

void pulse_green_led() {
    // Öka ljusstyrkan (0 → 1023 eftersom Timer1 är 10-bit)
    for (uint16_t brightness = 0; brightness < 1023; brightness += 4) {
        OCR1B = brightness;
        _delay_ms(4);
    }
    
    // Minska ljusstyrkan (1023 → 0)
    for (uint16_t brightness = 1023; brightness > 0; brightness -= 4) {
        OCR1B = brightness;
        _delay_ms(4);
    }
}

void pulse_led() {
    // Öka ljusstyrkan (0 → 1023 eftersom Timer1 är 10-bit)
    for (uint16_t brightness = 0; brightness < 1023; brightness += 4) {
        OCR1A = brightness;
        _delay_ms(4);
    }
    
    // Minska ljusstyrkan (1023 → 0)
    for (uint16_t brightness = 1023; brightness > 0; brightness -= 4) {
        OCR1A = brightness;
        _delay_ms(4);
    }
}

int main(void) {
    init_pwm(); // Initiera PWM på Pin 11
    OCR2A = 0;
    while (1) {
        pulse_red_led(); // Pulsera LED
    }
}
