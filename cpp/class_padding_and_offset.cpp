#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class nick
{
public:
    char name[10]; 
};

class person
{
public:
    const char* name;
    short age;
    float height;
    nick n;
    char bufferA[12];
    char bufferB[5];
};

int main()
{
    person* justin = new person;

    justin->name = "justin";

    justin->age = 22;

    justin->height = 5.4f;

    char* n = "adrien456";

    for (int i = 0; i < sizeof(nick) - 1; i++)
    {
        justin->n.name[i] = n[i];
    }
    justin->n.name[sizeof(nick)] = '\0';

    for (int i = 0; i < sizeof(justin->bufferA) - 1; i++)
    {
        justin->bufferA[i] = 'a';
    }
    justin->bufferA[sizeof(justin->bufferA)] = '\0';

    for (int i = 0; i < sizeof(justin->bufferB) - 1; i++)
    {
        justin->bufferB[i] = 'b';
    }
    justin->bufferB[sizeof(justin->bufferB)] = '\0';

    size_t offset_name = reinterpret_cast<char*>(&justin->name) - reinterpret_cast<char*>(justin);
    size_t offset_age = reinterpret_cast<char*>(&justin->age) - reinterpret_cast<char*>(justin);
    size_t offset_height = reinterpret_cast<char*>(&justin->height) - reinterpret_cast<char*>(justin);
    size_t offset_nick = reinterpret_cast<char*>(&justin->n) - reinterpret_cast<char*>(justin);
    size_t offset_bufferA = reinterpret_cast<char*>(&justin->bufferA) - reinterpret_cast<char*>(justin);
    size_t offset_bufferB = reinterpret_cast<char*>(&justin->bufferB) - reinterpret_cast<char*>(justin);

    cout << offset_bufferA << endl;

    cout << "name(" << sizeof(justin->name) << ")     = offset(" << offset_name << ")  = " << &justin->name << '\n'; 
    cout << "age(" << sizeof(justin->age) << ")      = offset(" << offset_age << ")  = " << static_cast<void*>(&justin->age) << '\n'; 
    cout << "height(" << sizeof(justin->height) << ")   = offset(" << offset_height << ") = " << &justin->height << '\n';
    cout << "nick(" << sizeof(justin->n) << ")    = offset(" << offset_nick << ") = " << &justin->n << "\n";
    cout << "bufferA(" << sizeof(justin->bufferA) << ") = offset(" << offset_bufferA << ") = " << &justin->bufferA << '\n'; 
    cout << "bufferB(" << sizeof(justin->bufferB) << ")  = offset(" << offset_bufferB  << ") = " << &justin->bufferB << '\n';

    cout << endl;

    cout << sizeof(person) << '\n' << sizeof(justin) << endl;
    
    cout << justin->n.name << endl;

    delete justin;
}