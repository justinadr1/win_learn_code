

ip = "10.27.140.39/28"

ip_part, cidr_part = ip.split('/')

cidr = int(cidr_part)

octets = [int(o) for o in ip_part.split('.')]


for i in range(0, 4):
    if i == 3:
        print(octets[i], end="")
        break
    print(f"{octets[i]}.", end="")

print(f"/{cidr}")