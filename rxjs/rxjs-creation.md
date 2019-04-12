# Creation
Creation 오퍼레이터는 해당 값을 옵저버블로 만들어 반환해줍니다.

## 목록
* ajax ⭐️
* create
* defer
* empty
* [from](#from)⭐️
* fromEvent
* fromPromise
* interval
* [of](#of)⭐️
* range
* throw
* timer

## ajax ⭐️
## create
## empty
## [from](https://github.com/tienne/learn-rxjs/blob/master/operators/creation/from.md) ⭐️
![이미지](http://reactivex.io/rxjs/img/from.png)

열거가능한(이터러블한) 데이터들을 순서대로 내보내 옵저버블로 반환합니다.
```js
//emit array as a sequence of values
const arraySource = Rx.Observable.from([1,2,3,4,5]);
//output: 1,2,3,4,5
const subscribe = arraySource.subscribe(val => console.log(val));
```

## fromEvent

## fromPromise

## interval

## [of](https://github.com/tienne/learn-rxjs/blob/master/operators/creation/of.md) ⭐️

![이미지](http://reactivex.io/rxjs/img/of.png)

파라미터로 전달된 값들을 순서대로 내보냅니다.
```js
//emits values of any type
const source = Rx.Observable.of({name: 'Brian'}, [1,2,3], function hello(){ return 'Hello'});
//output: {name: 'Brian}, [1,2,3], function hello() { return 'Hello' }
const subscribe = source.subscribe(val => console.log(val));
```

## range

## throw

## timer
