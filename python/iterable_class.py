class Iterable:
    def __init__(self, max_val):
        if max_val % 2 != 0:
            raise ValueError("max_val must be even number")
        self.max_val = max_val
    
    def __iter__(self):
        self.current = 0
        return self

    def __next__(self):
        if self.current > self.max_val:
            raise StopIteration
        val = self.current
        self.current += 2
        return val

itr = Iterable(10)

for i, n in enumerate(itr):
    print(i, n)