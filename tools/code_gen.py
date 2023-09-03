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
for i in sorted_map:
    if any(item in i for item in ['LDA', 'LDX', 'LDY', 'STA', 'STX', 'STY', 'DEX', 'DEY', 'JSR',
                                  'TSX', 'TXS', 'TXA', 'TAX', 'TAY', 'TYA', 'RTS', 'RTI', 'CLC',
                                  'CLD', 'CLI', 'CLV']):
        ops[sorted_map[i]] = '\tCPU6502_' + i

printed_ops = ',\n'.join(ops)

with open(write_target, 'r') as file:
    data = file.readlines()

placeholder_found = False
header_inserted = False
start_idx = data.index('// Code generator placeholder begin\n')
end_idx = data.index('// Code generator placeholder end\n')
code_src = data[:start_idx+1]
code_src.append('const static OpSignature Ops[] = {\n')
code_src.append(printed_ops)
code_src.append('\n};\n')
code_src.extend(data[end_idx:])

with open(write_target, 'w') as file:
    file.writelines(code_src)
