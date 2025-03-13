#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void uart_init() {
    // Ställ in baud rate (9600 baud vid 16 MHz klockfrekvens)
    uint16_t baud_prescaler = ((F_CPU / (16UL * 9600)) - 1);
    UBRR0H = (baud_prescaler >> 8);
    UBRR0L = baud_prescaler;

    // Aktivera TX (sändning) i USART
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data, 1 stop-bit
}

void uart_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Vänta tills bufferten är tom
    UDR0 = data;
}

void uart_println(uint16_t value) {
    char buffer[10];
    itoa(value, buffer, 10); // Omvandla int till sträng
    for (char *ptr = buffer; *ptr != '\0'; ptr++) {
        uart_transmit(*ptr);
    }
    uart_transmit('\r');
    uart_transmit('\n');
}

void adc_init() {
    // Aktivera ADC, ställ in prescaler till 128 (för 16 MHz -> 125 kHz ADC-frekvens)
    ADMUX = (1 << REFS0); // Välj AVcc som referensspänning, kanal 0 (A0)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read() {
    ADCSRA |= (1 << ADSC); // Starta konvertering
    while (ADCSRA & (1 << ADSC)); // Vänta på att konverteringen ska bli klar
    return ADC;
}

int main(void) {
    adc_init();   // Initiera ADC
    uart_init();  // Initiera UART

    while (1) {
        uint16_t pot1Value = adc_read(); // Läs potentiometervärdet
        uart_println(pot1Value); // Skriv ut till UART
        _delay_ms(100); // Vänta 100 ms
    }
}
