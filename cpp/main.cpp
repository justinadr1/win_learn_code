
#include <iostream>
using namespace std;

class Node
{
public:
    std::string key;
    int value;
    Node* next;
    Node(const std::string& k, int v) : key(k), value(v), next(nullptr) {}
};  

class Map
{
private:
    Node** buckets;
    size_t table_size;

    Map(size_t size = 1024)
    {
        table_size = size;
        buckets = new Node*[table_size];
        for (size_t i = 0; i < table_size; i++)
            buckets[i] = nullptr;       
    }

    ~Map()
    {
        for (size_t i = 0; i < table_size; i++)
        {
            Node* curr = buckets[i];
            while (curr)
            {
                Node* tmp = curr;
                curr = curr->next;
                delete tmp;
            }
        }
        delete[] buckets;
    }


    size_t hash(const std::string& key)
    {
        size_t hash = 5381;
        for (char c : key)
            hash = ((hash << 5) + hash) + c;
        return hash % table_size;
    }

    void put(const std::string& key, int value)
    {
        size_t idx = hash(key);
        Node* curr = buckets[idx];
        while (curr)
        {
            if (curr->key == key)
            {
                curr->value = value;
                return;
            }
            curr = curr->next;
        }
        Node* node = new Node(key, value);
        node->next = buckets[idx];
        buckets[idx] = node;
    }

    bool get(const std::string& key, int& out)
    {
        size_t idx = hash(key);
        Node* curr = buckets[idx];
        while (curr)
        {
            if (curr->key == key)
            {
                out = curr->value;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    void remove(const std::string& key)
    {
        size_t idx = hash(key);
        Node* curr = buckets[idx];
        Node* prev = nullptr;
        while (curr)
        {
            if (curr->key == key)
            {
                if (prev)
                    prev->next = curr->next;
                else
                    buckets[idx] = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void printAll() const
    {
        for (size_t i = 0; i < table_size; i++)
        {
            Node* curr = buckets[i];
            while (curr)
            {
                std::cout << curr->key << " = " << curr->value << '\n';
                curr = curr->next;
            }
        }
    }


};



int main()
{
    
    Node* x = new Node("Fuck", 4);
    Node* y = new Node("Chat", 5);
    Node* z = new Node("GPT", 6);
    

    Node** nodes = new Node*[3];

    nodes[0] = x;
    nodes[1] = y;
    nodes[2] = z;

    std::cout << x << std::endl;
    std::cout << y << std::endl;
    std::cout << z << std::endl << std::endl;

    for (int i = 0; i < 3; i++)
        std::cout << nodes[i] << std::endl;

    for (int i = 0; i < 3; i++)
        delete nodes[i];

    delete[] nodes;
}
