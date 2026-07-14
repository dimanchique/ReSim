#!/bin/bash
set -e

if [ -z "$1" ]; then
    echo "cc65 toolchain required! Usage: compile.sh <cc65-directory>"
    exit 1
fi

CC65DIR="$1"
CL="$CC65DIR/bin/cl65"

$CL -t none -C bios.cfg -o program.bin program.s
