## 배열을 이용한 스택의 구현 (2018. 06. 08)

* `stack[n]` 을 사용시 n 은 배열의 크기이며 다시말하면 스택의 크기이다.


* 스택에 데이터가 쌓이는 순서는 배열의 `index` 로 표현.

* 변수 `top` 은 `index` 가 0 부터 n-1 까지를 표현해야 하므로 공백은 -1 을 저장한다.


#### **장점**
구현이 쉽다

#### **단점**
물리적으로 크기가 고정된 배열(정적)은 스택의 크기를 변경하기가 어렵기 때문에 메모리낭비가 생길 수 있다.
