void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud

  uint8_t sum;      // Variable to store the running total
  uint8_t counter;  // Counter variable for iteration
  uint8_t limit;    // Upper limit for the counter (used as the stopping condition)

  asm volatile(
    "clr %[sum]           \n\t"   // Clear the sum register (initialize sum = 0)
    "ldi %[counter], 1    \n\t"   // Load 1 into the counter
    "ldi %[limit], 11     \n\t"   // Load 11 into limit (loop will run until counter reaches 10)

    "loop%=:              \n\t"   // Define a local label 'loop'
    "add %[sum], %[counter]\n\t"  // Add the counter value to sum
    "inc %[counter]       \n\t"   // Increment the counter by 1
    "cp  %[counter], %[limit]\n\t"// Compare counter to limit
    "brne loop%=          \n\t"   // If not equal, jump back to 'loop'; exit when equal

    : [sum]     "=r"(sum),      // Output operand mapping for sum
      [counter] "+r"(counter),  // Read/write operand for counter
      [limit]   "+r"(limit)     // Read/write operand for limit
    :                           // No input operands
    : "cc"                      // Condition flags are affected (status register modified)
  );

  Serial.print("1 + 2 + 3 + ... + 10 = ");
  Serial.println(sum);  // Display the final result (55)
}

void loop() {
  // Empty loop — all operations are performed once in setup()
}
