
#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
};

struct Queue
{
    Node* front;
    Node* rear;
    Queue() : front(nullptr), rear(nullptr) {}

    bool empty()
    {
        return front == nullptr;
    }

    void enqueue(int x)
    {
        Node* node = new Node(x);
        if (!rear)
        {
            front = rear = node;
        }    
        else
        {
            rear->next = node;
            rear = node;
        }
    }

    int dequeu()
    {
        if (!front)
            return 0;
        Node* t = front;
        int a = t->val;
        front = front->next;
        if (!front)
            rear = nullptr;
        delete t;
        return a;
    }

    void printAll()
    {
        if (empty())
        {
            std::cout << "queue empty\n";
            return;
        }
        std::cout << front->val << " <- front\n";
        Node* curr = front->next;
        while (curr)
        {
            std::cout << curr->val;
            std::cout << (curr->next != nullptr ? "\n" : " <- rear\n");
            curr = curr->next;
        }
    }

    int peek()
    {
        if (empty())
            return 0;
        return front->val;
    }


    ~Queue()
    {
        while (!empty())
            dequeu();
    }

};


int main()
{
    Queue line;

    line.enqueue(400);
    line.printAll();
    std::cout << std::endl;
    
    line.enqueue(600);
    line.printAll();
    std::cout << std::endl;
    
    line.enqueue(800);
    line.printAll();
    std::cout << std::endl;
    
    line.dequeu();
    line.printAll();
    std::cout << std::endl;
    
    line.dequeu();
    line.printAll();
    
    line.dequeu();
    line.printAll();
}