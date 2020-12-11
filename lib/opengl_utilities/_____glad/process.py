
f = open("text", "r")
lines = f.readlines()
for line in lines:
    if line.startswith("    auto val = glad_") or line.startswith("    glad_"):
        start = line.find("(")+1
        end = line.find(")")
        print(line[:start], end="")
        params = line[start:end].split(",")
        for i,param in enumerate(params):
            param = param.strip()
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
        print(");")
    else:
        print(line, end="")
