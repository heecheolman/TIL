# 클래스 (Class)
자바스크립트는 ES6부터 클래스를 도입했다. 하지만 다른언어의 클래스와는 다르다. 상속에 대해 문법적으로 보기 편하게 만든것일 뿐이다.  
이를 `Syntactic Sugar` 라고 한다.

## 클래스 정의 (Class declarations)
클래스는 함수이므로 함수 표현식과 함수 선언식을 사용하는것처럼 사용가능하다.

```javascript
class Person{}
console.log(typeof Person); // function
```

`class` 는 다른 함수처럼 호이스팅(hoisting) 을 지원하지 않는다.
```javascript
const p = new Person(); // error! Person is not defined
class Person{}
```

일반함수처럼 함수 표현식이 가능하며 이를 클래스표현식이라 한다.  
이름은 선택적으로 가질 수 있다.
```javascript
const Person = class{}; // 익명클래스표현식
```
클래스 표현식에서 클래스에 이름을 지정하면 이름은 클래스 본문 내에서만 유효하다.
```javascript
const Person = class cPerson{
    constructor(){}
    getName() {
        return cPerson.name;
    }
};

const p = new Person();
console.log(p.getName()); // cPerson
console.log(p.name); // undefined
```
## 생성자 (constructor)
생성자는 클래스로 생성된 객체를 만들고 초기화하는데 쓰이는 메서드이며, 특징은 다음과같다.

* 클래스당 하나의 생성자만 가질 수 있음

* 생성자를 지정하지않으면 기본생성자를 생성해줌
```javascript
constructor(){}
```
* `super()` 를 통해 부모 클래스 생성자를 호출 가능

## getter, setter
클래스의 프로토타입속성이며, 클래스의 인스턴스에서 상속된다.
### getter
getter 는 어떤 속성을 얻고자 할 때 사용되며, 반드시 `return` 값이 존재해야한다.
### setter
setter 는 어떤 속성을 새로 할당하고자할 때 사용된다.

```javascript
const Person = class{
    constructor(name, age){
        this.name = name;
        this.age = age;
    }
    get getName(){
        return this.name;
    }
    get getAge(){
        return this.age;
    }
    set setName(name){
        this.name = name;
    }
    set setAge(age){
        this.age = age;
    }
};

const p = new Person("희철", 24);
console.log(p.getName); // 희철
console.log(p.getAge); // 24

p.setName = "heecheol";
p.setAge = 0;

console.log(p.getName); // heecheol
console.log(p.getAge); // 0
```
`get`, `set` 을 붙이는것에 유념하며, 함수호출방식과 다르게 `()` 를 붙이지 않는다.

여기서 인스턴스가 생성된 후에 getter 와 setter 를 추가해야하는 상황이라면  
`__defineGetter__` 와 `__defineSetter__` 를 이용한다.


```javascript
const Person = class{
    constructor(name, age){
        this.name = name;
        this.age = age;
    }
    get getAge(){
        return this.age;
    }
    set setAge(age){
        this.age = age;
    }
};

const p = new Person("희철", 24);
console.log(p.getAge); // 24
p.setAge = 0;
console.log(p.getAge); // 0

// 객체가 생성된 후 getter setter 추가
p.__defineGetter__("getName", function(){ return this.name; });
p.__defineSetter__("setName", function(name){ this.name = name; });

console.log(p.getName); // 희철
p.setName = "heecheol";
console.log(p.getName); // heecheol
```

## 정적 메서드 (static)
```javascript
static methodName() {...}
```
`methodName` : 메서드이름

정적 메서드는 클래스를 인스턴스화 하지않고 호출하며, 인스턴스에서는 호출할 수 없다. 그 이유를 알아보도록하자
> 프로토타입에 관해 사전지식이 있어야 이해가능


클래스도 함수라고 했다. 확인해보면
```javascript
class Foo{}
console.log(typeof Foo); // function
```

```javascript
class Foo{
  constructor(){}
  static sMethod(){
    return 'static method';
  }
  pMethod(){
    return 'prototype method';
  }
}
//객체 생성
var foo = new Foo();
```
`FooPrototypeObject` 는 `Foo` 함수를 통해 생성된 객체의 부모가 되는 객체이다.  
즉, `foo.__proto__ === Foo.prototype` 인 셈이다.

여기서 `static`인 `sMethod` 메서드는 `Foo` 함수의 멤버이고,  
프로토타입메서드인 `pMethod` 메서드는 `Foo.prototype`의 멤버인것이다.

