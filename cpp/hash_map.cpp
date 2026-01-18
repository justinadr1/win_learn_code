#include <iostream>
#include <string>
#include <list>
#include <cstring>
#include <cstdlib>

struct Node
{
    std::string key;
    int value;
    Node* next;

    Node(const std::string& k, int v) : key(k), value(v), next(nullptr) {}
};

class HashMap
{
    Node** buckets;
    size_t table_size;

    size_t hashFunc(const std::string& key) const 
    {
        size_t hash = 5381;
        for (char c : key)
            hash = ((hash << 5) + hash) + c;
        return hash % table_size;
    }

public:
    HashMap(size_t size = 1024)
    {
        table_size = size;
        buckets = new Node*[table_size];
        for (size_t i = 0; i < table_size; i++)
            buckets[i] = nullptr;
    }   

    ~HashMap()
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

    void put(const std::string& key, int value)
    {
        size_t idx = hashFunc(key);
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

    bool get(const std::string& key, int& out) const
    {
        size_t idx = hashFunc(key);
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
        size_t idx = hashFunc(key);
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
    HashMap map(8);

    map.put("one", 1);
    map.put("two", 2);
    map.put("three", 3);
    
    int value;
    if (map.get("one", value))
        std::cout << "one = " << value << '\n';

    map.remove("one");

    if (map.get("one", value))
        std::cout << "one = " << value << '\n';

}