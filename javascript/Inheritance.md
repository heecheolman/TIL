상속 (Inheritance)
============

자바스크립트는 클래스기반 언어가 아니기때문에 상속(Inheritance)이라는 기능이 없다. 하지만 프로토타입을 이용해서 상속을 구현할 수 있다.  

> ES6부터 추가된 `class` 라는 문법이 있지만 이는 문법이 추가된 것이지 클래스 기반으로 바뀌었다는 의미는 아니다.

자바스크립트에서는 두가지의 상속방법이 존재한다.

1. Classical 방식
2. Prototypal 방식

classical 방식은 `new` 연산자를 통해 마치 `JAVA` 의 객체 생성방식과 비슷해 classical 방식이라 한다.  
prototypal 방식은 `Object.create()` 메서드를 이용해 객체를 생성하고 확장하는 방식이다.

## 짚고 넘어가기

### 함수를 정의하면 일어나는 일 (Parsing)

1. `Func` 라는 함수가 정의됐다.
```javascript
function Func(){}
```
  모든 함수 내에는 기본적으로 `prototype` 이라는 속성이 존재

2. `Func` 의 원형객체 (`FuncPrototypeObject`) 가 생성된다.
    모든 함수 내의 `prototype` 속성은 해당 함수를 정의할 때 생성된 `PrototypeObject` 를 가리킨다.
    ```
    함수이름.prototype    ----> 함수이름 PrototypeObject
    ```
3. `Func` 의 원형객체로 생성된 `FuncPrototypeObject` 내에는 `constructor` 라는 속성이 존재하며 `Func` 함수를 참조
```
함수이름.prototype    ---->   함수이름 PrototypeObject
            함수      <----           constructor
```
`constructor` 함수는 `PrototypeObject` 를 만든 함수를 참조
```javascript
function Func(){}
console.log(Func === Func.prototype.constructor) // true
```

4. 모든 함수와 객체에는 `__proto__` 라는 속성이 존재하는데 의미하는 바는 자신을 만든 `PrototypeObject` 를 참조하는 숨겨진 링크이다
```javascript
function Func(){}
const obj = new Func();
console.log(obj.__proto__ === Func.prototype); // true
```

### new 연산자를 하면 일어나는 일

```javascript
function foo(){}
const obj = new foo();
```
자바스크립트 엔진에서 일어나는일

1. 아무속성이없는 비어있는 객체 `obj` 를 만든다
2. 이 때, `obj` 는 `this` 값으로 설정됨
3. `this.__proto__` 속성이 `foo.prototype` 을 참조
4. 다른것을 반환하지 않는다면 객체 `this`를 반환
5. `obj`가 반환된 `this`(= `fooObject`) 를 참조

```javascript
function foo(){
  // obj = {};
  // this.__proto__ = foo.prototype;
  // return this;
}
```

## 상속(Inheritance) 을 하자
앞의 _prototype 짚고넘어가기_ 목차를 이해했다면 상속을 해보도록 한다.  

#### 프로토타입체인

부모의 객체를 생성한다.
자식이되는 함수의 `prototype` 이  부모함수로 생성한 객체를 참조한다.
```
Shape
  |
TwoDShape
  |
Triangle
```
이러한 상속을 구현하고싶다. 바로 예제로 넘어가자
```javascript
// Shape
function Shape(){
  this.name = 'Shape';
  this.getName = function() { return this.name; };
}
// 2DShape
function TwoDShape(){ this.name = '2DShape';}
// Triangle
function Triangle(side, height){
  this.name = 'Triangle';
  this.side = side;
  this.height = height;
  this.getArea = function() {
    return this.side * this.height / 2;
  };
}
//상속을 구현하는 코드
TwoDShape.prototype = new Shape();
Triangle.prototype = new TwoDShape();
```
상속을 구현하는 코드를 보자.  
`TwoDShapePrototypeObject` 는 `new Shape()` 된 객체를 참조한다.
`TrianglePrototypeObject` 는 `new TwoDShape()` 된 객체를 참조한다

위의 코드가 적용된 상태에서 `new` 연산자를 생각해서 내부구조를 다시 살펴보자
```javascript
const td = new TwoDShape();
/*
function TwoDShape(){
// obj = {};
// 비어있는 새 객체 생성 ,이때 obj 는  this값으로 설정

// this.__proto__ = Shape.prototype;
//      빈객체를 만들게한 객체 = Shape함수의 원형객체

// return this;
//      반환
}
*/
```
적용이 되지않은 상태라면 5행에 `rValue` 는 `TwoDShape.prototype` 이지만  
상속을 구현했으므로 `this.__proto__` 는  `ShapePrototypeObject` 를 참조하게 된다.
`Triangle` 도 마찬가지이다.

