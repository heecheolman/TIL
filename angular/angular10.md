<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 파이프
앵귤러의 파이프에 대해서 살펴보겠습니다.

## 📝 목차
* [파이프란?](#파이프란)
  * [파이프 사용법](#파이프-사용법)
* [빌트인 파이프](#빌트인-파이프)
* [체이닝 파이프](#체이닝-파이프)
* [커스텀 파이프](#커스텀-파이프)
* [파이프와 변화감지](#파이프와-변화감지)
* [순수 파이프와 비순수 파이프](#순수-파이프와-비순수-파이프)

## 파이프란?
데이터형식중에서는 익숙한 형태가 아닐 수 있습니다. 때문에 익숙한 형태로 바꾸어 보여주는것이 편합니다. 하지만 그 데이터 자체를 변형시켜서 보여주기에는 side effect 가 발생할 수 있으므로 **화면에 표시되는 형식만 변경하고 싶을 때 사용하는 것이** 파이프입니다.

### 파이프 사용법
```html
<!-- 기본사용법 -->
{{ value | PipeName }}

<!-- 옵션지정 -->
{{ value | PipeName : Option : OptionValue }}

<!-- 체이닝 -->
{{ value | PipeName1 | PipeName2 }}
```

예를들어 디버깅할 때 많이 쓰는 `json` 형식으로 변경시켜주는 파이프를 실행해봅니다.

```html
{{ data | json }}
```

## 빌트인 퍄이프
앵귤러 자체에 포함되어 있는 빌트인 파이프가 있습니다.

| 파이프 | 의미 |
|:---:|:---:|
|date|날짜 형식 변환|
|json| json 형식 변환|
|uppercase | 대문자 변환|
| lowercase | 소문자 변환|
| currency | 통화형식 변환|
| precent | 퍼센트형식 변환|
| decimal | 자리수 형식 변환|
| slice | 문자열 추출|
| async | 비동기 객체 출력 |

## 체이닝 파이프
파이프 여러개를 조합해 결과를 출력해내는 것을 '체이닝 파이프'라 합니다.
```html
{{ url | slice: 4 | json }}
```
`url` 를 4번째 문자부터 끝까지 잘라낸 후 json 형식으로 바꾸어 표현하는 체이닝 파이프입니다.

## 커스텀 파이프
때로는 개발자가 직접 만들어야 할 때도 있을것입니다. 커스텀파이프를 만들어보겠습니다.

```ts
// mypipe.pipe.ts

import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'mypipe',
})
export class Mypipe implements PipeTransform {
  transform(value: any, args?: any): any {
    return null;
  }
}
```
파이프의 이름은 `mypipe` 이며 `PipeTransform` 인터페이스의 추상메서드인 `transform()` 을 구현해야합니다. `value` 는 변환 대상인 값, `args`는 옵션입니다. 그리고 이렇게 만들어 놓은 커스텀 파이프는 모듈의 `declarations` 에 등록해야합니다.
```ts
// app.module.ts
// ...생략
@NgModule({
  declarations: [
    Mypipe, // 추가
  ],
  //...
})
```

위의 작업은 `angular-cli` 를 통해 한번에 할 수 있습니다.
```bash
# 커스텀파이프 생성
$ ng generate pipe mypipe

# 축약형
$ ng g p mypipe
```

사용법도 빌트인과 동일합니다.
```html
{{ data | mypipe }}
```

## 파이프와 변화감지
뷰와 모델의 동기화를 유지하기 위해 상태 변화를 감지하고 그것을 반영하는것을 '변화감지'라고 합니다.


```ts
// ...생략
todos: Todo[] = [
 { ... },
 { ... },
 { ... },
]
add(content: string) {
  this.todos.push( {...} );
}
```
간단한 todo 앱에서 리스트를 추가하는 `add()`함수를 보면 `push`를 통해 `todo` 를 추가시키고 있습니다.  
그리고 템플릿은 다움과 같을것 입니다.
```HTML
<li *ngFor="let todo of (todos | mypipe)"
></li>
```

하지만 add 를 하여도 추가되지 않습니다. 그 이유는 배열 원본 자체에 추가되어 배열의 참조는 변경되지 않기 때문인데 다음과같이 코드를 고치면 정상적으로 추가되는것을 확인할 수 있습니다.

```ts
// 생략


add(content: string) {
  // this.todos.push( {...} );  --> 제거
  this.todo = [...this.todos, { ... }] // 추가
}
```
`스프레드연산(...)` 을 통해 `todos` 를 넣고 마지막에 todo 를 추가합니다.

이렇게되면 해결이되지만 단점이있습니다. 복잡한 웹 애플리케이션의 경우 `todos` 프로퍼티가 어디서 변경되는지 파악하기 힘들 수 있습니다. 때문에 **비순수 파이프(impure pipe)** 를 앵귤러는 제공합니다.

## 순수 파이프와 비순수 파이프
파이프는 비순수 파이프와 순수 파이프로 나눌 수 있는데 비순수 파이프는 `@Pipe` 데코레이터의 메타데이터 객체의 `pure` 프로퍼티에 `false` 를 지정해주면 됩니다.

```ts
// ...
@Pipe({
  name: 'pipename',
  pure: fase,
})
// ...
```

이렇게 되면 아까와 같은 todo 앱에서 `push()` 메서드를 사용하더라도 변화에 감지가 되어 반영이 되지만 퍼포먼스 측면에서 좋지 않으므로 주의해야합니다.

순수 파이프는 순수한 변경만(참조)을 감지해 파이프를 실행합니다. 그 이유는 앵귤러는 퍼포먼스를 위해 객체 내부의 변경은 무시해 순수 파이프를 실행하지 않기 때문입니다.

## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
