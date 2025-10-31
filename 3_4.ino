void setup() {
  DDRB = 0b00100000;   // Configure PB5 (digital pin 13) as an output for the LED
}

void loop() {
  PORTB = (1 << 5);    // Turn the LED ON by setting bit 5 (0b00100000)
  delay(500);          // Wait for 500 milliseconds
  PORTB = 0b00000000;  // Turn the LED OFF by clearing all bits in PORTB
  delay(500);          // Wait for 500 milliseconds before repeating
}
