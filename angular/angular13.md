<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 리액티브 프로그래밍과 RxJS
앵귤러 CLI 를 사용해 생성한 프로젝트는 RxJS 가 포함되어있고 RxJS 는 리액티브 프로그래밍 패러다임입니다. 리액티브 프로그래밍에 관해 그리고 RxJS 를 살펴보겠습니다.

## 📝 목차
* [리액티브 프로그래밍이란?](#리액티브-프로그래밍이란)
  * [반응](#반응)
  * [옵저버 패턴](#옵저버-패턴)
* [옵저버블과 옵저버](#옵저버블과-옵저버)
  * [생성과 구독](#생성과-구독)
  * [Observable 클래스 살펴보기](#observable-클래스-살펴보기)
    * [생성자](#생성자)
    * [subscribe](#subscribe)
* [Cold Observable과 Hot Observable](#cold-observable과-hot-observable)
* [Subject 종류](#subject-종류)
  * [AsyncSubject](#asyncsubject)
  * [PublishSubject](#publishsubject)
  * [BehaviorSubject](#behaviorsubject)
  * [ReplySubject](#replysubject)
* [오퍼레이터](#오퍼레이터)

## 리액티브 프로그래밍이란?
리액티브 프로그래밍(Reactive Programming) 이란 비동기 데이터 스트림(Asynchronous Data Stream) 에 기반을 둔 프로그래밍 패러다임입니다.

> 데이터 스트림?  
연속적이 데이터의 흐름

**기존**: 동기데이터의 처리방식과 비동기 데이터 처리방식이 각각 다름  
**리액티브 프로그래밍**: 동기/비동기와 관계없이 데이터를 생산한다면 시간 축을 따라 연속으로 흐르는 데이터 스트림으로 처리

즉, 리액티브 프로그래밍이란 다양한 데이터를 '데이터 스트림' 이라는 일관된 형식으로 만들고, 해당 데이터 스트림을 구독(subscribe) 하여 상태 변화에 반응하는 방식을 말합니다.


#### 반응
반응을 한다는것은 '외부에서 어떠한 행동(자극)이 있을 때 응답하는것' 을 말합니다.

우리가 사용하던 기존의 방식은 외부환경에 명령하여 원하는 결과를 획득했다면, 리액티브 프로그래밍은 외부에서 반응이 있을 시 이에 대해 응답하는것을 말합니다.

<img src="http://huns.me/wp/wp-content/uploads/2016/09/reactive-eric.png" style="width: 400px;">  

정리하자면 프로그램이 외부 환경과 통신하는 방법은 크게 두가지가 있습니다.

1. **pull-scenario** : 애플리케이션이 외부 환경에서 데이터를 가죠오는 방식
2. **push-scenario** : 외부 환경이 애플리케이션에 데이터를 넣는 방식

리액티브 프로그래밍은 **푸시 시나리오** 방식을 사용합니다.


#### 옵저버 패턴
옵저버 패턴(Observer Pattern)을 사용하여 '반응'합니다.

**옵저버블(Observable)** : 데이터 스트림을 생성하고 방출하는 객체  
**노티피케이션(Notification)** : 옵저버블이 방출할 수 있는 푸시 기반 이벤트 또는 값  
**옵저버(Observer)** : 옵저버블이 방출한 노티피케이션을 획득해 사용하는 객체  

**옵저버블은 데이터를 생산하는 생산자이며, 옵저버는 데이터를 소비하는 소비자라고 생각하면 됩니다.**

옵저버는 옵저버블을 **구독(subscribe)** 하여 구독에 의해 옵저버블의 상태를 관찰하고 옵저버블이 방출한 노티피케이션은 옵저버에게 전파됩니다.

```
Observable (데이터 스트림 생산 : 생산자)
            ↑     |
    구독     |     |       방출
 subscribe  |     |   notification
            |     ↓
┌─────────────────────────────────┐
│                                 │
│ Observer1, Observer2, Observer3 │
│                                 │
└─────────────────────────────────┘
```

## 옵저버블과 옵저버

### 생성과 구독

옵저버블을 생성하고 구독하는 과정을 살펴보겠습니다.

```ts
// myComponent.component.ts
import { Observable } from '@angular/core';
...
export class MyComponent implements OnInit {
  ngOnInit() {

    // 옵저버블이 '구독'될 때 호출되는 구독 함수
    const subscriber = (observer) => {
      // next()           - next()
      // error()          - error()
      // complete()       - complete()
      // return () => {}  - 구독 해지될 때
    }

    // 옵저버블 생성
    const observable$ = new Observable(subscriber);

    // 구독
    observable$.subscribe(
      next(), // next 에 반응할 메서드
      error(), // error 에 반응할 메서드
      complete(), // complete 에 반응할 메서드
    );
  }
}
```

`new Observable()` 함수를 통해 옵저버블을 생성하고, 구독 시 응답에 반응할 각 메서드(next, error, complete)를 인자로 넣어줍니다. **구현에서의 구독이란 옵저버블의 `subscribe` 오퍼레이터를 호출할 때 인자로 옵저버를 전달하는 것을 말합니다.**

|구분|설명|노티피케이션내용|
|:----:|:------:|:-------------:|
|next|옵저버블이 방출한 next타입에 반응하는 콜백함수|값 또는 이벤트|
|complete|옵저버블이 방출한 complete타입에 반응하는 콜백함수|없음|
|error|옵저버블이 방출한error 타입에 반응하는 콜백함수|에러 객체|

### Observable 클래스 살펴보기


#### 생성자
```ts
// Observable.ts
/**
   * @constructor
   * @param {Function} subscribe the function that is called when the Observable is
   * initially subscribed to. This function is given a Subscriber, to which new values
   * can be `next`ed, or an `error` method can be called to raise an error, or
   * `complete` can be called to notify of a successful completion.
   */
constructor(subscribe?: (this: Observable<T>, subscriber: Subscriber<T>) => TeardownLogic) {
    if (subscribe) {
      this._subscribe = subscribe;
    }
  }
```
**`new Observable()`** : 생성자 호출을 하면 인자로 '구독'될 때 호출되는 구독함수를 전달 할 수 있으며 옵셔널합니다. 그리고 구독함수가 있다면 구독함수를 할당(?) 해주는것 같습니다.

#### subscribe
```ts
// Observable.ts
subscribe(next?: (value: T) => void, error?: (error: any) => void, complete?: () => void): Subscription;
```
`subscribe`의 인자로 `next()`, `error()`, `complete()` 함수를 보낼 수 있고 옵셔널합니다.

> 옵저버블은 구독을 해지(unsubscribe) 하거나 complete 메서드가 호출될 때까지 옵저버에게 새로운 데이터를 계속해서 전파합니다.

## Cold Observable과 Hot Observable

### Cold Observable
옵저버블은 '구독'되기 전까지 동작하지 않습니다. 때문에 옵저버는 '구독'이라는것을 하게되면 옵저버블이 방출하는 모든 데이터 스트림을 처음부터 받을 수 있습니다. 이것을 **Cold Observable** 이라합니다. 그리고 RxJS 는 Cold Observable 이 기본값입니다.

옵저버블을 구독하는 옵저버는 여러개일 수 있습니다. Cold Observable 을 구독하는 모든 옵저버들은 Cold Observable 이 방출하는 모든 데이터를 구독하는 시점에 상관없이 모두 받을 수 있습니다.

이것은 모든 옵저버는 자신만을 위해 독립적인 실행을 하는 옵저버블을 갖게된다는 특징이 있는데 이것을 **유니캐스트(unicast)** 라고 합니다.

### Hot Observable
Cold Observable 과는 반대로 옵저버블을 생성하자마자 **구독과 상관없이 바로 데이터 스트림을 방출하기 시작합니다.** 때문에 일정 시간이 지난 뒤에 구독을 하면 **데이터 스트림의 중간 부분부터 구독하게 됩니다.**

RxJS 는 Cold Observable 이 기본 이지만 Hot Observable 로 만들려면 `publish`, `share` 오퍼레이터를 사용할 수 도 있지만 `Subject` 를 사용하는것이 편리합니다.

Subject 는 Observable 과 Observer 역할을 모두 할 수 있습니다. Observable 처럼 구독할 수 있지만 Observable 과의 차이가 있다면 '멀티 캐스트(multicast)'방식이라는 점입니다.

Subject 는 옵저버블을 구독할 수도 있지만 옵저버처럼 next, complete 메서드를 직접 호출할 수 있습니다.

```ts
// ...
const subject = new Subject();
const hotObservable = subject.asObservable(); // hotObservable 생성
subject.next(1); // 데이터 방출
hotObservable.subscribe(...) // 구독
```

### 차이점 살펴보기

#### Cold Observer
구독하기 시작하면 1, 2, 3 데이터를 처음부터 모두 받습니다.
```ts
// mycomponent.component.ts
...
ngOnInit() {
  const numbers$ = new Observable((observer) => {
      observer.next(1);
      observer.next(2);
      observer.next(3);
    });

    numbers$.subscribe(
      (value) => console.log(`1st next: ${ value }`),
      (error) => console.error(`1st error: ${ error }`),
      () => console.log('1st complete')
    );

    numbers$.subscribe(
      (value) => console.log(`2nd next: ${ value }`),
      (error) => console.error(`2nd error: ${ error }`),
      () => console.log('2nd complete')
    );
}
/*
1st next: 1
1st next: 2
1st next: 3
2nd next: 1
2nd next: 2
2nd next: 3
*/
```

#### Hot Observer
구독하기 전 데이터는 받아볼 수 없습니다. 처음의 1, 2, 3 은 받지 못하고 4, 5, 6 부터 받을 수 있습니다.
```ts
// mycomponent.component.ts
...
ngOnInit() {
  const subject = new Subject();
    const numbersBySubject$ = subject.asObservable();

    subject.next(1);
    subject.next(2);
    subject.next(3);

    numbersBySubject$.subscribe(
      (value) => console.log(`1st next: ${ value }`),
      (error) => console.error(`1st error: ${ error }`),
      () => console.log('1st complete')
    );

    numbersBySubject$.subscribe(
      (value) => console.log(`2nd next: ${ value }`),
      (error) => console.error(`2nd error: ${ error }`),
      () => console.log('2nd complete')
    );

    subject.next(4);
    subject.next(5);
    subject.next(6);
}
/*
1st next: 4
2nd next: 4
1st next: 5
2nd next: 5
1st next: 6
2nd next: 6
*/
```

## 유니캐스트와 멀티캐스트
**유니캐스트** : Cold Observable 을 구독하는 모든 옵저버는 각각 독립적으로 실행하는 옵저버블을 갖게되어 일대일 관계입니다.  
**멀티캐스트** : Hot Observable 은 옵저버와 일대다 관계를 갖습니다.

```ts
// mycomponent.component.ts
...
ngOnInit() {
  ngOnInit(): void {
    // COLD
    console.log('COLD');
    const coldObservable$ = Observable.create((observer) => observer.next(Math.random()));
    coldObservable$.subscribe(
      (value) => console.log(`1st Cold Observable's observer: ${value}`),
    );
    coldObservable$.subscribe(
      (value) => console.log(`2nd Cold Observable's observer: ${value}`),
    );

    // HOT
    console.log('HOT');
    const subject = new Subject();
    const hotObservable$ = subject.asObservable();
    hotObservable$.subscribe(
      (value) => console.log(`1st Hot Observable's observer: ${value}`),
    );
    hotObservable$.subscribe(
      (value) => console.log(`2nd Hot Observable's observer: ${value}`),
    );
    subject.next(Math.random());
  }
}

/*
COLD
1st Cold Observable's observer: 0.3458584261362281
2nd Cold Observable's observer: 0.6683291493239305

HOT
1st Hot Observable's observer: 0.10435603985906838
2nd Hot Observable's observer: 0.10435603985906838
*/
```

실행 결과를 보면 Cold Observable 은 각각의 옵저버가 독립된 실행환경을 갖지만 Hot Observable 은 동일한 값을 갖는것을 알 수 있습니다. 추가적으로 subject 를 통해 옵저버블의 역할과 옵저버의 역할을 둘다 하는것도 확인할 수 있습니다.

## Subject 종류
Subject 는 4종류로 분류됩니다.

### AsyncSubject
AsyncSubject 는 Observable 로부터 배출된 마지막 값을 방출(emit)하고 `complete()`된 후에야 동작합니다.

<img src="https://smilebin.github.io/images/S.AsyncSubject.png" style="width: 400px">

### PublishSubject
PublishSubject는 구독(subscribe) 전의 이벤트는 방출(emit)하지 않습니다. 그리고 error 가 발생하면 그 이후에 이벤트를 emit 하지 않습니다.

<img src="https://smilebin.github.io/images/S.PublishSubject.png" style="width: 400px">

### BehaviorSubject
BehaviorSubject 는 PublishSubject 와 비슷하지만 **반드시 값을 초기화** 해줘야합니다. 그리고 Observer 에게 구독(subscribe) 하기 전 마지막 이벤트 또는 값부터 emit 합니다.

<img src="https://smilebin.github.io/images/S.BehaviorSubject.png" style="width: 400px">

### ReplySubject
ReplySubject 는 **미리 정해진 사이즈 만큼** 가장 최근의 이벤트를 새로운 Subscriber 에게 전달합니다.

<img src="https://smilebin.github.io/images/S.ReplaySubject.png" style="width: 400px">

## 오퍼레이터
오퍼레이터(operator) 는 옵저버블을 생성, 변환, 필터링, 에러처리의 기능을 하는 함수입니다. 오퍼레이터는 새로운 옵저버블을 return 하므로 `subscribe`을 호출하기 전까지 체이닝이 가능한데 이를 '옵저버블 시퀀스(Observable Sequence)'라고 합니다.

간단한 사용 예
```ts
// ...
export class MyComponent implements OnInit, OnDestroy {
  myArray = [1, 2, 3, 4, 5];
  subscription: Subscription;

  ngOnInit() {
    const observable$ = from(this.myArray);
    this.subscription = observable$
      .pipe(
        // 옵저버블 변형
        map(item => item * 2), // 2, 4, 6, 8, 10
        filter(item => item > 5), // 6, 8, 10
        tap(item => console.log(item)) // print 6, 8, 10
      )
      .subscribe(
        ...
      )
  }

  ngOnDestroy() {
    this.subscription.unsubscribe(); // 구독 해제 (메모리 누수 방지)
  }
}
```
라이프사이클 훅인 `ngOnDestroy()` 에서 컴포넌트가 파괴되기 직전에 메모리누수를 방지하기위해 구독을 해제하였습니다.

> 옵저버블의 오퍼레이터는 [다음 페이지](http://reactivex.io/documentation/operators.html)를 참고합니다.

## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
* [MS는 ReactiveX를 왜 만들었을까? - 김코딩](http://huns.me/development/2051)
* [Reactive Programming : RxJS 알아가기](https://smilebin.github.io/2018-03-16/rxjs-intro/)
