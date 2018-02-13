# 소괄호의 의미

소괄호 () 가 의미하는 바가 무엇인지 알아보고, 즉시실행함수(IIFE)가 무엇인지 알아보도록한다.
## 함수 선언과 표현
먼저 함수 선언과 표현에대한 차이점을 알아보도록 한다.
#### 함수선언 (Function Declarations)
```JavaScript
function name (parameter){
    statements
}
```
`name` : 함수이름  
`parameter` : 함수의 인자이며 255개까지 인자를 가질 수 있습니다  
`statements` : 함수의 본문을 기술합니다

함수의 선언은 이름을 가지며 선언시 자동으로 호이스팅(hoisting) 됩니다.
```JavaScript
foo();

function foo(){
    console.log("hello");
}
// "hello"
```
함수 선언을 뒤에 했음에도 불구하고 foo() 호출시에 정상적으로 작동


#### 함수표현 (Function Expressions)
```JavaScript
var variable = function name (parameter){
  statements
}
```
`variable` : 함수를 담을 변수  
`name` : 함수이름이며 생략가능  
`parameter` : 함수의 인자이며 255개까지 인자를 가질 수 있습니다  
`statements` : 함수의 본문 기술

함수를 변수에 할당을 시키면 함수표현이 된다. 변수 선언과 같음  
자동으로 호이스팅이 되지 않으며, 인터프리터가 라인에 도달해야 실행 가능하다
```JavaScript
foo();

var foo = function(){
    console.log("hello");
}

foo();
/*
Uncaught TypeError: foo is not a function
"hello"
*/
```


## 즉시실행함수(IIFE)



[MDN문서](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Operators/function) 에 보면 함수표현식만이
즉시실행 가능하다고 적혀있다. 선언과 동시에 즉시 실행이 가능하게 하려면, 선언을 표현식으로 바꿔야한다.


선언을 표현식으로 바꾸는 방법은 소괄호로 감싸는 방법이다.  
```JavaScript
(foo = function(){
  console.log("foo");
}); // 함수선언을 함수 표현식으로 표현
foo(); // "foo"
```
다음은 선언과 동시에 사용되는 방법이다.
```JavaScript
(foo = function(){
  console.log("foo");
})(); // "foo"
```
익명함수 표현식은 다음과 같이 표현한다
```JavaScript
(function(){
  console.log("hello");
})(); // "hello"

```

_소괄호안에 익명의 함수를 기술하면, 소괄호의 시작부분부터 종결부분까지
전체가 평가된 후 반환 된다. 결국 반환값은 자기 자신이 되어버린다_

위의 코드에서 실제로 반환된 값은 익명함수 전체이다. 반환된 익명함수 전체를 실행시키기 위해 괄호를 추가했다.
추가적으로 이 익명함수의 반환값은 무엇일까?
```JavaScript
var a = (function(){
  console.log("hello");
})();
console.log(a);
//console.log(a());

/* 출력결과
hello
undefined

마지막 주석문은 변수 a에는 익명함수가 아닌 익명함수의 반환값인
undefined 이므로 error 이다.
*/
```

## 즉시실행함수 (IIFE) 를 쓰는이유는?
#### 전역변수(global scope) 의 선언을 막기위해
IIFE 내부에 선언된 변수들의 범위(scope)는 익명함수내로 한정이 되기 때문에 중복선언문제가 해결된다.
```JavaScript
var foo = "bye";

(function(){
    var foo = "hello";
    console.log(foo); // "hello"
})();

console.log(foo); // "bye"
```
똑같은 변수 foo임에도 불구하고 익명함수를 통해 중복문제를 해결했다.

#### 클로저에서의 값의 중복 해결
클로저는 외부함수의 변수에대한 참조를 기억한다. 흔한 루프문이다.
```JavaScript
for(var i = 0; i < 3; i++){
     setTimeout(() => {
         console.log(i);
     }, 1000);
}
/*출력값
3
3
3
*/
```
i 를 참조하지만 i는 전역으로 선언이 되어있기 때문에 전역 i는 마지막 값인 3이 된다. 그래서 3이 세번 찍힌다.

그렇다면 for문이 돌때 각각의 환경을 만들어주어야한다.  
이 때 IIFE를 쓰면 된다.

```JavaScript
for(var i = 0; i < 3; i++){
    (function(x) {
        setTimeout(function(){
            console.log(x);
        }, 1000);
    })(i);
}
/*출력값
0
1
2
*/
```
for문이 돌때마다 즉시실행함수에 i값이 parameter로 전달된다. 그리고 그 값을 x에 저장한다.  
함수각각의 환경이 다르므로 각자의 값들을 기억할 수 있는것이다.
