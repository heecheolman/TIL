# 프로토타입 (Prototype)

## 워밍업
자바스크립트는 프로토타입 기반 언어라고 불린다. 그렇다면 프로토타입이 무엇인지 파헤쳐봐야 재밌어지지 않을까 싶다.  
prototype 이라는 단어의 뜻 부터 알고 시작하도록 하자!

`prototype` : 원형, 본형, 원작

## 자바스크립트는 사실 객체지향이다?
Java, C++ 등 다른 언어는 class 라는 개념이 있다. 하지만 자바스크립트에는 존재하지 않는다. ES6 부터 지원된 class 라는 문법이 존재하지만 문법이 추가됐을 뿐 class 기반으로 바뀌지는않았다. class 기반이 아니므로 상속도 존재하지않는다.

자바스크립트가 class 기반이 아닌데도 객체지향이라고 불리는이유는 `prototype` 이라는것이 존재하기 때문이다. 그렇기 때문에 우리는 `prototype` 을 공부해야한다.

#### 일급객체 (first-class object)
자바스크립트는 함수를 통해 객체지향을 실현한다. 자바스크립트에서 함수는 일급객체(first-class object) 이다.  

일급객체란?

1. 함수를 변수나 다른 데이터구조에 할당 가능

2. 다른 함수의 `parameter`로 전달 가능

3. 함수의 `return` 값으로 함수를 반환가능

4. 동적으로 프로퍼티를 생성 및 할당 가능,

#### 함수를 통한 객체 생성

자바스크립트 생성자는 자바스크립트에서 객체를 생성되는데 사용되는 함수를 말한다. 하지만 모든 함수가 생성자가 되는 것은 아니다.

`Object` 는 `new` 연산자에 의해 생성이 된다. `new` 연산자를 쓰지않으면 객체가 되지 않는다.  

다음 코드를 보자
```javascript
const str = String("string");
console.log(typeof str); // string

const obj = new String("Object");
console.log(typeof obj); // object
```
`new` 연산자를 통해 객체가 생성되는 것을 확인했다. 그렇기 때문에 모든 `Object` 의 조상은 함수이다.

크롬 콘솔에서 `Object` 를 입력하면 `Object` 도 함수인것을 확인할 수 있다.

## Prototype
자바스크립트에는 `PrototypeObject` `PrototypeLink` 두개가 존재한다. 이 둘을 `Prototype` 이라고 부른다.

하나씩 알아보도록하자

### PrototypeObject 이해하기

모든 함수 객체는 `prototype` 이라는 속성을 가지고 있다.  
`prototype` 은 원형이라는 뜻이라고했다.

`.prototype` 은 자신의 원형 객체를 가리킨다.
```javascript
function func(){}
```
위의 코드에서
###### func.prototype 은 func의 원형객체를 가리킴

이게 뭔소리냐 하면

자바스크립트에서 함수를 정의하면 두가지 일이 일어난다.
##### 1. constructor 자격 부여
함수만이 constructor 자격이 부여되어 `new` 연산자를 통해 객체를 생성할 수 있게된다
```javascript
const obj = {};
const err = new obj();
//TypeError: obj is not a constructor
```

`new` 연산자를 사용하면 내부에서 일어나는 일을 보자

```javascript
function foo(){
  // obj = {};
  // 이때 obj를 this 값으로 봄
  // this.__proto__ = foo.prototype;

  // 함수가 Object, Array, Function 중 하나를 반환하지않으면
  // this를 새로 만들어진 객체로 바인드하여 반환

  // return this;
}
```

##### 2. 해당함수의 PrototypeObject 생성 및 연결
자신이 생성될 당시의 `PrototypeObject` 객체를 cloning(복제) 하여 만든다.  
자신의 분신이 생기는것이다.  
다시 말하면 `PrototypeObject` 는 자신을 원형으로 만들어질 다른 객체가 참조할 `prototype` 이 되는것이다.


`func()` 생성자를 통해 객체를 마구마구 찍어내도 `func()`의 `PrototypeObject` 는 '원형' 하나이며 찍어낸 객체들은 `PrototypeObject` 의 값들을 공유합니다.


예제 코드를 보면 이해가 쉽다
```javascript
function Person(){};
Person.prototype.type = "human";
Person.prototype.age = "24";
//PersonPrototypeObject 에 속성추가

let p1 = new Person();
let p2 = new Person();
console.log(p1.type); // human
console.log(p1.age); // 24
console.log(p2.type); // human
console.log(p2.age); // 24

Person.prototype.age = "25";
// 원형의  age 속성 변경

console.log(p1.age); // 25
console.log(p1.age); // 25
console.log(p1.prototype); // undefined
// p1은 객체일뿐이다.
//함수가 아니므로 PrototypeObject가 생성되지않았기때문에 undefined
```
이전의 예제를 웹콘솔로 확인하고 다음 코드를 입력하자
```javascript
console.log(p1)
```

