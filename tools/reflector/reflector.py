#
# Extract the struct/class declarations declared in the header file which derive from dummy class SERIALIZE.
# This is done after pre-processing. Only structs/classes defined in the file, not through #includes, are considered.
#

# C++ syntax understanding here is minimal, so SERIALIZE struct declarations
# should be written simply as to be readable by this tool.
import subprocess
import sys
import os

def generate_pack(name, entry_names, serialized_base_names):
    code = "void pack({name} &obj, std::ostream &out) {{\n".format(name=name)
    for base_name in serialized_base_names:
        code += "    pack(({base_name} &)obj, out);\n".format(base_name=base_name)
    for entry_name in entry_names:
        code += "    pack(obj.{entry_name}, out);\n".format(entry_name=entry_name)
    code += "}\n"
    return code

def generate_unpack(name, entry_names, serialized_base_names):
    code = "void unpack(std::ostream &in, {name} &obj) {{\n".format(name=name)
    for base_name in serialized_base_names:
        code += "    unpack(in, ({base_name} &)obj);\n".format(base_name=base_name)
    for entry_name in entry_names:
        code += "    unpack(in, obj.{entry_name});\n".format(entry_name=entry_name)
    code += "}\n"
    return code

def generate_print(name, entry_names, serialized_base_names):
    code = "void print({name} &obj) {{\n".format(name=name)
    code += "    std::cout << \"{name} {{\\n\";\n".format(name=name)
    for base_name in serialized_base_names:
        code += "    std::cout << \"    base {base_name} {{\\n\";\n".format(base_name=base_name)
        code += "    print(({base_name} &)obj);\n".format(base_name=base_name)
        code += "    std::cout << \"    }}\\n\";\n"
    for entry_name in entry_names:
        code += "    std::cout << \"    {entry_name}: \";\n".format(entry_name=entry_name)
        code += "    print(obj.{entry_name});\n".format(entry_name=entry_name)
        code += "    std::cout << \"    \\n\";\n"
    code += "    std::cout << \"}\";\n"
    code += "}\n"
    return code


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
pp = subprocess.check_output(["g++", "-E", "-I", "../../core", "-I", "../../lib", "-I", "../../tools", filename])

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

def generate_code(name, declaration):
    code = ""
    lines = [line for line in declaration.split("\n")]

    colon_pos = declaration.find(":")
    if colon_pos < 0:
        fail("Must derive from at least base class SERIALIZE.")
    first_brace_pos = declaration.find("{")
    bases = [base.strip() for base in declaration[colon_pos+1:first_brace_pos].split(",")]

    # Collect names of the serializable base classes. Code will be generated to call the serialization functions of these.
    if "SERIALIZE" not in bases:
        fail("SERIALIZE must be a base class.")
    serialized_base_names = []
    for base in bases:
        words = base.split(" ")
        if len(words) == 2 and words[0] == "public" and words[1] != "SERIALIZE":
            # Derives from public class. This must be serializable by the rules of this tool.
            #--What about protected?
            serialized_base_names.append(words[1])

    entry_names = []
    # Collect the entries of the struct/class.
    for line in lines[1:]:
        if line.endswith(";") and line.find("(") < 0:
            words = line[:-1].strip().split(" ")
            if len(words) >= 2:
                entry_names.append(words[1])

    code += generate_pack(name, entry_names, serialized_base_names)
    code += generate_unpack(name, entry_names, serialized_base_names)
    code += generate_print(name, entry_names, serialized_base_names)
    return code
	

gen_code = ""
for i,declaration in enumerate(struct_declarations):
    # Run the declaration through the parser.
    # gen_code = subprocess.check_output(["./reflector_parser", "temp", filename])
    # gen_code_lines = [line.decode("utf-8") for line in gen_code.split(b"\n")]
    gen_code += generate_code(struct_names[i], declaration)
print(gen_code)
