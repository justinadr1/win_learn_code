#include <windows.h>
#include <stdio.h>


struct Node
{
    char bufferA[7];
    char bufferB[5];
    int x;
    char bufferC[9];
    float y;
};

int main(void)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    printf("%i\n", sizeof(struct Node));

    int offset_bufferA = (int)( (char*)&node->bufferA - (char*)node );
    int offset_bufferB = (int)( (char*)&node->bufferB - (char*)node );
    int offset_X = (int)( (char*)&node->x - (char*)node );
    int offset_bufferC = (int)( (char*)&node->bufferC - (char*)node );
    int offset_Y = (int)( (char*)&node->y - (char*)node );
    

    printf("bufferA(%i) = offset(%u) = %p\n", sizeof(node->bufferA), offset_bufferA, &node->bufferA);
    printf("bufferB(%i) = offset(%u) = %p\n", sizeof(node->bufferB), offset_bufferB, &node->bufferB);
    printf("X(%i)       = offset(%u) = %p\n", sizeof(node->x), offset_X, &node->x);
    printf("bufferC(%i) = offset(%u) = %p\n", sizeof(node->bufferC), offset_bufferC, &node->bufferC);
    printf("Y(%i)       = offset(%u) = %p\n",  sizeof(node->y),offset_Y, &node->y);

    free(node);

    struct Node nodem = { "abcdef", "abcde", 0xabcdef, "abcdefghi", 1.5f };
    
    nodem.bufferA[6] = '\0';

    printf("\n%u\n", (int) ((char*)&nodem.bufferA - (char*)&nodem));
    printf("%u\n", (int) ((char*)&nodem.bufferB - (char*)&nodem));
    printf("%u\n", (int) ((char*)&nodem.x - (char*)&nodem));
    printf("%u\n", (int) ((char*)&nodem.bufferC - (char*)&nodem));
    printf("%u\n", (int) ((char*)&nodem.y - (char*)&nodem));

    printf("%s, hex = 0x%X | dec = %d\n", nodem.bufferA, nodem.x, nodem.x);
    
    // overwrite nodem.x's first byte
    nodem.bufferA[12] = 0x35;
    
    printf("%s, hex = 0x%X | dec = %d\n", nodem.bufferA, nodem.x, nodem.x);
    

}
