void setup() {
  DDRB = 0b00100000;   // Set PB5 (digital pin 13) as an output for the LED
}

void loop() {
  PORTB ^= 0b00100000;  // Toggle PB5 using XOR: turns LED ON if it’s OFF, or OFF if it’s ON
  delay(750);            // Wait for 750 milliseconds
  PORTB ^= 0b00100000;  // Toggle PB5 again to switch the LED back
  delay(750);            // Wait another 750 milliseconds before repeating
}
