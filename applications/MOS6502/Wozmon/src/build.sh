#!/bin/bash
set -e

if [ -z "$1" ]; then
    echo "cc65 toolchain required! Usage: build.sh <cc65-directory>"
    exit 1
fi

CC65DIR="$1"
CL="$CC65DIR/bin/cl65"

$CL -t none -C wozmon.cfg -o wozmon.bin wozmon.s
