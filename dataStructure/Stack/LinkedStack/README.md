## 연결리스트를 이용한 스택의 구현 (2018. 06. 08)

* 단순 연결리스트를 이용해 스택을 구현하면 메모리가 동적으로 생겨 상대적으로 효율적.

* 스택의 초기상태는 포인터 top 을 널포인터로 설정하여 표현.

```cpp
typedef struct Stack {
  DataType data;
  Stack * link;
} Stack;
```


![이미지1](http://2.bp.blogspot.com/-CBEUC1eKTNU/ViKeKtTydzI/AAAAAAAAA8c/aENXV5bL-tk/s320/62.png)

출처: [http://learnshareimprove.blogspot.com/2015/10/programming-c-program-to-implement.html](http://learnshareimprove.blogspot.com/2015/10/programming-c-program-to-implement.html)
#### **장점**
동적으로 메모리를 사용할 수 있다.

#### **단점**
자료를 저장하는 공간 외에 다음 자료가 저장되는 메모리의 주소가 저장되므로 추가적으로 메모리 사용이 됨.
