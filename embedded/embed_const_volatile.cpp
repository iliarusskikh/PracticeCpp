// =============================================================================
// demo_const_volatile.cpp
//
//->Hardware can update the register anytime (volatile)
//->Firmware can only read, never write (const)
//->Compiler never optimizes away reads
..
// Purpose:
//   Demonstrate WHY `const volatile` is the recommended qualifier combination
//   when declaring memory-mapped **read-only** hardware registers in embedded
//   C/C++ systems (status registers, flags, data-ready bits, etc.).
//
// Key learning objective:
//   - `volatile`          → compiler must never cache / optimise away reads
//   - `const`             → code is physically prevented from writing (compile error)
//   - `const volatile`    → both guarantees at once → safest contract for read-only peripherals
// =============================================================================

#include <cstdint>      // For fixed-width types: uint32_t, etc.
#include <cstdio>       // Only used here for host-based demo printing

// =============================================================================
// Example memory-mapped peripheral register base addresses
// (typical 32-bit ARM Cortex-M style addresses – replace with your SoC values)
// =============================================================================
#define UART_STATUS_REG_BASE    0x4000C000u     // Example: STM32 USART SR or similar
#define ADC_STATUS_REG          0x40012404u     // Example: ADC ready/flag register
#define PWR_FAULT_STATUS_REG    0xE0042008u     // Example: power management fault flags

// =============================================================================
// WRONG / DANGEROUS / INCOMPLETE declarations – shown for teaching contrast
// =============================================================================

// Dangerous: no qualifiers → compiler can freely optimise and code can write
uint32_t* dangerous_no_qualifiers = reinterpret_cast<uint32_t*>(UART_STATUS_REG_BASE);

// Still dangerous: allows accidental firmware writes (very common bug source)
volatile uint32_t* only_volatile = reinterpret_cast<volatile uint32_t*>(UART_STATUS_REG_BASE);

// Subtly dangerous: prevents writes, BUT compiler may cache value → stale data bugs
const uint32_t* only_const = reinterpret_cast<const uint32_t*>(UART_STATUS_REG_BASE);

// =============================================================================
// Correct & recommended: read-only hardware register
// Guarantees:
//   1. Hardware can change value at any time                  → volatile
//   2. Compiler always reads from memory (no caching)         → volatile
//   3. Firmware is physically prevented from writing          → const
// =============================================================================
const volatile uint32_t* uart_status   = reinterpret_cast<const volatile uint32_t*>(UART_STATUS_REG_BASE);
const volatile uint32_t* adc_dataready = reinterpret_cast<const volatile uint32_t*>(ADC_STATUS_REG);
const volatile uint32_t* fault_flags   = reinterpret_cast<const volatile uint32_t*>(PWR_FAULT_STATUS_REG);

// =============================================================================
// Common helper macros for bit testing (used in almost every embedded project)
// =============================================================================
#define BIT_POSITION(n)         (1u << (n))
#define IS_BIT_SET(reg_ptr, bit)   ((*(reg_ptr) & BIT_POSITION(bit)) != 0u)

// =============================================================================
// Example usage: safe, fresh reads from hardware
// =============================================================================

// Check if UART transmitter is ready for next byte (typical THRE / TXE bit)
bool is_uart_transmitter_empty() {
    // volatile → compiler MUST re-read the register every time this function is called
    return IS_BIT_SET(uart_status, 7);
}

// Check if ADC has finished a conversion and data is ready
bool is_adc_conversion_complete() {
    return IS_BIT_SET(adc_dataready, 0);   // Assuming bit 0 = EOC / data ready
}

// Check for critical hardware fault condition
bool has_overvoltage_condition() {
    return IS_BIT_SET(fault_flags, 3);     // Example bit position
}

// =============================================================================
// These MUST cause a **compile-time error** – this is the safety provided by const
// =============================================================================
void demonstrate_write_protection() {
    // All of these should fail to compile (good!):

    // *uart_status   |= BIT_POSITION(5);          // error
    // *adc_dataready  = 0xFFFFFFFFu;              // error
    // fault_flags->some_member = 42;              // error (if struct syntax used)
    // *(uint32_t*)fault_flags = 0x0000FFFFu;      // error – even with cast

    // Contrast: these would compile (and potentially brick hardware):
    // *only_volatile |= BIT_POSITION(5);          // allowed – dangerous
    // *dangerous_no_qualifiers = 0xDEADBEEFu;     // allowed – very dangerous
}

// =============================================================================
// Polling example – shows why volatile is mandatory
// =============================================================================
void wait_until_adc_is_ready_blocking() {
    // WRONG version using only const (compiler may optimise to single read):
    // while (!(*only_const & BIT_POSITION(0))) { /* spin */ }

    // CORRECT version using const volatile:
    // Every loop iteration → fresh read from memory-mapped register
    while (!IS_BIT_SET(adc_dataready, 0)) {
        // In real code: add timeout, small delay, feed watchdog, etc.
    }

    // Now data register (different address) can be safely read
}

// =============================================================================
// Typical usage pattern in real firmware
// =============================================================================
void example_status_polling_usage() {
    // Wait for transmitter ready before writing next character
    while (!is_uart_transmitter_empty()) {
        // Optional: feed watchdog, check other conditions, etc.
    }

    // Write would go to a different register (usually just volatile, not const)
    // volatile uint32_t* uart_data = ...;
    // *uart_data = 'A';
}

int main() {
    // Simulated host demonstration (embedded target would not use printf)

    if (is_adc_conversion_complete()) {
        std::printf("ADC conversion complete – data ready to read\n");
    }

    if (has_overvoltage_condition()) {
        std::printf("!!! CRITICAL: Overvoltage detected !!!\n");
    }

    // demonstrate_write_protection();   // Uncomment → compilation should fail

    return 0;
}
