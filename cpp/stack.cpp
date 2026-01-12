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

    Stack() : top(nullptr)
    {

    }

    bool empty() const { return top == nullptr; }

    unsigned int pop()
    {
        if (!top)
            return 0;
        unsigned int a = top->value;
        Node* t = top;
        top = top->bot;
        delete t;
        return a;
    }

    void push(int x)
    {
        Node* node = new Node(x); 
        node->bot = top;
        top = node;
    }

    void printAll()
    {
        if (!top)
            return;

        cout << top->value << " <- top" << endl;
        
        for (Node* t = top->bot; t != nullptr; t = t->bot)
        {
            cout << t->value << endl;
        }
    }

    ~Stack()
    {
        while (!empty())
            pop();
        
    }
};


int main() 
{
    Stack stack;

    stack.push(400);
    stack.push(500);
    stack.push(600);

    stack.printAll();

    stack.pop();
    cout << ".........\n";
    stack.printAll();

}