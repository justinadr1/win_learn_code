#include <iostream>
#include <thread>
#include <chrono>
#include <string>
using namespace std;

class node
{
public:
    char x[6];
    int a;
    char y[7];
    char z[9];
    int b;
    node(int v) : a(v), b(0)  
    {
        int q = 1;
        for (int i = 0; i < sizeof(x); i++)
            x[i] = q++;
        for (int i = 0; i < sizeof(y); i++)
            y[i] = q++;
        for (int i = 0; i < sizeof(z); i++)
            z[i] = q++;
    }

    node(char* a, char* b, int v) : a(v) 
    {
        for (int i = 0; i < sizeof(x); i++)
            x[i] = a[i];
        for (int i = 0; i < sizeof(y); i++)
            y[i] = b[i];
    }
    
};

int main() 
{
    node* buffer[] = { new node("revers", "enginee", 0xaabb), new node("binary", "exploit", 0xccdd), 
        new node("malwre", "devlopm", 0xeeff) };
    int s = 42;
    
    cout << sizeof(node) << endl;
    cout << &s << endl << endl; 

    cout << &buffer[0] << endl;
    cout << &buffer[1] << endl;
    cout << &buffer[2] << endl << endl;
    
    cout << buffer[0] << endl;
    cout << buffer[1] << endl;
    cout << buffer[2] << endl << endl;


    for (int i = 0; i < sizeof(buffer) / sizeof(buffer[0]); i++)
    {
        cout << "x = " << &buffer[i]->x << endl;
        cout << "a = " << &buffer[i]->a << endl;
        cout << "y = " << &buffer[i]->y << endl;
        cout << "z = " << &buffer[i]->z << endl;
        cout << "b = " << &buffer[i]->b << endl << endl;
    }
    
    cout << buffer[2]->a << endl;
    
    (*(buffer + 2))->a = 10;

    cout << buffer[2]->a << endl;


    for (int i = 0; i < sizeof(buffer) / sizeof(buffer[0]); i++)
    {
        delete buffer[i];
    }
   
    cout << endl;


    node nodes[] = { node(0xf1122), node(0xf3344), node(0xf4455), node(0xf6677) };

    cout << &nodes[0] << endl;
    cout << &nodes[1] << endl;
    cout << &nodes[2] << endl;
    cout << &nodes[3] << endl;

}