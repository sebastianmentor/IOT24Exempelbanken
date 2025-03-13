# Projektets namn (utan filändelse) (ändra efter behov)
PROJECT = blink

# Mikrokontroller och klockhastighet (ändra efter behov)
MCU = atmega328p
F_CPU = 16000000UL

# Programmerare och port (justera vid behov)
PROGRAMMER = arduino
PORT = COM3

# Sökvägar till AVR-verktyg
AVR_PATH = C:/avr
AVRDUDE = $(AVR_PATH)/bin/avrdude.exe
CC = $(AVR_PATH)/bin/avr-gcc.exe 
OBJCOPY = $(AVR_PATH)/bin/avr-objcopy.exe

# Flaggor för kompilering och länkning
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra
LDFLAGS = -mmcu=$(MCU)

# Källfiler
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Regler
all: $(PROJECT).hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PROJECT).elf: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload: $(PROJECT).hex
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -U flash:w:$(PROJECT).hex:i

clean:
	rm -f *.o *.elf *.hex
