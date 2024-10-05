#!/bin/bash

# Path to the kernel binary
KERNEL_BIN="build/iso/boot/myos.bin"

# Check if the kernel binary exists
if [ ! -f "$KERNEL_BIN" ]; then
    echo "Kernel binary not found. Building the OS first..."
    make
fi

# Run QEMU with the kernel binary
echo "Running the OS in QEMU without GRUB..."
qemu-system-i386 -kernel "$KERNEL_BIN" -serial stdio
