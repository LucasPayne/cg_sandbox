# Generate random data for use in lighting shaders
import random
import math

num_samples = 8
min_dis = 0.25

ns = []
counter = 0
while counter < num_samples:
    (a, b) = (random.uniform(-1,1), random.uniform(-1,1))
    if a**2 + b**2 > 1:
        continue
    bad = False
    for (c,d) in ns:
        if math.sqrt((c-a)**2 + (d-b)**2) < min_dis:
            bad = True
    if bad:
        continue
    counter += 1
    ns += [(a,b)]


axis_angles = []
for s in ns:
    length = math.sqrt(s[0]**2 + s[1]**2)
    axis = (-s[1]/length, s[0]/length)
    axis_angles.append((axis, length))

for (axis, angle) in axis_angles:
    print("vec2({}, {}),".format(axis[0], axis[1]))
print("--")
for (axis, angle) in axis_angles:
    if random.uniform(0,1) > 0.5:
        print("-{},".format(angle))
    else:
        print("{},".format(angle))
    
    


