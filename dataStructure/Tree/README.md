
# 트리 (Tree)
트리는 비선형 자료구조 중에서 자료들 간의 계층 관계를 가진 계층형 자료구조(Hierarchical Data Structure) 이다.

![이미지](http://cs.umw.edu/~finlayson/class/fall12/cpsc230/notes/images/tree.png)  
출처 : [http://cs.umw.edu/~finlayson/class/fall12/cpsc230/notes/17-binary-search-trees.html]


위 그림에서 원들을 Node(자료) 라 하고, Node 와 Node 사이의 선을 Edge 라 한다.

한 노드가 가지는 자식 노드의 수를 차수(Degree) 라 하는데 위의 그림은
차수가 일정하지않다.

일정하지 않으면 자료들을 순회하는데 복잡함이 존재한다.  
그렇기 때문에 모든 노드의 차수를 2 이하로 제한해 전체 트리의 차수가 2이하가 되도록 정의한것이 **이진트리(Binary Tree)** 이다.

이렇게 일반화 함으로써 트리의 연산이 단순화되고 명확해진다.

다음은 이진트리의 모양과 용어들을 나타낸 이미지이다.

![이미지](https://www.tutorialspoint.com/data_structures_algorithms/images/binary_tree.jpg)

출처 : [https://www.tutorialspoint.com/data_structures_algorithms/tree_data_structure.htm](https://www.tutorialspoint.com/data_structures_algorithms/tree_data_structure.htm)


### 이진트리의 분류

#### 포화 이진 트리 (Full Binary Tree)
![이미지](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQ6PKHfRLeaIqzFViGFnzxiQXANk6IOi6tn8D3GZoPZzr3kXl1uqg)

출처 : [http://blog.naver.com/PostView.nhn?blogId=justkukaro&logNo=220618338784](http://blog.naver.com/PostView.nhn?blogId=justkukaro&logNo=220618338784)

모든 레벨에 노드가 꽉 차서 높이를 늘이지 않는 한 더 이상 노드를 추가할 수 없는 상태  
```
[포화 이진트리의 노드 수 계산]

높이가 h 인 포화이진트리의 노드 수
2^(h + 1) - 1 개
```


#### 완전 이진 트리 (Complete Binary Tree)
![이미지](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRa8VPypYP_5BtVwYNW_8KCd5IcMjdeko-BgqVOnkNGl3hBraq6)

출처 : [http://blog.naver.com/PostView.nhn?blogId=justkukaro&logNo=220618338784](http://blog.naver.com/PostView.nhn?blogId=justkukaro&logNo=220618338784)

위에서 아래, 왼쪽에서 오른쪽으로 순서대로 채워져있는 트리

#### 편향 이진 트리 (Skewed Binary Tree)
![이미지](http://cfile24.uf.tistory.com/image/17466F474E0010EC1F8400)

출처 : [http://destiny738.tistory.com/category/?page=46](http://destiny738.tistory.com/category/?page=46)

이진 트리중에서 최소 개수의 노드를 가지면서 왼쪽이나 오른쪽 서브트리만 가지고있는 트리
