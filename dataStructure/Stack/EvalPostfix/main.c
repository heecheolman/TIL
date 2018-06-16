//
//  main.c
//  Linked_Stack
//
//  Created by 김희철 on 2018. 6. 8..
//  Copyright © 2018년 Heekim. All rights reserved.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element;

typedef struct StackNode {
    element data;
    struct StackNode * link;
} StackNode;

StackNode * top;

void push(element data) {
    StackNode * temp = (StackNode *)malloc(sizeof(StackNode));
    temp->data = data;
    temp->link = top;
    top = temp;
}

element pop() {
    if(!top) {
        printf("\n stack is empty! \n");
        return 0;
    }
    StackNode * del;
    element popData;
    
    del = top;
    popData = del->data;
    top = del->link;
    free(del);
    return popData;
}

element peek() {
    if(!top) {
        printf("\n stack is empty! \n");
        return 0;
    }
    return top->data;
}

void del() {
    if(!top) {
        printf("\n stack is empty! \n");
        return;
    }
    StackNode * del;
    del = top;
    top = del->link;
    free(del);
}

int getPriority(char opr) {
    switch(opr) {
        case '(':
        case ')':
            return 0;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
    }
    return -1;
}

// 중위표기법을 후위표기법으로 변환하는 과정
// postfix 를 동적할당한 후 문자열로 이어붙여 main 함수에 반환
// 이어 붙이는 함수 strcat() 이용
// 문자배열 tempStr 의 1번째 요소에 '\0' 널문자를 포함시켜 문자열로 강제
char * infixToPostfix(char * express) {
    char symbol;
    char tempSymbol;
    char * postfix = malloc(sizeof(char) * 20);
    
    // 문자열로 만들기위한 변수
    char tempStr[2];
    char c;
    
    int length = (int)strlen(express);
    for(int i = 0; i < length; i++) {
        symbol = express[i];
        switch(symbol) {
            case '(':
                push(symbol);
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                // top 이 null 이 아니고 현재 symbol 의 우선순위가 stack 의 가장위에있는 요소의 우선순위보다 적다면
                // 스택에있는것을 우선적으로 pop
                while(top && (getPriority(symbol) <= getPriority(peek()))) {
                    c = pop(); tempStr[0] = c; tempStr[1] = '\0';
                    strcat(postfix, tempStr);
                }
                // 그리고 현재의 symbol 을 push
                push(symbol);
                break;
            case ')':
                tempSymbol = pop();
                // '(' 를 만날때까지 출력
                while(tempSymbol != '(') {
                    c = tempSymbol; tempStr[0] = c; tempStr[1] = '\0';
                    strcat(postfix, tempStr);
                    tempSymbol = pop();
                }
                break;
            default:
                c = symbol; tempStr[0] = c; tempStr[1] = '\0';
                strcat(postfix, tempStr);
                break;
        }
    }
    while(top) {
        c = pop(); tempStr[0] = c; tempStr[1] = '\0';
        strcat(postfix, tempStr);
    }
    
    return postfix;
}

// 후위표기법 계산하는 함수
// 스택의 data 가 현재 char 이므로 변환과정을 거친다
// character to integer : char thing - '0';
// integer to character : int thing + '0';
int evalPostfix(char * exp) {
    int opr1, opr2;
    char value;
    int length = (int)strlen(exp);
    int result;
    char symbol;
    top = NULL;
    
    for(int i = 0; i < length; i++) {
        symbol = exp[i];
        if(symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/') {
            value = symbol;
            push(value);
        } else {
            opr2 = pop() - '0';
            opr1 = pop() - '0';
            switch(symbol) {
                case '+':
                    push(opr1 + opr2 + '0');
                    break;
                case '-':
                    push(opr1 - opr2 + '0');
                    break;
                case '*':
                    push(opr1 * opr2 + '0');
                    break;
                case '/':
                    push(opr1 / opr2 + '0');
                    break;
            }
        }
    }
    result = pop() - '0';
    return result;
}

int main(void) {
    top = NULL;
    char * express = "(2+3)*4+9";
    char * postfix;
    int result;
    
    printf("중위 표기법 ==> (2+3)*4+9");
    printf("\n\n");
    printf("후위 표기법 변환 ==> \t");
    postfix = infixToPostfix(express);
    printf("%s \n", postfix);
    result = evalPostfix(postfix);
    printf("후위 표기법 계산 결과 ==> %d\n", result);
    
    /* 출력결과
     
     중위 표기법 ==> (2+3)*4+9
     
     후위 표기법 변환 ==>     23+4*9+
     후위 표기법 계산 결과 ==> 29
     
     */
}

