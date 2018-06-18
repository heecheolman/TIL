# 연결자료구조를 이용한 이진트리와 이진트리의 순회
- 배열을 이용한 순차 자료구조는 메모리 효율에 있어서 비효율적이므로 연결 자료구조를 통해 이진트리를 구현한다.  
- 구현한 이진트리가 가지고있는 모든 데이터를 순회하는 방법도 알아본다.

### 연결자료구조를 이용한 이진트리
다음은 연결리스트를 이용한 이진트리의 구조체이다.

**트리노드의 구조체**
``` c
typedef struct TreeNode {
    element data;
    struct TreeNode * left;
    struct TreeNode * right;
} TreeNode;
```

**모델**
```
  TreeNode
 ┌───────┬────────┬───────┐
 │       │        │       │
 │ *left │  data  │ *right│
 │       │        │       │
 └───────┴────────┴───────┘
```

`left` 는 해당 노드의 왼쪽 자식 노드,  
`right` 은 해당 노드의 오른쪽 자식 노드를 가리킨다.


### 이진트리의 순회 (Tree Traversal)

이진트리의 하나의 노드에서 순회를 위해 수행할 수 있는 작업은 세가지로 구분되며, D, L, R 로 구분한다.  
또한, 순회순서는 왼쪽 서브트리를 먼저 방문하고 그 후에 오른쪽 서브트리로 이동하는 것으로 한다.

```
1. 현재 노드의 데이터를 읽는 작업         D
2. 현재 노드의 왼쪽 서브트리로 이동        L
3. 현재 노드의 오른쪽 서브트리로 이동      R
```


![이미지](http://2.bp.blogspot.com/-m-c-4PgDLUI/VO1EPmAoSJI/AAAAAAAAAuY/ov1rknsdcts/s1600/%ED%8F%AC%ED%99%94%EC%9D%B4%EC%A7%84%ED%8A%B8%EB%A6%AC.PNG)

출처 : [http://logonluv.blogspot.com/2015/02/datastructure-tree.html](http://logonluv.blogspot.com/2015/02/datastructure-tree.html)

현재 노드를 방문하는 순서에 따라 3가지로 나누게 된다.  
데이터 순회의 예는 위의 이진트리를 가지고 설명한다.

#### 전위순회 (Preorder Traversal)
**순서**
```
1. 현재 노드 n 방문                 D
2. 현재 노드 n 의 왼쪽 서브트리 이동    L
3. 현재 노드 n 의 오른쪽 서브트리 이동   R
```
**다음은 전위순회에 따른 데이터 출력결과**
```
A B C D E F G
```

#### 중위순회 (Inorder Traversal)
**순서**
```
1. 현재 노드 n 의 왼쪽 서브트리 이동    L
2. 현재 노드 n 방문                 D
3. 현재 노드 n 의 오른쪽 서브트리 이동   R
```

**다음은 중위순회에 따른 데이터 출력결과**
```
C B D A F E G
```
#### 후위순회 (Postorder Traversal)
**순서**
```
1. 현재 노드 n 의 왼쪽 서브트리 이동    L
2. 현재 노드 n 의 오른쪽 서브트리 이동   R
3. 현재 노드 n 방문                 D
```
**다음은 후위순회에 따른 데이터 출력결과**
```
C D B F G E A
```



# 구현
세가지 순회방법을 구현한 함수는 다음과 같고, 재귀호출을 이용했다.  
코드는 위에서 설명한 알고리즘대로 작성하였다. (main.c 참고)


#### makeRootNode()
노드를 만들고 반환하는 함수

#### preOrder()
전위순회 함수

#### inOrder()
중위순회 함수

#### postOrder()
후위순회 함수
