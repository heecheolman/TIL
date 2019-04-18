# RxJS Operator

![](http://reactivex.io/assets/Rx_Logo_S.png)

[Rx](http://reactivex.io/intro.html) 는 비동기 데이터 스트림을 처리하는 API 를 제공하는 라이브러리입니다. 모던 웹에서 비동기 통신은 필수적입니다. 때문에 자바스크립트 언어의 특징을 이용해 콜백을 사용했습니다. 콜백지옥을 해결하고자 프로미스가 나오고 더 나아가서 프로미스 기반의 `async/await` 도 나왔습니다.

> 만약 동기방식으로 통신을 한다면 기다림의 연속

또 다른 해결법으로 등장한것이 RxJS 입니다. RxJS 는 요약하자면 이벤트 스트림과 데이터를 쉽게 만들고 다룰 수 있게 해주는 라이브러리입니다. RxJS 를 배우기 전에 [리액티브 프로그래밍의 개념을 짚고 넘어가는게 좋습니다.](https://github.com/heecheolman/TIL/blob/master/angular/angular13.md)


RxJS 에서 이벤트 스트림과 데이터를 다루기위해 여러 연산자들을 사용하게 되는데 연산자들이 꽤 많아 하나씩 알아보려합니다. 주로 [learnrxjs](https://www.learnrxjs.io/) 를 참고합니다.

RxJS 사용되는 Operator(연산자)들을 알아보려합니다. 연산자들이 너무 많아 어떤것들이 있는지 조금씩 살펴보고 싶어 정리합니다.

> RxJS 를 배우며 함수형 프로그래밍도 배우고 싶습니다.

## 연산자 타입

* [Combination](https://github.com/heecheolman/TIL/blob/master/rxjs/rxjs-combination.md)
* [Conditional](https://github.com/heecheolman/TIL/blob/master/rxjs/rxjs-conditional.md)
* [Creation](https://github.com/heecheolman/TIL/blob/master/rxjs/rxjs-creation.md)
* [Error Handling](https://github.com/heecheolman/TIL/blob/master/rxjs/rxjs-error-handling.md)
* Multicasting
* Transformation
* Utility

## Observable

옵저버블은 계속해서 데이터를 생성하는 데이터 스트림 역할을하며 보통 변수 뒤에 `$` 표시를 붙여줍니다. 데이터를 생성해 옵저버블이 만든 데이터를 방출(emit) 할 수 있습니다.

## Observer

옵저버는 옵저버블이 방출(emit) 한 데이터를 받아보는 '구독자' 역할을 합니다. 보통 옵저버블을 구독하고, 옵저버블이 데이터를 방출하면 옵저버는 구독을 하고있기 때문에 해당 데이터를 받아볼 수 있습니다. 일종의 Notification 과 같습니다.

## 참고문서
* [learnrxjs.io](https://www.learnrxjs.io/)
* [MS 는 ReactiveX를 왜 만들었을까? - 개발왕 김코딩](https://huns.me/development/2051)
* [[번역] 반응형 프로그래밍과 RxJS 이해하기 - DailyEngineering](https://hyunseob.github.io/2016/10/09/understanding-reactive-programming-and-rxjs/)
