import os

script_path = __file__
parent = os.path.split(__file__)[0]
root = os.path.split(parent)[0]
target = os.path.join(os.path.join(root, 'inc'), 'CPU6502_OpCodes.h')

with open(target, 'r') as file:
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
    if 'LDA' in i or 'LDX' in i or 'LDY' in i:
        ops[sorted_map[i]] = '\tCPU6502_' + i

ops[0x20] = '\tCPU6502_JSR_ABS'
ops[0xCA] = '\tCPU6502_DEX_IMPL'
ops[0x88] = '\tCPU6502_DEY_IMPL'

printed_ops = ',\n'.join(ops)
print('const static OpSignature Ops[] = {')
print(printed_ops)
print('};')
