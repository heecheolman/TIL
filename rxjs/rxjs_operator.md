# RxJS Operator
RxJS 사용되는 Operator(연산자)들을 알아보려합니다. 연산자들이 너무 많아 어떤것들이 있는지 조금씩 살펴보고 싶어 정리합니다.

## 연산자 분류

* [Combination](#combination)
* Conditional
* [Creation](#creation)
* Error Handling
* Multicasting
* Transformation
* Utility

---

# Combination
combination operator(조합 연산자)는 여러개의 Observable을 결합하는 연산자이며 결합된 스트림은 값의 순서, 시간 및 구조가 변경된다는점이 특징입니다.

### 목록
* combineAll
* [combineLatest](#combinelatest)
* [concat](#concat)
* concatAll
* forkJoin
* [merge](#merge)
* mergeAll
* pairwise
* race
* [startWith](#startwith)
* withLatestFrom
* [zip](#zip)

## combineAll

## [combineLatest](https://github.com/tienne/learn-rxjs/blob/master/operators/combination/combinelatest.md)

결합시키는 Observable 들 중 어느것이라도 Observable 의 값이 발생하면, 마지막 값 을 넘겨줍니다.

![이미지](https://camo.githubusercontent.com/d1ca47f1c9da43d026c31865f0e402e3f12caafb/687474703a2f2f7265616374697665782e696f2f72786a732f696d672f636f6d62696e654c61746573742e706e67)

```js
// 1초에 한번, 4초에 한번씩 값 발생
const timerOne = Rx.Observable.timer(1000, 4000);
// 2초에 한번, 4초에 한번씩 값 발생
const timerTwo = Rx.Observable.timer(2000, 4000);

// 묶어줍니다.
const combined$ = Rx.Observable.combineLatest(
  timerOne,
  timerTwo,
);

const subscribe = combined$.subscribe(latestValues => {
  const [timerValOne, timerValTwo] = latestValues;
  // ... 처리
})
```

## [concat](https://github.com/tienne/learn-rxjs/blob/master/operators/combination/concat.md)

Observable을 차례대로 구독완료하며 값을 발생시킵니다. 실행순서가 상관없다면 [merge](#merge) 를 사용합니다.

![이미지](https://camo.githubusercontent.com/65ce224e5ba1cacfbc4a7ae1a62cd0991aa602ee/687474703a2f2f7265616374697665782e696f2f72786a732f696d672f636f6e6361742e706e67)

```js
const sourceOne = Rx.Observable.of(1, 2, 3); // 1, 2, 3
const sourceTwo = Rx.Observable.of(4, 5, 6); // 4, 5, 6
const example = sourceOne.concat(sourceTwo); // 연결
```

## concatAll

## forkJoin

## [merge](https://github.com/tienne/learn-rxjs/blob/master/operators/combination/merge.md)
![이미지](http://reactivex.io/rxjs/img/merge.png)

여러개의 옵저버블을 하나의 옵접버블로 바꿔줍니다.

```ts
const first = Rx.Observable.interval(2500); // 2.5초마다
const second = Rx.Observable.interval(2000); // 2초마다

const example = Rx.Observable.merge(first.mapTo('FIRST'), second.mapTo('SECOND')); // merge 해줍니다.
```

## mergeAll

## pairwise

## race

## [startWith](https://github.com/tienne/learn-rxjs/blob/master/operators/combination/startwith.md)

![이미지](http://reactivex.io/rxjs/img/startWith.png)

첫번째 값을 주어 방출합니다.

```js
const source = Rx.Observable.of(1, 2, 3);
const example = source.startWith(0);
const subscribe$ = example.subscribe(val => console.log(val))
// 0, 1, 2, 3
```

## withLatestFrom

## zip

모든 옵저버블의 방출값들을 array 로 만들어줍니다. 그리고 모든 방출값들이 들어올 때 까지 기다리고 방출합니다.

```js
const sourceOne = of('Hello');
const sourceTwo = of('World!');
const sourceThree = of('Goodbye');
const sourceFour = of('World!');
//wait until all observables have emitted a value then emit all as an array
const example = zip(
  sourceOne,
  sourceTwo.pipe(delay(1000)),
  sourceThree.pipe(delay(2000)),
  sourceFour.pipe(delay(3000))
);
//output: ["Hello", "World!", "Goodbye", "World!"]
const subscribe = example.subscribe(val => console.log(val));
```

---

# Conditional

---

# Creation
Creation 오퍼레이터는 해당 값을 옵저버블로 만들어 반환해줍니다.

### 목록
* create
* defer
* empty
* [from](#from)
* fromEvent
* fromPromise
* interval
* [of](#of)
* range
* throw
* timer

## create
## empty
## [from](https://github.com/tienne/learn-rxjs/blob/master/operators/creation/from.md)
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
## [of](https://github.com/tienne/learn-rxjs/blob/master/operators/creation/of.md)
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

# Error Handling

에러 핸들링을 사용해 에러 발생 시 에러를 정상적으로 처리해주는 연산자들

* [catch](#catch)
* [retry][#retry]
* [retryWhen](#retryWhen)

## catch

옵저버블의 에러를 잡아 처리해주는 연산자입니다.

```ts
// 에러 방출
const source = Rx.Observable.throw('This is an error!');
// catch 로 에러 잡기, 여기서는 of 연산자로 메세지를 던짐
const example = source.catch(val => Rx.Observable.of(`I caught: ${val}`));
//output: 'I caught: This is an error'
const subscribe = example.subscribe(val => console.log(val));
```


## retry

## retryWhen
