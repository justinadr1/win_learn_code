

class Node:
    def __init__(self, x):
        self.val = x
        self.bot = None

class Stack:
    def __init__(self):
        self.top = None

    def empty(self) -> bool:
        return self.top is None

    def push(self, x):
        node = Node(x)  
        node.bot = self.top
        self.top = node
    
    def pop(self) -> int:
        if self.empty():
            print("stack empty")
            return
        tmp = self.top
        val = tmp.val
        self.top = tmp.bot
        return val

    def print_all(self):
        print(f"{self.top.val} <- top")
        node = self.top.bot
        while node:
            print(f"{node.val}")
            node = node.bot
    def peek(self):
        if self.empty():
            print("Stack empty")
            return None
        return self.top.val
    
stack = Stack()

stack.push(400)
stack.push(500)
stack.push(600)
stack.print_all()
print()

y = stack.pop()
stack.print_all()
print()

