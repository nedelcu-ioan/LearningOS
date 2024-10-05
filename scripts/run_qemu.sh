3#!/bin/bash

# Path to the ISO file
ISO="build/iso/myos.iso"

# Check if the ISO file exists
if [ ! -f "$ISO" ]; then
    echo "Error: ISO file '$ISO' not found. Please build the OS first."
    exit 1
fi

# Run the OS using QEMU
qemu-system-i386 -cdrom "$ISO" -m 512M -boot d

# Explanation:
# - `qemu-system-i386`: This runs QEMU for the i386 architecture (32-bit).
# - `-cdrom "$ISO"`: This tells QEMU to boot from the specified ISO file.
# - `-m 512M`: Allocates 512 MB of memory to the virtual machine.
# - `-boot d`: This tells QEMU to boot from the CD-ROM (the ISO).

