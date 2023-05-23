#include<stdio.h>
#include<stdlib.h> // malloc()
#include<string.h> // strlen()
#include<ctype.h> // igdigit()
int ch;
void menu();
char* postfix;
int evaluateResult;
void evaluate();
void display();

#define MAX_EXPR_SIZE 100
char infix[MAX_EXPR_SIZE];

void getInput()
{
    char infix[MAX_EXPR_SIZE] = "(5 + 3) * 2 - 4 / (1 + 2)";
    printf("Enter infix expression: ");
    scanf("%s", infix);
}

void display()
{
    printf("\n%d", evaluateResult);
    
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

char* infixToPostfix(char* infix)
{
	int i, j;
	int len = strlen(infix);
	char* postfix = (char*)malloc(sizeof(char) * (len + 2));
	char stack[MAX_EXPR_SIZE];
	int top = -1;

	for (i = 0, j = 0; i < len; i++) {
		if (infix[i] == ' ' || infix[i] == '\t')
			continue;
		
		// If the scanned character is operand
		// add it to the postfix expression
		if (isalnum(infix[i])) {
			postfix[j++] = infix[i];
		}
		
		// if the scanned character is '('
		// push it in the stack
		else if (infix[i] == '(') {
			stack[++top] = infix[i];
		}
		
		// if the scanned character is ')'
		// pop the stack and add it to the
		// output string until empty or '(' found
		else if (infix[i] == ')') {
			while (top > -1 && stack[top] != '(')
				postfix[j++] = stack[top--];
			if (top > -1 && stack[top] != '(')
				return "Invalid Expression";
			else
				top--;
		}
		
		// If the scanned character is an operator
		// push it in the stack
		else if (isOperator(infix[i])) {
			while (top > -1
				&& precedence(stack[top])
						>= precedence(infix[i]))
				postfix[j++] = stack[top--];
			stack[++top] = infix[i];
		}
	}

	// Pop all remaining elements from the stack
	while (top > -1) {
		if (stack[top] == '(') {
			return "Invalid Expression";
		}
		postfix[j++] = stack[top--];
	}
	postfix[j] = '\0';
	//menu();
	return postfix;
	//menu();
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
    //menu();
    return pop(stack);
    
}



/////////////////////////////////
// Main menu
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
    
    //char infix[MAX_EXPR_SIZE] = "(5 + 3) * 2 - 4 / (1 + 2)";
    if (choice == 1) {
        getInput();
        menu();
    }
    else if (choice == 2)
    {
        printf("%s", infix);
        /*
        char* postfix = infixToPostfix();
        printf("%d\n", evaluatePostfix(postfix));
        free(postfix);*/
    }
    
    // switch(choice)
    // {
    //     case 1:
    //       getInput();
    //       break;
    //     case 2:
    //       postfix = infixToPostfix(infix);
    //       break;
    //     case 3:
    //       evaluateResult = evaluatePostfix(postfix);
    //       free(postfix);
    //       display();
    //       //break;
    //     case 4:
    //       display();
    //       break;
    //     default:
    //       out();
    //       break;
    // }
}







int main() {
    menu();
    // char infix[MAX_EXPR_SIZE] = "(5 + 3) * 2 - 4 / (1 + 2)"; //"a+b*(c^d-e)^(f+g*h)-i";
    // char post[MAX_EXPR_SIZE] = "53+2*412+/-";
    // // Function call
    // char* postfix = convert(infix);
    // printf("%s\n", postfix);
    // free(postfix);
    
//     char infix[MAX_EXPR_SIZE] = "(5 + 3) * 2 - 4 / (1 + 2)";
// 	char post[MAX_EXPR_SIZE] = "53+2*412+/-";
// 	// Function call
// 	char* postfix = infixToPostfix(infix);
// 	printf("%s\n", postfix);
	
// 	printf("%d\n", evaluatePostfix(postfix));
	//free(postfix);

    //menu();

    // if (option == 2)
    // {
    //     //char* postfix = convert(infix);
    //     printf("%d\n", evaluatePostfix(postfix));
    //     free(postfix);
    // }
    // int option;
    // int result;
    // printf("1. convert\n2. evaluate\n3. display");
    // scanf("%d", &option);
    // switch(option)
    // {
    //     case 1:
    //         printf("first option");
    //         break;
    //     case 2:
    //         result = evaluatePostfix(postfix);
    //         free(postfix);
    //         printf("\n%d", result);
    //         break;
    //     case 3:
    //         printf("\n%d", result);
    //         break;
    // }
    
    return 0;
}