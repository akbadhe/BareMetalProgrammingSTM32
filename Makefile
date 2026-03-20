# Toolchain definition
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Add the hal directory to your include path so #include "hal_gpio.h" works
INC_DIRS = -I. -Ihal

# Compiler Flags
# -mcpu=cortex-m3: Target your specific ARM core
# -mthumb: STM32 only supports Thumb-2 instructions
# -Os: Optimize for SIZE (Crucial for 32KB Flash)
# -Wall: Show all warnings
CFLAGS = -mcpu=cortex-m3 -mthumb -Os -Wall -g $(INC_DIRS)

# Linker Flags
# -T: Point to your 32KB/10KB linker script
# -nostdlib: Don't include standard C libraries (keeps binary tiny)
# --gc-sections: Remove unused code (saves space)
LDFLAGS = -T linker_script.ld -nostdlib -Wl,--gc-sections

# Alternatively, use wildcards if you add more files later:
SRCS = $(wildcard *.c) $(wildcard hal/*.c)

all: final.bin

final.elf: startup.c main.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o final.elf

final.bin: final.elf
	$(OBJCOPY) -O binary final.elf final.bin

clean:
	rm -f *.elf *.bin

flash:
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program final.bin verify reset exit 0x08000000"
