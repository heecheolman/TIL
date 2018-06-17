## 연결 자료구조를 이용한 덱 구현

### 덱 (Deque : Double-ended queue)

- 기존의 연결 큐를 확장한 개념
- 양방향 출입구
- 스택과 큐의 연산을 모두 가지고 있음


#### 덱의 노드 구조
``` c
typedef struct DequeNode {
    element data;
    struct DequeNode * rlink;
    struct DequeNode * llink;
} DequeNode;
```

#### 덱의 front와 rear 구조체
``` c
typedef struct {
    DequeNode * front;
    DequeNode * rear;
} DequeType;
```


**구현 예)**

![이미지](http://interactivepython.org/runestone/static/pythonds/_images/basicdeque.png)
출처 : [http://interactivepython.org/runestone/static/pythonds/BasicDS/WhatIsaDeque.html](http://interactivepython.org/runestone/static/pythonds/BasicDS/WhatIsaDeque.html)

#### 초기화
함수 : `createQueue()`
동적할당을 한 후에 `front` 와 `rear` 를 NULL 로 초기화


#### Front로 삽입
함수 : `insertFront()`  
```
1. 공백덱인지 확인
2. 공백이라면 front 와 rear 둘다 삽입된 노드를 가리킴
3. 공백이 아니라면 front 로 삽입후 연결
```


#### Rear로 삽입
함수 : `insertRear()`
```
1. 공백덱인지 확인
2. 공백이라면 front 와 rear 둘다 삽입된 노드를 가리킴
3. 공백이 아니라면 rear 로 삽입후 연결
```

#### Front로 삭제하고 데이터 반환
함수 : `deleteFront()`
```
1. 공백덱인지 확인
2. 공백덱이라면 함수 종료
3. 공백덱이 아니라면 front가 참조하는 노드를 임시포인터로 참조
4. 참조된 임시포인터의 데이터를 임시로 저장
5. front 를 front->rlink 로 이동
5. 임시포인터가 참조하는 노드 삭제
```

#### Rear로 삭제하고 데이터 반환
함수 : `deleteRear()`
```
1. 공백덱인지 확인
2. 공백덱이라면 함수 종료
3. 공백덱이 아니라면 rear가 참조하는 노드를 임시포인터로 참조
4. 참조된 임시포인터의 데이터를 임시로 저장
5. rear 를 rear->llink 로 이동
5. 임시포인터가 참조하는 노드 삭제
```
#### Front 단순삭제
함수 : `removeFront()`
```
deleteFront 알고리즘에서
데이터 반환만 하지 않음
```
#### Rear 단순삭제
함수 : `removeRear()`
```
deleteRear 알고리즘에서
데이터 반환만 하지 않음
```
#### Front 데이터 얻기
함수 : `peekFront()`
```
1. 공백덱인지 확인
2. 공백덱이라면 종료
3. 공백덱이 아니라면 front가 참조하는 노드의 데이터 반환
```
#### Rear 데이터 얻기
함수 : `peekRear()`
```
1. 공백덱인지 확인
2. 공백덱이라면 종료
3. 공백덱이 아니라면 rear가 참조하는 노드의 데이터 반환
```

#### 공백덱 확인
함수 : `isEmpty()`
```
1. 덱의 front 가 NULL 이라면 1 반환
2. 아니라면 0 반환
```
