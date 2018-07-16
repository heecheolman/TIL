# 추상 팩토리 (Abstract Factory) - 객체 생성

## 의도
상세화된 서브클래스를 정의하지 않고도 서로 관련성이 있거나 독립적인 여러 객체의 군을 생성하기 위한 **인터페이스를 제공** 합니다.

## 다른이름
키트(Kit)

## 동기
포르쉐 자동차 공장에서 자동차를 모델별로 찍어내고있을 때, 모델별로 찍어내는 부품(문, 후드 등)들이 다를 것이다.  
이렇게 다르게 되니, 제품군을 생성하기 위한 **공통적인 인터페이스** 를 생성한 후 해당 인터페이스를 별도로 작성해 사용할 수 있게끔 해주는것이 좋을것 같다.


## 활용
* 객체가 생성되거나 구성, 표현되는 방식과 무관하게 시스템을 독립적으로 만들고자 할 때

* 여러 제품군 중 하나를 선택해서 시스템을 설정해야 하고 한번 구성한 제품을 다른 것으로 대체할 수 있을 때

* 관련된 제품 객체들이 함께 사용되도록 설계되었고, 이 부분에 대한 제약이 외부에도 지켜지도록 하고 싶을 때

* 제품에 대한 클래스 라이브러리를 제공하고, 그들의 구현이 아닌 인터페이스를 노출시키고 싶을 때