다음결과를 보자.
```javascript
console.log(Foo.sMethod()); // static method
console.log(foo.pMethod()); // prototype method

console.log(foo.__proto__.pMethod()); // prototype method
// foo 에는 pMethod가 존재하지않으므로 __proto__ 링크를 타고 Foo.prototype내의 pMethod 를 찾게된다.

console.log(foo.__proto__ === Foo.prototype); // true
// Foo 함수를 통해 생성된 객체 foo의 부모객체는 Foo.prototype이 된다.

// console.log(foo.sMethod()); // error! foo.sMethod is not a function
// console.log(Foo.pMethod()); // error! Foo.pMethod is not a function
```
다른 방법으로 쓴다면 이 방식과 같다.
```javascript
var Foo = function(){};
Foo.sMethod = function(){ return 'static method'; };
 // Foo 함수의 멤버

Foo.prototype.pMethod = function(){ return 'prototype method'; };
// Foo.prototype 의 멤버
var foo = new Foo();

// console.log(foo.sMethod()); // error! foo.sMethod is not a function
// console.log(Foo.pMethod()); // error! Foo.pMethod is not a function
console.log(Foo.sMethod()); // static method
console.log(foo.pMethod()); // prototype method

console.log(foo.__proto__ === Foo.prototype); // true;
```

## 클래스 상속 (Class Inheritance)
클래스도 당연히 상속이 된다. ES6 부터 추가된 `extends` 키워드를 통해 상속이 가능하며, 코드의 재사용성을 높여준다.
### extends
사용법은 부모클래스를 상속받는 자식클래스를 `extends`로 이어준다.
```javascript
class 자식클래스 extends 부모클래스{ ... }
```
다음 예를 보자
```javascript

// Base class
class Vehicle{

}

// Sub class
class Car extends Vehicle{

}
```
상속을 통해서 오버라이딩을 구현할 수 있다.  
오버라이딩이란 부모 클래스가 가지고있는 메서드를 자식 클래스가 재정의해서 사용하는 것이다.
```javascript
// Base Class
class Vehicle{
  foo(){
    console.log("Vehicle");
  }
}

// Sub class
class Car extends Vehicle{
    foo(){
      console.log("Car");
    }
}
var car = new Car();
car.say(); // "Car"
```
부모클래스 내에 똑같은 함수 `foo()` 가 있지만 `Car` 함수의 `foo()` 를 호출했다.

### super
`super` 키워드는 부모오브젝트의 함수를 호출할 때 사용한다.  
다음의 주의사항이 있다.

* `super` 를 통해 부모의 속성을 삭제할 수 없다.  
* `super.prop`을 통해 `non-writable` 인 속성을 덮어 쓸 수 없다.
* 자식클래스의 생성자에 필수적으로 `super`  를 먼저 호출해야한다.
* `super` 를 호출하기전에 `this` 를 사용할 수 없다.

```javascript
// Base Class
class Vehicle{
    constructor(){
        console.log("Vehicle constructor");
    }
}

// Sub class
class Car extends Vehicle{
    constructor(){
        // console.log(this);  // super() 를 먼저 호출해야한다.
        super();
        console.log("Car constructor");
        console.log(this);
    }
}
var car = new Car();
// "Car constructor"
// Car {}
```

### static메서드 상속, prototype메서드 상속
이전예제에서 `Car` 클래스는 `Vehicle` 클래스의 자식클래스이다.  
관계도를 보면
```
Vehicle        ---prototype--->     Vehicle.prototype


__proto__                              __proto__


Car            ---prototype--->       Car.prototype

```
```JavaScript
console.log(Car.__proto__ === Vehicle); // true
console.log(Car.prototype.__proto__ === Vehicle.prototype); // true

console.log(Car.prototype.constructor === Car); // true
console.log(Vehicle.prototype.constructor === Vehicle); // true
```
그렇기 때문에 부모클래스의 `static` 메서드도 상속받는다. 정확히말하면 상속받는다는 표현보단 프로토타입 체인에의해 사용 할 수 있게되는것이다.

```JavaScript
// Base Class
class Vehicle{
    constructor(){}
    static sMethod(){
        console.log('static method');
    }
}
// Sub class
class Car extends Vehicle{
    constructor(){ super(); }
    pMethod(){
        super.sMethod();
    }
}
var car = new Car();

Car.sMethod(); // staticMethod
// car.pMethod(); // error!
```
단 위의 예제에서 `car.pMethod()` 를 호출하려하면 에러를 호출한다. 그이유는 무엇일까?

앞서 말했듯이 `static`은 인스턴스에서 호출할 수 없다.  
`car` 는 인스턴스로 만들어진 객체이고 `super.sMethod()` 는 정적메서드이기때문에 프로토타입체인에의해 인스턴스에서 호출이 불가능하다.


##### 참고문서
[https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Operators/super](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Operators/super)  
[https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Classes/static](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Classes/static)  
[http://poiemaweb.com/es6-class](http://poiemaweb.com/es6-class)  
[http://beomy.tistory.com/15](http://beomy.tistory.com/15)
### 아무말대잔치
* 프로토타입을 이해하고나니 클래스를 이해하는것이 좀 더 수월했다.

* 결국엔 class 도 프로토타입이고, 보기편하게 만든 Syntactic sugar 일 뿐이다.

* 어제 알바해서 힘듦

* 개강 2주도 안남음 더 달려야함. 치킨먹고싶다
