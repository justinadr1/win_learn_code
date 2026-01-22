lines = []          
current_line = []  
word = bytearray() 

with open("code.bin", "rb") as f:
    while True:
        b = f.read(1)
        if not b:
            if word: 
                current_line.append(word.decode('utf-8', errors='ignore'))
            if current_line:
                lines.append(current_line)
            break

        byte_val = b[0]
        if byte_val == 0x20: 
            if word:
                current_line.append(word.decode('utf-8', errors='ignore'))
                word.clear()
        elif byte_val == 0x3B: 
            if word:
                current_line.append(word.decode('utf-8', errors='ignore'))
                word.clear()
            if current_line:
                lines.append(current_line)
                current_line = [] 
        else:
            word.append(byte_val)
            print(word)

# Print results
for i, line in enumerate(lines):
    print(f"Line {i+1}: {line}")

a = 0
if lines[0][0] == "set":
    a = int(lines[0][3])

print(a)
