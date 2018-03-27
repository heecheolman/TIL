# Singleton Pattern

## 싱글톤패턴(singleton pattern) 이란?
싱글톤 패턴은 전체 시스템에서 하나의 인스턴스만 존재하도록 보장하는 객체 생성패턴이다.  
동일 클래스로 `new` 를 해도 인스턴스 하나만 존재한다는 것이다.

## 특징
* 객체 자체에는 접근이 불가능해야함  
* 객체에 대한 접근자(비공개 멤버: 클로저)를 사용해 실제 객체를 제어할 수 있다.
* 객체는 단 하나만 만들어지며, 해당 객체를 공유함


다음과 같은 객체 리터럴도 싱글톤 패턴이다.
```javascript
var obj = {
  a: 'foo',
  b: function(){}
}
```
이렇게 하게되면 비공개상태 및 함수를 정의할 수 없다.

그렇기 때문에 `closure` 를 통해 비공개로 만들어야한다.
```javascript
var Singleton = (function() {

  // instance 비공개 변수 정의
  var instance;

  // foo 비공개 메서드 정의
  function foo(){
    return {
      // public 메서드 정의
      publicMethod: function() {
        return `hello Singleton Pattern!`;
      },
      // public 속성 정의
      publicProp: `single value`
    }
  }


  // public 메서드인 getInstance 를 정의한 객체
  // 이 메서드를 통해 비공개된 메서드와 변수에 접근 가능 (closure)
  return {
    getInstance: function(){
      if(!instance){
        instance = foo();
      }
      return instance;
    }
  }
})();

// singleton object 를 생성
var a = Singleton.getInstance();
// singleton object 를 생성
var b = Singleton.getInstance();


// a 와 b 의 객체는 서로 같은 객체를 가리킴
console.log(a === b); // true

console.log(a.publicMethod()); // hello Singleton Pattern!
console.log(b.publicMethod()); // hello Singleton Pattern!
```

`foo()` 의 `return` 문에서 객체 리터럴로 정의되는 객체가 `Singleton Object` 임. 이 객체는 프로그램 전체에서 하나만 존재하게 된다.  
`getInstance()`의 public 메서드를 통해 `instance` 변수의 값을 확인한 후 아직 `Singleton Object` 가 생성되지않았다고 판단한다면, 내부 함수인 `foo()` 를 통해 `Singleton Object` 를 반환해 `instance`에 할당한다.


## in ES6
위의 방법과는 완전 동일하지 않지만 `es6` 문법으로 고쳐보자!
```javascript
let instance = null;
class Singleton{
  constructor(){
    if(instance) return instance;
    this.name = "heecheolman";
    this.age = 24;
    instance = this;
  }
}

var firstSingleton = new Singleton();
var secondSingleton = new Singleton();

console.log(firstSingleton === secondSingleton); // true
console.log(instance === firstSingleton); // true
```
`es6` 방법으로는 `instance` 가 캡슐화에 어려움이 있었다. `es7` 으로 바꿔보자

## in ES7
```javascript
class Singleton{
  static instance;

  constructor(){
    if(instance) return instance;
    this.name = "heecheolman";
    this.age = 24;
    instance = this;
  }
}

var firstSingleton = new Singleton();
var secondSingleton = new Singleton();

console.log(firstSingleton === secondSingleton); // true
console.log(instance === firstSingleton); // true
```

`es7` 에서 프로퍼티도 `static` 이 가능해졌다. 고한다.
#### 참고문서
[http://webclub.tistory.com/150](http://webclub.tistory.com/150)  
[http://projectl33t.xyz/archives/50763](http://projectl33t.xyz/archives/50763)  
[https://kkd927.github.io/general/web/javascript/2017/04/12/4-JavaScript-Design-Patterns-You-Should-Know.html](https://kkd927.github.io/general/web/javascript/2017/04/12/4-JavaScript-Design-Patterns-You-Should-Know.html)
