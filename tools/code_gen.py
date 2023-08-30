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
    if any(item in i for item in ['LDA', 'LDX', 'LDY', 'STA', 'STX', 'STY', 'DEX', 'DEY', 'JSR',
                                  'TSX', 'TXS', 'TXA', 'TAX', 'TAY', 'TYA']):
        ops[sorted_map[i]] = '\tCPU6502_' + i

printed_ops = ',\n'.join(ops)
print('const static OpSignature Ops[] = {')
print(printed_ops)
print('};')
