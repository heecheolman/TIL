<div align=center>
<img src="https://pbs.twimg.com/profile_images/743155381661143040/bynNY5dJ_400x400.jpg" width="80" height="80">
</div>

# 타입스크립트 클래스
자바스크립트는 애초에 프로토타입기반을 이용해 상속을 구현합니다. 하지만 이는 클래스기반 프로그래머들에게 익숙하지 않을 수 있습니다.

 `ES6` 에 존재하는 `class` 키워드를 이용해 구현할 수 있습니다. 타입스크립트도 이와 동일하게 `class` 키워드를 이용합니다.


## 📝 목차

* [클래스 키워드](#클래스-키워드)
* [생성자](#생성자)
* [상속](#상속)
* [오버라이드](#오버라이드)
* [접근제어자](#접근제어자)
  - [public](#public)
  - [protected](#protected)
  - [private](#private)
  - [readonly](#readonly)
  - [매개변수 프로퍼티](#매개변수-프로퍼티)
  - [static](#static)
* [추상 클래스](#추상-클래스)
* [Deep dive into Class](#deep-dive-into-class)

## 클래스 키워드
ES6 를 다루어보셨다면 기존에 생각했던 것과 동일합니다. `class` 키워드 뒤에 클래스 이름을 적어줍니다.
```ts
// TS
class Button {
    constructor() {
      // ...
    }
}
```

## 생성자
클래스 기반 언어들에서는 생성자를 통해 멤버들을 초기화시켜줬습니다. ES6 에서도 동일하게 `this.` 을 이용하였던것이 생각납니다. 타입스크립트도 동일한데 다만, 사전에 등록되지 않은 프로퍼티를 초기화하려하면 에러를 내뱉습니다.

```ts
// TS
class Button {
    constructor(name: string) {
        this.name = name; // Error!
        // TS2339: Property 'name' does not exist on type 'Button'.
    }
}
```

다음과 같이 변경되어야합니다.

```ts
// TS
class Button {
    name: string;
    constructor(name: string) {
        this.name = name;
    }
}
```

해당 클래스의 프로퍼티를 미리 등록해주는것을 확인합니다.

## 상속
ES6 문법에서 사용하던 `extends` 키워드를 동일하게 사용합니다.
```ts
// TS
class Input {
    name: string;
    constructor(name: string) {
        this.name = name;
    }

    inputName() {
        console.log(`input name is ${ this.name }`);
    }
}

class Button extends Input {
    constructor(name: string) {
        super(name);
    }
}

const button = new Button('click me');
button.inputName(); // input name is click me


```

현재 상속계층은 `Button` 이 `Input` 을 상속받고있습니다.  
하위클래스에서 `constructor` 를 정의하고싶다면 반드시 상위클래스의 `constructor` 를 호출해야만합니다. `super(name)` 을 보면 매개변수도 동일하게 전달하는것을 확인할 수 있습니다. 그리고 마지막에 `inputName()` 을 호출하여 콘솔로그에 찍히는 것도 볼 수 있습니다.


## 오버라이드
타입스크립트에서도 오버라이드를 구현할 수 있습니다.

> 오버라이드(Override)란?  
상위 클래스에서 정의한 메서드를 자식클래스에서 재정의 하는 것.

```ts
class Input {
    name: string;
    constructor(name: string) {
        this.name = name;
    }

    inputName() {
        console.log(`input name is ${ this.name }`);
    }
}

class Button extends Input {
    constructor(name: string) {
        super(name);
    }
    inputName() {
        console.log(`button name is ${ this.name }`);
    }
}

const button = new Button('click me');
button.inputName(); // button name is click me
```
`inputName()` 메서드를 하위클래스인 `Button` 에서 오버라이드 하여 호출했습니다. 출력결과가 다른것을 확인할 수 있습니다.

#### 오버로딩?
오버로딩은 지원되지 않습니다. 대신 `any` 를 이용하여 메서드 내에서 오버로딩 비슷하게(?) 구현할 수 있습니다. Function 파트에서 알아보도록 하겠습니다. 우선은 넘기자!

## 접근제어자
`public`, `protected`, `private` 는 클래스기반 언어들에는 익숙합니다. 타입스크립트에서도 동일하게 이용가능합니다.

* **public** : 디폴트값, 어디에서나 접근가능.
* **protected** : 상속받은 하위클래스만 접근가능.
* **private** : 선언한 클래스 내에서만 접근가능.

### public
default 값이 public 입니다. 별도로 프로퍼티나 메서드 앞에 추가해주지않아도 됩니다. 명시적으로 다음과 같이 수정할 수 있습니다.

```ts
// TS
class Input {
    public name: string;
    public constructor(name: string) {
        this.name = name;
    }

    public inputName() {
        console.log(`input name is ${ this.name }`);
    }
}

class Button extends Input {
    public constructor(name: string) {
        super(name);
    }
    public inputName() {
        console.log(`button name is ${ this.name }`);
    }
}


```

### protected
선언한 클래스를 포함해 상속받는 하위클래스에서만 접근 가능합니다.
```ts
class Input {
    protected name: string;
    constructor(name: string) {
        this.name = name;
    }

    protected inputName() {
        console.log(`input name is ${ this.name }`);
    }
}

const input = new Input('input');
// console.log(input.inputName()); Error!
// TS2445: Property 'inputName' is protected and only accessible within class 'Input' and its subclasses.

```
`public` 인 `constructor()` 를 통해 인스턴스를 생성했지만 `protected` 접근제어자가 붙은 `inputName()` 는 외부에서 호출불가능한것을 볼 수 있습니다.

`constructor()` 에 `protected`가 붙는다면 해당 클래스는 바로 인스턴스화 될 수 없습니다. 상속받은 하위클래스에서 `super` 를 이용해 호출할 수 있습니다.


```ts
// TS
class Input {
    protected name: string;
    protected constructor(name: string) {
        this.name = name;
    }

    protected inputName() {
        console.log(`input name is ${ this.name }`);
    }
}

class Button extends Input {
    constructor(name: string) {
        super(name);
    }
    inputName() {
        console.log(`button name is ${ this.name }`);
    }
}

const button: Input = new Input('button'); // Error!
// TS2674: Constructor of class 'Input' is protected and only accessible within the class declaration.
```

`protected` 이기 때문에 `Input()` 생성자를 이용해 인스턴스화 하려하였지만 실패했습니다. 이를 수정한다면 다음과 같습니다.

```ts
// TS
// 생략...
const button: Input = new Button('button');
```

> **추상클래스와의 차이점?**   
추상클래스도 상속을 위한 클래스이지만 추상클래스는 구현되지 않은 메서드가 존재할 수 있지만, 이 방식은 모두 구현되어야 합니다.

### private
선언한 클래스 내에서만 접근이 가능합니다. 보통 `private` 키워드가 붙은 프로퍼티는 `_(언더바)` 를 붙이는것이 통상적이라고 합니다. 이후에 외부에서 접근을 할 시에는 `get / set` 을 이용합니다.

```ts
// TS
class Input {
    private _name: string;
    protected constructor(name: string) {
        this._name = name;
    }

    get name(): string {
        return this._name;
    }
    set name(name: string) {
        this._name = name;
    }
}

class Button extends Input {
    constructor(name: string) {
        super(name);
        // console.log(this._name);  Error!
        // TS2341: Property '_name' is private and only accessible within class 'Input'.
    }
}

const button = new Button('my Button');

// get 호출
console.log(`button name is ${ button.name }`); // button name is my Button
// set 호출
button.name = 'my Button2';
// get 호출
console.log(`button name is ${ button.name }`); // button name is my Button2
```

### readonly
읽기전용 프로퍼티로 만듭니다. 프로퍼티 앞에 `readonly` 만 붙이면됩니다.

```ts
// TS

class Person {
    readonly name: string;
    constructor(name: string) {
        this.name = name;
    }
}

const person = new Person('heecheolman');
// person.name = 'kimheecheol'; Error!
// TS2540: Cannot assign to 'name' because it is a read-only property.
```
`readonly` 를 붙이면 constant(상수) 로 인식되며 생성자에서 한번 결정된 후에는 변경할 수 없습니다.

### 매개변수 프로퍼티
매개변수 프로퍼티(Parameter Property) 를 이용하여 선언과 할당을 동시에 할 수 있습니다.

```ts
// TS

class Person {
    constructor(readonly name: string) {}
    greet() {
        console.log(`my name is ${ this.name }`);
    }
}

const person = new Person('heecheolman');
person.greet(); // my name is heecheolman
```

> 개인적인 생각으로 이렇게 작성하면 코드 가독성이 떨어지는것 같다. 왜냐하면 괄호() 안에 넣어서 읽는데 모호해지기 때문이다. 장점을 생각해본다면 단순히 초기화를 위한 일회성 변수가 줄어든다는것?

### static
지금까지의 변수나 메서드들을 살펴보면 흐름은 다음과 같았습니다.
* 인스턴스화 -> 호출

그렇지만 인스턴스화가 필요하지 않은 경우도 있습니다. 예를들면 바뀌지않고 공통적으로 사용될 값 혹은 메서드 입니다. ES6 에서는 메서드만 `static` 을 붙일 수 있었지만 TS 에서는 프로퍼티도 가능합니다.

```ts
// TS

interface Point {
    x: number;
    y: number;
}

class Grid {
    static origin: Point = {
        x: 0,
        y: 0,
    };

    scale: number;
    constructor(scale: number) {
        this.scale = scale;
    }

    calcDistanceFromOrigin(point: Point): number {
        let dx = point.x - Grid.origin.x;
        let dy = point.y - Grid.origin.y;

        return Math.sqrt((dx * dx) + (dy * dy) / this.scale);
    }
}

let grid1 = new Grid(1.0); // 1x scale
let grid2 = new Grid(5.0); // 2x scale

const point: Point = {
    x: 10,
    y: 10,
};

console.log(grid1.calcDistanceFromOrigin(point)); // 14.142135623730951
console.log(grid2.calcDistanceFromOrigin(point)); // 10.954451150103322
```
타입스크립트 공식 핸드북에 있는 예제에서 사전에 배웠던 `interface`를 적용시켰습니다. 특징은 `calcDistanceFromOrigin()` 메서드 내에서 `origin` 을 사용할 때 `this`를 이용하지 않는다는 점입니다. 대신에 `클래스이름.정적멤버/정적메서드` 로 호출합니다.


## 추상 클래스
추상클래스(Abstract Class) 란 다른 클래스에서 파생될 수 있는 말 그대로 '추상적인' 클래스입니다. 다음은 추상클래스의 특징들입니다.

* 추상클래스는 `abstract` 키워드를 클래스 앞에 추가시켜주면 됩니다.
* 추상클래스 내의 메서드에 `abstract` 키워드를 붙이면 파생클래스에서 반드시 구현해야합니다.
* 추상클래스는 `new` 를 통해 인스턴스화 할 수 없습니다.

#### 인터페이스와 다른점?
인터페이스와 달리 추상 클래스는 클래스의 멤버에 대한 구현 세부 정보를 포함할 수 있습니다.


```ts
// TS

abstract class Job {
    readonly nickname: string;

    constructor(nickname: string) {
        this.nickname = nickname;
    }

    greet(): void {
        console.log(`My nickname is ${ this.nickname }`);
    }

    abstract attack(): void;
}

class Warrior extends Job {
    attack() {
        console.log('검을 사용해 공격!');
    }
}

class Magician extends Job {
    attack() {
        console.log('마법을 사용해 공격!');
    }
}

// const job: Job = new Job('what'); Error!
// TS2511: Cannot create an instance of an abstract class.

const warrior: Job = new Warrior('heecheolman');
const magician: Job = new Magician('heecheol');

warrior.greet(); // My nickname is heecheolman
magician.greet(); // My nickname is heecheol

warrior.attack(); // 검을 사용해 공격!
magician.attack(); // 마법을 사용해 공격!
```

첫번째 에러는 추상클래스를 인스턴스화 하려하여 생긴 에러입니다.

#### 추상클래스 사용이유?
추상과 구체에 관해 살펴보면  
**구체** 란 어떠한 형태가 갖추어져 있는 어떤 '것'이고  
**추상** 이란 특정 부분들만을 뽑아내어 표현한 것입니다.

위의 코드에서 '직업' 을 나타내는 `Job` 클래스를 `new(인스턴스화)` 하였을 시 어떤 객체가 나오는가? 에 대한 답은 없습니다. 직업은 추상적이기 때문입니다.

그렇다면 인터페이스를 사용하지 왜 추상클래스를 사용하는가? 에 대한 답변은 객체지향 프로그래밍에서 상속관계를 나타내기 위함입니다. 인터페이스는 어떤 **'행동'에 대한 명세일 뿐**, 그 자체가 상속관계를 나타내주진 않습니다.

## Deep dive into Class
장황하게 Deep dive into Class 라고 썻지만 별 내용이 없습니다.  
이 섹션에서는 typescript 로 작성한 class 가 어떻게 트랜스파일링 되는지 알아봅니다.

```ts
// TS
class Person {
    static standardGreeting = 'Hello, there';
    public readonly greeting: string;
    constructor(message: string) {
        this.greeting = message;
    }
    greet() {}
}
```

알아볼 목록은 다음과 같습니다.

* static 키워드
* 생성자
* greeting 프로퍼티
* public 접근제어자
* readonly

```js
// ES5
var Person = (function () {
    function Person(message) {
        this.greeting = message;
    }
    Person.prototype.greet = function () { };
    Person.standardGreeting = 'Hello, there';
    return Person;
}());
```

#### 살펴보기
* `static` 키워드가 붙은 standardGreeting 은 Person 의 멤버변수가 되어 있습니다.
* `greet(){}` 은 Person.prototype 이 갖는 메서드가 되어있습니다.
* 생성자였던 부분은 내부에 `Person()` 을 선언하고 `return Person` 으로 클로저를 이용한것을 확인할 수 있습니다.


#### 없어진것
`public`, `readonly` 키워드는 변환이 되지 않습니다. 이를 보면 해당 키워드들은 타입스크립트 컴파일러 자체에서만 정적으로 검사하는것을 알 수 있습니다.

#### readonly 의문점
`readonly` 는 읽기전용 프로퍼티임을 나타냅니다.
```ts
// TS
class Person {
    static standardGreeting = 'Hello, there';
    public readonly greeting: string;
    constructor(message: string) {
        this.greeting = message;
    }
    greet() {}
}

const p = new Person('Hi');

console.log(Object.getOwnPropertyDescriptor(p, 'greeting'));
// {value: "Hi", writable: true, enumerable: true, configurable: true}
```

한가지 의문점은 readonly 를 붙였지만 [`Object.getOwnPropertyDescriptor`](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Object/getOwnPropertyDescriptor) 를 사용해 해당 프로퍼티에 대한 속성을 조회해보면

* writable: true - 속성과 관련된 값이 변경될 수 있는지 여부
* enumerable: true - 열거할 수 있는지 여부
* configurable: true - 속성이 해당객체에서 삭제될 수 있는지 여부

임을 알 수 있습니다. 여기서 눈여겨볼 점은 `writable` 입니다. `readonly` 라고 썻지만 사실상 `writable: true` 인것을 보아 타입스크립트 자체에서만 검사를 하는것 같습니다.

> 혹시 이와 관련하여 아시는분은 연락주시면 감사하겠습니다!!


## 참고문헌
* [Typescript 핸드북 4 - 클래스[번역]](https://typescript-kr.github.io/pages/Classes.html)
* [[TS]2. Class in Typescript - Jbee](https://jaeyeophan.github.io/2017/12/13/TS-2-Class/)
* [추상클래스(abstract)의 존재 이유? - DeveloperGatsby.com](http://itewbm.tistory.com/entry/%EC%B6%94%EC%83%81%ED%81%B4%EB%9E%98%EC%8A%A4abstract-class%EC%9D%98-%EC%A1%B4%EC%9E%AC-%EC%9D%B4%EC%9C%A0)