```javascript
const s = new Shape(); // Shape 생성
const td = new TwoDShape(); // 2DShape 생성
const t = new Triangle(10, 10); // Triangle 생성

console.log(t.getName()); // Triangle
```
`t` 에는 `getName()` 라는 메서드가 없다.  `getName()` 어떻게 호출된것일까?

자바스크립트 내부 엔진이 어떻게 돌아가는지 보자!

```
t 의 속성을 조회 -> getName() 없음
t.__proto__ 가 참조하는 this 객체를 상속과정에서 생성된 new TwoDShape() 로 본다.
TwoDShape의 인스턴스를 조회하고 getName() 을 찾지 못한다.
해당객체.__proto__ 가 참조하는 this 객체를 new Shape() 로 본다.
new Shape() 인스턴스 안에서 getName()을 찾았다. 호출한다.
이때 getName()의 this는 호출한 객체, t 에서 호출했으므로 this 는 t를 참조한다.
```
`toString()` 과 같은 내장 메서드들도 최상위객체인 `Object` 에 내장된 메서드이므로 `__proto__` 의 프로토타입체인을 통해 호출될 수 있는 것이다.

하지만 이렇게 하게되면 문제점이 생긴다.
```javascript
console.log(s.constructor); // function Shape()
console.log(td.constructor); // function Shape()
console.log(t.constructor); // function Shape()
```

생성자가 전부 `Shape` 이다. 그 이유는 상속구현의 코드에 있다.

```javascript
TwoDShape.prototype = new Shape();
Triangle.prototype = new TwoDShape();
```
`Triangle.prototype` 은 `new TwoDShape()`로 만들어진 객체를 참조하게된다.  
 `TwoDShape 인스턴스.__proto__` 는 원래라면 `TwoDShape` 함수의 `prototype` 인 `TwoDShapePrototypeObject` 를 참조하는것이 정상이지만 `TwoDShape` 함수의 `prototype` 이 다시 `new Shape()`로 만들어진 객체를 참조한다.  

`Shape 인스턴스.__proto__` 는 `Shape` 함수의 `prototype`인 `ShapePrototypeObject` 를 참조하게되고 `ShapePrototypeObject` 의 `constructor` 는 `Shape` 함수를 참조하게된다.

`constructor` 의 링크가 끊어진것이다. 이를 방지하기위해서는 다시 재설정해주는것이다.
```javascript
TwoDShape.prototype.constructor = TwoDShape;
Triangle.prototype.constructor = Triangle;
```
이렇게 설정을 해주게되면 정상적으로 생성자가 출력될 것이다.

`instanceof` 연산자의 결과를 보자

```javascript
console.log(t instanceof Triangle); // true
console.log(t instanceof TwoDShape); // true
console.log(t instanceof Shape); // true
```
`instanceof` 의 정의를 살펴보자
```javascript
object instanceof constructor
```
`object` : 테스트 대상인 오브젝트
`constructor` : 테스트할 함수

쉽게말하면 `object` 는 `constructor` 객체다. 라는 말의 참 거짓을 `Boolean` 값으로 반환한다.  
즉 `object의 prototype` 과 `constructor의 prototype` 이 일치하냐는 질문이다.

위에서 코드의 프로토타입체인 관계를 설명했으므로 하나씩 살펴보자

```javascript
t instanceof Triangle
```

t 는 Triangle 객체다.
-> t의 prototype 과 Triangle 의 prototype이 일치하냐?
-> t의 prototype 은 프로토타입체인에 의해 ShapePrototypeObject를 참조
-> Triangle 의 prototype도 프로토타입체인에 의해 ShapePrototypeObject를 참조
-> true

```javascript
t instanceof TwoDShape
```

t 는 TwoDShape 객체다
-> t의 prototype 과 TwoDShape 의 프로토타입이 일치하냐?
-> t의 prototype 은 프로토타입체인에 의해 ShapePrototypeObject를 참조
-> TwoDShape 의 prototype도 프로토타입체인에 의해 ShapePrototypeObject를 참조
-> true

```javascript
t instanceof Shape
```
t 는 Shape 객체다
-> t의 prototype 과 Shape 의 프로토타입이 일치하냐?
-> t의 prototype 은 프로토타입체인에 의해 ShapePrototypeObject를 참조
-> Shape 의 prototype도 프로토타입체인에 의해 ShapePrototypeObject를 참조
-> true


이 프로토타입 체인을 이해하는것이 핵심이다.


#### 공유속성
#### 프로토타입만 상속
#### 임시생성자
#### Uber




##### 참고문서
[http://www.nextree.co.kr/p7323/](http://www.nextree.co.kr/p7323/_)  
[http://unikys.tistory.com/320](http://unikys.tistory.com/320)
