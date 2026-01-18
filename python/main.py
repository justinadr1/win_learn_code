

file = open("log.txt", "r")
ln = file.readlines()

e = enumerate(ln)

print(type(e))

for l in ln:
    print(l)