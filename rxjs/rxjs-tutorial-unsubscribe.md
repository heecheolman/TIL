# RxJS 튜토리얼 - 여러가지 구독 해제 패턴

RxJS 에서는 '구독' 하는 방식으로 데이터를 받아봅니다. 즉, 구독이 끝나기 전까지 옵저버블이 `next()` 를 통해 데이터를 보내면 계속 받아보게 되는것입니다. 만약 구독을 취소하지 않는다면 사용하지 않는 스트림들은 메모리를 차지하게되고 메모리 누수로 번져질 수 있습니다. 그만큼 구독해제에 신경을 써야합니다.

먼저 구독을 할 때 데이터를 다루는 두 가지 방법이 있는데 이 방법을 살펴보고 이후에 패턴을 다루겠습니다.

> Angular 에서 공식적으로 RxJS를 다루므로 Angular 컴포넌트로 진행합니다.

### `async` 파이프를 이용한 구독과 구독해제

#### 장점

* `async` 파이프를 이용하면 컴포넌트가 destroy 될 때 자동적으로 구독을 해제해줍니다.

#### 단점

* `.ts` 안에서 데이터를 다루고 싶을 때 별도의 `tap()` 과 같은 훅을 통해 별도로 저장해야합니다.
* 템플릿 내에서는 `async` 파이프로 감싸진 태그 안에서만 해당 데이터를 접근할 수 있습니다.
* `async` 파이프를 사용할 때마다 api 요청이 들어갑니다.

```ts
@Component({ ... })
export class MyComponent implements OnInit {
  data$: Observable<Item[]>;
  constructor(
    private dataService: DataService,
  ) {}
  ngOnInit() {
    this.data$ = this.dataService.getData();
    /* 훅으로 데이터 저장
      this.data$ = this.dataService.getData()
        .pipe(
          tap((data) => { ... })
        )
    */
  }
}
```
```html
<ul *ngIf="data$ | async as dataList">
  <li *ngFor="let item of dataList">
    {{ item.name }} : {{ item.color }}
  </li>
</ul>
```



### `subscribe` 메서드를 이용한 구독과 `unsubscribe` 구독해제

보통 구독해제를 하려고한다면 `unsubscribe()` 메서드를 특정 시점에 호출하는 방법이 있습니다. 예를들어, 앵귤러의 라이프사이클중 컴포넌트가 파괴될 때인 `OnDestroy` 시점에 `unsubscribe()` 하는 것입니다.

#### 장점

* `aysnc` 파이프와 달리 템플릿에서 받아온 데이터를 자유롭게 접근 가능합니다.
*  컴포넌트 클래스 안의 어느 메서드에서도 받아온 데이터에 대해 접근이 가능합니다.

#### 단점

* 구독해제를 신경쓰지 않는다면 메모리 누수가 발생할 수 있습니다.
* 비동기적으로 이루어지기 때문에 템플릿에서 데이터에대해 바로 접근하려하면 에러가 날 수 있습니다. 때문에 로딩을 다루는 flag 변수를 두어 시점을 조정해야 합니다.

```ts
@Component({ ... })
export class MyComponent implements OnInit, OnDestroy {

  dataSubscription: Subscription;

  constructor(
    private dataService: DataService,
  ) {}

  ngOnInit() {
    this.dataSubscription = this.dataService.getData()
      .subscribe( ... );
  }

  ngOnDestroy() {
    this.dataSubscription.unsubscribe();
  }
}
```

`subscribe()` 메서드를 통해 구독이 많아지게 되면 `ngOnDestroy` 훅에서 다뤄야하는 Subscription 들이 많아지게 되는데 제어하는 일종의 패턴이 존재합니다.

## 구독해제 패턴

### take ⭐️

