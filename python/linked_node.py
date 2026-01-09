
class Node:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class LinkedList:
    def __init__(self):
        self.head = None

    def insert_head(self, val):
        node = Node(val)
        node.next = self.head
        self.head = node

    def print_list(self):
        curr = self.head
        while curr:
            print(curr.val, end="")
            if curr.next:
                print(" -> ", end="")
            curr = curr.next
        print()
    
    def clear(self):
        self.head = None


head = LinkedList()
head.insert_head(30)
head.insert_head(40)
head.insert_head(50)

head.print_list()

head.clear()
