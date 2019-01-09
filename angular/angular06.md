<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 컴포넌트 상태 공유
앵귤러 컴포넌트를 중심으로 웹앱이 만들어집니다. 때문에 컴포넌트는 재사용성이 높게끔 작성하는것이 좋습니다. 다시말해, 다른 컴포넌트와의 결합도를 낮게 유지하면서 상태 정보를 교환할 수 있어야합니다.


## 📝 목차
* [계층적 트리구조](#계층적-트리구조)
* [부모컴포넌트에서 자식컴포넌트](#부모컴포넌트에서-자식컴포넌트)
  * [`@Input` 데코레이터 이용](#input-데코레이터-이용)
  * [`@Input` 데코레이터와 setter](#input-데코레이터와-setter)
* [자식컴포넌트에서 부모컴포넌트](#자식컴포넌트에서-부모컴포넌트)
  * [`@Output` 데코레이터와 EventEmitter](#output-데코레이터와-eventemitter)
  * [getter, setter 를 이용해 양방향 바인딩으로 바꾸기](#getter-setter-를-이용해-양방향-바인딩으로-바꾸기)
* [Stateful 컴포넌트와 Stateless 컴포넌트](#stateful-컴포넌트와-stateless-컴포넌트)

## 계층적 트리구조
분할된 컴포넌트를 조립하다보면 자연스레 계층적인 구조가 형성되는데 이를 '부모-자식 관계로 표현된다' 라고 합니다. 이로인해 부모-자식 관계에서 데이터를 주고받는일이 많아지게 됩니다.

* 부모컴포넌트에서 자식컴포넌트로 상태 전달
* 자식컴포넌트에서 부모컴포넌트로 상태 전달



## 부모컴포넌트에서 자식컴포넌트
여기서는 부모컴포넌트에서 자식컴포넌트로 상태를 전달하는 다양한 방법을 알아보겠습니다.

구조는 다음과 같습니다.
```
Parent Component
      |
      |
      |
 Child Component
```

### `@Input` 데코레이터 이용
부모 컴포넌트에서 프로퍼티 바인딩을 통해 자식 컴포넌트로 상태를 전달하게되는데 그 상태정보를 `@Input` 데코레이터를 통해 바인딩합니다.

```html
<!-- 프로퍼티 바인딩 -->
<child [state]="myState"></child>
```
```ts
// 자식 컴포넌트
@Input() state: any;
```
1. `Parent Component` 에서 자식 컴포넌트를 마크업하고 전달할 `props` 를 `[]` 로 감싸 전달합니다.
2. 자식 컴포넌트에서는 받아질 `props` 를 `@Input` 데코레이터뒤에 선언합니다. (이때 부모에서 전달할 프로퍼티 이름과 자식에서 받아질 프로퍼티이름을 일치시켜야합니다.`state === state`)

### `@Input` 데코레이터와 setter
setter 와 getter 를 사용하게되면 데이터를 받는 시점에 필요한 로직을 동작시킬 수 있습니다.
```html
<!-- 프로퍼티 바인딩 -->
<child [state]="myState"></child>
```

```ts
// 자식 컴포넌트
_state: any;

@Input()
set state(param: any) {
  // ... something
  this._state = param;
}
get state() {
  return this._state;
}
```
setter 를 사용하게되면 데이터를 받는 중간단계에서 필요한 로직을 작성할 수 있어 유용한 면이 많은 것 같습니다.

## 자식컴포넌트에서 부모컴포넌트
반대로 자식컴포넌트에서 부모컴포넌트로 데이터를 전달하는 방법을 알아보겠습니다.

### `@Output` 데코레이터와 EventEmitter
`@Output` 데코레이터로 선언된 컴포넌트 프로퍼티를 EventEmitter 로 초기화한 후 `emit()` 메서드를 사용해 이벤트를 발생시켜 상태를 전달합니다.

다음 두 코드는 부모 컴포넌트에서 작성되어야합니다.
```html
<child (myEvent)="myEventHandler($event)"></child>
```
```ts
myEventHandler(state: any) {
  // do something with state
}
```

다음 두 코드는 자식 컴포넌트에서 작성되어야합니다.
```html
<button (click)="handleClick(state)">X</button>
```
```ts
@Output() myEvent = EventEmitter<string>();

handleClick(state) {
  // do something with state
  this.myEvent.emit(state);
}
```

1. 부모 컴포넌트에 전달(데이터 방출)을 위한 프로퍼티를 `@Output` 데코레이터에 작성
2. EventEmitter로 초기화
3. 이벤트가 발생할 때 `myEvent.emit()`을 통해 방출하는데 이 때 인자 전달.
4. 부모컴포넌트에서 `myEvent` 가 호출될 때 `myEventHandler($event)`를 호출
5. `myEventHandler` 에서 처리

### getter, setter 를 이용해 양방향 바인딩으로 바꾸기
부모 컴포넌트 코드
```HTML
<child [(state)]="parentState"></child>
```
```ts
// 생략
parentState: any;
```

자식 컴포넌트 코드
```html
<button (click)="handler()"></button>
```
```ts
private _state = '';

@Input()
get state() {
  return this._state;
}
set state(param: any) {
  this._state = param;
  this.stateChange.emit(this._state); // 부모 컴포넌트로 방출
}

@Output() stateChange = new EventEmitter();

handler() {
  // state change code
}
```

이제 `[()]` 문법을 사용하여 양방향 바인딩이 됩니다.

## Stateful 컴포넌트와 Stateless 컴포넌트
부모-자식 컴포넌트 간에 상태 공유가 일어나는것을 지금까지 확인했습니다.

양방향 바인딩을 통해 부모 컴포넌트의 상태가 변하면 자식 컴포넌트의 상태도 변하고, 자식컴포넌트의 상태가 변해도 부모컴포넌트의 상태가 변하는것도 확인했습니다. 둘 다 같은 프로퍼티에 대한 참조를 갖는데 자식 컴포넌트에서는 이벤트를 바인딩을 통해 상태변화를 일으켰습니다. 이렇게 번거롭게 한 이유는 웹 어플리케이션이 복잡해질수록 상태 정보의 변화를 예측하기 어렵기 때문입니다. 그래서 이벤트 바인딩을 통해 변경한 것입니다.

**Stateful 컴포넌트(Smart 컴포넌트)** : 상태 정보를 저장하고 변경할 수 있음 - 부모 컴포넌트  
**Stateless 컴포넌트(Dumb 컴포넌트)** : 상태 정보를 참조하여 출력, 직접변경하지 않음 - 자식 컴포넌트

결론적으로 이런 구조로 side effect 를 줄이고 디버깅을 쉽게합니다.

## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
