# `@HostListener` 와 `@HostBinding`

`@HostListener` 와 `@HostBinding`은 앵귤러에서 빌트인 디렉티브 이외에 커스텀 디렉티브를 만들 때 사용되는 데코레이터다. 이름을 보고 추측하자면 `@HostListener` 는 이벤트를 수신하는 느낌이고, `@HostBinding` 은 어떠한 '것'을 바인딩해주는 느낌이다.

## `@HostListener`
첫 번째 파라미터로는 이벤트 이름을 문자열로 받고, 두 번째 파라미터로는 이벤트가 발생될 때 발생하는 파라미터들을 받는다. 둘 다 옵셔널하다.

```ts
export interface HostListener {
  /**
   * The CSS event to listen for.
   */
  eventName?: string;
  /**
   * A set of arguments to pass to the handler method when the event occurs.
   */
  args?: string[];
}
```

간단한 사용법

```ts
import { ..., HostListener } from '@angular/core';

@Component({...})
export class SomeComponent  {
  @HostListener('keydown', ['$event.target'])
  onKeyDown(target) {
    ...
  }
}

```


## `@HostBinding`

이 데코레이터를 사용하면 DOM 속성을 동적으로 설정할 수 있다. 앵귤러는 자동적으로 변화를 감지해 업데이트 시킨다. 첫 번째 파라미터로 속성값을 받는다.

```ts
export const HostBinding: HostBindingDecorator =
    makePropDecorator('HostBinding', (hostPropertyName?: string) => ({hostPropertyName}));
```
```ts
export interface HostBinding {
  /**
   * The DOM property that is bound to a data property.
   */
  hostPropertyName?: string;
}
```

간단한 사용법
```ts
import { ..., HostBinding } from '@angular/core';

@Component({...})
export class SomeComponent  {
  // style 속성의 color
  @HostBinding('style.color') color: string;
  @HostListener('click')
  setColor() {
    this.color = 'red';
  }
}
```

## 참고문서

* [Using @HostBinding and @HostListener in Custom Angular Directives - alligator.io](https://alligator.io/angular/hostbinding-hostlistener/)
* [@HostListener - Angular 공식문서](https://angular.io/api/core/HostListener)
* [@HostBinding - Angular 공식문서](https://angular.io/api/core/HostBinding)
