
def simple_hash(s, size):
    h = 0
    for c in s:
        h = (h * 31 + ord(c)) % size
    return h

class SimpleHashMap:
    def __init__(self, size=5):
        self.size = size
        self.table = [[] for _ in range(size)]

    def _hash(self, key):
        return simple_hash(key, self.size)

    def put(self, key, value):
        idx = self._hash(key)
        for i, (k, _) in enumerate(self.table[idx]):
            if k == key:
                self.table[idx][i] = (key, value)
                return
        self.table[idx].append((key, value))

    def get(self, key):
        idx = self._hash(key)
        for k, v in self.table[idx]:
            if k == key:
                return v
        raise KeyError(key)

    def delete(self, key):
        idx = self._hash(key)
        for i, (k, _) in enumerate(self.table[idx]):
            if k == key:
                self.table[idx].pop(i)
                return
        raise KeyError(key)



m = SimpleHashMap()
m.put("apple", 10)
m.put("banana", 20)

print(m.table)

m.delete("apple")
print(m.table)  # "apple" removed
