# bind, call, apply

## bind()
```javascript
.bind(thisArg[, arg1[, arg2[,...]]])
```

`bind()` 의 역할은 새로운 함수를 만든다. 이 함수의 실행 문맥은 `.bind()`의 첫번째 인자로 받은게 된다. 바인딩함수는 미리 정의해둔 `this` 값으로 함수를 생성할 수 있기 때문에 매우 유용하다.

## call()
```javascript
.call(thisArg[,arg1[,arg2[,...]]])
```
`call()` 함수는 첫번째 인자로 함수 내부에서 사용할 `this`로 만들어준다  
나머지 parameter 는 메서드에 전달한 인자 목록이다.

## apply()
```javascript
.apply(thisArg[,argsArray])
```
`apply()` 함수는 `call()` 함수와 동일하지만 배열로 메서드에 인자를 전달한다는것이 차이이다.

## 헷갈리는 부분
`call()` 과 `apply()` 는 특정 객체의 메서드를 빌려쓴다는 개념이고  
`bind()` 함수는 함수를 리턴한다. 이 함수는 앞서 말했듯이 미리 정의해둔 `this`를 가진 새로운 함수이다.

#### `bind()`예제
```javascript
function multiply(number) {
    'use strict';
    return this * number;
}
// 문맥을 지정해서 바인딩 함수를 생성
var double = multiply.bind(2);

// 바인딩 함수를 실행
console.log(double(3));  // => 6
console.log(double(10)); // => 20
```

#### `call()`, `apply()` 예제
```javascript
var num = 5;
var obj = {
    num: 50
};

function double(){
    return this.num * 2;
}

// this 는 window
console.log(double());
console.log(double.call(this));
console.log(double.apply(this));

// this 는 obj
console.log(double.call(obj));
console.log(double.apply(obj));
```
### 생성자 함수를 `new` 를 붙이지 않고 호출할 경우

생성자 함수를 `new` 를 붙이지 않고 호출할경우 `this`는 전역객체에 바인딩된다. 이런 현상을 막기위해 널리 사용되는 패턴이 있다.

```JavaScript
function Foo(arg){
  // 생성된 this 가 A의 인스턴스가 아니라면
  // new 연산을 통해 바인딩
  if(!(this instanceof A)){
    return new Foo(arg);
  }

  this.value = arg ? arg : 0;
}
```
#### 참고 문서
[https://goo.gl/z1qxC9](https://goo.gl/z1qxC9)  
[http://codepitcher.tistory.com/4](http://codepitcher.tistory.com/4)  
[http://itstory.tk/entry/JavaScript-4-%ED%95%A8%EC%88%98%EC%99%80-%ED%94%84%EB%A1%9C%ED%86%A0%ED%83%80%EC%9E%85-%EC%B2%B4%EC%9D%B4%EB%8B%9D-2-this%EB%9E%80](http://itstory.tk/entry/JavaScript-4-%ED%95%A8%EC%88%98%EC%99%80-%ED%94%84%EB%A1%9C%ED%86%A0%ED%83%80%EC%9E%85-%EC%B2%B4%EC%9D%B4%EB%8B%9D-2-this%EB%9E%80)
