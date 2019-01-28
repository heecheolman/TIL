# RxJS Operator
RxJS 에서 사용되는 Operator(연산자)들을 알아봅니다.

## 연산자 분류

* Combination
* Conditional
* Creation
* Error Handling
* Multicasting
* Transformation
* Utility



## Combination
combination operator(조합 연산자)는 여러개의 Observable을 결합하는 연산자이며 결합된 스트림은 값의 순서, 시간 및 구조가 변경된다는점이 특징입니다.

### 목록
* combineAll
* [combineLatest](#combine)
* [concat](#concat)
* concatAll
* forkJoin
* merge
* mergeAll
* pairwise
* race
* startWith
* withLatestFrom
* zip

#### combineAll

#### combineLatest

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

#### concat

Observable을 차례대로 구독완료하며 값을 발생시킵니다. 실행순서가 상관없다면 [merge](#merge) 를 사용합니다.

![이미지](https://camo.githubusercontent.com/65ce224e5ba1cacfbc4a7ae1a62cd0991aa602ee/687474703a2f2f7265616374697665782e696f2f72786a732f696d672f636f6e6361742e706e67)

```js
const sourceOne = Rx.Observable.of(1, 2, 3); // 1, 2, 3
const sourceTwo = Rx.Observable.of(4, 5, 6); // 4, 5, 6
const example = sourceOne.concat(sourceTwo); // 연결
```

#### concatAll

#### forkJoin

#### merge

여러개의 옵저버블을 하나의 옵접버블로 바꿔줍니다.

```ts
const first = Rx.Observable.interval(2500); // 2.5초마다
const second = Rx.Observable.interval(2000); // 2초마다

const example = Rx.Observable.merge(first.mapTo('FIRST'), second.mapTo('SECOND')); // merge 해줍니다.
```

#### mergeAll

#### pairwise

#### race

#### startWith

첫번째 값을 주어 방출합니다.

```js
const source = Rx.Observable.of(1, 2, 3);
const example = source.startWith(0);
const subscribe$ = example.subscribe(val => console.log(val))
// 0, 1, 2, 3
```

#### withLatestFrom

#### zip
