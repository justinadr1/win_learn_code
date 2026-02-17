#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>
using namespace std;

void worker()
{
    std::cout << "worker thread id: " << std::this_thread::get_id() << '\n';
}

int main() 
{
    
    std::thread t(worker);

    std::cout << "main thread id: " << std::this_thread::get_id() << '\n';

    t.join();

    return 0;
}       