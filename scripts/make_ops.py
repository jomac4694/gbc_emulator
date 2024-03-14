import os

# quick script to auto gen some of the opcode stuff because it's super tedious

class Opcode:
    def __init__(self, name = "", params = "", op = "", cycles = "", function_name = "", bit = "", p1= ""):
        self.name = name
        self.params = params
        self.op = op
        self.cycles = cycles
        self.param_split = self.params.split(",")
        if (len(self.param_split) == 2):
            self.single_param = False
        else:
            self.single_param = True
            self.param = params
        self.function_name = function_name
        self.bit = bit
        self.p1 = p1
    
    def get_param1(self):
        if self.single_param:
            return self.param
        return self.param_split[0]
    
    def get_param2(self):
        if self.single_param:
            return ""
        return self.param_split[1]

def read_codes2(filepath):
    op_list = list()
    function_name = ""
    with open(filepath, "r") as file:    
        for line in file:
            line = line.rstrip()
            split = line.split(" ")
            cycles = "8"
            if split[3] == "hl":
                cycles = "16"
            op_list.append(Opcode(op=split[0],function_name=split[1], bit=split[2],  p1=split[3], cycles=cycles))    
    return op_list

def gen_code2(op_list):
    for opcode in op_list:
        if opcode.p1 == "hl":
            print("{0x" + opcode.op + ", OpcodeCommand(\" " + opcode.function_name + " " + opcode.bit + ":" + opcode.p1 + "\", std::bind(&Opcode::"+opcode.function_name+"_HL, this, "+ opcode.bit + "), " + opcode.cycles + ")},")
        else:
            print("{0x" + opcode.op + ", OpcodeCommand(\" " + opcode.function_name + " " + opcode.bit + ":" + opcode.p1 + "\", std::bind(&Opcode::"+opcode.function_name+", this, " + opcode.bit + ", &(CPU->" + opcode.p1.upper() + ")), " + opcode.cycles + ")},")


def read_codes3(filepath):
    op_list = list()
    function_name = ""
    with open(filepath, "r") as file:    
        for line in file:
            line = line.rstrip()
            split = line.split(" ")
            cycles = "8"
            if split[2] == "hl":
                cycles = "16"
            op_list.append(Opcode(op=split[0],function_name=split[1], p1=split[2], cycles=cycles))    
    return op_list

def gen_code3(op_list):
    for opcode in op_list:
        if opcode.p1 == "hl":
            print("{0x" + opcode.op + ", OpcodeCommand(\" " + opcode.function_name + " " + opcode.p1 + "\", std::bind(&Opcode::"+opcode.function_name+"_HL, this), " + opcode.cycles + ")},")
        else:
            print("{0x" + opcode.op + ", OpcodeCommand(\" " + opcode.function_name + " " + opcode.p1 + "\", std::bind(&Opcode::"+opcode.function_name+", this, &(CPU->" + opcode.p1.upper() + ")), " + opcode.cycles + ")},")


def read_codes(filepath):
    op_list = list()
    function_name = ""
    with open(filepath, "r") as file:
        for line in file:
            line = line.rstrip()
            if "//" in line:
                function_name = line[2:]
                continue
            split = line.split(" ")
            op = Opcode(split[0], split[1], split[2], split[3], function_name)
            op_list.append(op)
    return op_list


def gen_code(op_list):
    for opcode in op_list:
        if "(" in opcode.get_param2() or "(" in opcode.get_param1() or "#" in opcode.get_param2() or "#" in opcode.get_param1():
                print("{0x" + opcode.op + ", OpcodeCommand(\"0x" + opcode.op + " " + opcode.function_name + " " + opcode.get_param1() + ":" + opcode.get_param2() + "\", std::bind(&Opcode::"+opcode.function_name+", this), " + opcode.cycles + ")},")
        else:
            print("{0x" + opcode.op + ", OpcodeCommand(\"0x" + opcode.op + " " + opcode.function_name + " " + opcode.get_param1() + ":" + opcode.get_param2() + "\", std::bind(&Opcode::"+opcode.function_name+", this, &(Cpu::Instance()->" + opcode.get_param1() + "), &(Cpu::Instance()->" + opcode.get_param2() + ")), " + opcode.cycles + ")},")
#op_list = read_codes(os.getcwd()+"/opcodes.txt")
#gen_code(op_list)
            
op_list = read_codes3(os.getcwd()+"/otherstuff2.txt")
gen_code3(op_list)


        