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

## 상속을 하자
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
`Triangle.prototype` 은 `new TwoDShape()`로 만들어진 객체로 덮어 씌워진다.  
 `new Shape()`를 통해 `TwoDShape인스턴스`가 생성됐다. `TwoDShape 인스턴스.__proto__` 는 원래라면 `TwoDShape` 함수의 `prototype` 인 `TwoDShapePrototypeObject` 를 덮어씌우는 것이 정상이지만 `TwoDShape` 함수의 `prototype` 이 다시 `new Shape()`로 만들어진 객체로 덮어씌워진다.  

`new Shape()`로 만들어진 객체의 `__proto__`는  `Shape` 함수의 `prototype`인 `ShapePrototypeObject` 를 참조하게되고 `ShapePrototypeObject` 의 `constructor` 는 `Shape` 함수를 참조하게된다.

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
위의 방법으로 계속 객체를 생성하면 자체 속성은 `this` 를 이용해 계속해서 추가한다.  
100개의 객체가 있을 때 속성을 변경하지 않는경우 비효율적일 수 있다.  
`name` 이라는 속성을 변경하고 싶지않은데 `this.name`으로 해놓는다면 생성할때마다 `name`속성이 생겨나기 때문이다.

이럴 때, `PrototypeObject` 속성으로 `name`을 추가한다면 모든 인스턴스에서 공유를 한다
```javascript
function Shape(){}
Shape.prototype.name = 'Shape';
```
이렇게 한다면 `new Shape()` 를 할 때마다 모든 인스턴스자체의 속성엔 `name` 속성이 존재하지않지만, 숨겨진 링크 `__proto__`를 통해 `ShapePrototypeObject` 의 `name` 속성에 접근하기 때문에 공유 할 수 있는것이다.


```javascript
function Shape(){}
Shape.prototype.name = 'Shape';
Shape.prototype.toString = function(){ return this.name; };

function TwoDShape(){}
TwoDShape.prototype = new Shape(); // 상속
TwoDShape.prototype.constructor = TwoDShape; // 생성자 설정

TwoDShape.prototype.name = "2DShape"; // 상속이 끝난 뒤에 재설정
```

여기서 포인트는 상속이 끝난뒤에 `name` 속성을 추가해주는 것이다.  
상속을 하기 전에 `name` 속성이 추가된다면, `TwoDShape.prototype = new Shape()` 구문을 통해 다시 덮어씌워지므로 무의미한 작업이 될 뿐만아니라 `name` 속성이 사라지게된다. 참고로 재설정이라는 단어로 인해 혼동이 올 수 있는데, 이는 `TwoDShape.prototype` 에 `name` 속성이 존재하지 않으므로 `name` 속성이 `TwoDShape.prototype` 에 추가가되는것이다.

#### 프로토타입만 상속
앞의 예제와 같이 `new object()` 로 생성한 객체를 통해 상속하는 방법은 생성한 객체의 자체속성만 제공한다. 모든 재사용 가능한 코드는 프로토타입에 있으므로  
프로토타입을 상속하면 효율이 증가하지만 장단점이 존재한다.
```javascript
function Shape(){}
Shape.prototype.name = 'Shape';
Shape.prototype.toString = function(){ return this.name; };

function TwoDShape(){}
//상속
TwoDShape.prototype = Shape.prototype;
TwoDShape.prototype.constructor = TwoDShape;
//보강
TwoDShape.prototype.name = '2DShape';

function Triangle(side, height){
    this.side = side;
    this.height = height;
}
//상속
Triangle.prototype = TwoDShape.prototype;
Triangle.prototype.constructor = Triangle;
//보강
Triangle.prototype.constructor = Triangle;
Triangle.prototype.name = 'Triangle';
Triangle.prototype.getArea = function(){
    return this.side * this.height / 2
};
```
위의 코드에서는 상속 부분의 코드에서 `TwoDShape.prototype` 이 가리키는 객체와 `Shape.prototype` 이 가리키는 객체가 동일한 객체를 가리킨다.  
`Triangle` 도 마찬가지이다. 그렇기 때문에 같은 `prototype`을 공유하므로 부모나 자식의 `prototype`속성을 변경하면 상속관계이 있는 모든 객체의 속성에 영향을 받게된다.
```javascript
var s = new Shape();
console.log(s.constructor); //  function Triangle () {}
console.log(s.name); // "Triangle"
```
같은 `prototype` 을 공유하기때문에 `new Shape()`임에도 불구하고 `Triangle` 의 보강에서 적용된 값이 출력된다.
#### 임시생성자
위의 방법은 모든 프로토타입이 동일한 객체를 가리키고, 부모나 자식의 속성을 변경하면 모든 객체의 속성이 영향을 받는다는 단점이 존재한다.  
이를 해결하는 방법은 임시생성자를 이용하는것이다.

