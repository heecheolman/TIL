## 순차 자료구조, 배열을 이용한 선형 큐 구현

``` c
typedef struct ArrayQueue {
    element queue[QUEUE_SIZE];
    int front;
    int rear;
} ArrayQueue;
```

#### 초기화
함수 : `createQueue()`
동적할당을 한 후에 front 와 rear 를 -1 로 초기화


#### 삽입
함수 : `enQueue()`  
rear 를 증가시킨 후 증가된 rear 에 데이터 삽입

#### 삭제
함수 : `deQueue()`  
front 가 가리키는 배열원소를 반환하고 front 값 증가



### 장점
구현이 쉽다.

### 단점
큐를 삽입하고 삭제하는 작업을 반복하면 배열이 비어있음에도 불구하고  
큐가 가득 차있다고 인식  
**원형 큐로 해결가능**
