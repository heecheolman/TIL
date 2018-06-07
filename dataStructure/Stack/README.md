# 스택 (Stack)
**스택(stack)** 이란 쌓아 올린다는 뜻이다.  
스택은 시간순서에 따라 자료가 쌓여서 가장 마지막에 삽입된 자료가 가장 먼저 삭제되는 **후입선출 (LIFO : Last-In-First-Out)** 구조이다.

![이미지 1](https://www.tutorialspoint.com/data_structures_algorithms/images/stack_representation.jpg)
출처 : [https://www.tutorialspoint.com/data_structures_algorithms/stack_algorithm.htm](https://www.tutorialspoint.com/data_structures_algorithms/stack_algorithm.htm)


## 스택의 기본 연산 (Basic Operation of Stack)

#### push()
스택에 element 를 pushing(삽입) 하는 연산
```
[알고리즘]
1. 스택이 가득 차 있는지 확인한다.
2. 스택이 가득 차 있다면 에러메세지 출력 후 종료
3. 가득차 있지 않다면 top 이 그 다음 빈공간에 위치
4. top이 위치하고있는 곳에 데이터를 삽입
```

#### pop()
스택에 존재하는 element 를 removing(제거) 하고 제거된 데이터를 반환하는 연산

```
[알고리즘]
1. 스택이 비어있는지 확인한다.
2. 스택이 비어있다면 에러메세지 출력 후 종료.
3. 비어있지않다면 현재 top 이 위치하고있는 데이터를 임시로 저장(반환을 위해)
4. top 을 감소시킨다.
5. 반환을 위해 저장해 두었던 데이터를 반환한다.
```

#### peek()
스택의 가장 상단에 존재하는 요소를 반환하는 함수. `pop()` 과는 다르게 제거하진 않음

#### isFull()
스택이 가득 차 있는지 상태를 확인하는 함수. 반환값은 `true` or `false`

#### isEmpty()
스택이 비어있는지 상태를 확인하는 함수. 반환값은 `true` or `false`
