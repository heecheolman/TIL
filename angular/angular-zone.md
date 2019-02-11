# Zone.js 와 변경감지

앵귤러에서 데이터 바인딩을 할 때 브라우저에서 뷰로 데이터를 전달할 때는 이벤트를 통해 전달하게 되므로 데이터가 변경됨을 알 수 있습니다. 하지만 반대로 데이터가 변경되었음을 알고 뷰에서 바뀌는 것은 자바스크립트 자체 기능에는 없는데 이것을 가능하게 해주는것이 `Zone.js` 입니다.

## [Zone.js](https://github.com/angular/zone.js)

`Zone.js` 의 원래 목적은 **여러가지의 비동기 실행을 하나의 컨텍스트로 다룰 수 있도록 하는데 있다고합니다.**  

### 브라우저의 에러 스택 트레이스

브라우저는 에러의 스택 트레이스(Stack Trace) 를 해당 에러까지만 보여주지만 해당 에러가 발생한 시점부터의 실질적인 실행 컨텍스트를 알고 싶다면 `Zone.js` 를 사용합니다.

### zone

`Zone.js` 는 브라우저의 Native API 에 대해 몽키패치하여 호출되는 모든 Native API 를 추적해 비동기 요청들을 하나의 컨텍스트로 묶어줍니다. 그리고 이런 컨텍스트를 'zone' 이라는 용어로 사용합니다.

> 몽키패치(Monkey Patch)란 런타임중인 프로그램 메모리의 소스 내용을 직접 바꾸는 것

### Angular 의 변경감지

Angular 는 zone.js 를 사용하여 감지합니다.

1. Angular는 애플리케이션 시작 시 zone.js 의 zone을 하나 만듦.
2. 해당 구역에서 애플리케이션을 구동
3. 해당 구역에서 호출되는 Native API 호출에 대해 통지를 받음
4. 통지가 왔을 때 변경 감지(Change Detection) 수행

## Angular 의 변경감지 관련 라이프사이클 메서드

Angular 는 변경감지 순회과정에서 컴포넌트에 대해 두가지 메서드를 호출합니다.

1. ngOnChanges
2. ngDoCheck

### ngOnChanges

```ts
interface OnChanges {
  ngOnChanges(changes: SimpleChanges): void;
}
```

ngOnChanges 는 `@Input` 데코레이터에 의해 정의된 멤버변수에 **새로운 값(혹은 새로운 레퍼런스)** 이 들어올 때마다 호출됩니다. 예를들어 객체 내의 또다른 객체 값이 변경될 경우에는 레퍼런스가 동일하기 때문에 변경감지가 되지 않습니다.

#### SimpleChanges

SimpleChanges 는 key로 문자열을 value로 SimpleChange 를 객체로 담는 맵입니다.

```ts
interface SimpleChanges {
    [propName: string]: SimpleChange;
}
```

#### SimpleChange

SimpleChange 는 다음과 같은 클래스로 생성된 객체입니다.

```ts
class SimpleChange {
    previousValue: any;
    currentValue: any;
    firstChange: boolean;
    constructor(previousValue: any, currentValue: any, firstChange: boolean);
    isFirstChange(): boolean;
}
```

* previousValue: 변경되기 이전 값
* currentValue: 변경된 후 값
* firstChange: 처음 바뀌었는지 여부
* isFirstChange: 처음 바뀌었는지 여부(메서드)


### ngDoCheck
```ts
interface DoCheck {
  ngDoCheck(): void;
}
```
ngDoCheck 는 변경감지 프로세스가 진행될 때마다 호출됩니다. 객체 내의 또다른 객체 데이터가 변경되었을 경우 ngOnChanges 는 감지할 수 없지만 ngDoCheck 는 감지할 수 있습니다.

#### 주의사항
변경될 때마다 매번 호출되기 때문에 애플리케이션의 성능이 낮아질 수 있어 ngDoCheck 는 정말 가볍게 써야한다고 합니다.


## Zone.js 밖에서의 이벤트 수신

Zone.js 를 피해서 이벤트를 수신하고 싶은 경우에는 **NgZone** 이라는 서비스 객체를 사용합니다.

```ts
import { Component, NgZone } from '@anular/core';

@Component({
  ...
})
export class MyComponent {
  constructor(private zone: NgZone) {}
}
```

### NgZone 메서드
NgZone 멤버로 다음 세가지의 메서드가 있습니다.
```ts
run(fn: () => any): any
runGuarded(fn: () => any): any
runOutsideAngular(fn: () => any): any
```

runOutsideAngular() 는 앵귤러의 Zone 외부에서 실행되어 데이터가 변경되어도 변경을 감지할 수 없는 상태가 됩니다.

runOutsideAngular() 로 실행한 데이터 변경을 다시 감지하고싶을 때 호출하는 메서드는 run() 과 runGuarded() 입니다. 차이점이라면, run() 은 실행되는 함수가 에러를 발생시키면 run() 호출의 에러로 다시 던지고, runGuarded() 는 발생한 에러를 NgZone.onError 이벤트로 전달합니다.


## 되짚어보기

echarts 를 적용시키면서 option 값을 변경하였는데 왜 감지가 안될까하며 헤맨적이 있었는데 위의 내용들을 공부하다보니 OnChanges 는 레퍼런스가 변경이 되어야 감지를 한다는것을 알았습니다.

`@Input options: EChartOption` options 의 내부 데이터를 변경하더라도 레퍼런스는 그대로이기에 감지를 할 수 없었던 것이었습니다.

```ts
export class NgxEchartsDirective implements OnChanges, OnDestroy, OnInit, DoCheck, AfterViewInit {
  @Input() options: EChartOption;
  //...
}
```

## 참고문서
* [제대로 배우는 Angular4 - 조주민](http://www.yes24.com/24/goods/42497045)
