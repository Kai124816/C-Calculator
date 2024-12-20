#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef enum
{
   ADD,
   MULT,
   SUBTRACT,
   DIV,
   UNSUPPORTED
} MathOperation;

void IssueBadNumberError()
{
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}
void IssueBadOperationError()
{
    printf("The string does not represent a valid operation.\n");
    exit(EXIT_FAILURE);
}


int strlength(char *str){
    char* ptr = str;
    int count=0;
    while(*ptr != '\0'){
        ptr++;
        count++;
    }
    return count;

}


int power(int x)
{
    int pow_of = x;
    int num = 1;
    int i = 0;

    for(i=0; i<=pow_of; i++)
    {
        num=num*10;
    }
    
    return num;

}


double Is_Num(char *str)
{

    int i = 0;
    int n = strlength(str);
    int counter = 0;
    int is_num = 1;

    if(!((str[0] >= '0' && str[0] <= '9') || str[0] == '-')) // Process digits and '.' for fractional part
        {
            
            IssueBadNumberError();
        }
    
    for(i=1; i<n; i++)
    {
        if(str[i] == '.')
        {
            counter++;
            if(counter>1)
            {
                IssueBadNumberError();
            }   
        }
        if(!((str[i] >= '0' && str[i] <= '9') || str[i] == '.')) // Process digits and '.' for fractional part
        {
            IssueBadNumberError();
        }
    }
    return is_num;
}


double CalculateFraction(char *str)
{
    double fraction = 0.0;
    int fractionDigits = 0;
    int i = 0;
    int n = strlength(str);
    
    for(i=0; i<n; i++)
    {
        fraction += (double)(str[i] - '0')/(double)(power(i));
        // printf("%lf\n", fraction);
        // printf("%d\n", i);
        // printf("%c\n",str[i]);
        // printf("%d\n",(power(i+1)));
        // printf("%d\n", (str[i] - '0'));

        
    }
    
    // Return the fractional part
    return fraction;
}


int CalculateInteger(char *str)
{
    int final = 0;
    int fractionDigits = 0;
    int n = strlength(str);
    
    for(int i=0; i<n; i++)
    {
        if(str[i]=='.')
        {
            n=i;
            break;
        }
    }
    for(int i=0; i<n; i++)
    {
        final+=(str[i] - '0')*power(n-i-2);
    }
    
    // Return the fractional part
    return final;
}


double StringToDouble(char* str)
{
    int sign = 0; 
    if(str[0] == '-')
    {
        sign=1;
        str++;
    }
    int n = strlength(str);
    int i = 0;
    double num = CalculateInteger(str);
    double fraction = 0; // Variable to store the fractional part
    
    Is_Num(str);
    
    for(i=0; i<n; i++) // Process digits and '.' for fractional part
    {
        
        if(str[i] == '-')
        {
            sign = -1;
        }
        if (str[i] == '.') 
        {
            fraction=CalculateFraction(&str[i+1]); 
        }

               
    }
    
    double result = num+fraction;
    return sign ? result*-1.0 : result;
}


MathOperation GetOperation(char *op)
{
    if (strlength(op)!=1)
    {
        return UNSUPPORTED;
    }
    if (*op == '+')
    {
        return ADD;
    }
    else if (*op == '-')
    {
        return SUBTRACT;
    }
    else if (*op == 'x' ) 
    {
        return MULT;
    }
    else if (*op == '/')
    {
        return DIV;
    }
    
    return UNSUPPORTED;
}

typedef struct Stack 
{
    double *data;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) 
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (double *)malloc(capacity * sizeof(int));
    return stack;
}

void push(Stack *stack, double item) 
{
    stack->data[++stack->top] = item;
}

int pop(Stack *stack) 
{
    return stack->data[stack->top--];
}

int main(int argc, char *argv[])
{
    Stack *main_stack = createStack(10);
    for(int i=1;i<argc;i++)
    {
        if(GetOperation(argv[i])==UNSUPPORTED)
        {
            push(main_stack,StringToDouble(argv[i]));
        }
        if(GetOperation(argv[i])==ADD)
        {
            double operand1 = main_stack->data[main_stack->top];
            pop(main_stack);
            double operand2 = main_stack->data[main_stack->top];
            pop(main_stack); 
            double result = operand1 + operand2;
            push(main_stack,result);
        }
        if(GetOperation(argv[i])==SUBTRACT)
        {
            double operand1 = main_stack->data[main_stack->top];
            pop(main_stack);
            double operand2 = main_stack->data[main_stack->top];
            pop(main_stack);
            double result = operand2 - operand1;
            push(main_stack,result);
        }
        if(GetOperation(argv[i])==MULT)
        {
            double operand1 = main_stack->data[main_stack->top];
            pop(main_stack);
            double operand2 = main_stack->data[main_stack->top];
            pop(main_stack);
            double result = operand1 * operand2;
            push(main_stack,result);
        }
    }
    double final_total = main_stack->data[main_stack->top];
    printf("The total is %d\n", (int) final_total);
    free(main_stack);

}

