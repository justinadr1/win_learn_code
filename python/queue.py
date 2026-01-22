class Node:
    def __init__(self, x):
        self.val = x
        self.next = None


class Queue:
    def __init__(self):
        self.front = None
        self.rear = None

    def empty(self):
        return self.front is None

    def enqueue(self, x):
        node = Node(x)
        if not self.rear:
            self.front = self.rear = node
        else:
            self.rear.next = node
            self.rear = node

    def dequeue(self):
        if self.empty():
            print("Queue is empty")
            return
        tmp = self.front
        val = tmp.val
        self.front = tmp.next
        if not self.front:
            self.rear = None
        return val

    def peek(self):
        if self.empty():
            return None
        return self.front.val

    def print_all(self):
        if self.empty():
            print("Queue empty")
            return

        print(f"{self.front.val} <- front")

        curr = self.front.next
        while curr:
            if not curr.next:
                print(f"{curr.val} <- rear")
            else:
                print(curr.val)
            curr = curr.next


line = Queue()

line.enqueue(400)
line.print_all()
print()

line.enqueue(500)
line.print_all()
print()

line.enqueue(600)
line.print_all()
print()

line.enqueue(700)
line.print_all()
print()

x = line.dequeue()
line.print_all()
print()
