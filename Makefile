# Target binary and ISO names
TARGET_BIN = build/iso/boot/myos.bin
ISO = build/iso/myos.iso

# Source directories
ASM_SRC = boot/boot.s
KERNEL_SRC_DIR = kernel
DRIVER_SRC_DIR = drivers
LIBC_SRC_DIR = libs/libc
TEST_SRC_DIR = tests

LINKER_SCRIPT = config/linker.ld
GRUB_CFG = config/grub.cfg

# Directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
ISO_DIR = $(BUILD_DIR)/iso
GRUB_DIR = $(ISO_DIR)/boot/grub

# Compiler and tools
AS = i686-elf-as
CC = i686-elf-gcc
LD = i686-elf-gcc
GRUB_MKRESCUE = grub-mkrescue

# Include directories
INCLUDE_DIRS = -I. -Ilibs/libc -Itests

# Compiler flags
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra $(INCLUDE_DIRS)
LDFLAGS = -ffreestanding -O2 -nostdlib
LIBS = -lgcc

# Find all C source files and generate corresponding object files
KERNEL_SRC = $(wildcard $(KERNEL_SRC_DIR)/*.c)
DRIVER_SRC = $(wildcard $(DRIVER_SRC_DIR)/*.c)
LIBC_SRC = $(wildcard $(LIBC_SRC_DIR)/*.c)
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.c)

# Convert source file paths into object file paths
OBJ = $(OBJ_DIR)/boot.o \
      $(KERNEL_SRC:$(KERNEL_SRC_DIR)/%.c=$(OBJ_DIR)/$(KERNEL_SRC_DIR)/%.o) \
      $(DRIVER_SRC:$(DRIVER_SRC_DIR)/%.c=$(OBJ_DIR)/$(DRIVER_SRC_DIR)/%.o) \
      $(LIBC_SRC:$(LIBC_SRC_DIR)/%.c=$(OBJ_DIR)/$(LIBC_SRC_DIR)/%.o) \
      $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(OBJ_DIR)/$(TEST_SRC_DIR)/%.o)

# Default target
all: $(ISO)

# Rule to create object directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/kernel
	mkdir -p $(OBJ_DIR)/libs/libc
	mkdir -p $(OBJ_DIR)/drivers
	mkdir -p $(OBJ_DIR)/tests
	
# Rule to assemble boot.s
$(OBJ_DIR)/boot.o: $(ASM_SRC) | $(OBJ_DIR)
	$(AS) $(ASM_SRC) -o $@

# Generic rule to compile .c files to .o files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Rule to link object files into a binary
$(TARGET_BIN): $(OBJ) $(LINKER_SCRIPT)
	mkdir -p $(ISO_DIR)/boot
	$(LD) -T $(LINKER_SCRIPT) -o $(TARGET_BIN) $(LDFLAGS) $(OBJ) $(LIBS)

# Rule to create the ISO directory and copy necessary files
$(ISO_DIR): $(TARGET_BIN) $(GRUB_CFG)
	mkdir -p $(GRUB_DIR)
	cp $(GRUB_CFG) $(GRUB_DIR)/grub.cfg

	# Multiboot check
	@if grub-file --is-x86-multiboot $(TARGET_BIN); then \
		echo "Multiboot confirmed"; \
	else \
		echo "The file is not multiboot"; \
		exit 1; \
	fi


# Rule to generate the ISO file
$(ISO): $(ISO_DIR)
	$(GRUB_MKRESCUE) -o $(ISO) $(ISO_DIR)

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

