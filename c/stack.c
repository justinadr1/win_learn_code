#include <windows.h>
#include <stdio.h>


typedef struct Node_
{
    unsigned int val;
    struct Node_* bot;
} Node;

typedef struct Stack_
{
    Node* top;
} Stack;

void push_stack(Stack* stack, int a)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = a;
    node->bot = stack->top;
    stack->top = node;
}

unsigned int pop_stack(Stack* stack)
{
    if (!stack->top)
    {
        printf("Stack is emtpy\n");
        return 0;
    }

    Node* tmp = stack->top;
    int out = tmp->val;
    stack->top = tmp->bot;
    free(tmp);
    return out;
}

int peek_stack(Stack* stack)
{
    if (!stack->top)
    {
        printf("stack is empty\n");
        return 0;
    }
    return stack->top->val;
}

void print_stack(Stack* stack)
{
    if (!stack->top)
    {
        printf("Stack is empty\n");
        return;
    }

    printf("%u <- top\n", stack->top->val);

    Node* node = stack->top->bot;
    while (node)
    {
        printf("%u\n", node->val);
        node = node->bot;
    }
}

void free_stack(Stack* stack)
{
    while (stack->top)
    {
        struct Node* t = stack->top;
        stack->top = stack->top->bot;
        free(t);
    }
}

int main(void)
{
    Stack stack = { NULL };

    push_stack(&stack, 400);
    push_stack(&stack, 500);
    push_stack(&stack, 600);
    push_stack(&stack, 700);

    print_stack(&stack);

    printf("\n");

    printf("popped: %u\n\n", pop_stack(&stack));

    print_stack(&stack);

    free_stack(&stack);
}
