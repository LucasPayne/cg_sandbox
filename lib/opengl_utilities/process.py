
f = open("text", "r")
lines = f.readlines()

# for line in lines:
#     if line.startswith("    auto val = glad_") or line.startswith("    glad_"):
#         start = line.find("(")+1
#         end = line.find(")")
#         print(line[:start], end="")
#         params = line[start:end].split(",")
#         for i,param in enumerate(params):
#             param = param.strip()
#             p = param.split(" ")[-1]
#             if p[:2] == "**":
#                 p = p[2:]
#             if p.startswith("*const*"):
#                 p = p[len("*const*"):]
#             if p[0] == "*":
#                 p = p[1:]
#             print(p, end="")
#             if (i != len(params)-1):
#                 print(", ", end="")
#         print(");")
#     else:
#         print(line, end="")

for line in lines:
    params = line[line.find("(")+1:line.find(")")].split(",")
    print(line[:line.find("(")+1], end="")
    for i,param in enumerate(params):
        param = param.strip()
        if param == "":
            continue
        p = param.split(" ")[-1]
        if p[:2] == "**":
            p = p[2:]
        if p.startswith("*const*"):
            p = p[len("*const*"):]
        if p[0] == "*":
            p = p[1:]
        print(p, end="")
        if (i != len(params)-1):
            print(", ", end="")
    print(")", end="")

    name = line[line.find("gl"):line.find("(")]
    print(" _" + name + "(", end="")
    params += ["__FILE__", "__LINE__"]
    for i,param in enumerate(params):
        param = param.strip()
        if param == "":
            continue
        p = param.split(" ")[-1]
        if p[:2] == "**":
            p = p[2:]
        if p.startswith("*const*"):
            p = p[len("*const*"):]
        if p[0] == "*":
            p = p[1:]
        print(p, end="")
        if (i != len(params)-1):
            print(", ", end="")
    print(")")
