//
//  main.c
//  ArrayCircularQueue
//
//  Created by 김희철 on 2018. 6. 17..
//  Copyright © 2018년 Heekim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

// 큐 사이즈 4
// 사실상 들어갈 수 있는 data 는 3개만 들어갈 수 있다.
// 원형 큐는 자리 하나를 항상 비워야 하기 때문
#define QUEUE_SIZE 4

typedef int element;
typedef struct CircularQueue {
    element queue[QUEUE_SIZE];
    int front;
    int rear;
} CircularQueue;

// 큐를 동적할당한 후 반환
CircularQueue * createQueue() {
    CircularQueue * cq;
    cq = (CircularQueue *)malloc(sizeof(CircularQueue));
    cq->front = 0;
    cq->rear = 0;
    return cq;
}

// 비어있으면 1 아니면 0
int isEmpty(CircularQueue * cq) {
    return cq->front == cq->rear ? 1 : 0;
}

// 가득차있으면 1 아니면 0
int isFull(CircularQueue * cq) {
    return ((cq->rear) + 1) % QUEUE_SIZE == cq->front ? 1 : 0;
}

void enQueue(CircularQueue * cq, element data) {
    if(isFull(cq)) {
        exit(1);
    }
    cq->rear = (cq->rear + 1) % QUEUE_SIZE;
    cq->queue[cq->rear] = data;
}

element deQueue(CircularQueue * cq) {
    if(isEmpty(cq)) {
        exit(1);
    }
    cq->front = (cq->front + 1) % QUEUE_SIZE;
    return cq->queue[cq->front];
}

void del(CircularQueue * cq) {
    if(isEmpty(cq)) {
        exit(1);
    }
    cq->front = (cq->front + 1) % QUEUE_SIZE;
}

element peek(CircularQueue * cq) {
    if(isEmpty(cq)) {
        exit(1);
    }
    return cq->queue[(cq->front + 1) % QUEUE_SIZE];
}

void printQueue(CircularQueue * cq) {
    printf("Circular Queue [");
    int first = (cq->front + 1) % QUEUE_SIZE;
    int last = (cq->rear + 1) % QUEUE_SIZE;
    int i = first;
    while(i != last) {
        printf("%d ", cq->queue[i]);
        i = (i + 1) % QUEUE_SIZE;
    }
    printf("]\n");
}

int main(void) {
    CircularQueue *circularQueue;
    circularQueue = createQueue();
    element data;
    
    printf("삽입 5 >> "); enQueue(circularQueue, 5); printQueue(circularQueue);
    printf("삽입 4 >> "); enQueue(circularQueue, 4); printQueue(circularQueue);
    printf("삽입 1 >> "); enQueue(circularQueue, 1); printQueue(circularQueue);
    // n - 1만큼만 삽입이 되므로 4개를 삽입하려하면 프로그램 종료
//    printf("삽입 1 >> "); enQueue(circularQueue, 1); printQueue(circularQueue);
    printf("삭제 >> "); deQueue(circularQueue); printQueue(circularQueue);
    printf("삽입 6 >> "); enQueue(circularQueue, 6); printQueue(circularQueue);
    data = peek(circularQueue); printf("peek Data -->  %d \n", data);
    printf("삭제 >> "); deQueue(circularQueue); printQueue(circularQueue);
    printf("삭제 >> "); deQueue(circularQueue); printQueue(circularQueue);
    printf("삭제 >> "); deQueue(circularQueue); printQueue(circularQueue);
    
    
    // 선형 큐와는 달리 나머지연산자를 이용하므로 인덱스의 첫번째부터 다시 삽입된다. 정확히말해선 덮어씌워진다.
    printf("삽입 1 >> "); enQueue(circularQueue, 1); printQueue(circularQueue);
    printf("삽입 2 >> "); enQueue(circularQueue, 2); printQueue(circularQueue);
    printf("삽입 3 >> "); enQueue(circularQueue, 3); printQueue(circularQueue);
    
    printf("삭제 >> "); deQueue(circularQueue); printQueue(circularQueue);
    printf("삭제 >> "); deQueue(circularQueue); printQueue(circularQueue);
    printf("삭제 >> "); deQueue(circularQueue); printQueue(circularQueue);
    
    
    /* 출력결과
     
     삽입 5 >> Circular Queue [5 ]
     삽입 4 >> Circular Queue [5 4 ]
     삽입 1 >> Circular Queue [5 4 1 ]
     삭제 >> Circular Queue [4 1 ]
     삽입 6 >> Circular Queue [4 1 6 ]
     peek Data -->  4
     삭제 >> Circular Queue [1 6 ]
     삭제 >> Circular Queue [6 ]
     삭제 >> Circular Queue []
     삽입 1 >> Circular Queue [1 ]
     삽입 2 >> Circular Queue [1 2 ]
     삽입 3 >> Circular Queue [1 2 3 ]
     삭제 >> Circular Queue [2 3 ]
     삭제 >> Circular Queue [3 ]
     삭제 >> Circular Queue []
     
    */
}