뭔가 이상하다. `p1` 의 속성에는 아무것도 존재하지않는다.  
그런데 어떻게 `age`와 `type`속성에 접근할 수 있는 것일까?

### PrototypeLink 이해하기
모든 객체는 `__proto__` 라는 속성을 가지고있다. 함수도 마찬가지이다.

`__proto__` 는 숨겨진 링크로써 자신을 만들게 해준 원형인 `PrototypeObject` 를 가리킨다.

```javascript
console.log(p1.age); // 25
console.log(p1.type); // human
console.dir(p1);
// console.dir 을 해서 내부를 들여다보면
// p1에는 age, name 속성이 존재하지않는다
```
`p1` 에 `age` 와 `type` 속성이 존재하지않는다는것을 확인했다.  
하지만 `__proto__` 속성이 존재한다.

이부분이 포인트다

`__proto__` 내부를 확인해보니 `age`, `type` 속성이 존재했다.
즉, `p1` 의 속성으로서 존재하지는 않지만 `__proto__` 를 통해 `p1` 을 만들게 해준 `PersonPrototypeObject` 내의 `age` 와 `name` 에 접근한것이다.


이렇게 `__proto__` 를 통해 상위 `prototype` 과 연결된 형태를 프로토타입 체인(Prototype Chain) 이라 한다.  
프로토타입 체인을통해 최상위객체인 `Object` 의 메서드들도 사용할 수 있는 것이다.

```javascript
console.log(p1.age.toString());
```

#### 다시 들여다보기
우리는 앞서 상위 `prototype`에 참조된다고했다. 그렇다면 두가지 의문이 생긴다.

1. 만약 프로토타입체인을 통해서 못찾으면?
```javascript
console.log(p1.hahaha); //undefined
```
`hahaha` 가 상위 프로토타입에 존재할때까지 프로토타입체인을 통해 거슬러 올라간다. 하지만 그래도 없다면  
`undefined` 반환

2. 상위 `PrototypeObject` 내의 속성이름과 객체자체속성의 이름이 겹친다면?

다음과 같은 예가 있다
```javascript
function foo(){};
foo.prototype.a = 1;
foo.prototype.greet = function(){ console.log(`Hello ${this.a}`); };
const obj = new foo();

console.log(obj.a); // 1
console.log(obj.greet());
// Hello 1
// undefined
console.log(obj); // foo {}

obj.a = 5;
obj.greet = function(){ console.log(`Bye ${this.a}`); };

console.log(obj.a); // 5
console.log(obj.greet());
// Bye 5
// undefined;
console.log(obj); // foo { a: 5, greet: [Function] }
```
`obj.a = 5` `obj.greet` 구문은 상위`PrototypeObject` 의 속성을 재정의 한것인가?

정답은 No
크롬의 콘솔창에서 마지막 구문의 내부를 살펴보면
```
foo {a: 5, greet: ƒ}
  a: 5
  greet: ƒ ()
  __proto__:
      a: 1greet: ƒ ()
      constructor: ƒ foo()
      __proto__: Object
```
자신의 객체의 속성을 추가한것임을 알 수 있다.
#### 그럼 어떻게 상위 `PrototypeObject` 의 속성을 변경하는가?


`PrototypeObject.prototype` 속성을 이용해서 수정하거나  
객체의 `Object.__proto__` 을 이용해서 수정하거나 하면된다.

```javascript
// 방법 1
foo.prototype.a = 5;
foo.prototype.greet = function(){ console.log(`Bye ${this.a}`); };
// 방법 2
obj.__proto__.a = 5;
obj.__proto__.greet = function(){ console.log(`Bye ${this.a}`); };
```
하지만 전자의 방법을 추천한다. 어떤 원형을 바꿨는지 명확하게 알 수 있기 때문이다.


#### 참고문서  
[https://medium.com/@bluesh55/javascript-prototype-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0-f8e67c286b67](https://medium.com/@bluesh55/javascript-prototype-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0-f8e67c286b67)  
[http://rhio.tistory.com/236](http://rhio.tistory.com/236)  
[http://insanehong.kr/post/javascript-prototype/](http://insanehong.kr/post/javascript-prototype/)  
[http://www.nextree.co.kr/p7323/](http://www.nextree.co.kr/p7323/)  
[https://gist.github.com/crispynap/0e693a305eb2acdc87be979c3ed95bee](https://gist.github.com/crispynap/0e693a305eb2acdc87be979c3ed95bee)

### 아무말 대잔치

* 프로토타입이 제일 중요하다고 들어서 빡집중했다

* 프로토타입 상속이 더 어려울것같다. 무섭다.

* 잠을 4시간잤더니 너무 피곤하다.

* 인터넷의 문서들은 정말 양질의 자료들이 많은것같다.

* 프로토타입이 강력한만큼 그만큼 책임이 따를것같다
