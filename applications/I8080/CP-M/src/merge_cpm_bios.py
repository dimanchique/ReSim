#!/usr/bin/env python3
"""Merge CPM22.ASM + CBIOS.ASM into cpm22_bios.asm.

- Takes CPM22.ASM lines 1-3711 (everything before the BIOS stub table)
- Appends CBIOS.ASM content, uppercased, with console I/O stubs filled in
"""

import sys
import os
import re

def transform_cbios(lines):
    """Transform CBIOS.ASM lines: uppercase, remove org/jump vector, fix stubs."""
    result = []
    skip_until_36 = False
    in_jump_vector = False

    for i, line in enumerate(lines):
        ln = i + 1  # 1-based line number

        # Line 3: change msize equ 20 to MSIZE EQU 62 (match CPM22's MEM)
        if ln == 3:
            line = re.sub(r'\bmsize\b', 'MSIZE', line, flags=re.IGNORECASE)
            line = re.sub(r'\b20\b', '62', line)
            result.append(line)
            continue

        # Skip 'org bios' (line 15)
        if ln == 15:
            continue

        # Skip jump vector (lines 18-35)
        if 18 <= ln <= 35:
            continue

        # Skip nsects line when it comes right after org (we re-add it)
        # Actually line 16 is nsects, keep it but uppercase
        if ln == 16:
            line = re.sub(r'nsects', 'NSECTS', line, flags=re.IGNORECASE)
            line = re.sub(r'\bccp\b', 'CCP', line, flags=re.IGNORECASE)
            result.append(line)
            continue

        # --- Console I/O stubs (lines 170-183) ---
        if ln == 170:
            result.append("CONST:\t;console status, return 0FFh if character ready, 00h if not\n")
            result.append("\tIN\t0\t;keyboard status\n")
            result.append("\tRET\n")
            result.append("\tDS\t0DH\n")
            continue
        if ln == 171:
            continue  # replaces ds 10h
        if ln == 172:
            continue  # replaces mvi a,00h
        if ln == 173:
            continue  # replaces ret (our ret is above)
        if ln == 174:
            continue  # blank after const

        if ln == 175:
            result.append("CONIN:\t;console character into register A\n")
            result.append("\tIN\t1\t;keyboard data\n")
            result.append("\tANI\t7FH\t;strip parity\n")
            result.append("\tRET\n")
            result.append("\tDS\t0CH\n")
            continue
        if ln == 176:
            continue
        if ln == 177:
            continue
        if ln == 178:
            continue
        if ln == 179:
            continue

        if ln == 180:
            result.append("CONOUT:\t;console character output from register C\n")
            result.append("\tMOV\tA,C\n")
            result.append("\tOUT\t2\t;TTY output\n")
            result.append("\tRET\n")
            result.append("\tDS\t0CH\n")
            continue
        if ln == 181:
            continue
        if ln == 182:
            continue
        if ln == 183:
            continue

        # --- Generic transformation for all other lines ---

        # Comment out iobyte equate (line 13) - CPM22 already defines IOBYTE
        if ln == 13:
            result.append(";" + line.lstrip())
            continue

        # Uppercase all labels (line starts with lowercase label followed by colon)
        # Handle labels like "boot:", "load1:", "gocpm:", "prmsg:", "dpbase:", etc.
        line = re.sub(r'^([a-z_][a-z0-9_]*)\s*:', lambda m: m.group(1).upper() + ':', line)

        # Uppercase equate names
        line = re.sub(r'^([a-z_][a-z0-9_]*)\s+equ\b', lambda m: m.group(1).upper() + ' equ', line, flags=re.IGNORECASE)

        # Uppercase references to known equates/labels in operands
        # Pattern: instruction operand reference
        # e.g., lxi h,ccp -> lxi h,CCP
        #        jmp ccp -> jmp CCP
        #        sta iobyte -> sta iobyte (but iobyte is commented out)
        #        sta cdisk -> sta CDISK
        #        lxi h,bdos -> lxi h,BDOS
        #        lxi h,wboote -> lxi h,WBOOT
        #        jmp gocpm -> jmp GOCPM
        
        # Fix specific wboote -> WBOOT reference
        line = line.replace('wboote', 'WBOOT')

        # Uppercase remaining label/equate references in operands
        # These are the known CBIOS symbols
        symbols = ['msize', 'bias', 'ccp', 'bdos', 'bios', 'cdisk', 'iobyte', 'nsects',
                   'dpbase', 'trans', 'dpblk', 'dirbf', 'chk00', 'chk01',
                   'chk02', 'chk03', 'all00', 'all01', 'all02', 'all03',
                   'track', 'sector', 'dmaad', 'diskno',
                   'boot', 'wboot', 'const', 'conin', 'conout',
                   'list', 'punch', 'reader', 'home', 'seldsk',
                   'settrk', 'setsec', 'setdma', 'read', 'write',
                   'listst', 'sectran',
                   'gocpm', 'load1', 'prmsg', 'bootmsg',
                   'rewait', 'werror', 'wready',
                   'booterr', 'booter0', 'begdat', 'enddat', 'datsiz',
                   'waitio', 'dpbase', 'setfunc', 'setdrive',
                   'setfunc', 'intype', 'inbyte', 'instat',
                   'iodr1', 'wait0', 'wready', 'werror', 'trycount',
                   'iod', 'iof', 'ion', 'iot', 'ios',
                   'iopb', 'dbank', 'retry']

        # Function to uppercase symbol references in operand part
        def uppercase_syms(line):
            # Match instructions followed by operands
            # Don't uppercase comments
            if ';' in line:
                code, comment = line.split(';', 1)
                code_upper = code
                for sym in sorted(symbols, key=len, reverse=True):
                    # Match whole word only (word boundary)
                    code_upper = re.sub(r'\b' + re.escape(sym) + r'\b', sym.upper(), code_upper, flags=re.IGNORECASE)
                return code_upper + ';' + comment
            else:
                code_upper = line
                for sym in sorted(symbols, key=len, reverse=True):
                    code_upper = re.sub(r'\b' + re.escape(sym) + r'\b', sym.upper(), code_upper, flags=re.IGNORECASE)
                return code_upper

        line = uppercase_syms(line)

        # Also uppercase equate references in the form (expression)
        line = re.sub(r'\b' + re.escape('msize') + r'\b', 'MSIZE', line, flags=re.IGNORECASE)

        result.append(line)

    # Add SECTRN alias for SECTRAN (CPM22 calls it SECTRN)
    for i, line in enumerate(result):
        if line.strip().startswith('SECTRAN:'):
            # Insert SECTRN EQU SECTRAN right after the SECTRAN label
            result.insert(i + 1, 'SECTRN\tEQU\tSECTRAN\n')
            break

    return result


def main():
    src_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)))
    cpm_path = os.path.join(src_dir, 'CPM22.ASM')
    cbios_path = os.path.join(src_dir, 'CBIOS.ASM')
    out_path = os.path.join(src_dir, 'cpm22_bios.asm')

    # Read CPM22.ASM (lines 1-3711)
    with open(cpm_path, 'r') as f:
        cpm_lines = f.readlines()
    cpm_part = cpm_lines[:3711]

    # Read and transform CBIOS.ASM
    with open(cbios_path, 'r') as f:
        cbios_lines = f.readlines()
    cbios_part = transform_cbios(cbios_lines)

    # Write merged file
    with open(out_path, 'w') as f:
        f.writelines(cpm_part)
        f.writelines(cbios_part)

    print(f"Created: {out_path}")
    print(f"  CPM22.ASM lines: {len(cpm_part)}")
    print(f"  CBIOS.ASM lines (transformed): {len(cbios_part)}")
    print(f"  Total: {len(cpm_part) + len(cbios_part)} lines")


if __name__ == '__main__':
    main()
