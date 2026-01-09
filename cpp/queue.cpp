#include <iostream>
#include <thread>
using namespace std;

struct Node
{
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

class Queue
{
public:
    Node* front;
    Node* rear;

    Queue() : front(nullptr), rear(nullptr) {}

    bool empty() const
    {
        return front == nullptr;
    }

    void enqueue(int v)
    {
        Node* n = new Node(v);
        
        if (rear == nullptr)
        {
            front = rear = n;
            cout << "enqueue = " << rear << endl;
        }
        else
        {
            rear->next = n;
            rear = n;
            cout << "enqueue = " << rear << endl;
        }
    }

    void dequeue()
    {
        if (empty())
            return;
        cout << "dequeue = " << front << endl;
        Node* t = front;
        front = front->next;


        if (front == nullptr)
            rear = nullptr;
        
        delete t;
    }

    int peek() const 
    {
        if (empty())
            throw std::runtime_error("queue empty");
        return front->val;
    }

    ~Queue()
    {
        while (!empty())
            dequeue();
    }

};


int main() 
{
    
    Queue q;

    q.enqueue(40);
    q.enqueue(50);
    q.enqueue(60);

    cout << q.peek() << '\n';
    q.dequeue();
    cout << q.peek() << '\n';
    q.dequeue();
    cout << q.peek() << '\n';

}
