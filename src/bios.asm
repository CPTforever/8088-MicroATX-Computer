BITS 16
CPU 186

ORG 0xE0000

TIMES (ROM_UPPER_BASE - ROM_LOWER_BASE) - ($ - $$)   DB 0xF4
%include "hardware.inc"
;%include "lcd.inc"

start:
; init programmable peripheral interface
mov ax, (STACK_BASE >> 4)
mov ss, ax
mov sp, 0xFFFE

loop:
mov al, 0x04
out FLAG_REG, al
mov al, 0x00
out FLAG_REG, al
jmp loop

TIMES (RESET_VEC - ROM_LOWER_BASE) - ($ - $$)   DB 0xF4
reset: 
  ; disables interrupts that could happen spuriously
  cli
  ; setup stack at top of nonbanked ram
  jmp start 
halt:
  hlt
  jmp reset
TIMES (ROM_END - ROM_LOWER_BASE) - ($ - $$)     DB 0xF4