## 구조
![이미지](http://trans.onionmixer.net/mediawiki/images/c/c3/Dpsc_chapter03_AbstractFactory_01.png)

## 참여자
* **AbstractFactory** : 개념적 제품에 대한 객체를 생성하는 연산으로 인터페이스를 정의

* **ConcreteFactory** : 구체적인 제품에 대한 객체를 생성하는 연산을 구현

* **AbstractProduct** : 개념적 제품 객체에 대한 인터페이스를 정의

* **ConcreteProduct** : 구체적으로 팩토리가 생성할 객체를 정의하고, **AbstractProduct** 가 정의하는 인터페이스를 구현

* **Client** : AbstractFactory 와 AbstractProduct 클래스에 선언된 인터페이스를 사용

## 협력방법
* 일반적으로 ConcreteFactory 클래스의 인스턴스 한 개가 런타임에 만들어진다. 이 concrete factory 는 어떤 특정 구현을 갖는 제품 객체를 생성한다. 서로 다른 제품 객체를 생성하려면 사용자는 서로 다른 구체 팩토리를 사용해야 한다.

* AbstractFactory 는 필요한 제품 객체를 생성하는 책임을 ConcreteFactory 서브 클래스에 위임한다.

## 결과 <span style="font-size: 15px">(이익과 부담)</span>


#### 1. 구체적인 클래스를 분리한다.
팩토리는 제품 객체를 생성하는 과정과 책임을 캡슐화했기 때문에, 구체적인 구현 클래스가 사용자에게서 분리된다.

> 생성하는 과정과 책임을 캡슐화해서 구체클래스에 책임을 위임했으므로 인터페이스만 알고있으면 된다.

#### 2. 제품군을 쉽게 대체할 수 있도록 한다.
ConcreteFactory 를 바꿈으로써 원하는 제품군으로 쉽게 변경가능하다.

> 대응하는 팩토리를 단순히 교체해주면 된다.

#### 3. 제품 사이의 일관성을 증진시킨다.
하나의 군 안에 속한 제품 객체들이 함께 동작하도록 설계되어 있을 때,  
다른 제품과 동시에 사용되지 않게 막아야할 필요가 있다.

> "추상 팩토리 패턴"을 통해 보장할 수 있다.


#### 4. 새로운 종류의 제품을 제공하기 어렵다.
새로운 종류의 제품이 등장하면 팩토리의 구현을 변경해야한다.  
> 이는 추상 팩토리와 모든 서브 클래스의 변경을 가져오는데 이렇게되면 재사용성을 해치는 단점이 된다.


## 구현
#### 1. 팩토리를 단일체로 정의
한 제품군에 대한 하나의 ConcreteFactory 인스턴스만 존재하면 되므로, 단일체로 구현하는것이 바람직하다.
> Singleton 패턴은 간단히 여러번 new 를 해도 처음에 new 를 한 인스턴스를 가리키게 하는 기법

#### 2. 제품을 생성합니다.
AbstractFactory 는 제품 생성을 위한 **인터페이스** 를 선언한것이고, 생성하는 책임은 Product 의 서브클래스인 Concrete-Product 에 있다.  
이를 위한 가장 공통적인 방법은 각 제품을 위해 **팩토리 메서드** 를 정의하는 것이다.  
AbstractFactory는 각 제품 생성을 위한 팩토리 메서드를 오버라이딩 함으로써 각 제품의 인스턴스를 만든다.

> **팩토리메서드란?**  
추후에 다룰 예정이지만, 간단히 객체를 생성해서 반환하는 메서드이다.

#### 3. 확장 가능한 팩토리들을 정의한다.
AbstractFactory 에는 생성할 각 제품의 종류별로 서로 다른 연산을 정의한다.  
새로운 종류의 제품이 추가되면 AbstractFactory의 인터페이스에도 새로운 연산을 추가해야한다.


## 예제코드
**ES6 기반으로 작성**
```javascript
// Abstract Factory
class CarFactory {
  // Factory Method
  createCar(model) {
    let car = null;
    switch(model) {
      case 'Cayman':
        car = new Cayman();
        break;
      case 'Boxster':
        car = new Boxster();
        break;
      case 'Panamera':
        car = new Panamera();
        break;
      default:
        car = new Cayman();
        break;
    }
    if(typeof car.printModel === 'undefined') {
      car.printModel = () => {
        console.log(`This car model is: ${car.model}`);
      }
    }
    return car;
  }
}

// Car를 상속받는 Caymen, Boxster, Panamera 팩토리
// 각 팩토리에 맞게 오버라이딩하여 재구현
class Car {
  constructor(name) {
    this.model = name;
  }
  // Abstract Product
  createDoor() {}
  createHood() {}
}

class Door {
  constructor(side, name) {
    this.name = name;
    this.side = side;
  }
  build() {
    console.log(`Build a ${this.side} door for ${this.name}`);
  }
}

class Hood {
  constructor(name) {
    this.name = name;
  }
  build() {
    console.log(`Build a hood for ${this.name}`);
  }
}

// Concrete Factory
class Cayman extends Car{
  constructor() {
    super('Cayman');
  }
  // Concrete Product
  createDoor(side) {
    return new CaymanDoor(side, this.constructor.name);
  }
  // Concrete Product
  createHood() {
    return new CaymanHood(this.constructor.name);
  }
}

// Concrete Factory
class Boxster extends Car{
  constructor() {
    super('Boxster');
  }
  // Concrete Product
  createDoor(side) {
    return new BoxsterDoor(side, this.constructor.name);
  }
  // Concrete Product
  createHood() {
    return new BoxsterHood(this.constructor.name);
  }
}

// Concrete Factory
class Panamera extends Car{
  constructor() {
    super('Panamera');
  }
  // Concrete Product
  createDoor(side) {
    return new PanameraDoor(side, this.constructor.name);
  }
  // Concrete Product
  createHood() {
    return new PanameraHood(this.constructor.name);
  }
}

class CaymanDoor extends Door {
  constructor(side, name) {
    super(side, name);
  }
}
class BoxsterDoor extends Door {
  constructor(side, name) {
    super(side, name);
  }
}
class PanameraDoor extends Door {
  constructor(side, name) {
    super(side, name);
  }
}

class CaymanHood extends Hood {
  constructor(name) {
    super(name);
  }
}
class BoxsterHood extends Hood {
  constructor(name) {
    super(name);
  }
}
class PanameraHood extends Hood {
  constructor(name) {
    super(name);
  }
}


const factory = new CarFactory();

// Client
const boxsterCar = factory.createCar('Boxster');

boxsterCar.printModel();
boxsterCar.createDoor('right').build();
boxsterCar.createDoor('left').build();
boxsterCar.createHood().build();

/* output

This car model is: Boxster
Build a right door for Boxster
Build a left door for Boxster
Build a hood for Boxster

*/
```

#### Abstract Factory - `CarFactory`
* Abstract Factory 는 개념적 제품에대한 객체를 생성하는 연산으로 인터페이스를 정의해야한다.   

#### Concrete Factory - `Caymen`, `Boxster`, `Panamera`
Caymen 을 생성하는 팩토리, Boxster 를 생성하는 팩토리, Panamera 를 생성하는 팩토리

#### Abstract Product - Car 클래스의 `createDoor()`, `createHood()`
* Car 의 createDoor 와 createHood 를 상속받아 인터페이스 제공

#### Concrete Product - `Caymen`, `Boxster`, `Panamera` 클래스 내부의 `createDoor(), createHood()` 구현
* Car 를 상속받는 Caymen, Boxster, Panamera 는 인터페이스인 createDoor 와 createHood 를 각각의 팩토리에 맞게 구현함

#### Client - `// Client` 주석 다음 줄
* client 는 팩토리에 message 만 전달해 내부가 어떻게 진행되는지 알 수 없고, 알 필요가 없다.


## 관련패턴
* AbstractFactory 클래스는 팩토리 메서드 패턴을 이용해서 구현되는데, 원형 패턴을 이용할 때도 있다.  

* ConcreteFactory 는 단일체 패턴을 이용해 구현하는 경우가 많다.

## 마치며
* 예제코드를 작성하며 개념을 이해하는데 많은 혼란이 있었다.

* 인터페이스가 없는 자바스크립트의 경우에는 클래스의 오버라이딩을 통하여 구현하였다.

* **참여자** 부분의 개념을 이해하는데 많은 노력이 필요했다.

* 습관적으로 분기를 나누어 상황에 맞는 객체를 return 시키는 기법이 **팩토리 메서드** 라는걸 알았다.

## 참고문서
* [이미지출처 - DesignPatternSmalltalkCompanion:AbstractFactory](http://trans.onionmixer.net/mediawiki/index.php?title=DesignPatternSmalltalkCompanion:AbstractFactory)
* [팩토리패턴 - JSPark ](http://jusungpark.tistory.com/14)
* [디자인패턴 - 추상 팩토리(Abstract Factory) - YUKARIKO](https://yukariko.github.io/designpattern/2016/08/19/abstract-factory.html)
* [The Abstract Factory Pattern In JavaScript - 예제코드 참고](https://anasshekhamis.com/2017/08/17/the-abstract-factory-pattern-in-javascript/)
