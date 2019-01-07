CSOURCES := $(shell find $(SOURCEDIR) -name '*.c')
SSOURCES := $(shell find $(SOURCEDIR) -name '*.s')
CPPSOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')

ARMGNU ?= arm-none-eabi

GCCARGS = -O0 -DRPIBPLUS -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles


all: clear kernel.img clear_extra


kernel.elf:
	$(ARMGNU)-gcc $(GCCARGS) -g $(SSOURCES) t.ld $(CSOURCES) $(CPPSOURCES) -o kernel.elf

kernel.img: kernel.elf
	$(ARMGNU)-objcopy kernel.elf -O binary kernel.img

clear: clear_extra
	rm -f *.elf
	rm -f *.img

clear_extra:
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.asm
	
dump:
	$(ARMGNU)-objdump -D kernel.elf > kernel.elf.asm
	
dumpSource:
	$(ARMGNU)-objdump -S kernel.elf > kernel.elf.asm