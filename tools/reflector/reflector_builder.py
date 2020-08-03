import subprocess
import sys
import os

if len(sys.argv) != 2:
    print("give good args")
    sys.exit()

dir_path = sys.argv[1]
if not os.path.isdir(dir_path):
    print("A valid directory must be given.")
    sys.exit()

def process_header(root, filename):
    print(root)
    print(filename)

for root, dirs, files in os.walk(dir_path):
    path = root.split(os.sep)
    print((len(path) - 1) * '---', os.path.basename(root))
    for filename in files:
        if filename.endswith(".h"):
            process_header(root, filename)
