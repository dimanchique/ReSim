import os

instructions = [
    'ADC', 'AND', 'ASL', 'BCC', 'BCS', 'BEQ', 'BIT', 'BMI', 'BNE', 'BPL', 'BRK',
    'BVC', 'BVS', 'CLC', 'CLD', 'CLI', 'CLV', 'CMP', 'CPX', 'CPY', 'DEC', 'DEX',
    'DEY', 'EOR', 'INC', 'INX', 'INY', 'JMP', 'JSR', 'LDA', 'LDX', 'LDY', 'LSR',
    'NOP', 'ORA', 'PHA', 'PHP', 'PLA', 'PLP', 'ROL', 'ROR', 'RTI', 'RTS', 'SBC',
    'SEC', 'SED', 'SEI', 'STA', 'STX', 'STY', 'TAX', 'TAY', 'TSX', 'TXA', 'TXS', 'TYA'
]

instruction_type_size = {
    "IM":   2, "ACC":  1, "REL":  2, "IMPL": 1,
    "ZP":   2, "ZPX":  2, "ZPY":  2,
    "ABS":  3, "ABSX": 3, "ABSY": 3,
    "INDX": 2, "INDY": 2, "IND": 3,
}

args_num_classification = {
    "IM":   [0, 1], "ACC":  [0, 1], "REL":  1, "IMPL": 0,
    "ZP":   1, "ZPX":  2, "ZPY":  2,
    "ABS":  1, "ABSX": 1, "ABSY": 1,
    "INDX": 2, "INDY": 2, "IND": 1
}

instruction_types = dict()

script_path = __file__
parent = os.path.split(__file__)[0]
root = os.path.split(parent)[0]
read_target = os.path.join(os.path.join(root, 'inc'), 'MOS6502_OpCodes.h')

with open(read_target, 'r') as file:
    data = file.readlines()

data = [i for i in data if '=' in i]

ops = []
for i in data:
    splitter = i.split('=')
    ops.append(splitter[0].strip())

for instr in ops:
    instr = instr.split('_')
    if instr[0] in instruction_types:
        instruction_types[instr[0]].append(instr[1])
    else:
        instruction_types[instr[0]] = [instr[1]]


def get_instruction_type(instruction, args_num):
    possible_instructions = []
    if instruction in instructions:
        types = instruction_types[instruction]
        for instr_type in types:
            if instr_type in args_num_classification:
                instr_type_args = args_num_classification[instr_type]
                if type(instr_type_args) is list:
                    for arg in instr_type_args:
                        if arg == args_num:
                            possible_instructions.append(instr_type)
                elif args_num_classification[instr_type] == args_num:
                    possible_instructions.append(instr_type)
    return possible_instructions
