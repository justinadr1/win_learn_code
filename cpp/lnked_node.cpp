#include <iostream>
using namespace std;

struct LinkedNode
{
    LinkedNode* next;
    int val;

    LinkedNode() : val(0), next(nullptr) {}
    LinkedNode(int x) : val(x), next(nullptr) {}
    LinkedNode(int x, LinkedNode* n) : val(x), next(n) {}
};

void insertHead(LinkedNode*& head, int val)
{
    LinkedNode* node = new LinkedNode(val);
    node->next = head;
    head = node;
}

void insertTail(LinkedNode*& head, int val)
{
    LinkedNode* node = new LinkedNode(val);

    if (head == nullptr)
    {
        head = node;
        return;
    }
    
    LinkedNode* curr = head;
    while (curr->next != nullptr)
    {
        curr = curr->next;
    }
    curr->next = node;
}

void printList(LinkedNode* head)
{
    LinkedNode* curr = head;
    while (curr != nullptr)
    {
        cout << hex << "0x" << curr->val;
        if (curr->next != nullptr)
            cout << " -> ";
        curr = curr->next;
    }
    cout << endl;
}

void deleteList(LinkedNode*& head)
{
    LinkedNode* curr = head;
    while (curr != nullptr)
    {
        LinkedNode* next = curr->next;
        delete curr;
        curr = next;
    }
}

void printMem(LinkedNode* head)
{
    LinkedNode* curr = head;
    while (curr != nullptr)
    {
        LinkedNode* temp = curr->next;
        cout << hex << (void*)curr << ": 0x" << curr->val << endl;
        curr = temp;
    }
}

bool removeNodeR(LinkedNode*& node, int x)
{
    if (node == nullptr)
        return false;

    if (node->val == x)
    {
        LinkedNode* temp = node;
        node = node->next;
        delete temp;
        return true;
    }
    removeNodeR(node->next, x);
}

void removeNodes(LinkedNode*& head, int x)
{
    while (head && head->val == x)
    {
        LinkedNode* temp = head;
        head = head->next;
        delete temp;
    }

    LinkedNode* curr = head;
    while (curr && curr->next)
    {
        if (curr->next->val == x)
        {
            LinkedNode* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        }
        else
        {
            curr = curr->next;
        }
    }
}


int main()
{
    LinkedNode* head = nullptr;

    insertTail(head, 0x30);
    
    insertTail(head, 0x30);

    insertTail(head, 0x43);
    
    insertTail(head, 0x50);
    
    insertTail(head, 0x65);

    insertTail(head, 0x30);

    printMem(head);
    cout << endl;

    removeNodes(head, 0x30);

    printMem(head);
    
    deleteList(head);
}
