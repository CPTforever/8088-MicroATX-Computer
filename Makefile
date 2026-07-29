ASM     := nasm 
INCDIR  := src
TARGET  := bios.bin
SRC     := $(INCDIR)/bios.asm

ASFLAGS := -f bin -i $(INCDIR)/ -w+all 
INCS    := $(wildcard $(INCDIR)/*.inc)

.PHONY: all clean debug prog

all: $(TARGET)

$(TARGET) : $(SRC) $(INCS)
	$(ASM) $(ASFLAGS) $< -o $@ 

debug: ASFLAGS += -d DEBUG=1 -l $(TARGET:.bin=.lst)
debug: clean $(TARGET)

prog: $(TARGET)
	minipro -w $< -p SST39SF010A

clean:
	rm -f $(TARGET) $(TARGET:.bin=.lst)