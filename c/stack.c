#include <windows.h>
#include <stdio.h>


struct Node
{
    unsigned int val;
    struct Node* bot;
};

struct Stack
{
    struct Node* top;
};

unsigned int pop(struct Stack* stack)
{
    if (!stack->top)
        return 0;
    struct Node* t = stack->top;
    int a = t->val;
    stack->top = t->bot;
    printf("popped: %p(%u)\n", (void*)t, t->val);
    free(t);
    return a;
}

void push(struct Stack* stack, int a)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->val = a;
    node->bot = stack->top;
    stack->top = node;
    printf("pushed: %p(%u)\n", (void*)stack->top, stack->top->val);
}

void printAll(struct Stack* stack)
{
    if (!stack->top)
        return;

    printf("printing:\n%p(%u) <- top\n", (void*)stack->top, stack->top->val);

    for (struct Node* t = stack->top->bot; t != NULL; t = t->bot)
    {
        printf("%p(%u)\n", (void*)t, t->val);
    }
}

void cleanup(struct Stack* stack)
{
    while (stack->top)
    {
        struct Node* t = stack->top;
        stack->top = stack->top->bot;
        printf("freeing: %p(%u)\n", (void*)t, t->val);
        free(t);
    }
}

int main(void)
{
    struct Stack stack = { NULL };

    push(&stack, 400);
    push(&stack, 500);
    push(&stack, 600);
    push(&stack, 700);

    printf("\n");
    
    printAll(&stack);

    printf("\n");

    pop(&stack);

    printf("\n");

    printAll(&stack);

    printf("\n");

    cleanup(&stack);
}
