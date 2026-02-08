#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>
using namespace std;

struct _epicClass
{
    void _epicMethod()
    {
        int a = 0xaabb;
        cout << "A = " << &a << " = " << hex << a << endl;
        cout << "Epic Method ID : " << this_thread::get_id() << endl;     
    }
};

void _epicThread()
{
    int y = 0x3040;
    cout << "Y = " << &y << " = " << hex << y << endl;
    cout << "Epic Thread ID: " << this_thread::get_id() << endl;
}

void _awesomeThread()
{
    this_thread::sleep_for(chrono::seconds(1));
    int z = 0x5060;
    cout << "Z = " << &z << " = " << hex << z << endl;
    cout << "Awesome Thread ID: " << this_thread::get_id() << endl;
}

int main() 
{
    int x = 0x1020;
    cout << "X = " << &x << " = " << hex << x << endl;
    cout << "Main Thread ID: " << this_thread::get_id() << endl;

    this_thread::sleep_for(chrono::milliseconds(1500));
    thread epic(_epicThread);
    
    this_thread::sleep_for(chrono::milliseconds(1500));
    thread awesome(_awesomeThread);
    
    this_thread::sleep_for(chrono::milliseconds(1500));
    _epicClass _epicObject;
    thread method(&_epicClass::_epicMethod, &_epicObject);
    // or: thread method([&_epicObject]() { _epicObject._epicMethod(); });
    
    

    epic.join();
    cout << "Epic Thread Finished\n";

    awesome.join();
    cout << "Awesome Thread Finishsed\n";
    
    method.join();
    cout << "Epic Method Thread Finished\n";


    return 0;
}       