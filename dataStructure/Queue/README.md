# 큐 (Queue)
**큐(Queue)** 란 줄을 서서 기다리는 뜻이다.
스택은 삽입과 삭제가 같은 위치에서 일어나지만 큐는 그렇지않다.  
큐는 한쪽 끝에선 삽입, 다른 한쪽 끝은 삭제 연산이 이루어진다.  
즉, 삽입된 순서대로 삭제가 이루어지는 **선입선출 (FIFO : First-In First-Out)** 방식이다.



![이미지 1](https://www.tutorialspoint.com/data_structures_algorithms/images/queue_diagram.jpg)

출처 : [https://www.tutorialspoint.com/data_structures_algorithms/dsa_queue.htm](https://www.tutorialspoint.com/data_structures_algorithms/dsa_queue.htm)


## 큐의 기본 연산 (Basic Operation of Queue)

#### enqueue()
큐에 element 를 삽입 하는 연산
```
[알고리즘]
1. 큐가 가득 차 있는지 확인한다.
2. 큐가 가득차 있다면 에러메세지 출력 후 종료.
3. 가득차 있지 않다면 rear 값을 증가시켜 빈 공간에 위치하게 한다.
4. rear 가 위치한 빈 공간에 element 를 삽입한다.
```
![이미지2](https://www.tutorialspoint.com/data_structures_algorithms/images/queue_enqueue_diagram.jpg)


#### dequeue()
큐에 element 를 제거 하는 연산

```
[알고리즘]
1. 큐가 가득 차 있는지 확인한다.
2. 큐가 가득차 있다면 에러메세지 출력 후 종료.
3. 가득차 있지 않다면 데이터 front 를 증가시켜 데이터에 접근한다.
4. element 를 반환한다.
```

#### peek()
큐의 front 에 위치한 데이터를 단순 반환한다.

#### isFull()
큐가 가득 차 있는지 상태를 확인하는 함수. 반환값은 `true` or `false`
```
rear 값이 지정한 최대값과 동일 하면 가득 찬 상태
```

#### isEmpty()
큐가 비어있는지 상태를 확인하는 함수. 반환값은 `true` or `false`
```
rear 와 front 값이 일치한다면 비어있는 상태
```
