import os
import re
import sys
from os import walk
from pathlib import Path
from typing import Callable

# Get CPU name from command line arguments or use default
cpu_name = sys.argv[1] if len(sys.argv) > 1 else 'I8086'

print(f"ReSim instructions table generator. Target CPU: {cpu_name}")

# Determine root paths for file operations
root = Path(__file__).parents[1]
cpu_root = os.path.join(root, 'chips', cpu_name)
cpu_include_root = os.path.join(cpu_root, 'inc')

# Validate that required directories exist
if not os.path.exists(cpu_root) or not os.path.exists(cpu_include_root):
    print("ERROR! Can't find necessary paths:")
    if not os.path.exists(cpu_root):
        print("\t" + cpu_root)
    if not os.path.exists(cpu_include_root):
        print("\t" + cpu_include_root)
    print("Check CPU name and listed paths")
    exit(-1)

# Regular expressions for identifying target files
opcodes_targets_re = re.compile(f'{cpu_name}_OpCodes_([A-Za-z0-9_]+)')
instructions_re = re.compile(f'INSTRUCTIONS_([A-Za-z0-9_]+)')


def group_target_files(regexp: re.Pattern, path: str) -> dict:
    """
    Scan a directory and group files based on a regex pattern.

    Args:
        regexp (re.Pattern): Compiled regular expression to match filenames.
                            Should contain a capture group for the key.
        path (str): Directory path to search for files.

    Returns:
        dict: Dictionary where keys are the captured regex groups and values
              are full file paths to matching files.
    """
    target_storage = dict()
    for (dirpath, dirnames, filenames) in walk(path):
        for filename in filenames:
            re_res = regexp.search(filename)
            if re_res:
                target_storage[re_res.group(1)] = os.path.join(path, filename)
    return target_storage


# Find all opcode definition files and instruction markdown files
read_targets = group_target_files(opcodes_targets_re, cpu_include_root)
instructions_targets = group_target_files(instructions_re, cpu_root)

# Validate that instruction files were found
if len(instructions_targets) == 0:
    print("No instruction groups found")
    exit(-1)

print("Found groups: " + ", ".join(list(instructions_targets.keys())))


def scan_regex(path: str, re_exp: str, callback: Callable) -> None:
    """
    Scan a file line by line and apply a callback to regex matches.

    Args:
        path (str): Path to the file to scan.
        re_exp (str): Regular expression pattern to search for.
        callback (callable): Function to call for each regex match. Should
                            accept a re.Match object as parameter.

    Returns:
        None
    """
    with open(path, 'r') as file:
        re_instance = re.compile(re_exp)
        for line in file.readlines():
            re_res = re_instance.search(line)
            if re_res:
                callback(re_res)

total_used_instructions = 0
detected_instructions = 0

# Process each instruction group
for group_name, group_instructions_file in instructions_targets.items():
    # Skip groups that don't have corresponding opcode definitions
    if group_name not in read_targets:
        continue

    print(f'Processing group "{group_name}"')

    # Extract instruction names from markdown file (lines starting with [x])
    opcodes_list = []
    opcode_re_exp = r'\[x\]\s+(\w+).*$'  # [x] INSTRUCTION_NAME
    scan_regex(group_instructions_file, opcode_re_exp, lambda x: opcodes_list.append(x.group(1)))

    # Extract opcode values from header file
    op_map = dict()
    opcode_re_exp = r'\s+([\w]+)\s+=\s+(0[xX][0-9a-fA-F]+)'  # INSTRUCTION_NAME = 0xAE
    scan_regex(read_targets[group_name], opcode_re_exp, lambda x: op_map.update({x.group(1): int(x.group(2), 16)}))

    print(f'--> Group "{group_name}": ', end="")
    if len(op_map) == 0:
        print('skipped, no instructions found')
        continue
    else:
        print(f'found {len(op_map)} instructions')

    # Create initial opcode table filled with INVALID_OP placeholders
    ops = ['ADD_CALL(INVALID_OP)'] * (max(list(op_map.values())) + 1)

    # Replace placeholders with actual instructions that are marked with [x]
    used_instructions = 0
    for i in op_map:
        """
        fixme:
        We're using 'startswith' method to capture MOS6502 addressing mode instructions
        in this case 'MOS6502_AND' matches MOS6502_AND_IM/ZP/ZPX/ABS/...
        and no need to use AND_IM, AND_ABS, AND_WHATEVER in instructions.md file
        but maybe (!) there's a more clean way to handle this case
        """
        if any(i.startswith(item) for item in opcodes_list):
            ops[op_map[i]] = f'ADD_CALL({i})'
            used_instructions += 1

    total_used_instructions += used_instructions
    detected_instructions += len(op_map.keys())

    # Format the opcode table into rows of 5 instructions for readability
    ops_strings = []
    align_len = max(map(len, ops)) + 3
    while ops:
        row = ops[:5]
        ops = ops[5:]
        row_str = [(op + ',').ljust(align_len) for op in row]
        ops_strings.append(''.join(row_str))

    # Header comment for generated files
    disclaimer_string = '''//##############################################################################
// This is a lookup table entries generated by tools/code_gen.py
// Please don't edit
//##############################################################################

'''

    out_content = disclaimer_string + '\n'.join(ops_strings)

    # Write the generated lookup table to output file
    with open(os.path.join(cpu_include_root, f'{cpu_name}_OpCodesList_{group_name}.h'), 'w') as out_file:
        out_file.writelines(out_content)

used_instructions_percentage = (total_used_instructions/detected_instructions) * 100
print()
print(f"Used instructions: {total_used_instructions}/{detected_instructions} ({used_instructions_percentage:.2f}%)")
