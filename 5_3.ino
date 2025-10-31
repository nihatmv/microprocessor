#include <avr/io.h>
#include <util/delay.h>

// ===== Setup function =====
void setup() {
  // ===== Configure LED pins as outputs =====
  DDRD |= (1 << PD6);  // Pin 6 (OC0A / Timer0)
  DDRB |= (1 << PB1);  // Pin 9 (OC1A / Timer1)
  DDRB |= (1 << PB3);  // Pin 11 (OC2A / Timer2)

  // ===== Configure button pin as input with pull-up =====
  DDRB &= ~(1 << PB0); // Set PB0 as input
  PORTB |= (1 << PB0); // Enable internal pull-up resistor

  // ===== Timer0 setup (Fast PWM) =====
  TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM, clear OC0A on compare match
  TCCR0B = (1 << CS01); // Prescaler = 8

  // ===== Timer1 setup (8-bit Fast PWM) =====
  TCCR1A = (1 << WGM10) | (1 << COM1A1); // Fast PWM, clear OC1A on compare match
  TCCR1B = (1 << WGM12) | (1 << CS11);   // Prescaler = 8

  // ===== Timer2 setup (Fast PWM) =====
  TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2A1); // Fast PWM, clear OC2A on compare match
  TCCR2B = (1 << CS21); // Prescaler = 8
}

// ===== Counter for button presses =====
uint8_t press_count = 0;

// ===== Function to read button with simple debounce =====
uint8_t readButton() {
  static uint8_t prev = 1;                  // Previous button state
  uint8_t current = (PINB & (1 << PB0)) ? 1 : 0; // Current button state

  // Detect falling edge (button press)
  if (prev == 1 && current == 0) {
    _delay_ms(30); // Debounce delay
    if ((PINB & (1 << PB0)) == 0) { // Confirm button is still pressed
      prev = current;
      return 1; // New button press detected
    }
  }
  prev = current;
  return 0; // No new press
}

// ===== Main loop =====
void loop() {
  if (readButton()) {          // If a new button press is detected
    press_count++;             // Increment press counter
    if (press_count > 12) press_count = 1; // Wrap around after 12 presses

    // Determine brightness level (1-4) and scale to 0-255
    uint8_t level = ((press_count - 1) % 4) + 1;
    uint8_t brightness = (level * 64) - 1; // Brightness steps: 63, 127, 191, 255

    // Activate one LED at a time based on press_count
    if (press_count <= 4) {
      OCR0A = brightness; // LED1 active
      OCR1A = 0;
      OCR2A = 0;
    } else if (press_count <= 8) {
      OCR0A = 0;
      OCR1A = brightness; // LED2 active
      OCR2A = 0;
    } else {
      OCR0A = 0;
      OCR1A = 0;
      OCR2A = brightness; // LED3 active
    }
  }
}