임시 생성자는 빈 함수 `F()` 를 생성하고, 이함수의 `prototype`을 부모 생성자의 `prototype` 으로 설정하면 `new F()`를 호출할 때 부모의 `prototype`의 모든것을 상속받은 객체를 생성 할 수 있다.

```javascript
function Shape(){}
Shape.prototype.name = 'Shape';
Shape.prototype.toString = function(){ return this.name; };

function TwoDShape(){}
//상속
var F = function(){};
F.prototype = Shape.prototype;
TwoDShape.prototype = new F();
TwoDShape.prototype.constructor = TwoDShape;
//보강
TwoDShape.prototype.name = '2DShape';

function Triangle(side, height){
    this.side = side;
    this.height = height;
}
//상속
var F = function(){};
F.prototype = TwoDShape.prototype;
Triangle.prototype = new F();
Triangle.prototype.constructor = Triangle;
//보강
Triangle.prototype.name = 'Triangle';
Triangle.prototype.getArea = function(){
    return this.side * this.height / 2
};
```
```javascript
var F = function(){};
F.prototype = Shape.prototype;
TwoDShape.prototype = new F();
```
위의 코드에서 빈함수 `F` 를 만든다. 이함수는 자체속성을 가지고있지않는다.
`F.prototype` 의 참조를 `Shape.prototype` 으로 설정한다.
`TwoDShape.prorotype` 을 `F`의 인스턴스로 덮어씌운다.`new F()`의 인스턴스에는 자체 속성이 존재하지않지만 `Shape.prototype`을 상속받은 객체를 생성할 수 있으며, 프로토타입체인은 유지된다.
```javascript
TwoDShape.prototype = new Shape();
```
위의 코드와 비슷하다고 생각할 수 있지만 차이점은 아래의 방식은 `Shape` 의 자체속성도 물려받는다는것이고, `임시생성자` 를 이용하면 자체속성은 물려받지 않고 `prototype` 을 물려받는것이다.
```javascript
const t = new Triangle(5, 5);
console.log(t.__proto__ === Triangle.prototype) // true;
console.log(t.__proto__.__proto__ === TwoDShape.prototype) // true;
console.log(t.__proto__.__proto__.__proto__ === Shape.prototype) // true;
```
프로토타입 체인은 유지되는것을 볼 수 있다.

#### 상위 클래스 저장
상위 객체의 원본을 저장하고 싶다면 `_super` 를 이용한다. 마치 다른 언어의 슈퍼클래스로 접근하는 것과 같다.
```javascript
function Shape() {}
Shape.prototype.name = 'Shape';
Shape.prototype.toString = function() { return this.name; };

function TwoDShape() {}
var F = function () {};
F.prototype = Shape.prototype;
TwoDShape.prototype = new F();
TwoDShape.prototype.constructor = TwoDShape;
TwoDShape._super = Shape.prototype; // _super 속성 추가, 슈퍼클래스에 접근
```


#### 함수로 만들어버리자
상속을 할 때 일일이 코드를 구현한다면 너무 귀찮은 일이다. 그래서 이 부분을 함수로 처리한다면 이것또한 재사용 가능한 코드가 된다.  
`inherit()` 함수로 구현해보겠다.
```javascript
function inherit(Child, Parent){
    var F = function() {};
    F.prototype = Parent.prototype;
    Child.prototype = new F();
    Child.prototype.constructor = Child;
    Child._super = Parent.prototype;
}

function Shape(){}
Shape.prototype.name = 'Shape';
Shape.prototype.toString = function(){ return this.name; };

function TwoDShape(){}
inherit(TwoDShape, Shape);
TwoDShape.prototype.name = '2DShape';

const td = new TwoDShape();
console.log(td.name); // "2DShape"
```
하지만 이렇게 `inherit` 함수를 구현하면 호출할 때마다 임시생성자함수 `F`가 생성되므로 비효율적일 수 있다. 사실상 임시생성자의 역할은  
`prototype`만 변경하면 되므로 클로저를 이용하여 다음과같이 표현할 수 있다.
```javascript
var inherit = (function (){
    var F = function() {};
    return function(Child, Parent) {
        F.prototype = Parent.prototype;
        Child.prototype = new F();
        Child.prototype.constructor = Child;
        Child._super = Parent.prototype;
    }
})();
```

