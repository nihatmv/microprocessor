void setup() {
  DDRB |= 0b00100000;   // Configure PB5 (digital pin 13) as an output for the LED
}

void loop() {
  PORTB |= 0b00100000;  // Use bitwise OR to set PB5 HIGH, turning the LED on
  delay(750);           // Wait for 750 milliseconds
  PORTB &= 0b11011111;  // Use bitwise AND to clear PB5, turning the LED off
  delay(750);           // Wait another 750 milliseconds before repeating
}
