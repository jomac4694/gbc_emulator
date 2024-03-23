import os
import glob

# auto gen all of the CPU instruction tests
def gen_test_block(filename):
    hex_val = filename.replace(" ", "").split(".")[0].upper()
    print("BOOST_AUTO_TEST_CASE(cpu_instruction_" + hex_val + ")")
    print("{")
    print("\tboost::property_tree::ptree pt;")
    print("\tboost::property_tree::read_json(\"../tests/v1/" + filename + "\", pt);")
    print("\tfor(auto& a : pt)")
    print("\t{")
    print("\t\tExpected e;")
    print("\t\tSetInitialParams(a);")
    print("\t\tSetExpectedParams(a, e);")
    print("\t\tCPU->Execute();")
    print("\t\tCheckFinalState(e, a);")
    print("\t}")
    print("}")

def gen_code():
    for line in glob.glob("../tests/v1/*.json"):
        if "cb " not in line:
            gen_test_block(os.path.basename(line))


#op_list = read_codes(os.getcwd()+"/opcodes.txt")
#gen_code(op_list)
            
#op_list = read_codes(os.getcwd()+"/otherstuff2.txt")
#gen_code(op_list)
gen_code()