#### 얕은 복사 (Shallow copy), 깊은 복사 (Deep copy)를 통한 상속패턴

얕은 복사는 부모의 멤버들을 순회하며 자식에 복사하는 것을 말한다.
```javascript
function inherit(Parent, Child){
  var i;
  var Child = Child || {};
  for(i in Parent){
    if(Parent.hasOwnProperty(i)){
      Child[i] = Parent[i];
    }
  }
  return Child;
}
```
`Child` 인자를 생략하면 기존 `Child`의 기능확장이아닌 새로운 객체가 생성된다.

```javascript
var parent = {
    name: 'parent',
    count: [1, 2, 3, 4]
};
var child = inherit(parent);
console.log(child); // { name: 'parent', count: [ 1, 2, 3, 4 ] }
//
```
간단하게 속성들을 `for...in` 문으로 반복해서 복사했다. 하지만 여기서 문제가 생긴다.
```javascript
child.name = 'child';
child.count[0] = 100;
console.log(child.name); // 'child'
console.log(parent.name); // 'parent'
console.log(child.count); // [ 100, 2, 3, 4 ]
console.log(parent.count); // [ 100, 2, 3, 4 ]
```
`name`속성은 자식객체에서 변경을 해도 부모객체에 영향이 없었는데 배열은 영향이 생겼다.  
속성이 객체나 배열, 함수일경우 참조(주소)만 전달을 하기때문에 같은 주소를 가리키게되므로  
자식객체에서 속성을 변경하면 부모객체에서도 바뀌는 것이다.

여기서 `count` 라는 속성에는 배열이 들어있다. 이 배열의 주소를 예를들어 `0x0001` 이라고 한다면 위의 얕은복사에서  
`child.count` 속성 에는 `0x0001` 이라는 주소가 복사가 되는것이다.  
그리고 `0x0001` 주소는 [1, 2, 3, 4] 라는 배열을 가리키게되는것이기 때문에 결국엔 같은 배열을 가리키게되는것이다.  
이러한 주소복사는 함수, 배열을 포함한 모든 객체에서 일어나는 현상이다.

이런 현상을 이용하면 불필요한 메서드 중복이 발생하지 않을것이다. 객체나 배열일경우에는 `깊은복사(deep copy)` 를 이용한다.  
깊은 복사의 방법은 복사 도중 속성이 객체라면 `재귀함수`로 내부의 요소에 접근해 복사하면 된다.

```javascript
function inherit(Parent, Child){
  var i;
  var Child = Child || {};
  for(i in Parent){
    if(Parent.hasOwnProperty(i)){
      if(typeof Parent[i] === 'object'){ // 1
        Child[i] = Array.isArray(Parent[i]) ? [] : {}; // 2
        inherit(Parent[i], Child[i]); // 3
      }else{
        Child[i] = Parent[i];
      }
    }
  }
  return Child;
}
```
1 번 구문 : `Parent` 객체의 `i` 번째 요소가 객체라면,  
2 번 구문 : `Parent` 객체의 `i` 번째 요소가 배열이면 빈 배열`[]`, 아니라면 빈 객체`{}` 를 `Child`의 `i` 번째 요소에 할당  
3 번 구문 : `Parent` 객체의 `i` 번째 요소와 2번 구문에서 할당된 새로운 객체나 배열속성 `Child[i]`를 재귀함수로 호출

실제로 깊은 복사가 이루어졌나 확인을 해보자

```javascript
var parent = {
    name: 'parent',
    count: [1, 2, 3, 4],
    showCount: function(){
        return this.count;
    }
};
var child = inherit(parent);

console.log(child); // { name: 'parent', count: [ 1, 2, 3, 4 ] }

child.count[0] = 9999;

console.log(parent.showCount()); // [1, 2, 3, 4]
console.log(child.showCount()); // [9999, 2, 3, 4]

console.log(parent.showCount === child.showCount); // true
```
자식의 `count[0]` 을 변경해도 부모의 배열에는 영향이 없는 깊은 복사가 이루어진것을 확인했다.  
또한 이 예제에서 확인할 수 있는것은 메서드도 객체이기 때문에 참조로인한 얕은 복사가 이루어져  
마지막 출력값이 `true`로 같은 `showCount`를 가리키는것을 확인했다.

