#!/bin/bash
set -e

if [ -z "$1" ]; then
    echo "vasm assembler required! Usage: build.sh <vasm-binary-or-directory>"
    exit 1
fi

VASM="$1"
if [ -d "$VASM" ]; then
    VASM="$VASM/vasm"
fi

DIR="$(cd "$(dirname "$0")" && pwd)"

echo "=== Building Wozmon for ReSim ==="
"$VASM" -Fbin -dotdir -o "${DIR}/wozmon.bin" "${DIR}/wozmon.asm" -Lfmt=wide -L listing.lst

echo "=== Done ==="
ls -la "${DIR}/wozmon.bin"
