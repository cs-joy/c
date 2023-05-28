#include<stdio.h>
#include<stdlib.h> // malloc()
#include<string.h> // strlen()
#include<ctype.h> // igdigit()

void menu();
char* postfix;

char* infixToPostfix(char* infix);
int evaluatePostfix(char* postfix);
int evaluateResult;
void display();

#define MAX_EXPR_SIZE 1000
char infix[MAX_EXPR_SIZE];

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

    return pop(stack);

}
char infix[MAX_EXPR_SIZE];

void display(char* infix, char* postfix, int evaluateResult)
{
    printf("The infix expression \"%s\" converts to the postfix expression \"%s\" and evaluates to \"%d\".\n\n", infix, postfix, evaluateResult);

    menu();
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

    switch(choice)
    {
        case 1:
          printf("Enter an Infix Expression: ");
          scanf("%s", infix);
          menu();
          break;
        case 2:
          postfix = infixToPostfix(infix);
          if (postfix)
          {
            printf("successfully converted into postfix expression \"%s\".\n\n", postfix);
          }
          menu();
          break;
        case 3:
          evaluateResult = evaluatePostfix(postfix);
          if (evaluateResult)
          {
            printf("successfully evaluated the postfix expression!\n\n");
          }
          menu();
          break;
        case 4:
          display(infix, postfix, evaluateResult);
          free(postfix);
          break;
        case 0:
          out();
          break;
    }
}


int main() {
    menu();

    return 0;
}
