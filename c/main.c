#include <windows.h>
#include <stdio.h>

typedef struct address
{
    int octet[4];
    int cidr;
} adr;

void printoct(adr* a)
{
    for (int i = 0; i < 3; i++)
        printf("%i.", a->octet[i]);
    printf("%i\n", a->octet[3]);
}

int main(void)
{
    adr ipv4;
    
    ipv4.octet[0] = 192;
    ipv4.octet[1] = 168;
    ipv4.octet[2] = 100;
    ipv4.octet[3] = 10;

    printoct(&ipv4);

}
