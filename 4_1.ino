volatile uint8_t counter;  // Counter stored in SRAM; value resets to 0 if power is lost

void setup() {
  Serial.begin(9600);  

  while (EECR & (1 << EEPE));   // Wait if a previous EEPROM write is still in progress
  EEAR = 0;                     // Set EEPROM address to 0
  EECR |= (1 << EERE);          // Start EEPROM read
  counter = EEDR;               // Load the value from EEPROM into SRAM counter

  DDRD &= ~(1 << PD2);          // Configure PD2 (digital pin 2, button) as input

  Serial.print("Starting counter from: ");
  Serial.println(counter);
}

void loop() {
  if (PIND & (1 << PD2)) {      // Check if the button is pressed
    delay(250);                 // Debounce delay

    // Update counter using inline assembly
    asm volatile(
      "lds r25, counter    \n\t"   // Load counter from SRAM into register r25
      "inc r25             \n\t"   // Increment r25 by 1
      "sts counter, r25    \n\t"   // Store updated value back into SRAM
    );
    // lds = load from SRAM to register
    // sts = store from register to SRAM

    while (EECR & (1 << EEPE));   // Wait if EEPROM is busy
    EEAR = 0;                     // Set EEPROM address to 0
    EEDR = counter;               // Load new counter value into EEPROM data register
    EECR |= (1 << EEMPE);         // Enable master write
    EECR |= (1 << EEPE);          // Start EEPROM write

    Serial.print("Counter: ");
    Serial.println(counter);

    while (PIND & (1 << PD2));    // Wait until the button is released
  }
}
