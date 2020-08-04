#
# Extract the struct/class declarations declared in the header file which derive from dummy class SERIALIZE.
# [removed pre-processing, maybe temporarily] --- This is done after pre-processing.
# Only structs/classes defined in the file, not through #includes, are considered.
#

# C++ syntax understanding here is minimal, so SERIALIZE struct declarations
# should be written simply as to be readable by this tool.
import subprocess
import sys
import os


# Generate templating code, if the serializable struct/class is templated.
def generate_templated_name(name, template_params):
    if len(template_params) == 0:
        return name
    return name + "<" + ", ".join([p[1] for p in template_params]) + ">"

def generate_template_declaration(template_params):
    if len(template_params) == 0:
        return ""
    return "template <" + ", ".join([p[0]+" "+p[1] for p in template_params]) + ">\n"


# Code generators.
#================================================================================
# Declarations
#--------------------------------------------------------------------------------
def generate_pack_declaration(name):
    code = "void pack({name} &obj, std::ostream &out);\n".format(name=name);
    return code
def generate_unpack_declaration(name):
    code = "void unpack(std::istream &in, {name} &obj);\n".format(name=name)
    return code
def generate_print_declaration(name):
    code = "void print({name} &obj);\n".format(name=name)
    return code

# Definitions
#--------------------------------------------------------------------------------
def generate_pack(name, entry_names, array_entries, serialized_base_names, template_params):
    code = ""
    templated_name = generate_templated_name(name, template_params)
    code += generate_template_declaration(template_params)

    code += "void pack({name} &obj, std::ostream &out) {{\n".format(name=templated_name)
    for base_name in serialized_base_names:
        code += "    pack(({base_name} &)obj, out);\n".format(base_name=base_name)
    for entry_name in entry_names:
        code += "    pack(obj.{entry_name}, out);\n".format(entry_name=entry_name)
    for (array_name, array_length) in array_entries:
        code += "    for (int i = 0; i < ( {array_length} ); i++) {{\n".format(array_length=array_length)
        code += "        pack(obj.{array_name}[i], out);\n".format(array_name=array_name)
        code += "    }\n"
    code += "}\n"
    return code

def generate_unpack(name, entry_names, array_entries, serialized_base_names, template_params):
    code = ""
    templated_name = generate_templated_name(name, template_params)
    code += generate_template_declaration(template_params)

    code += "void unpack(std::istream &in, {name} &obj) {{\n".format(name=templated_name)
    for base_name in serialized_base_names:
        code += "    unpack(in, ({base_name} &)obj);\n".format(base_name=base_name)
    for entry_name in entry_names:
        code += "    unpack(in, obj.{entry_name});\n".format(entry_name=entry_name)
    for (array_name, array_length) in array_entries:
        code += "    for (int i = 0; i < ( {array_length} ); i++) {{\n".format(array_length=array_length)
        code += "        unpack(in, obj.{array_name}[i]);\n".format(array_name=array_name)
        code += "    }\n"
    code += "}\n"
    return code

def generate_print(name, entry_names, array_entries, serialized_base_names, template_params):
    code = ""
    templated_name = generate_templated_name(name, template_params)
    code += generate_template_declaration(template_params)

    code += "void print({name} &obj) {{\n".format(name=templated_name)
    code += "    std::cout << \"{name} {{\\n\";\n".format(name=templated_name)
    for base_name in serialized_base_names:
        code += "    std::cout << \"    base {base_name} {{\\n\";\n".format(base_name=base_name)
        code += "    print(({base_name} &)obj);\n".format(base_name=base_name)
        code += "    std::cout << \"    }}\\n\";\n"
    for entry_name in entry_names:
        code += "    std::cout << \"    {entry_name}: \";\n".format(entry_name=entry_name)
        code += "    print(obj.{entry_name});\n".format(entry_name=entry_name)
        code += "    std::cout << \"\\n\";\n"
    for (array_name, array_length) in array_entries:
        code += "    std::cout << \"    array {array_name} [\";\n".format(array_name=array_name)
        code += "    for (int i = 0; i < ( {array_length} ); i++) {{\n".format(array_length=array_length)
        code += "        std::cout << \"    \";\n";
        code += "        print(obj.{array_name}[i]);\n".format(array_name=array_name)
        code += "        std::cout << \",\\n\";\n"
        code += "    }\n"
    code += "    std::cout << \"}\\n\";\n"
    code += "}\n"
    return code


def fail(string):
    print("ERROR:", string)
    sys.exit()

