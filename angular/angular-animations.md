# Angular Animations

컴포넌트와 HTML 요소에 대해 애니메이션을 줄 수 있다. 애니메이션을 주어 좀 더 살아있는듯(?)한 웹 페이지를 만들어 낼 수 있다.

## 필요한 모듈 임포트하기

#### BrowserAnimationsModule

```ts
// app.module.ts
// ...
import { BrowserAnimationsModule } from '@angular/platform-browser/animations'

@NgModule({
  imports: [
    //...
    BrowserAnimationsModule,
  ]
})
export class AppModule {}
```

## [애니메이션 함수들](https://angular.io/guide/animations#animations-api-summary)

* trigger
* animate
* group
* sequence
* style
* state
* keyframes
* transition
* animation
* animateChild
* useAnimation
* query
* stagger

## fadePop 애니메이션 만들기

```ts
// foo.component.ts
const popAnimation = trigger('pop', [
  transition(':enter', [
    style({
      opacity: 0.6,
      transform: 'scale(0.8)',
    }),
    animate('200ms cubic-bezier(0.165, 0.84, 0.44, 1)', style({
      transform: 'scale(1)',
      opacity: 1,
    }))
  ]),
  transition(':leave', [
    style({
      opacity: 1,
    }),
    animate('50ms', style({
      opacity: 0,
    })),
  ])
]);

@Component({
  // ...
  template: '<div @pop>...</div>',
  animations: [popAnimation]
})
```
`@pop` 애니메이션을 사용할 엘리먼트에 지정을 해주면, 특정 이벤트가 발생할 때 애니메이션이 실행된다.

## 튜토리얼 보며 느낌 알기
```ts
trigger('openClose', [
  state('open', style({ ... })),
  state('closed', style({ ... })),
  transition('open => closed', [ ... ]),
  transition('closed => open', [ ... ]),
])
```
`openClose` 라는 애니메이션이며 `open`, `closed` 라는 두 가지 상태값을 갖는다. 그리고 `transition()` 의 첫번째 파라미터로 '어떠한 상태에서 어떠한 상태로 이동하는지' 에 대하여 기술해준다. 위의 경우에는 'open 상태에서 closed 상태', 'closed 상태에서 open상태' 로가는 트랜지션을 두개 갖는다.

#### 공통적용

open 에서 closed 로 진입 진출의 애니메이션이 같다면 `<=>` 를 사용하여 대체할 수 있다.

```ts
transition('open <=> closed', [ ... ])
```

## 상태값

1. void
2. wildcard(`*`)
3. custom

#### void state
DOM 에 배치하기 전이나 제거되는 상태이며 페이지 진입 진출 시 유용하다.  

```ts
trigger('flyInOut', [
  transition('void => *', [
    style({ transform: 'translateX(-100%)' }),
    animate(100)
  ]),
  transition('* => void', [
    animate(100, style({ transform: 'translateX(100%)' }))
  ])
])
```

렌더링될 때 왼쪽에서 오른쪽으로, 렌더링 해제될 때 다시 오른쪽으로 이동하게된다.

```
DOM 배치 전 | 현재 화면 | DOM 제거
    void  =>   *
               *    =>  void
```

진입진출은 많이 써 앵귤러에서 별칭(alias)을 제공한다.

```ts
transition(':enter', [ ... ]) // void => *    ===  :enter
transition(':leave', [ ... ]) // * => void    ===  :leave
```

#### wildcard

앵귤러 애니메이션에는 wildcard 라는 것이 있는데, 아무 상태를 나타낸다. 다음을 보면 좀 더 이해가 빠르다.

![이미지](https://angular.io/generated/images/guide/animations/wildcard-state-500.png)

* **`open => closed`**: open 에서 closed 로 갈 때
* **`open => *`**: open 에서 아무 상태로 갈 때
* **`* => closed`**: 아무 상태에서 closed 로 갈 때
* **`* => *`**: 아무상태에서 아무상태로 갈 때


## 참고문서
* [앵귤러 공식문서-애니메이션](https://angular.io/guide/animations)
* [How to use animation with Angular 6 - Ankit Sharma](https://medium.freecodecamp.org/how-to-use-animation-with-angular-6-675b19bc3496)
