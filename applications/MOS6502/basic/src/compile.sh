#!/bin/bash

set -e

ASM="/home/dimanchique/Projects/asm/cc65/bin/ca65"
LD="/home/dimanchique/Projects/asm/cc65/bin/ld65"
CC65DIR="/home/dimanchique/Projects/asm/cc65"

$ASM --feature labels_without_colons -I $CC65DIR/include -o ehbasic.o min_mon.asm
$LD -C ehbasic.cfg -o ehbasic.bin ehbasic.o
