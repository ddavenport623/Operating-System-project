# Compiler and linker (remove prefix on Mac M1/M2/M3)
CC     = aarch64-linux-gnu-gcc
LD     = aarch64-linux-gnu-ld

CFLAGS  = -g -pedantic -Wall -Wextra -fPIC -std=gnu2x -MMD
ASFLAGS = -g -MMD
LDFLAGS = -g -N -Ttext=0x10000

OBJ  = kernel.o boot.o progress.o
DEPS = $(OBJ:.o=.d)

.PHONY: all clean run debug

all: kernel.elf

# --- Link final kernel image ---
kernel.elf: $(OBJ) libos.a
    $(LD) $(LDFLAGS) -o $@ $(OBJ) libos.a

# --- Object file rules ---
kernel.o: kernel.c
    $(CC) $(CFLAGS) -c $< -o $@

boot.o: boot.S
    $(CC) $(ASFLAGS) -c $< -o $@

progress.o: progress.S
    $(CC) $(ASFLAGS) -c $< -o $@

# --- Run OS in QEMU ---
run:
    qemu-system-aarch64 -machine raspi3b -kernel kernel.elf

# --- Debug OS in QEMU with GDB stub ---
debug:
	qemu-system-aarch64 -machine raspi3b  -S -s -kernel kernel.elf &
	ddd --debugger 'gdb-multiarch -ex "target remote localhost:1234" -ex "break main" -ex "continue"' kernel.elf

# --- Cleanup ---
clean:
    rm -f $(OBJ) $(DEPS) kernel.elf

# Include dependency files
-include $(DEPS)
