class FileLogger:
    def __init__(self, filename):
        self.filename = filename
        self.file = None

    def __enter__(self):
        print("Opening file")
        self.file = open(self.filename, "r")
        return self.file

    def __exit__(self, exc_type, exc_value, traceback):
        print("Closing file")
        self.file.close()
        return False


with FileLogger("log.txt") as f:  # f becomes whatever __enter__ returns
    print(f.read())

