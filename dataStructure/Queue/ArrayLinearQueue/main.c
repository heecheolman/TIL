//
//  main.c
//  ArrayQueue
//
//  Created by 김희철 on 2018. 6. 17..
//  Copyright © 2018년 Heekim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

// 큐 사이즈 10
#define QUEUE_SIZE 4

typedef int element;
typedef struct ArrayQueue {
    element queue[QUEUE_SIZE];
    int front;
    int rear;
} ArrayQueue;

// 큐를 동적할당한 후 반환
ArrayQueue * createQueue() {
    ArrayQueue * aq;
    aq = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    aq->front = -1;
    aq->rear = -1;
    return aq;
}

// 비어있으면 1 아니면 0
int isEmpty(ArrayQueue * aq) {
    return aq->front == aq->rear ? 1 : 0;
}

// 가득차있으면 1 아니면 0
int isFull(ArrayQueue * aq) {
    return aq->rear == QUEUE_SIZE ? 1 : 0;
}

void enQueue(ArrayQueue * aq, element data) {
    if(isFull(aq)) {
        exit(1);
    }
    (aq->rear)++;
    aq->queue[aq->rear] = data;
}

element deQueue(ArrayQueue * aq) {
    if(isEmpty(aq)) {
        exit(1);
    }
    // aq->front 를 증가 후 반환시킴
    return aq->queue[++(aq->front)];
}

void del(ArrayQueue * aq) {
    if(isEmpty(aq)) {
        exit(1);
    }
    (aq->front)++;
}

element peek(ArrayQueue * aq) {
    if(isEmpty(aq)) {
        exit(1);
    }
    return aq->queue[(aq->front) + 1];
}

void printQueue(ArrayQueue * aq) {
    printf(" Queue [");
    for(int i = aq->front + 1; i <= aq->rear; i++) {
        printf("%d ", aq->queue[i]);
    }
    printf("]\n");
}

int main(void) {
    ArrayQueue * Queue = createQueue();
    element data;
    printf("삽입 5 >> "); enQueue(Queue, 5); printQueue(Queue);
    printf("삽입 4 >> "); enQueue(Queue, 4); printQueue(Queue);
    printf("삽입 1 >> "); enQueue(Queue, 1); printQueue(Queue);
    printf("삭제 >> "); deQueue(Queue); printQueue(Queue);
    printf("삽입 6 >> "); enQueue(Queue, 6); printQueue(Queue);
    data = peek(Queue); printf("peek Data -->  %d \n", data);
    printf("삭제 >> "); deQueue(Queue); printQueue(Queue);
    printf("삭제 >> "); deQueue(Queue); printQueue(Queue);
    printf("삭제 >> "); deQueue(Queue); printQueue(Queue);
    
    // 배열이 비어있음에도 불구하고 삽입 불가.
//    printf("삽입 1 >> "); enQueue(Queue, 1); printQueue(Queue);
//    printf("삽입 1 >> "); enQueue(Queue, 1); printQueue(Queue);
    
    /* 출력결과
     
     삽입 5 >>  Queue [5 ]
     삽입 4 >>  Queue [5 4 ]
     삽입 1 >>  Queue [5 4 1 ]
     삭제 >>  Queue [4 1 ]
     삽입 6 >>  Queue [4 1 6 ]
     peek Data -->  4
     삭제 >>  Queue [1 6 ]
     삭제 >>  Queue [6 ]
     삭제 >>  Queue []
    */
}
