import os

script_path = __file__
parent = os.path.split(__file__)[0]
root = os.path.split(parent)[0]
read_target = os.path.join(os.path.join(root, 'inc'), 'CPU6502_OpCodes.h')
write_target = os.path.join(os.path.join(root, 'src'), 'CPU6502_OpHelpers.cpp')

with open(read_target, 'r') as file:
    data = file.readlines()

data = [i for i in data if '=' in i]

op_map = dict()
for i in data:
    splitter = i.split('=')
    key = splitter[0].strip()
    value = int(splitter[1][1:].split(',')[0], 16)
    op_map[key] = value

sorted_map = sorted(op_map.items(), key=lambda x: x[1])
sorted_map = dict(sorted_map)
ops = ['\tCPU6502_NOOP'] * 255
used_instructions = 0
for i in sorted_map:
    if any(item in i for item in ['LDA', 'LDX', 'LDY', 'STA', 'STX', 'STY', 'DEX', 'DEY', 'JSR',
                                  'TSX', 'TXS', 'TXA', 'TAX', 'TAY', 'TYA', 'RTS', 'RTI', 'CLC',
                                  'CLD', 'CLI', 'CLV', 'JMP', 'SEC', 'SEI', 'SED', 'PHP', 'PLP',
                                  'PLA', 'PHA', 'DEC', 'INC', 'INX', 'INY', 'AND', 'EOR', 'ORA',
                                  'ASL', 'LSR', 'BIT', 'ROL', 'ROR']):
        ops[sorted_map[i]] = '\tCPU6502_' + i
        used_instructions += 1

print(f"Used instructions: {used_instructions}/{len(op_map.keys())}")
ops_cpy = ops.copy()
ops_strings = []
while ops_cpy:
    line = ops_cpy[:5]
    ops_cpy = ops_cpy[5:]
    line_str = []
    for i in line:
        line_str.append((str(i)+',').ljust(20))
    res = ''.join(line_str)
    ops_strings.append(res)

ops_to_pass = '\n'.join(ops_strings)

with open(write_target, 'r') as file:
    data = file.readlines()

placeholder_found = False
header_inserted = False
start_idx = data.index('// Code generator placeholder begin\n')
end_idx = data.index('// Code generator placeholder end\n')
code_src = data[:start_idx+1]
code_src.append('const static OpSignature Ops[] = {\n')
code_src.append(ops_to_pass)
code_src.append('\n};\n')
code_src.extend(data[end_idx:])

with open(write_target, 'w') as file:
    file.writelines(code_src)
