#
# Extract the struct/class declarations declared in the header file which derive from dummy class SERIALIZE.
# This is done after pre-processing. Only structs/classes defined in the file, not through #includes, are considered.
#

# C++ syntax understanding here is minimal, so SERIALIZE struct declarations
# should be written simply as to be readable by this tool.
import subprocess
import sys
import os

if len(sys.argv) != 2:
    print("give good args")
    sys.exit()

filename = sys.argv[1]
if not os.path.exists(filename):
    print("File \"{}\" does not exist.".format(filename))
    sys.exit()

if not filename.endswith(".h"):
    print("Reflector only works with header files ending with \".h\".")
    sys.exit()

# Helper function that tests if a line is the start of a SERIALIZE struct/class declaration.
def is_named_struct(line):
    if line.startswith("struct") or line.startswith("class"):
        if line.find("SERIALIZE") >= 0:
            words = line.split(" ")
            if (len(words) >= 2):
                return (True, words[1])
    return (False, "")

# In the non-preprocessed file, find each SERIALIZE struct or class declaration,
# and store a list of their names.
f = open(filename, "r")
f_lines = f.readlines()
struct_names = []
for line in f_lines:
    (is_declaration, name) = is_named_struct(line)
    if is_declaration:
        struct_names.append(name)

# Run the file through "g++ -E", which is the C preprocessor with C++ standard include directories.
pp = subprocess.check_output(["g++", "-E", "-I", "../../core", "-I", "../../lib", filename])

# Look for the named structs (included SERIALIZE structs aren't considered),
# and output the whole declaration. This filters out everything the code generator doesn't need to look at.
pp_lines = [line.decode("utf-8") for line in pp.split(b"\n")] # Convert from bytes to string.
line_iter = iter(pp_lines)
struct_declarations = []
while True:
    line = next(line_iter, 0)
    if line == 0:
        break # note: This could be done with :=.

    (is_declaration, name) = is_named_struct(line)
    if is_declaration:
        print(name)
    if is_declaration and name in struct_names:
        starting_brace = line.find("{")
        num_braces = 1

        struct_declaration = line + "\n"
        # Track brace stack to capture the declaration. Incomplete braces in comments will mess with this.
        while True:
            line = next(line_iter, 0)
            if line == 0:
                break
            done = False
            for i,c in enumerate(line):
                if c == "{":
                    num_braces += 1
                if c == "}":
                    num_braces -= 1
                    if num_braces == 0:
                        struct_declaration += line[:i+1] + "\n"
                        done = True
                        break
            if done:
                break
            struct_declaration += line + "\n"
        struct_declarations.append(str(struct_declaration))


def fail(string):
    print("ERROR:", string)
    sys.exit()

def generate_code(declaration):
    code = ""
    lines = [line for line in declaration.split("\n")]

    colon_pos = declaration.find(":")
    if colon_pos < 0:
        fail("Must derive from at least base class SERIALIZE.")
    first_brace_pos = declaration.find("{")
    bases = [base.strip() for base in declaration[colon_pos+1:first_brace_pos].split(",")]

    if "SERIALIZE" not in bases:
        fail("SERIALIZE must be a base class.")
    serialized_base_names = []
    for base in bases:
        words = base.split(" ")
        if len(words) == 2 and words[0] == "public":
            # Derives from public class. This must be serializable by the rules of this tool.
            #--What about protected?
            serialized_base_names.append(words[1])
    for name in serialized_base_names:
        print("serialized base class:", name)


    return code
	

gen_code = ""
for declaration in struct_declarations:
    print(declaration)
    input()
    # Run the declaration through the parser.
    # gen_code = subprocess.check_output(["./reflector_parser", "temp", filename])
    # gen_code_lines = [line.decode("utf-8") for line in gen_code.split(b"\n")]
    gen_code += generate_code(declaration)
print(gen_code)
