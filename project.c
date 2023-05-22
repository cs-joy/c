// @spring 2023 - Data Structure->project
// @Zahangir Alam

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int ch;
void menu();
char* convert(char* infix);
void evaluate();
void display();

#define MAX_EXPR_SIZE 100

char infix[MAX_EXPR_SIZE];

void getInput()
{
    printf("Enter infix expression: ");
    scanf("%s", infix);
    menu();
}

void display()
{
    //printf("expression= %s\n", infix);
    
    char* postfix = convert(infix);
    printf("%s\n", postfix);
    free(postfix);
    menu();
}

void out()
{
    exit(0);
}

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
            while(top > -1 && stack[top] == '(')
            {
                postfix[j++] = stack[top--];
            }
            if (top > -1 && stack[top] == ')')
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
            stack[top++] = infix[i];
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

void evaluate()
{
    //
}

void menu()
{
    int choice;
    
    printf("\t*****MAIN MENU*****\n");
    printf("\t1. INFIX Expression\n");
    printf("\t2. INFIX to POSTFIX\n");
    printf("\t3. Evaluate POSTFIX\n");
    printf("\t4. Display\n");
    printf("\t0. EXIT");
    
    printf("\n\nEnter your option: ");
    scanf("%d", &choice);
    
    switch(choice)
    {
        case 1:
          getInput();
          break;
        case 2:
          convert();
          break;
        case 3:
          evaluate();
          break;
        case 4:
          display();
          break;
        default:
          out();
          break;
    }
}


int main()
{
    
    menu();


    return 0;
}
