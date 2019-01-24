<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular LifeCycle
컴포넌트와 디렉티브는 생명주기를 갖습니다. 즉 컴포넌트와 디렉티브가 생성하고 소멸되기까지의 과정들을 말하고 Angular에 의해 관리됩니다. 이 장에서는 앵귤러가 관리하는 생명주기에 대해 알아보고 각 라이프사이클별로 어떤역할을 하는지 알아보겠습니다.

## 📝 목차
* [LifeCycle 이란?](#lifecycle-이란)
* [메서드 훅](#메서드-훅)
  * [`ngOnChanges`](#ngonchanges)
  * [`ngOnInit`](#ngoninit)
  * [`ngDoCheck`](#ngdocheck)
  * [`ngAfterContentInit`](#ngaftercontentinit)
  * [`ngAfterContentChecked`](#ngaftercontentchecked)
  * [`ngAfterViewInit`](#ngafterviewinit)
  * [`ngAfterViewChecked`](#ngAfterViewChecked)
  * [`ngOnDestroy`](#ngondestroy)
* 디렉티브 라이프사이클

## LifeCycle 이란?
생명주기(LifeCycle) 이란 컴포넌트 기반 프레임워크 및 라이브러리에서 컴포넌트가 생성하고 소멸되기까지의 과정들을 거치는데 이러한 `생성 -> 소멸` 까지의 과정을 생명주기라합니다.

앵귤러는 컴포넌트와 디렉티브가 생명주기를 갖으며 각 단계에 필요한 행위를 처리해야하는 훅 메서드를 구현함으로 각 단계에 필요한 행위들을 처리할 수 있습니다.

## 메서드 훅
앵귤러는 각 단계별로 메서드 훅을 갖습니다. 이 메서드 훅은 인터페이스 형태로 제공되므로 필요한 메서드 훅(인터페이스)가 있다면 `implements` 를 통해 반드시 구현해야합니다.

*예시*
```ts
import { Component, OnInit } from '@angular/core';
// ...
export class MyComponent implements OnInit {
  // ...
  ngOnInit() {
    // ngOnInit 구현
  }
}
```
이 이후에 소개되는 라이프사이클 훅들이 어느시점에 호출되는지 알아보겠습니다.

### `ngOnChanges`
부모 컴포넌트에서 자식 컴포넌트의 입력 프로퍼티(`@Input`)로 바인딩한 값이 초기화 또는 변경되었을 때 실행됩니다. 입력 프로퍼티가 존재하는 경우 최소 1회 호출됩니다. 그리고 입력 프로퍼티가 변경될 때마다 호출되는데 변경은 **참조변경** 을 말합니다.

```ts
class MyComponent implements OnChanges {
  @Input prop: any;
  ...
  ngOnChanges(changes: SimpleChanges) {
    console.log(changes);
/*  changes {
      previousValue: 이전 값
      currentValue: 현재 값
    } */
  }
}
```

`previousValue` 에는 이전값이 들어있고 `currentValue` 에는 현재의 값이 들어있습니다.

### `ngOnInit`
입력 프로퍼티를 포함한 모든 프로퍼티의 초기화가 완료된 시점에 한번만 호출됩니다. 앵귤러에서는 `constructor` 가 아닌 `ngOnInit` 에서 프로퍼티를 초기화하는것이 좋습니다. `constructor` 에서는 앵귤러가 관리하는 입력 프로퍼티가 초기화되지않아 `undefined` 상태를 갖기 때문입니다. 반면에 `ngOnInit` 은 입력 프로퍼티에 대한 참조가 보장됩니다.

```ts
// ...
class MyComponent implements OnInit {
  @Input() prop;

  constructor() {
    console.log(this.prop); // undefined;
  }

  ngOnInit() {
    console.log(this.prop); // myProp;
  }
}
```
### `ngDoCheck`
컴포넌트 또는 디렉티브의 모든 상태 변화가 발생할 때마다 호출됩니다. DOM 이벤트, Ajax 통신 등과 같은 비동기 처리가 수행될 때, 변화 감지 로직(`ngDoCheck()`)을 실행합니다. 하지만 모든 상태 변화가 발생할 때마다 호출되므로 성능문제를 야기할 수 있습니다.

#### `ngOnChanges` vs `ngDoCheck`
공통점이라면 둘다 상태변화에 감지한다는점입니다.
```ts
class MyChildComponent {
  @Input() prop1: string; // 'something string'
  @Input() prop2: object; // prop2 { foo: 1 }
}
```
위와같은 자식컴포넌트의 `@Input` 값으로 prop1 과 prop2 가 있습니다.

부모 컴포넌트에서 prop1 의 값을 **다른 string 으로 바꾼다면 `ngOnChanges` 는 반응합니다.** 그 이유는 입력 프로퍼티에 대해 기존 참조 값이 바뀌었기 때문입니다.

하지만 반대로 prop2의 foo 키의 값을 바꾸게된다면(예를들면 `prop2.foo = 5`) `ngOnChanges` 는 반응하지 않습니다. 그 이유는 프로퍼티 내부의 foo 에 대한 값은 변경되었지만 foo 라는 object 에 대한 참조값은 그대로 유지되기 때문입니다.


### `ngAfterContentInit`
컴포넌트의 뷰가 초기화되는 시점헤 호출되며, `ng-content` 디렉티브를 사용해 외부 콘텐츠를 컴포넌트의 뷰에 콘텐츠 프로젝션한 이후에 호출됩니다.

### `ngAfterContentChecked`
부모 컴포넌트가 전달한 부모 컴포넌트의 템플릿 조각을 체크한 후 호출됩니다. 뷰를 검사한 후에 실행됩니다.

### `ngAfterViewInit`
컴포넌트의 뷰와 자식 컴포넌트의 뷰를 초기화한 이후 호출됩니다. 뷰 안의 모든 디렉티브를 초기화한 후에 실행됩니다.

### `ngAfterViewChecked`
컴포넌트의 뷰와 자식 컴포넌트의 뷰를 체크한 이후 호출됩니다.

### `ngOnDestroy`
컴포넌트와 디렉티브가 소멸하기 이전 호출됩니다. 여기서 메모리누수를 처리합니다. 예를들어 Rxjs 의 `unsubscribe`가 있습니다.

## 디렉티브 라이프사이클
디렉티브도 컴포넌트와 별 다를건 없습니다. 다만 뷰(view)와 관련된 생명주기인 다음 4가지를 빼줍니다.

* AfterViewInit
* AfterViewChecked
* AfterContentInit
* AfterContentChecked

즉, 디렉티브의 라이프사이클은 다음과 같습니다.

* OnChanges
* DoCheck
* OnInit
* OnDestroy


## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
* [Angular 공식 사이트 - 라이프사이클  ](https://angular.kr/guide/lifecycle-hooks)
