volatile keyword
In C++, the volatile keyword is a type qualifier that tells the compiler not to optimize accesses to a variable because its value may change unexpectedly at any time. It is typically used when interacting with hardware registers, shared memory (in multithreading), or signal handlers.




volatile int x = 10;
while (x == 10) {
    // Do nothing
}


instruction level:
-The compiler cannot assume x remains unchanged.
-It must generate an actual memory load instruction every time x is read.

    .L1:
        mov eax, DWORD PTR [x]   ; Load x from memory
        cmp eax, 10              ; Compare x with 10
        je .L1                   ; If x is still 10, loop



without volatile:
        jmp .L1  ; Infinite loop (x is assumed constant)


Conclusion:
volatile tells the compiler to always read/write directly from memory.
It prevents compiler optimizations but does NOT ensure thread safety.
Use it for hardware registers, signals, or special memory locations.
For multi-threading, prefer std::atomic.

