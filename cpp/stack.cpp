#include <iostream>
#include <thread>
#include <chrono>
#include <string>
using namespace std;

class Node
{
public:
    unsigned int value;
    Node* bot;
    Node(int x) : value(x), bot(nullptr) {}
};

class Stack
{
public:
    Node* top;

    Stack() : top(nullptr) {}

    void push(int x)
    {
        Node* node = new Node(x); 
        node->bot = top;
        top = node;
    }

    unsigned int pop()
    {
        if (!top)
        {
            cout << "stack is empty\n";
            return 0;
        }
        Node* tmp = top;
        unsigned int out = tmp->value;
        top = tmp->bot;
        delete tmp;
        return out;
    }

    void print_stack()
    {
        if (!top)
        {
            cout << "stack is empty\n";
            return;
        }

        cout << top->value << " <- top" << endl;
        
        for (Node* t = top->bot; t != nullptr; t = t->bot)
        {
            cout << t->value << endl;
        }
    }

    ~Stack()
    {
        while (top)
        {
            pop();
        }
    }
};


int main() 
{
    Stack stack;

    stack.push(400);
    stack.push(500);
    stack.push(600);
    stack.push(700);
    
    stack.print_stack();

    stack.pop();
    stack.print_stack();
}