void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud

  uint8_t result;  // Variable to hold the outcome of the subtraction
  uint8_t sreg;    // Variable to store the Status Register (SREG) after the operation

  asm volatile (
    "ldi r16, 50\n\t"             // Load the value 50 into register r16
    "ldi r17, 200\n\t"            // Load the value 200 into register r17
    "sub r16, r17\n\t"            // Subtract r17 from r16; result wraps to 106, and SREG flags are updated (Z=0, C=1)
    "in __tmp_reg__, __SREG__\n\t" // Copy the SREG into the temporary register
    "mov %1, __tmp_reg__\n\t"      // Move the SREG value into the output variable ‘sreg’
    "mov %0, r16\n\t"              // Move the subtraction result from r16 into the output variable ‘result’
    : "=r"(result), "=r"(sreg)     // Output operands mapping
    :                              // No input operands
    : "r16", "r17"                 // Indicate that r16 and r17 are modified
  );

  bool Z = (sreg & (1 << 1));   // Retrieve the Zero (Z) flag from SREG (bit 1)
  bool C = (sreg & (1 << 0));   // Retrieve the Carry/Borrow (C) flag from SREG (bit 0)

  Serial.print("Result = ");
  Serial.println(result);        // Display the wrapped subtraction result (106)
  Serial.print("SREG (binary) = ");
  Serial.println(sreg, BIN);     // Display the SREG value in binary form
  Serial.print("Z (Zero flag) = ");
  Serial.println(Z);             // Show the Z flag state (0)
  Serial.print("C (Carry/Borrow flag) = ");
  Serial.println(C);             // Show the C flag state (1)
}

void loop() {
  // Empty loop — all operations run once during setup
}
