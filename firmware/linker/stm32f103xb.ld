/*
 * Linker script for STM32F103RB (NUCLEO-F103RB)
 * Flash: 128K @ 0x08000000
 * SRAM:   20K @ 0x20000000
 *
 * Symbol names (_sidata, _sdata, _edata, _sbss, _ebss, _estack) are
 * referenced directly by startup/startup_stm32f103xb.s — do not rename.
 */

ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

/* Top of stack = end of RAM */
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
  /* Vector table, must sit at 0x08000000 */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH

  /* Program code and read-only data */
  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    KEEP(*(.init))
    KEEP(*(.fini))
    . = ALIGN(4);
  } >FLASH

  /* C++-style init/fini arrays (needed by __libc_init_array) */
  .init_array :
  {
    . = ALIGN(4);
    __init_array_start = .;
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array*))
    __init_array_end = .;
  } >FLASH

  .fini_array :
  {
    . = ALIGN(4);
    __fini_array_start = .;
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array*))
    __fini_array_end = .;
  } >FLASH

  /* Initialized data: lives in FLASH, copied to RAM at startup */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >RAM AT>FLASH

  /* Used by startup to initialize .data (.data가 먼저 배치된 뒤에 와야 함) */
  _sidata = LOADADDR(.data);

  /* Zero-initialized data: RAM only, cleared at startup */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >RAM

  /* Discard exception-handling metadata we don't use (no C++ exceptions) */
  /DISCARD/ :
  {
    *(.ARM.exidx*)
    *(.ARM.extab*)
  }

  . = ALIGN(4);
  end = .;
  _end = .;
}
