//
//  main.c
//  LinkedQueue
//
//  Created by 김희철 on 2018. 6. 17..
//  Copyright © 2018년 Heekim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct QueueNode {
    element data;
    struct QueueNode * link;
} QueueNode;

typedef struct {
    QueueNode * front;
    QueueNode * rear;
} LinkedQueueType;

// 큐 초기화 작업
LinkedQueueType * createQueue() {
    LinkedQueueType *LQ;
    LQ = (LinkedQueueType *)malloc(sizeof(LinkedQueueType));
    LQ->front = NULL;
    LQ->rear = NULL;
    return LQ;
}

// LQ->front 가 NULL 이면 비어있는 상태      1반환
//                 아니면 하나라도 있는상태   0반환
int isEmpty(LinkedQueueType * LQ) {
    return LQ->front ? 0 : 1;
}

void enQueue(LinkedQueueType * LQ, element data) {
    QueueNode * newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->link = NULL;
    // 공백큐인 경우
    if(LQ->front == NULL) {
        LQ->front = newNode;
        LQ->rear = newNode;
        
    // 그렇지 않은경우
    } else {
        LQ->rear->link = newNode;
        LQ->rear = newNode;
    }
}

element deQueue(LinkedQueueType * LQ) {
    if(isEmpty(LQ)) {
        return 0;
    }
    // 제거할 노드를 가리킬 임시포인터 old
    QueueNode * old;
    // 제거할 노드의 data를 return 시킬 변수
    element dequeueData;
    // old 가 front 를 가리킴
    old = LQ->front;
    // old 의 data 를 dequeueData 에 할당
    dequeueData = old->data;
    // front 가 그 다음 노드를 가리키도록 함
    LQ->front = LQ->front->link;
    // 이동된 front 가 NULL 이라면 공백이니 rear도 NULL 로 만들어줌
    if(!(LQ->front)) {
        LQ->rear = NULL;
    }
    // 노드 제거
    free(old);
    return dequeueData;
}

// 단순히 큐 내의 노드하나를 삭제하는 함수, deQueue와 유사
// 삭제실패시 0, 성공시 1 반환
int del(LinkedQueueType * LQ) {
    if(isEmpty(LQ)) {
        return 0;
    }
    QueueNode * old;
    old = LQ->front;
    LQ->front = LQ->front->link;
    if(!(LQ->front)) {
        LQ->rear = NULL;
    }
    free(old);
    return 1;
}

// 가장 첫번째의 원소를 단순히 반환하는 함수, deQueue와 달리 삭제하지않음
element peek(LinkedQueueType * LQ) {
    if(isEmpty(LQ)) {
        return 0;
    }
    return LQ->front->data;
}

// 큐에 들어있는 모든 원소 출력
void printLQ(LinkedQueueType * LQ) {
    printf("LinkedQueue [ ");
    // 순회할 임시 포인터 target
    QueueNode * target;
    // target을 첫번째에위치시킴
    target = LQ->front;
    // target이 NULL 일 때까지 반복
    // 다시말하면, rear->link 는 NULL 이므로 target이 rear->link 를 만나면 종료.
    while(target) {
        printf("%d ", target->data);
        target = target->link;
    }
    printf("]\n");
}

int main(void) {
    LinkedQueueType *LQ = createQueue();
    element data;
    
    printf("삽입 1 >> "); enQueue(LQ, 1); printLQ(LQ);
    printf("삽입 2 >> "); enQueue(LQ, 2); printLQ(LQ);
    printf("삽입 3 >> "); enQueue(LQ, 3); printLQ(LQ);
    printf("삽입 4 >> "); enQueue(LQ, 4); printLQ(LQ);
    printf("삽입 5 >> "); enQueue(LQ, 5); printLQ(LQ);
    printf("삭제   >> "); deQueue(LQ); printLQ(LQ);
    printf("삭제   >> "); deQueue(LQ); printLQ(LQ);
    printf("삭제   >> "); deQueue(LQ); printLQ(LQ);
    data = peek(LQ); printf("peek Data -->   %d\n", data);
    printf("삭제   >> "); deQueue(LQ); printLQ(LQ);
    printf("삽입 7 >> "); enQueue(LQ, 7); printLQ(LQ);
    printf("삽입 9 >> "); enQueue(LQ, 9); printLQ(LQ);
    
    /* 출력결과
     
     삽입 1 >> LinkedQueue [ 1 ]
     삽입 2 >> LinkedQueue [ 1 2 ]
     삽입 3 >> LinkedQueue [ 1 2 3 ]
     삽입 4 >> LinkedQueue [ 1 2 3 4 ]
     삽입 5 >> LinkedQueue [ 1 2 3 4 5 ]
     삭제   >> LinkedQueue [ 2 3 4 5 ]
     삭제   >> LinkedQueue [ 3 4 5 ]
     삭제   >> LinkedQueue [ 4 5 ]
     peek Data -->   4
     삭제   >> LinkedQueue [ 5 ]
     삽입 7 >> LinkedQueue [ 5 7 ]
     삽입 9 >> LinkedQueue [ 5 7 9 ]
     
    */
}
