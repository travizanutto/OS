#include <stddef.h>
#include "vga_buffer.h"

/*#if defined(__linux__)
    #error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
    #error "Use x86-elf compiler"
#endif*/

void kernel_main()
{
    term_init();
    term_rainbow();
}