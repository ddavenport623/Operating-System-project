# Compiler and linker (remove aarch64-linux-gnu- prefix on Mac M1/M2/M3)
CC     = aarch64-linux-gnu-gcc
LD     = aarch64-linux-gnu-ld

CFLAGS = -g -pedantic -Wall -Wextra -fPIC -std=gnu2x -MMD
ASFLAGS = -g -MMD
LDFLAGS = -g -N -Ttext=0x10000

# Targets
OBJ = kernel.o boot.o progress.o
DEPS = $(OBJ:.o=.d)

.PHONY: all clean

all: kernel.elf

# --- Object file rules ---

kernel.o: kernel.c
    $(CC) $(CFLAGS) -c $< -o $@

boot.o: boot.S
    $(CC) $(ASFLAGS) -c $< -o $@

progress.o: progress.S
    $(CC) $(ASFLAGS) -c $< -o $@

# --- Link final kernel image ---

kernel.elf: $(OBJ) libos.a
    $(LD) $(LDFLAGS) -o $@ $(OBJ) libos.a

# --- Cleanup ---

clean:
    rm -f $(OBJ) $(DEPS) kernel.elf

# Include dependency files if they exist
-include $(DEPS)