#### 믹스인

만약 여러 객체의 속성을 한객체의 속성으로 모두 상속받고싶다면 믹스인을 이용하면된다.  
사용방법은 상속받고싶은 여러개의 객체들을 함수의 인자로 받고, `arguments` 속성으로 모든 객체를 반복한다.  
또한 중복되는 속성이 있다면 마지막으로 덮어씌운 속성으로 적용된다.

```javascript
function multi(){
    var obj = {}, // 1
        stuff, // 2
        len = arguments.length;  // 3
    for(var j = 0; j < len; j++){ // 4
        stuff = arguments[j]; // 5
        for(var i in stuff){ // 6
            if(stuff.hasOwnProperty(i)) {
                obj[i] = stuff[i]; // 7
            }
        }
    }
    return obj;
}
```
1 번 : 빈객체 `obj` 생성  
2 번 : `arguments` 를 순회할 때 `arguments` 의 각요소를 담기위한 변수  
3 번 : `arguments` 의 길이, 즉 받은 객체의 개수  
4 번 : `arguments` 의 길이만큼 반복  
5 번 : `stuff` 에 `j` 번째 `arugments` 객체 할당  
6 번 : `stuff` 객체 반복  
7 번 : `obj` 의 각요소에 `stuff` 요소 대입
```javascript
var shape = {
    name: 'Shape',
    toString: function(){
        return this.name;
    }
};

var twoDee = {
    name: '2D Shape',
};

var triangle = multi(shape, twoDee, {
   name: 'Triangle',
   getArea: function(){
       return this.side * this.height / 2;
   },
    side: 5,
    height: 10
});

console.log(triangle.toString()); // "Triangle"
console.log(triangle.getArea()); // 25
```
`multi()` 함수를 호출해서 `shape` 와 `twoDee`, 그리고 리터럴방식으로 속성을 전달한것들을 모두 상속받는 `triangle` 객체이다.  
`name` 속성은 마지막에 덮어씌워진 Triangle 이 `name`이 되었다. 믹스인 방식은 상속트리에 포함시키지 않으면서 모든 객체의 기능을 사용 할 수 있다.

### 생성자 빌려쓰기 + 프로토타입 지정

다음은 생성자를 빌려쓰는 방법으로 다중상속을 해보자.  

```javascript

function Person(name) {
    this.name = name || "희철";
}
Person.prototype.say = function(){ return this.name; };

Person.prototype.getName = function(){
    return this.name;
};

function Korean(name){
    Person.apply(this, arguments);
}

var kor1 = new Korean("익명");
console.log(kor1.name);
// console.log(kor1.say()); // error! say is not a function
```
`Function.prototype.apply()` 함수를 통해서 다른 생성자를 빌려썻다.  
이 방법은 부모의 속성을 모두 물려받고, 또한 부모함수의 `this` 에 자식함수의 `this` 를 바인딩 할 수 있습니다.  
하지만 부모객체의 프로토타입 속성은 사용할 수 없는 문제가 있다. 이러한 문제를 해결하기위해 프로토타입을 지정해주면 된다.

```javascript
function Person(name) {
    this.name = name || "희철";
}
Person.prototype.say = function(){ return this.name; };

Person.prototype.getName = function(){
    return this.name;
};

function Korean(name){
    Person.apply(this, arguments);
}

Korean.prototype = new Person();

var kor1 = new Korean("익명");

console.log(kor1.name); // 익명
console.log(kor1.say()); // 익명

console.log(kor1.__proto__.__proto__ === Person.prototype); // true
delete kor1.name; // kor1 객체내부 name 속성제거
console.log(kor1.name); // 희철
```
`Korean.prototype = new Person();` 구문을 통해 프로토타입을 지정해주었다.  
프로토타입이 연결됨에 따라 `PersonPrototypeObject` 의 속성도 사용할 수 있다.  
하지만 단점은 부모생성자가 두번 호출 됩니다. `new Person()` 한번 `new Korean()` 내부의 `Person.apply()` 한번.  

`delete kor1.name;` 을 했을 때 그다음 출력값이 "희철"인 이유는 `kor1` 내의 속성에 `name`은 없지만 `__proto__` 링크를 통해  
`Person` 내의 `name` 속성을 찾아간것을 볼 수 있다.

#### 기생상속 (parasitic inheritance)
기생상속은 다른 객체의 모든 기능을 가져온 후, 새로운 객체를 보강하고 이를 반환해 객체를 생성하는 함수이다.

