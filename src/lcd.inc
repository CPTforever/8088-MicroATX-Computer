%ifndef LCD_INC
%define LCD_INC

%include "hardware.inc"
%include "util.inc"

; datasheet reference: https://newhavendisplay.com/content/app_notes/ST7066U.pdf 

%define LCD_EN 0x1 
%define LCD_RW 0x2
%define LCD_RS 0x3

%define LCD_DISPLAY 0x1
%define LCD_CURSOR  0x2
%define LCD_BLINK   0x4


%macro lcd_clear_display 0
mov ax, 0x1
call lcd_write_instr
%endmacro

%macro lcd_return_home 0
mov ax, 0x2
call lcd_write_instr
%endmacro
 
%macro lcd_cursor_left 0
mov ax, 0x4
call lcd_write_instr
%endmacro

%macro lcd_cursor_right 0
mov ax, 0x5
call lcd_write_instr
%endmacro

%macro lcd_shift_left 0
mov ax, 0x7
call lcd_write_instr
%endmacro

%macro lcd_shift_right 0
mov ax, 0x6
call lcd_write_instr
%endmacro

%macro lcd_display_toggle 1
mov ax, (0x08 | (%1 & 0x07)) & 0xFFFF
call lcd_write_instr
%endmacro

%macro lcd_function_set 0
mov ax, 0x3C
call lcd_write_instr
%endmacro

%macro lcd_safe_call 1+
  ; wait ~80 us for busy flag to be read
  mov cx, 0x0030
  call busy_wait

  call lcd_wait_busy

  %1
%endmacro
lcd_init:



; assuming power on was recently... wait for ~15 ms 
mov cx, 0x2000 
call busy_wait

; strobe init function
mov ax, 0x30
call lcd_write_instr

; wait for ~4.1 ms 
mov cx, 0x0800 
call busy_wait

; strobe init function
mov ax, 0x30
call lcd_write_instr

; wait for ~100 us 
mov cx, 0x0032
call busy_wait

; strobe init function
mov ax, 0x0030
call lcd_write_instr

; lcd function set, 8 bits, 11 display lines, 
lcd_safe_call lcd_function_set
; turn off display
lcd_safe_call lcd_display_toggle (0)
; clear display
lcd_safe_call lcd_clear_display
; set cursor to go right
lcd_safe_call lcd_cursor_right


ret

; assumes port A is configured for reading
lcd_read_data:
ppi_reset_bit LCD_RS
ppi_set_bit   LCD_RW
ppi_set_bit   LCD_EN
in al, PPI_PORT_A
ppi_reset_bit LCD_EN
ret

lcd_wait_busy:
; set port A to read mode
mov al, 0x90
out PPI_CONTROL, al

; wait until busy flag is 0
_lcd_wait_busy_loop:
call lcd_read_data
test ax, 0x0080
jnz _lcd_wait_busy_loop

; set port A to write mode
mov al, 0x80
out PPI_CONTROL, al
ret

lcd_write_data:
out PPI_PORT_A, al
ppi_set_bit   LCD_RS
ppi_reset_bit LCD_RW
ppi_set_bit   LCD_EN
ppi_reset_bit LCD_EN
ret

lcd_write_instr:
out PPI_PORT_A, al
ppi_reset_bit LCD_RS
ppi_reset_bit LCD_RW
ppi_set_bit   LCD_EN
ppi_reset_bit LCD_EN
ret

%if 0
%macro lcd_display_on
mov ax, 0xC
call lcd_write_instr
%endmacro

%macro lcd_display_off
mov ax, 0x
call lcd_write_instr
%endmacro


%macro lcd_cursor_on
mov ax, 0x6
call lcd_write_instr
%endmacro

%macro lcd_cursor_off
mov ax, 0x6
call lcd_write_instr
%endmacro
%endif 

%endif