#!/bin/bash
set -e

if [ -z "$1" ]; then
    echo "cc65 toolchain required! Usage: compile.sh <cc65-directory>"
    exit 1
fi

CC65DIR="$1"
ASM="$CC65DIR/ca65"
LD="$CC65DIR/ld65"

$ASM --feature labels_without_colons -I $CC65DIR/include -o ehbasic.o min_mon.asm
$LD -C ehbasic.cfg -o ehbasic.bin ehbasic.o