```javascript
function object(o){
    function F() {}
    F.prototype = o;
    return new F();
}

var TwoD = {
    name: "2DShape",
    dimensions: 2
};

function triangle(s, h){
    var o = object(TwoD);
    o.name = "Triangle";
    o.getArea = function() {
        return this.side * this.height / 2;
    };
    o.side = s;
    o.height = h;
    return o;
}

var t = triangle(5, 10);
console.log(t.dimensions); // 2
console.log(t.getArea()); // 25

var t2 = new triangle(10, 10);
console.log(t.dimensions); // 2
console.log(t.getArea()); // 50

```
`new` 연산자가 필요하지 않은 이유는 일반 함수처럼 작동을 하기 때문이다. `new` 를 사용해도 정상적인 이유는  
`new` 의 내부 동작을 알면 왜 그런지 알것이다.

`var o = object(TwoD)` 구문에서 굳이 `object()` 함수를 쓰지않아도, 모든 속성을 복사하는 다른 방법을 이용해도 무방하다.  
앞서 말했던것처럼 다른객체의 모든기능을 가져오기만 하면 되기 때문이다.

#### Object.create() [prototypal 방식]
첫번째 인자로는 새로 만든 객체의 프로토타입이어야하는 객체  
두번째 인자는 선택적이며, 생성하는 객체의 키를 초기화한다.
```javascript
var shape = {
    name: "Shape",
    toString: function(){
        return this.name;
    }
};

var twoDShape = Object.create(shape, {name: {value: "2DShape"}});
twoDShape.name = "2DShape";

console.log(twoDShape); // {}
console.log(twoDShape.name); // "2DShape"
console.log(Object.getOwnPropertyDescriptors(twoDShape));
/*
{ name:
   { value: '2DShape',
     writable: false,
     enumerable: false,
     configurable: false } }
 */

twoDShape.name = "no";
console.log(twoDShape.name); // 2DShape
console.log(twoDShape.__proto__ === shape); // true
```

`twoDShape.name = "no";` 구문을통해 변경했는데 "2DShape" 로 출력됐다. 그이유는 해당 키의 속성중 `writable: false` 이기 때문에 변경할 수 없는것이다.

`Object.create()` 를 통해 간편하게 상속을 구현하는것을 봤다.

##### 아무말 대잔치

* 상속은 코드재사용의 일부분일 뿐이라는것을 알앗다.
* 솔직히 이거 글 너무 목차가 난잡함.
* 상속은 실제로 내가 코드를 써보며 해보는게 더 빨리 적응할것같다.
* 설연휴를 갖다바칩니다.

##### 참고문서
[http://www.nextree.co.kr/p7323/](http://www.nextree.co.kr/p7323/_)  
[http://unikys.tistory.com/320](http://unikys.tistory.com/320)  
[https://github.com/yamoo9/front-end-angular-camp/blob/master/Reference/js-07-reusable-pattern.md#%ED%81%B4%EB%9E%98%EC%8A%A4-%EB%B0%A9%EC%8B%9D%EC%9D%98-%EC%83%81%EC%86%8D-%ED%8C%A8%ED%84%B4-5--%EC%9E%84%EC%8B%9C-%EC%83%9D%EC%84%B1%EC%9E%90](https://github.com/yamoo9/front-end-angular-camp/blob/master/Reference/js-07-reusable-pattern.md#%ED%81%B4%EB%9E%98%EC%8A%A4-%EB%B0%A9%EC%8B%9D%EC%9D%98-%EC%83%81%EC%86%8D-%ED%8C%A8%ED%84%B4-5--%EC%9E%84%EC%8B%9C-%EC%83%9D%EC%84%B1%EC%9E%90)  
[http://superjang.com/archives/2535](http://superjang.com/archives/2535)  
[https://github.com/yoosoo-won/yoosoo-won.github.io/wiki/%EC%BD%94%EB%93%9C-%EC%9E%AC%EC%82%AC%EC%9A%A9-%ED%8C%A8%ED%84%B4](https://github.com/yoosoo-won/yoosoo-won.github.io/wiki/%EC%BD%94%EB%93%9C-%EC%9E%AC%EC%82%AC%EC%9A%A9-%ED%8C%A8%ED%84%B4)  
[http://hostmasterzone.info/parasiticinheritance.html](http://hostmasterzone.info/parasiticinheritance.html)
