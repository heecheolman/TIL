//
//  main.c
//  Dequeue
//
//  Created by 김희철 on 2018. 6. 17..
//  Copyright © 2018년 Heekim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DequeNode {
    element data;
    struct DequeNode * rlink;
    struct DequeNode * llink;
} DequeNode;

typedef struct {
    DequeNode * front;
    DequeNode * rear;
} DequeType;

// 덱을 생성 후 반환
DequeType * createDeque() {
    DequeType * deque = (DequeType *)malloc(sizeof(DequeType));
    deque->front = NULL;
    deque->rear = NULL;
    return deque;
}

// 덱이 공백인지 확인하는 함수
int isEmpty(DequeType * DQ) {
    return DQ->front ? 0 : 1;
}

// 덱의 front 부분으로 삽입
void insertFront(DequeType * DQ, element data) {
    DequeNode * newNode = (DequeNode *)malloc(sizeof(DequeNode));
    newNode->data = data;
    newNode->llink = NULL;
    newNode->rlink = NULL;
    // 공백덱일 경우 front와 rear 둘 다 새로운 노드를 가리킴
    if(!(DQ->front)) {
        DQ->front = newNode;
        DQ->rear = newNode;
    // 공백덱이 아닐경우 연결
    } else {
        DQ->front->llink = newNode;
        newNode->rlink = DQ->front;
        DQ->front = newNode;
    }
}

// 덱의 rear 부분으로 삽입
void insertRear(DequeType * DQ, element data) {
    DequeNode * newNode = (DequeNode *)malloc(sizeof(DequeNode));
    newNode->data = data;
    newNode->llink = NULL;
    newNode->rlink = NULL;
    // 공백덱일 경우 front와 rear 둘 다 새로운 노드를 가리킴
    if(!(DQ->rear)) {
        DQ->front = newNode;
        DQ->rear = newNode;
    // 공백덱이 아닐경우 연결
    } else {
        DQ->rear->rlink = newNode;
        newNode->llink = DQ->rear;
        DQ->rear = newNode;
    }
}

// 덱의 front 부분 삭제
element deleteFront(DequeType * DQ) {
    // 공백덱이라면 함수 종료
    if(isEmpty(DQ)) {
        return 0;
    }
    // 제거시킬 노드를 가리킬 임시 포인터 변수
    DequeNode * old;
    // 제거시킬 노드의 data를 담을 변수
    element frontData;
    // old가 덱의 front를 참조
    old = DQ->front;
    // frontData 에 삭제하려는 노드의 데이터를 담음
    frontData = old->data;
    // 만약 front의 오른쪽이 NULL이라면, 다시말해 해당노드를 지우면 공백덱이 될 경우
    if(!(DQ->front->rlink)) {
        DQ->front = NULL;
        DQ->rear = NULL;
    // 그렇지 않을 경우 front 를 오른쪽의 노드로 이동
    } else {
        DQ->front = DQ->front->rlink;
        DQ->front->llink = NULL;
    }
    // 이후 삭제
    free(old);
    return frontData;
}

// 덱의 rear 부분 삭제
element deleteRear(DequeType * DQ) {
    if(isEmpty(DQ)) {
        return 0;
    }
    // 제거시킬 노드를 가리킬 임시 포인터 변수
    DequeNode * old;
    // 제거시킬 노드의 data를 담을 변수
    element rearData;
    // old 가 덱의 rear 를 참조
    old = DQ->rear;
    // rearData 에 삭제하려는 노드의 데이터를 담음
    rearData = old->data;
    // 만약 rear의 왼쪽이 NULL 이라면, 다시말해 해당노드를 지우면 공백덱이 될 경우
    if(!(DQ->rear->llink)) {
        DQ->front = NULL;
        DQ->rear = NULL;
    // 그렇지 않을 경우 rear 를 왼쪽의 노드로 이동
    } else {
        DQ->rear = DQ->rear->llink;
        DQ->rear->rlink = NULL;
    }
    // 이후 삭제
    free(old);
    return rearData;
}

// 덱의 front 를 삭제후 성공여부를 반환 나머지는 deleteFront와 유사
int removeFront(DequeType * DQ) {
    if(isEmpty(DQ)) {
        return 0;
    }
    DequeNode * old;
    old = DQ->front;
    if(!(DQ->front->rlink)) {
        DQ->front = NULL;
        DQ->rear = NULL;
    } else {
        DQ->front = DQ->front->rlink;
        DQ->front->llink = NULL;
    }
    free(old);
    return 1;
}

// 덱의 front 를 삭제후 성공여부를 반환 나머지는 deleteRear와 유사
int removeRear(DequeType * DQ) {
    if(isEmpty(DQ)) {
        return 0;
    }
    DequeNode * old;
    old = DQ->rear;
    if(!(DQ->rear->llink)) {
        DQ->front = NULL;
        DQ->rear = NULL;
    } else {
        DQ->rear = DQ->rear->llink;
        DQ->rear->rlink = NULL;
    }
    free(old);
    return 1;
}

// 덱의 front 가 참조하는 노드의 데이터 반환
element peekFront(DequeType * DQ) {
    if(isEmpty(DQ)) {
        return 0;
    }
    return DQ->front->data;
}

// 덱의 rear 가 참조하는 노드의 데이터 반환
element peekRear(DequeType * DQ) {
    if(isEmpty(DQ)) {
        return 0;
    }
    return DQ->rear->data;
}

// 덱 내부의 데이터 전부 출력, front 에서 rear 방향으로 출력
void printDeque(DequeType * DQ) {
    printf("Deque [ ");
    // 순회를 위한 포인터변수 target
    DequeNode * target;
    // target 을 front에 위치시킴
    target = DQ->front;
    // target이 NULL 일때까지 반복
    while(target) {
        printf("%d ", target->data);
        target = target->rlink;
    }
    printf("]\n");
}

int main(void) {
    DequeType * DQ = createDeque();
    element data;
    
    printf("front 삽입 1  >> "); insertFront(DQ, 1); printDeque(DQ);
    printf("front 삽입 2  >> "); insertFront(DQ, 2); printDeque(DQ);
    printf("rear  삽입 6  >> "); insertRear(DQ, 6); printDeque(DQ);
    printf("rear  삽입 8  >> "); insertRear(DQ, 8); printDeque(DQ);
    printf("front 삽입 9  >> "); insertFront(DQ, 9); printDeque(DQ);
    printf("front 삭제    >> "); deleteFront(DQ); printDeque(DQ);
    printf("rear  삭제    >> "); deleteRear(DQ); printDeque(DQ);
    data = deleteFront(DQ); printf("removeFront data -->  %d  ", data); printDeque(DQ);
    data = peekRear(DQ); printf("peekRear data --> %d  ", data); printDeque(DQ);
    data = peekFront(DQ); printf("peekFront data --> %d  ", data); printDeque(DQ);
    
    /* 출력결과
     
     front 삽입 1  >> Deque [ 1 ]
     front 삽입 2  >> Deque [ 2 1 ]
     rear  삽입 6  >> Deque [ 2 1 6 ]
     rear  삽입 8  >> Deque [ 2 1 6 8 ]
     front 삽입 9  >> Deque [ 9 2 1 6 8 ]
     front 삭제    >> Deque [ 2 1 6 8 ]
     rear  삭제    >> Deque [ 2 1 6 ]
     removeFront data -->  2  Deque [ 1 6 ]
     peekRear data --> 6  Deque [ 1 6 ]
     peekFront data --> 1  Deque [ 1 6 ]
     
    */
}
