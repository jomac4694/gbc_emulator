import os
import glob


def gen_test_block(filename):
    hex_val = filename.replace(" ", "").split(".")[0].upper()
    print("BOOST_AUTO_TEST_CASE(cpu_instruction_" + hex_val + ")")
    print("{")
    print("\tboost::property_tree::ptree pt;")
    print("\tboost::property_tree::read_json(\"/Users/josephmcilvaine/gbc_emulator/tests/v1/" + filename + "\", pt);")
    print("\tfor(auto& a : pt)")
    print("\t{")
    print("\t\tExpected e;")
    print("\t\tSetInitialParams(a);")
    print("\t\tSetExpectedParams(a, e);")
    print("\t\tCPU->Execute();")
    print("\t\tBOOST_CHECK_EQUAL(CPU->PC.value() , e.pc.value());")
    print("\t\tBOOST_CHECK_EQUAL(CPU->SP.value() , e.sp.value());")
    print("\t\tBOOST_CHECK_EQUAL(CPU->A.value() , e.a.value());")
    print("\t\tBOOST_CHECK_EQUAL(CPU->B.value() , e.b.value());")
    print("\t\tBOOST_CHECK_EQUAL(CPU->C.value() , e.c.value());")
    print("\t\tBOOST_CHECK_EQUAL(CPU->D.value() , e.d.value());")
    print("\t\tBOOST_CHECK_EQUAL(CPU->E.value() , e.e.value());")
    print("\t\tBOOST_CHECK_EQUAL(CPU->FLAGS.value() , e.f.value());")
    print("\t\tBOOST_CHECK_EQUAL(CPU->H.value() , e.h.value());")
    print("\t\tBOOST_CHECK_EQUAL(CPU->L.value() , e.l.value());")
    print("\t}")
    print("}")

def gen_code():
    for line in glob.glob("/Users/josephmcilvaine/gbc_emulator/tests/v1/*.json"):
        gen_test_block(os.path.basename(line))


#op_list = read_codes(os.getcwd()+"/opcodes.txt")
#gen_code(op_list)
            
#op_list = read_codes(os.getcwd()+"/otherstuff2.txt")
#gen_code(op_list)
gen_code()