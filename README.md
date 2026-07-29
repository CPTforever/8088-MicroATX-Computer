# Insert header here

![pcb_front](https://github.com/CPTforever/8088-MicroATX-Computer/blob/main/assets/pcb_front.png)
![pcb_back](https://github.com/CPTforever/8088-MicroATX-Computer/blob/main/assets/pcb_back.png)
![schematic](https://github.com/CPTforever/8088-MicroATX-Computer/blob/main/assets/schematic.png)
# Features!
insert features

# Memory Map
Insert memory map

# I/O Port Map
Insert port map

# Rev 1 Mistakes
UART Controller uses system clock instead of external crystal, meaning standard buad times are
only achievable when system clock uses a UART compatible crystal

PIT Gate 1 does not have a pull up resistor, meaning gate is floating when the external io pin is not connected. (This can be bodged with a radial resistor at least.)
