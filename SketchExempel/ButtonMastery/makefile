BOARD = arduino:avr:uno  # Ändra till rätt kort
PORT = /dev/ttyUSB0      # Ändra till rätt port (kör `arduino-cli board list`)
BUILD_DIR = build

all: compile

compile:
	arduino-cli compile --fqbn $(BOARD) --output-dir $(BUILD_DIR)

upload: compile
	arduino-cli upload -p $(PORT) --fqbn $(BOARD) $(SKETCH)

clean:
	rm -rf $(BUILD_DIR)

monitor:
	arduino-cli monitor -p $(PORT) -c baudrate=9600

.PHONY: all compile upload clean monitor
