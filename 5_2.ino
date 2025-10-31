#include <avr/io.h>
#include <util/delay.h>

void setup() {
  // ===== Configure LED pins as outputs =====
  DDRD |= (1 << PD6);  // Pin 6 (OC0A / Timer0)
  DDRB |= (1 << PB1);  // Pin 9 (OC1A / Timer1)
  DDRB |= (1 << PB3);  // Pin 11 (OC2A / Timer2)

  // ===== Timer0 setup (Fast PWM) =====
  TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM, clear OC0A on compare match
  TCCR0B = (1 << CS01); // Prescaler = 8, sets PWM frequency

  // ===== Timer1 setup (8-bit Fast PWM) =====
  TCCR1A = (1 << WGM10) | (1 << COM1A1); // Fast PWM, clear OC1A on compare match
  TCCR1B = (1 << WGM12) | (1 << CS11);   // Prescaler = 8

  // ===== Timer2 setup (Fast PWM) =====
  TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2A1); // Fast PWM, clear OC2A on compare match
  TCCR2B = (1 << CS21); // Prescaler = 8, sets PWM frequency
}

void loop() {
  // ===== Gradually adjust PWM duty cycles for fading effect =====
  for (uint8_t i = 0; i <= 255; i++) {
    OCR0A = (uint8_t)(i * 0.3); // Pin 6 LED: up to ~30% brightness
    OCR1A = (uint8_t)(i * 0.5); // Pin 9 LED: up to ~50% brightness
    OCR2A = (uint8_t)(i * 0.8); // Pin 11 LED: up to ~80% brightness
    _delay_ms(10);              // Small delay for smooth fading
  }

  _delay_ms(1000); // Pause 1 second before repeating the fade
}
