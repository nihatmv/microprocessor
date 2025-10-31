void setup() {
  DDRB = 0b00100000; // Set PB5 (digital pin 13) as an output pin for the LED
}

void loop() {
  PORTB = 0b00100000; // Set PB5 HIGH to turn the LED on
  delay(750);         // Keep the LED on for 750 milliseconds
  PORTB = 0b00000000; // Set PB5 LOW to turn the LED off
  delay(750);         // Keep the LED off for 750 milliseconds
}
