#include "panic.h"

void panic() {
    __asm__ __volatile__("cli\n\t"   // Disable interrupts
                         "hlt\n\t"   // Halt the CPU
                         "jmp .\n\t" // Infinite loop to keep halting
    );
}
