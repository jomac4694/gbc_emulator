import os
import glob

# auto gen all of the CPU instruction tests
def gen_test_block(filename):
    hex_val = filename.replace(" ", "").split(".")[0].upper()
    print("MAKE_CPU_TEST(\"../tests/v1/" + filename + "\",cpu_opcode_" + hex_val + ")")


def gen_code():
    for line in glob.glob("../tests/v1/*.json"):
        #if "cb " not in line:
        gen_test_block(os.path.basename(line))



gen_code()