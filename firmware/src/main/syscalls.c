/*
 * __libc_init_array() (called from startup_stm32f103xb.s) unconditionally
 * calls _init()/_fini(). Those normally come from crti.o/crtn.o, which
 * -nostartfiles deliberately excludes since our own Reset_Handler replaces
 * crt0. We have no global C++ constructors to run, so empty stubs are enough.
 */
void _init(void) {}
void _fini(void) {}
