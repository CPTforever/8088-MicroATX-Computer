%ifndef HARDWARE_INC
%define HARDWARE_INC

STACK_TOP         equ 0x7FFFF
STACK_BASE        equ 0x70000
STACK_SIZE        equ 0xFFFF

RAM_BASE          equ 0x00000
RAM_END           equ 0x80000
RAM_BANKED_BASE   equ 0x80000
RAM_BANKED_END    equ 0xA0000

ROM_BASE          equ 0xE0000
ROM_END           equ 0x100000
ROM_LOWER_BASE    equ 0xE0000
ROM_UPPER_BASE    equ 0xF0000
RESET_VEC         equ 0xFFFF0

PIC_COMMAND       equ 0x20
PIC_DATA          equ 0x21

PIT_COUNTER_0     equ 0x40
PIT_COUNTER_1     equ 0x41
PIT_COUNTER_2     equ 0x42
PIT_CONTROL       equ 0x43

KBRD_DATA         equ 0x60
KBRD_CMD          equ 0x61

DMA_REG_0         equ 0x80
DMA_REG_1         equ 0x81
DMA_REG_2         equ 0x82
DMA_REG_3         equ 0x83

FLAG_REG          equ 0xA0

PPI_PORT_A        equ 0xC0
PPI_PORT_B        equ 0xC1
PPI_PORT_C        equ 0xC2
PPI_CONTROL       equ 0xC3

UART_RECV_REG     equ 0xE0
UART_TRANS_REG    equ 0xE0
UART_DIV_LATCH_L  equ 0xE0
UART_DIV_LATCH_H  equ 0xE1
UART_INT_EN       equ 0xE1
UART_INT_IDENT    equ 0xE2
UART_FIFO_CTRL    equ 0xE2
UART_LINE_CTRL    equ 0xE3
UART_MODEM_CTRL   equ 0xE4
UART_LINE_STATUS  equ 0xE5
UART_MODEM_STATUS equ 0xE6
UART_SCRATCH      equ 0xE7

RTC_SECONDS       equ 0x100
RTC_SECONDS_ALARM equ 0x101
RTC_MINUTES       equ 0x102
RTC_MINUTES_ALARM equ 0x103
RTC_HOURS         equ 0x104
RTC_HOURS_ALARM   equ 0x105
RTC_DAY           equ 0x106
RTC_DATE          equ 0x107
RTC_MONTH         equ 0x108
RTC_YEAR          equ 0x109
RTC_CONTROL_A     equ 0x10A
RTC_CONTROL_B     equ 0x10B
RTC_CONTROL_C     equ 0x10C
RTC_CONTROL_D     equ 0x10D
RTC_CENTURY       equ 0x132

%macro ppi_set_bit 1
  mov al, ((%1 & 0x7) << 0x1) | 0x1
  out PPI_CONTROL, al
%endmacro 

%macro ppi_reset_bit 1
  mov al, ((%1 & 0x7) << 0x1)
  out PPI_CONTROL, al
%endmacro 

%endif