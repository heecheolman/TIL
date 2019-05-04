# RxJS 튜토리얼 - 옵저버와 옵저버블

Reactive 프로그래밍이 익숙하지 않아 튜토리얼들을 하나씩 따라해보는 공간입니다.

## [Observer(옵저버)](http://reactivex.io/rxjs/class/es6/MiscJSDoc.js~ObserverDoc.html)

옵저버(Observer) 는 옵저버블(Observable)이 방출한 데이터를 받아보는 구독자 역할입니다. RxJS 에서 옵저버의 인터페이스는 다음과 같습니다.

```ts
export interface Observer<T> {
  closed?: boolean;
  next: (value: T) => void;
  error: (err: any) => void;
  complete: () => void;
}
```

옵저버는 3개의 인터페이스가 필수적입니다.

* `next()`: 옵저버블로부터 데이터를 받을 때 실행되는 콜백함수입니다.
* `error()`: 옵저버블로부터 에러를 받을 때 실행되는 콜백함수입니다.
* `complete()`: 옵저버블이 데이터 방출을 완료했을 때 실행되는 콜백함수입니다.

선택적인 인터페이스는 `closed` 인데 해당 인터페이스는 해당 옵저버가 구독을 취소했는지 여부를 나타내는 flag 입니다.

> closed 를 어떻게 써야할지 아직 감이 안잡힌다. 나중에 다시 봐야겠다.

### example

[`of`](https://www.learnrxjs.io/operators/creation/of.html) 연산자를 통해 데이터 스트림을 생성하고 해당 스트림을 구독하는 코드입니다.  `Observer<T>` 인터페이스를 구현해 어떻게 작동하는지 생각해봤습니다.

```ts
import { Observer, of } from 'rxjs';

const observer: Observer<number> = {
    closed: false,
    next(value): void {
        console.log(value);
    },
    error(error): void {
        console.error(error);
    },
    complete(): void {
        console.log('complete');
    }
};
of<number, number, number, number>(1, 2, 3, 4)
    .subscribe(observer);

// output: 1 2 3 4 complete
```

## [Observable(옵저버블)](http://reactivex.io/rxjs/class/es6/Observable.js~Observable.html)

완전 자세한 내용은 해당 도큐멘트를 보면 되겠지만 지금은 개념만 짚고 넘어가려 합니다.

### `Observable<T>`

```ts
export class Observable<T> implements Subscribable<T> {
  ...
}
```

### `Subscribable<T>`

```ts
export interface Subscribable<T> {
  subscribe(observer?: PartialObserver<T>): Unsubscribable;
  subscribe(next: null | undefined, error: null | undefined, complete: () => void): Unsubscribable;
  subscribe(next: null | undefined, error: (error: any) => void, complete?: () => void): Unsubscribable;
  subscribe(next: (value: T) => void, error: null | undefined, complete: () => void): Unsubscribable;
  subscribe(next?: (value: T) => void, error?: (error: any) => void, complete?: () => void): Unsubscribable;
}
```

### `Unsubscribable`

```ts
export interface Unsubscribable {
  unsubscribe(): void;
}
```

먼저 `Observable<T>` 는 `Subscribable<T>` 를 구현하고 있어야합니다. `Subscribable<T>` 의 인터페이스를 살펴보면 `subscribe()` 메서드를 구현해야 하는데 인자로 세개를 받고 있습니다.

`next()`, `error()`, `complete()` 순서로 받고있는데 아까 살펴본 옵저버(Observer) 의 인터페이스와 유사합니다. 대신 `complete()` 가 옵셔널입니다. 한번 더 살펴보면 `subscribe()` 는 `Unsubscribable` 을 리턴한다고 되어있는데 인터페이스는 `unsubscribe()` 메셔드입니다.

구독을 해서 원하는 만큼 실행이 되었으면 구독을 해제하는 시점도 있을 것입니다. 지금은 어떤 상황에 구독을 해제해야하는지보다는 어떻게 구독을 해제하는지에 대해 집중하겠습니다.

`subscribe()` 의 return 이 `unsubscribe()` 메서드이므로 해당 메서드를 통해 구독을 해제할 수 있습니다.

```ts
const number$ = of<number, number, number, number>(1, 2, 3, 4)
    .subscribe(observer);

number$.unsubscribe();
```
