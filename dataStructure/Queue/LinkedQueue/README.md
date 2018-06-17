## 연결 자료구조를 이용한 큐 구현

- 기존의 원형 큐의 단점을 극복
- 공백 큐는 `front` 와 `rear` 를 NULL 로 설정
- 길이 자유자제
- 메모리낭비 적음


#### 큐의 노드 구조
``` c
typedef struct QueueNode {
    element data;
    struct QueueNode * link;
} QueueNode;
```

#### 연결큐의 front와 rear의 구조체
``` c
typedef struct {
    QueueNode * front;
    QueueNode * rear;
} LinkedQueueType;
```


**구현 예)**

![이미지](http://1.bp.blogspot.com/-Cb5cQnnbwvk/ViKhgiDXP2I/AAAAAAAAA8o/LcII9oEehsY/s1600/linkedlist.gif)  

출처 : [http://learnshareimprove.blogspot.com/2015/10/programming-cpp-program-to-implement.html](http://learnshareimprove.blogspot.com/2015/10/programming-cpp-program-to-implement.html)

#### 초기화
함수 : `createQueue()`
동적할당을 한 후에 `front` 와 `rear` 를 NULL 로 초기화


#### 삽입
함수 : `enQueue()`  
``` c
    // 공백큐인 경우
    if(LQ->front == NULL) {
        LQ->front = newNode;
        LQ->rear = newNode;

    // 그렇지 않은경우
    } else {
        LQ->rear->link = newNode;
        LQ->rear = newNode;
    }
```

#### 삭제
함수 : `deQueue()`  
```c
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
```


### 장점
배열을 이용한 큐보다 메모리낭비가 적다.  
길이를 마음대로 조절 가능하다.

### 단점
연결을 위해 link 라는 포인터변수를 노드마다 사용한다.


[덱 배우기](https://github.com/heecheolman/TIL/tree/master/dataStructure/Queue/Dequeue)
