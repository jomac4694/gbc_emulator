import os

# quick script to auto gen some of the opcode stuff because it's super tedious

class Opcode:
    def __init__(self, name, params, op, cycles):
        self.name = name
        self.params = params
        self.op = op
        self.cycles = cycles

def read_codes(filepath):
    op_list = list()
    with open(filepath, "r") as file:
        for line in file:
            line = line.rstrip()
            split = line.split(" ")
            print(split)
            op_list.append(Opcode(split[0], split[1], split[2], split[3]))
    return op_list



op_list = read_codes(os.getcwd()+"/opcodes.txt")
        