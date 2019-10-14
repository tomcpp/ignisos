#include "mm.hpp"

.section ".text.boot"

.globl _start
_start:
    mrs     x0, mpidr_el1
    and     x0, x0, #0xFF       // Check processor id
    cbz     x0, master          // Hang if it's not the primary CPU
    b       proc_hang

proc_hang:
    b       proc_hang

master:
    adr     x0, bss_begin
    adr     x1, bss_end
    sub     x1, x1, x0          // Calculate the size of the bss section
    bl      memzero

    mov     sp, #LOW_MEMORY
    bl      kernel_main
    b       proc_hang