# Parse the struct declaration and call the code generators for each serialization function of this struct.
def generate_code(name, declaration, template_params, generate_definitions):
    code = ""
    lines = [line for line in declaration.split("\n")]

    bases = []
    colon_pos = declaration.find(":")
    if colon_pos >= 0:
        first_brace_pos = declaration.find("{")
        bases = [base.strip() for base in declaration[colon_pos+1:first_brace_pos].split(",")]

    # Collect names of the serializable base classes. Code will be generated to call the serialization functions of these.
    serialized_base_names = []
    for base in bases:
        words = base.split(" ")
        if len(words) == 2 and words[0] == "public":
            # Derives from public class. This must be serializable by the rules of this tool.
            #--What about protected?
            serialized_base_names.append(words[1])

    entry_names = []
    array_entries = []
    # Collect the entries of the struct/class.
    for line in lines[1:]:
        if line.strip().startswith("/*ENTRY*/"):
            inner_line = line[len("/*ENTRY*/"):-1]
            if inner_line.endswith("]"):
                # This is an array entry, handled differently.
                left_bracket_pos = inner_line.rfind("[")
                array_entries.append((inner_line[:left_bracket_pos].split(" ")[-1], inner_line[left_bracket_pos+1:-1]))
            else:
                entry_names.append(inner_line.split(" ")[-1])

    # Templated definitions are put in the header file.
    if len(template_params) > 0:
        if not generate_definitions:
            code += generate_pack(name, entry_names, array_entries, serialized_base_names, template_params)
            code += generate_unpack(name, entry_names, array_entries, serialized_base_names, template_params)
            code += generate_print(name, entry_names, array_entries, serialized_base_names, template_params)
    else:
        if generate_definitions:
            code += generate_pack(name, entry_names, array_entries, serialized_base_names, template_params)
            code += generate_unpack(name, entry_names, array_entries, serialized_base_names, template_params)
            code += generate_print(name, entry_names, array_entries, serialized_base_names, template_params)
        else:
            code += generate_pack_declaration(name)
            code += generate_unpack_declaration(name)
            code += generate_print_declaration(name)
    return code
	

def usage():
    print("Generate serialization header:")
    print("    python3 reflector.py -h [header_file.h]")
    print("Generate serialization definitions:")
    print("    python3 reflector.py -c [header_file.h]")
    

# This program takes one file as input, and searches for SERIALIZE structs/classes defined
# in the file (not #includes). The declarations are extracted and passed on to the code generator.
# Information such as serializable base classes and templating is also extracted here, to be passed for code generation.
def main():
    if len(sys.argv) != 3:
        usage()
        sys.exit()
    
    if sys.argv[1] == "-h":
        # Generating header file.
        generate_definitions = False
    elif sys.argv[1] == "-c":
        # Generating definitions file.
        generate_definitions = True
    else:
        usage()
        sys.exit()
    
    filename = sys.argv[2]
    if not os.path.exists(filename):
        print("File \"{}\" does not exist.".format(filename))
        sys.exit()
    
    if not filename.endswith(".h"):
        print("Reflector only works with header files ending with \".h\".")
        sys.exit()
    
    # Helper function that tests if a line is the start of a SERIALIZE struct/class declaration.
    def is_named_struct(line):
        if line.startswith("/*REFLECTED*/ struct") or line.startswith("/*REFLECTED*/ class"):
            words = line.split(" ")
            if (len(words) >= 3):
                return (True, words[2])
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
    # pp = subprocess.check_output(["g++", "-E", "-I", "../../core", "-I", "../../lib", "-I", "../../tools", filename])
    #---preprocessor might not be necessary ...
    pp = subprocess.check_output(["cat", filename])
    
    # Look for the named structs (included SERIALIZE structs aren't considered),
    # and output the whole declaration. This filters out everything the code generator doesn't need to look at.
    pp_lines = [line.decode("utf-8") for line in pp.split(b"\n")] # Convert from bytes to string.
    line_iter = iter(pp_lines)
    struct_declarations = []
    struct_template_params = []
    line = ""
    while True:
        prev = line #need one line lookback.
        line = next(line_iter, 0)
        if line == 0:
            break # note: This could be done with :=.
    
        (is_declaration, name) = is_named_struct(line)
        if is_declaration and name in struct_names:
            # Look back one line to see if this struct/class is templated.
            # The struct/class must be declared with the templating on the line above.
            template_params = []
            if prev.strip().startswith("template"):
                # print(prev)
                langle_pos = prev.find("<")
                rangle_pos = prev.find(">")
                params = prev[langle_pos+1:rangle_pos]
                # print(params)
                template_params += [param.split(" ") for param in params.split(",")]
            # print(template_params)
            if any(len(param) != 2 for param in template_params):
                fail("Malformed template parameter.")

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
            struct_template_params.append(template_params)
    
    gen_code = ""
    for i,declaration in enumerate(struct_declarations):
        # Run the declaration through the parser.
        gen_code += generate_code(struct_names[i], declaration, struct_template_params[i], generate_definitions)
    print(gen_code)

main()