[`take()`](https://www.learnrxjs.io/operators/filtering/take.html) 오퍼레이터는 인자로 number 를 하나 받는데, 넣어준 수 만큼 데이터를 받아보고 구독을 종료합니다.

```ts
export class MyComponent implements OnInit {
  ngOnInit() {
    this.dataService.getData()
      .pipe(
        take(1)
      )
      .subscribe( ... )
  }  
}
```

컴포넌트의 `ngOnInit` 훅에서 한 번만 데이터를 받아오고 구독을 종료합니다.

### takeWhile

[`takeWhile()`](https://www.learnrxjs.io/operators/filtering/takewhile.html) 오퍼레이터는 `return` 되는 값이 `false` 일 때 까지 구독을 합니다. `ngOnDestroy` 에서 `takeUntil` 에 넣어준 boolean 변수를 `false` 로 변경하게되면 구독을 종료하게 되는 것입니다.

```ts
export class MyComponent implements OnInit {
  private alive = true;

  ngOnInit() {
    this.dataService.getData()
      .pipe(
        takeWhile(() => this.alive)
      )
      .subsribe( ... )
  }

  ngOnDestroy() {
    this.alive = false;
  }
}
```

### takeUntil ⭐️

[`takeUntil()`](https://www.learnrxjs.io/operators/filtering/takeuntil.html) 은 인자로 넘겨준 옵저버블이 값을 방출하거나 종료할 경우 구독을 종료합니다.

```ts
export class MyComponent implements OnInit {
  termintaor$: Subject<void> = new Subject<void>();

  ngOnInit() {
    this.dataService.getData()
      .pipe(
        takeUntil(this.termintaor$)
      )
      .subsribe( ... )
  }

  ngOnDestroy() {
    this.termintaor$.next(); // 방출
    this.termintaor$.unsubscribe(); // 구독해제
  }
}
```

#### `takeUntil` vs `takeWhile`

`takeUntil` 은 전달받은 옵저버블이 데이터를 방출할 때 원본 옵저버블이 즉시 구독이 해지됩니다. 비슷하게 `takeWhile` 은 전달받은 `boolean` 값이 false 일 때 구독을 취소하게됩니다.

`takeWhile` 을 사용하여 구독을 취소할 때의 코드를 먼저 보면 다음과 같습니다.

```ts
ngOnInit() {
  this.dataService.getData()
    .pipe(takeWhile(() => this.alive))
    .subscribe((data) => {
      console.log(data);
    });
}

ngOnDestroy() {
  this.alive = false;
}
```
destroy 에서 alive 값을 false로 바꾸면 subscribe의 `next()` 콜백함수에서는 마지막 값을 전달받지 못하지만, 데이터를 방출하는 옵저버블은 그 다음 값을 방출합니다.  위의 코드를 아래 number 를 1초마다 방출하고 3일 때 구독을 해제하는 옵저버블로 예를들면

```
Observable
[  1, 2, 3, 4  ]

   1. 1초뒤 : 1 로그 찍힘
   2. 1초뒤 : 2 로그 찍힘
   3. 1초뒤 : 3 로그 찍힘
   4. 3이 돼서 구독 취소
   5. 4 값이 방출 됨 --- 방출이 중요
   6. 구독이 취소되어 4데이터를 받을 수 없다.
```

어쨌든 마지막 값이 방출된다는게 중요합니다. 즉시 구독이 해제되어 `next()` 를 호출하지않는 `takeUntil` 과는 달리 부가적인 메모리 누수가 발생할 여지가 있습니다. [참고 코드](https://stackblitz.com/edit/angular-takeuntil-v-takewhile) 를 실행해보면 더 와닿을 수 있습니다.

### [ngx-take-until-destroy](https://github.com/NetanelBasal/ngx-take-until-destroy)

외부 모듈인데, 구독을 해제하는 새로운 방법입니다. 보통 `takeUntil` 을 사용해 컴포넌트가 `ngOnDestroy` 될 때 구독을 해제하는 패턴을 사용하는데 해당 모듈은 `untilDestroyed` 를 사용하여 `this` 를 넘겨줍니다. `ngOnDestroy` 에서 별도로 관리할 필요가 없어집니다.

```ts
ngOnInit() {
  interval(1000)
    .pipe(untilDestroyed(this))
    .subscribe(val => console.log(val));
}
```


## 정리

* async Pipe ⭐️
* take ⭐️
* takeWhile 👎
* takeUntil ⭐️
* ngx-take-until-destroy ⭐️


## 참고문서
* [The Ultimate Answer To The Very Common Angular Question: subscribe() vs | async Pipe - Tomas Trajan](https://blog.angularindepth.com/angular-question-rxjs-subscribe-vs-async-pipe-in-component-templates-c956c8c0c794)
* [RxJS 구독을 취소하는 여러가지 방법 - Yohan Kim](https://ddalpange.github.io/2018/11/21/how-to-unsubscibe-in-rxjs/)
* [Angular: Don't forget to unsubscribe()](https://brianflove.com/2016/12/11/anguar-2-unsubscribe-observables/)
