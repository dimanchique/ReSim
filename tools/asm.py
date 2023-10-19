import os
import colorama
import instructions_6502

enable_test = True


def pprint(text):
    print(colorama.Fore.GREEN + text + colorama.Fore.RESET)


print("6502 assembler script 0.1")
if enable_test:

    script_path = __file__
    parent = os.path.split(__file__)[0]
    root = os.path.split(parent)[0]

    with open(os.path.join(parent, 'asm_tests/test.asm'), 'r') as file:
        test_asm = file.readlines()

    start_addr = 0x1000

    lines = []
    clean_lines = dict()
    code_lines = dict()
    labels = []

    print("Testing suite run...")
    print()
    pprint("----------------------------------------------------------------------------")
    pprint("Test asm program:")
    pprint("----------------------------------------------------------------------------")
    for i in range(len(test_asm)):
        value = test_asm[i].rstrip()
        if not value:
            continue
        lines.append(value)
        line_num = str(i+1) + ":"
        print(line_num, value)

    print()
    pprint("----------------------------------------------------------------------------")
    pprint("Comment detection:")
    pprint("----------------------------------------------------------------------------")
    for line in lines:
        comment = ""

        if line:
            clean_lines[len(clean_lines)] = line

        if '/' in line or ";" in line:
            line, comment = line.split("/" if "/" in line else ";")
            comment = "#COMMENT: " + comment

        print(line, comment)

    print()
    pprint("----------------------------------------------------------------------------")
    pprint("Line splitting:")
    pprint("----------------------------------------------------------------------------")
    for line in clean_lines:
        print(clean_lines[line].split())

    print()
    pprint("----------------------------------------------------------------------------")
    pprint("Operands detection:")
    pprint("----------------------------------------------------------------------------")
    for line in clean_lines:
        data = clean_lines[line]

        print("Processing line: " + data.strip())
        split = data.split()
        unknown = False
        for i in range(len(split)):
            if split[i] in instructions_6502.instructions:
                instr = split[i]
                if i == 1:
                    print('Possible label: ' + split[0])
                pprint('Instruction: ' + instr)
                if i == 0 and len(split) > 1:
                    print('Operands:' + str(split[1:]))
                args_num = len(split[i:]) - 1
                print("Possible instructions:", str(instructions_6502.get_instruction_type(instr, args_num)))

                unknown = False
                break
            else:
                unknown = True

        if unknown:
            print("Unknown line")

        print('------------------------------------------')
