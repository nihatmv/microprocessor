void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud to display output on the Serial Monitor

  uint8_t R18;  // 8-bit variable to store the sum, since we can’t directly print register values

  asm volatile (
      "ldi r17, 5\n\t"      // Load the number 5 into register r17
      "ldi r18, 8\n\t"      // Load the number 8 into register r18
      "add r18, r17\n\t"    // Add r17 to r18; the result is stored in r18
      "mov %0, r18\n\t"     // Copy the value from r18 into the C variable R18
      : "=r" (R18)          // Output operand: %0 corresponds to R18
      :                     // No input operands
      : "r17", "r18"        // Clobber list: tells the compiler that r17 and r18 are modified
  );

  Serial.print("Result = "); // Print "Result = " to the Serial Monitor
  Serial.println(R18);       // Print the calculated value stored in R18
}

void loop() {
  // Empty loop — setup() executes only once
}
