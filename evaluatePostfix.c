#include <stdio.h>
#include<stdlib.h> // malloc()
#include<string.h> // strlen()
#include<ctype.h> // igdigit()

// use define data type
// struct Stack 
// {
//     int top;
//     unsigned capacity;
//     int* array;
// };

struct Stack {
	int top;
	unsigned capacity;
	int* array;
};

// Stack operation
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    
    if (!stack)
    {
        return NULL;
    }
    
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    
    if (!stack->array)
    {
        return NULL;
    }
    
    return stack;
}

// check if stack is empty or not
int checkEmpty(struct Stack* stack)
{
    return stack->top = -1;
}

// pop out operands from stack
char pop(struct Stack* stack)
{
    if (!checkEmpty(stack))
    {
        return stack->array[stack->top--];
    }
    return '$';
}

// push operands in stack
void push(struct Stack* stack, char op)
{
    stack->array[++stack->top] = op;
}

// evaluating
int evaluatePostfix(char* postfixExpression)
{
    // create stack of capacity equal to given expression size
    struct Stack* stack = createStack(strlen(postfixExpression));
    int i;
    
    // check if our stack is created successfully or not
    if (!stack)
    {
        return -1;
    }
    
    // scan the given expression, one by one
    for (i=0; postfixExpression[i]; i++)
    {
        // if the scanned character is an operand, push it into stack
        if (isdigit(postfixExpression[i]))
        {
            push(stack, postfixExpression[i] - '0');
        }
        
        // if the scanned character is an operator, pop two elements from 
        //the stack and evalute(apply the oprator) that and push again in the stack
        else
        {
            int v1 = pop(stack);
            int v2 = pop(stack);
            
            switch(postfixExpression[i])
            {
                case '+':
                    push(stack, v2 + v1);
                    break;
                case '-':
                    push(stack, v2 - v1);
                    break;
                case '*':
                    push(stack, v2 * v1);
                    break;
                case '/':
                    push(stack, v2 / v1);
                    break;
            }
        }
    }
    
    return pop(stack);
    
}


int main()
{
    char ex[] = "231*+9-";
   
    printf("postfix evaluation: %d", evaluatePostfix(ex));

    return 0;
}
