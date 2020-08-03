import subprocess
import sys
import os
import shutil #copyfile
import pathlib #Path.touch

def generate_serialize_header(root, filename):
    path = root + os.sep + filename
    print("Generating serialize header for {}".format(path))
    gen_code = subprocess.check_output(["python3", "reflector.py", path]).decode("utf-8")
    try:
        f = open(path, "r")
    except:
        print("Failed to open header for writing.")
        sys.exit()
    lines = f.readlines()
    serialize_begin = -1
    changed_header_lines = []
    for i,line in enumerate(lines):
        changed_header_lines.append(line)
        if line.strip() == "/*SERIALIZE*/":
            serialize_begin = i
            break
    serialize_header_path = os.path.abspath(root + os.sep + filename[:-2] + ".serialize.h")
    changed_header_lines.append("#include \"{}\"".format(serialize_header_path))
    for line in lines[serialize_begin:]:
        changed_header_lines.append(line)
    f.close()

    # Create the generated header file.
    try:
        serialize_header_file = open(serialize_header_path, "w")
    except:
        print("Failed to create or open serialization header file \"{}\".".format(serialize_header_path))
        sys.exit()
    serialize_header_file.write(gen_code)

    # Now back up the regular header file, as something can and will go wrong.
    backup_path = os.path.abspath(root + os.sep + "." + filename[:-2] + ".backup")
    if not os.path.exists(backup_path):
        pathlib.Path(backup_path).touch()
    try:
        shutil.copyfile(os.path.abspath(path), backup_path)
    except:
        print("Failed to create backup header file \"{}\". Not continuing.".format(backup_path))
        sys.exit()

    # Edit the regular header to include the generated serialize header
    # (This is so that all you need to do is add /*SERIALIZE*/ to a header file. If a #include signified that instead,
    #  then it would need to exist before running the tool, since the preprocessor is invoked.)
    try:
        f = open(path + ".edited", "w")
    except:
        print("Failed to open header file \"{}\" for editing.")
        sys.exit()

    for line in changed_header_lines:
        f.write(line)
    
    


def process_header(root, filename):
    path = root + os.sep + filename
    # Search for the line
    # "/*SERIALIZE*/"
    try:
        f = open(path, "r")
    except:
        print("Failed to open header file \"{}\".".format(path))
        sys.exit()
    if any(line.strip() == "/*SERIALIZE*/" for line in f.readlines()):
        # Generate a SERIALIZE.h for this header to include.
        generate_serialize_header(root, filename)


def main():
    print("Generating reflection headers.")
    if len(sys.argv) != 2:
        print("give good args")
        sys.exit()
    
    dir_path = sys.argv[1]
    if not os.path.isdir(dir_path):
        print("A valid directory must be given.")
        sys.exit()
    
    for root, dirs, files in os.walk(dir_path):
        path = root.split(os.sep)
        for filename in files:
            if filename.endswith(".h"):
                process_header(root, filename)
main()
