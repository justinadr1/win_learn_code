import sys

def main():
    print("All arguments:", sys.argv)

    if len(sys.argv) < 3:
        print("Usage: python args.py <name> <age>")
        return

    name = sys.argv[1]
    age = sys.argv[2]

    print(f"Hello {name}, you are {age} years old")

if __name__ == "__main__":
    main()

