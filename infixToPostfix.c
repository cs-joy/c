#include<stdio.h>
#include<stdlib.h> // malloc()
#include<string.h> // strlen()
#include<ctype.h> // igdigit()
int ch;
void menu();
char* convert(char* infix);
void evaluate();
void display();

#define MAX_EXPR_SIZE 100

// precedence of operator
int precedence(char op)
{
    switch(op)
    {
        case '+':
        case '-':
          return 1;
        case '*':
        case '/':
          return 2;
        case '^':
          return 3;
        default:
          return -1;
    }
}

int isOperator(char op)
{
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^');
}


char* convert(char* infix)
{
    int i, j;
    int len = strlen(infix);
    char* postfix = (char*) malloc(sizeof(char) * (len + 2));
    char stack[MAX_EXPR_SIZE];
    int top = -1;
    
    for (i=0, j=0; i<len; i++)
    {
        if (infix[i] == ' ' || infix[i] == '\t')
        {
            continue;
        }
        
        if (isalnum(infix[i]))
        {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(')
        {
            stack[top++] = infix[i];
        }
        else if (infix[i] == ')')
        {
            while(top > -1 && stack[top] != '(')
            {
                postfix[j++] = stack[top--];
            }
            if (top > -1 && stack[top] != '(')
            {
                return "Invalid Expression";
            } else {
                top--;
            }
        }
        else if (isOperator(infix[i]))
        {
            while(top > -1 && precedence(stack[top]) >= precedence(infix[i]))
            {
                postfix[j++] = stack[top--];
            }
            stack[++top] = infix[i];
        }
    }
    
    while(top > -1)
    {
        if (stack[top] == '(')
        {
            return "Invalid Expression";
        }
        
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0';
    
    return postfix;
}


// evaluate
// use define data type
struct Stack 
{
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
    return stack->top == -1;
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

int main() {
    char infix[MAX_EXPR_SIZE] = "(5 + 3) * 2 - 4 / (1 + 2)"; //"a+b*(c^d-e)^(f+g*h)-i";
    char post[MAX_EXPR_SIZE] = "53+2*412+/-";
    // Function call
    char* postfix = convert(infix);
    printf("%s\n", postfix);
    // free(postfix);

    int option;
    printf("1. convert\n2. evaluate\n3.");
    scanf("%d", &option);

    if (option == 2)
    {
        //char* postfix = convert(infix);
        printf("%d\n", evaluatePostfix(postfix));
        free(postfix);
    }
    // switch(option)
    // {
    //     case 1:
    //         char* postfix = convert(infix);
    //         printf("%s\n", postfix);
    //         free(postfix);
    //         break;
    //     case 2:
    //         evaluatePostfix(convert(infix));
    //         break;
    //     case 3:
    //         printf("%s\n", postfix);
    //         free(postfix);
    //         printf("%d", evaluatePostfix(post));
    //         break;
    // }

    return 0;
}