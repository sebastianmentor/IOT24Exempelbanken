#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

// Definiera LED-pinnar
#define LED_ONE PB1  // Pin 9 på Arduino Uno (PORTB1)
#define LED_TWO PB2  // Pin 10 på Arduino Uno (PORTB2)

// Buffert för inmatning
char inputBuffer[20];

// Funktion för att initiera UART (seriell kommunikation)
void uart_init(unsigned int baud) {
    unsigned int ubrr = F_CPU / 16 / baud - 1;
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Aktivera RX och TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bitars dataformat
}

// Funktion för att skicka en enda karaktär via UART
void uart_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Vänta tills bufferten är tom
    UDR0 = data;
}

// Funktion för att skicka en sträng via UART
void uart_print(const char *str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

// Funktion för att läsa en sträng från UART
void uart_readline(char *buffer, int maxLength) {
    char c;
    int i = 0;
    while (1) {
        while (!(UCSR0A & (1 << RXC0))); // Vänta på inkommande data
        c = UDR0;
        if (c == '\n' || c == '\r') { // Om Enter trycks
            buffer[i] = '\0';
            break;
        } else if (i < maxLength - 1) {
            buffer[i++] = c;
        }
    }
}

int main(void) {
    // Initiera UART med baudrate 9600
    uart_init(9600);
    
    // Konfigurera LED-pinnar som utgångar
    DDRB |= (1 << LED_ONE) | (1 << LED_TWO);

    uart_print("Ange kommando (L1 on/off, L2 on/off):\r\n");

    while (1) {
        // Läs in en rad från terminalen
        uart_readline(inputBuffer, sizeof(inputBuffer));

        // Jämför med kända kommandon
        if (strcmp(inputBuffer, "L1 on") == 0) {
            PORTB |= (1 << LED_ONE);
            uart_print("LED 1 är tänd!\n");
        } else if (strcmp(inputBuffer, "L1 off") == 0) {
            PORTB &= ~(1 << LED_ONE);
            uart_print("LED 1 är släckt!\n");
        } else if (strcmp(inputBuffer, "L2 on") == 0) {
            PORTB |= (1 << LED_TWO);
            uart_print("LED 2 är tänd!\n");
        } else if (strcmp(inputBuffer, "L2 off") == 0) {
            PORTB &= ~(1 << LED_TWO);
            uart_print("LED 2 är släckt!\n");
        } else {
            uart_print("Okänt kommando! Använd 'L1 on/off' eller 'L2 on/off'\n");
        }
        uart_print("\r");
    }

    return 0;
}
