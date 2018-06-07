//
//  main.c
//  Stack
//
//  Created by 김희철 on 2018. 6. 7..
//  Copyright © 2018년 Heekim. All rights reserved.


#include <stdio.h>
#include <stdlib.h>

// 스택 사이즈 100
#define STACK_SIZE 100
typedef int element;

// 용량이 100 인 스택 생성
element stack[STACK_SIZE];

// top 은 아무것도없으므로 -1
int top = -1;

// 배열에 요소를 삽입하는 함수
void push(element ele) {
    // 스택이 가득찼다면 메세지 출력후 함수 종료
    if (top >= STACK_SIZE - 1) {
        printf("\n\n stack is full!! \n\n");
        return;
    } else
        stack[++top] = ele;
}

// 가장 위에있는 요소를 반환하고 삭제하는 함수
element pop() {
    // 스택이 비어있다면 메세지 출력후 함수 종료
    if (top == -1) {
        printf("\n\n stack is empty!! \n\n");
        return 0;
    } else
        // stack[top] 을 리턴한 후 top 을 감소시켜줌
        return stack[top--];
}

// 가장 위에있는 요소를 반환해주는 함수
element peek() {
    // 스택이 비어있다면 메세지 출력후 함수 종료
    if (top == -1) {
        printf("\n\n stack is empty!! \n\n");
        return 0;
    } else
        // 가장 위에있는 요소의 데이터를 반환
        return stack[top];
}

// 가장 위에있는 요소를 제거하는 함수
void del() {
    // 스택이 비어있다면 메세지 출력후 함수 종료
    if (top == -1) {
        printf("\n\n stack is empty!! \n\n");
        exit(1);
    } else
        // top 을 감소시켜줌. 사실상 비어있지는 않은 상태 top만 움직임
        top--;
    
}

// 스택을 출력
void printStack() {
    printf("\n stack[ ");
    for(int i = 0; i < top + 1; i++) {
        printf("%d ", stack[i]);
    }
    printf("] ");
}

int main(void) {
    int ele;
    printStack();
    push(1);
    
    
    printStack();
    push(2);
    
    printStack();
    push(3);
    
    printStack();
    push(4);
    
    printStack();
    del();
    
    printStack();
    ele = pop();
    printStack();
    printf("\t pop ele => %d\n", ele);
    
    ele = peek();
    printf("\t\t peek ele => %d\n", ele);
    
    
    return 0;
}
