//
//  main.c
//  Linked_Stack
//
//  Created by 김희철 on 2018. 6. 8..
//  Copyright © 2018년 Heekim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

// stack 의 요소
typedef int element;

// Stack 구조체 정의
typedef struct Stack {
    // stack 의 data
    element data;
    // 다음 Stack 노드
    struct Stack * link;
} Stack;

Stack * top;

// 노드를 스택에 쌓는 함수
void push(element data) {
    // Stack 포인터 temp 가 동적할당
    Stack * temp = (Stack *)malloc(sizeof(Stack));
    temp->data = data;
    // 쌓인 스택의 link 가 그 아래 노드를 가리킴
    temp->link = top;
    // top이 새로 추가된 노드를 가리킴
    top = temp;
}

// 스택의 가장 위에 있는 데이터를 가져오고 해당 노드 제거
element pop() {
    // top 이 NULL 이라면 함수 종료
    if(!top) {
        printf("\n\n stack is empty !! \n\n");
        return 0;
    }
    // pop 시킬 데이터
    element popData;
    // Stack 포인터 temp 가 현재의 top 위치를 가리킴
    Stack * temp = top;
    // temp(top)의 data 를 popData에 넣어줌
    popData = temp->data;
    // top 이 temp의 그다음 노드를 가리킴
    top = temp->link;
    // 메모리 해제
    free(temp);
    return popData;
}

// 스택의 가장 위에 있는 데이터를 가져오는 함수
element peek() {
    // top 이 NULL 이라면 함수 종료
    if(!top) {
        printf("\n\n stack is empty !! \n\n");
        return 0;
    }
    // return 을 위한 element type peekData
    element peekData;
    // 가장 위에있는 data를 peekData에 저장
    peekData = top->data;
    return peekData;
}

// 스택의 가장 위에 있는 노드를 제거하는 함수
void del() {
    // top 이 NULL 이라면 함수 종료
    if(!top) {
        printf("\n\n stack is empty !! \n\n");
    } else {
        Stack * temp;
        // temp 가 현재의 top을 가리킴
        temp = top;
        // top 은 top->link 를 가리킴. 즉, 아래의 노드
        top = top->link;
        // 이후에 가장 상단을 가리키고있던 temp 를 메모리 해제
        free(temp);
    }
}
// 스택을 출력
void printStack() {
    // target 은 가장 위의 노드를 가리킴
    Stack * target = top;
    printf("\n STACK [ ");
    
    // target 이 NULL 일때까지. 즉, 가장 아래의 노드까지.
    // iterable
    while(target) {
        // target 이 가리키고있는 data 출력
        printf("%d ", target->data);
        // target 은 다시 target 아래의 노드를 가리킴
        target = target->link;
    }
    printf(" ] \n");
}

int main(void) {
    top = NULL;
    element ele;
    printStack();
    push(5);
    printStack();
    push(8);
    printStack();
    push(12);
    printStack();
    
    ele = peek();
    printStack();
    printf("peek top => %d\n", ele);
    
    del();
    printStack();
    
    ele = pop();
    printStack();
    printf("\t pop top => %d\n", ele);
    
    ele = pop();
    printStack();
    printf("\t pop top => %d\n", ele);
    
    pop();
    return 0;
}
