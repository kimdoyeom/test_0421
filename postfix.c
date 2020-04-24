/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20
#define EOS 0

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
    lparen = 0,  /* ( 왼쪽 괄호 */
    rparen = 9,  /* ) 오른쪽 괄호*/
    times = 7,   /* * 곱셈 */
    divide = 6,  /* / 나눗셈 */
    plus = 5,    /* + 덧셈 */
    minus = 4,   /* - 뺄셈 */
    operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];       /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];    /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];    /* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];        /* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;       /* evalStack용 top */

int evalResult = 0;       /* 계산 결과를 저장 */

void postfixPush(char x)//postfix값 받는 것
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()//값 방출
{
    char x;
    if (postfixStackTop == -1)
        return '\0';
    else {
        x = postfixStack[postfixStackTop--];
    }
    return x;
}


void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if (evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s", infixExp);
}

precedence getToken(char symbol) // 토큰값으로 사용자가 입력한 문자를 구별하는데 사용
{
    switch (symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '/': return divide;
    case '*': return times;
    default: return operand;
    }

}

precedence getPriority(char x) //우선순위를 구별하는데 사용
{
    return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
    if (postfixExp == '\0')
        strncpy(postfixExp, c, 1);
    else
        strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
    /* infixExp의 문자 하나씩을 읽기위한 포인터 */
    char* exp = infixExp;
    char x;                     /* 문자하나를 임시로 저장하기 위한 변수 */
                    /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
    while (*exp != '\0') {

        x = exp[0];

        if (getToken(x) == operand)//숫자일때
            charCat(&x);
        else if (getToken(x) == lparen)//왼쪽 괄호일때
            postfixPush(x);
        else if (getToken(x) == times || getToken(x) == divide)//곱셉이나 나눗셈일때
            postfixPush(x);
        else if (getToken(x) == plus || getToken(x) == minus) {//덧셈이나 뺄셈일때
            if (postfixStackTop == -1 || getToken(postfixStack[postfixStackTop]) == lparen) {
                postfixPush(x);
            }
                
            else {
                while (postfixStackTop != -1) {
                    char n;
                    n = postfixPop();
                    charCat(&n);
                }
                postfixPush(x);
            }
        }
        else if (getToken(x) == rparen) {//오른쪽 괄호
             do {
                char n;
                n = postfixPop();
                charCat(&n);
             } while (postfixStack[postfixStackTop] != lparen);
             postfixPop();
        }
        exp++;
    }

    /*do
    {
        x = postfixPop();
        charCat(x);
    } while (postfixStackTop != -1);*/
}
void debug()
{
    printf("\n---DEBUG\n");
    printf("infixExp =  %s\n", infixExp);
    printf("postExp =  %s\n", postfixExp);
    printf("eval result = %d\n", evalResult);

    printf("postfixStack : ");
    for (int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%c  ", postfixStack[i]);

    printf("\n");

}

void reset()
{
    infixExp[0] = '\0';
    postfixExp[0] = '\0';

    for (int i = 0; i < MAX_STACK_SIZE; i++)
        postfixStack[i] = '\0';

    postfixStackTop = -1;
    evalStackTop = -1;
    evalResult = 0;
}

void evaluation()
{
    /* postfixExp, evalStack을 이용한 계산 */
    int  op1, op2;
    int n = 0;

    evalPush(EOS);

    while (postfixExp[n] != '\0') 
    {
        if (getToken(postfixExp[n]) == operand)
            evalPush(postfixExp[n] - '0');
        else {
            op2 = evalPop();
            op1 = evalPop();
            switch (getToken(postfixExp[n])) {
            case plus: evalPush(op1 + op2);
                break;
            case minus: evalPush(op1 - op2);
                break;
            case times: evalPush(op1 * op2);
                break;
            case divide: evalPush(op1 / op2);
            }

        }
        n++;
    }
    evalResult = evalPop();

}


int main()
{
    char command;

    printf("------- [2019038066] [Kim Do Yeom] -------");

    do {
        printf("----------------------------------------------------------------\n");
        printf("               Infix to Postfix, then Evaluation               \n");
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'i': case 'I':
            getInfix();
            break;
        case 'p': case 'P':
            toPostfix();
            break;
        case 'e': case 'E':
            evaluation();
            break;
        case 'd': case 'D':
            debug();
            break;
        case 'r': case 'R':
            reset();
            break;
        case 'q': case 'Q':
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 0;


}
