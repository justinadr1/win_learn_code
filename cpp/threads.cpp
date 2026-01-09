#include <iostream>
#include <thread>
#include <chrono>

void worker_thread() 
{
    std::cout << "Worker thread: running\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Worker thread: done\n";
}

int main() 
{
    std::cout << "Main thread: starting worker\n";

    std::thread t(worker_thread); 

    std::cout << "Main thread: waiting\n";
    t.join();

    std::cout << "Main thread: exiting\n";
    return 0;
}
