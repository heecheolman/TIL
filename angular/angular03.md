<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 컴포넌트 - 작성, 호출, 등록
컴포넌트 기반 프레임워크인 앵귤러에서 컴포넌트 작성은 가장 기본이 됩니다. 여기서는 컴포넌트를 작성, 호출, 등록 방법을 알아보겠습니다.

## 📝 목차
* [네이밍 컨벤션](#네이밍-컨벤션)
* [컴포넌트 클래스](#컴포넌트-클래스)
* [@Component 데코레이터](#component-데코레이터)
* [메타데이터](#메타데이터)
* [컴포넌트 작성](#컴포넌트-작성)
* [컴포넌트 호출](#컴포넌트-호출)
* [컴포넌트 등록](#컴포넌트-등록)

## 네이밍 컨벤션
컴포넌트를 작성하는데 있어서 일관성있는 네이밍이 중요한데 Angular 에서 권장하는 네이밍 패턴은 다음과 같습니다.
```
기능을 명확히 설명하는 구성요소이름.구성요소타입.ts
```
예를들어 유저를 등록하는 버튼 이라면 다음과 같을 것입니다.
```
user-add-button.component.ts
```

이 때, 단어와 단어사이는 하이픈(-) 으로 구분하는데 이것을 케밥표기법(kebab-case) 라고 합니다.

## 컴포넌트 클래스
Angular 프로젝트에서 컴포넌트를 작성하려하면 경로는 보통 `src/app/` 내에 만들어질텐데 컴포넌트 별로 폴더를 묶습니다.  
컴포넌트 클래스를 정의하는 네이밍컨벤션은 카멜표기법(camelCase) 를 기반으로 합니다.

HelloWorld 컴포넌트를 정의한다면 다음과 같이 합니다.
```ts
// src/app/hello-world/hello-world.component.ts

export class HelloWorldComponent {}
```

## `@Component` 데코레이터
위의 컴포넌트 클래스를 만들었다면 단지 일반적인 클래스에 불과한데 이것을 컴포넌트화 합니다. `@Component` 데코레이터를 이용하여 컴포넌트화를 하게되는데 이 데코레이터는 `@angular/core`라는 Angular 라이브러리에 존재하므로 `import` 가 필요합니다. 이전에 사용했던 예제에 추가합니다.
```ts
// src/app/hello-world/hello-world.component.ts
import { Component } from '@angular/core'; // import

@Component()
export class HelloWorldComponent {}
```
`@Component` 라는 데코레이터를 통해 아래에 위치한 클래스가 일반 클래스가 아닌 컴포넌트임을 알려줍니다.

> 데코레이터는 함수로서 런타임에 호출되며 데코레이팅된 클래스의 생성자를 변경할수 있습니다.

## 메타데이터
데코레이터는 함수라고 하였는데 아래 위치한 일반 클래스를 컴포넌트화 할 때 이러한 받아지는 인자(메타데이터) 를 컴포넌트 클래스에 반영합니다. 그 중에 중요한 세가지 프로퍼티를 알아보겠습니다.

#### `selector`
selector 는 해당 컴포넌트에 대한 표현(뷰) 를 마크업할 때 사용하는 이름입니다. html 태그처럼 사용하고 케밥표기법을 사용합니다.

```ts
// 생략
@Component({
  selector: 'app-hello-world',
})
```
그리고 마크업에서는 다음과 같이 사용합니다.
```html
<app-hello-world></app-hello-world>
```


#### `template` or `templateUrl`
화면을 구성하는 템플릿입니다. `selector` 에서 `<app-hello-world>` 로 사용하라고 하였지만 사실상 표현되는게 없습니다. 때문에 이러한 뷰를 정해주는 프로퍼티입니다.

`template` 과 `templateUrl` 의 차이는 전자는 인라인방식이고 후자는 외부파일입니다.

```ts
// 생략
@Component({
  selector: 'app-hello-world',
  // template: `<div></div>`;
  templateUrl: './hello-world.component.html',
})
```
여기서는 외부파일을 불러들이는 방식을 사용합니다.
> 인라인 템플릿은 백틱(\`\`)으로 템플릿을 묶어줍니다.


`hello-world.component.html`
```html
<div>
  <h1>{{ message }}</h1>
</div>
```

#### `styles` or `styleUrls`
구조를 잡는 템플릿을 만들었다면 옷을 입히는 스타일입니다. 템플릿과 동일하게 `styles` 는 인라인 스타일, `styleUrls` 는 외부파일입니다. 다른점이 있다면 문자열배열이라는 점입니다.

```ts
// 생략
@Component({
  selector: 'app-hello-world',
  // template: `<div></div>`;
  templateUrl: './hello-world.component.html',
  styleUrls: ['./hello-world.component.scss'],
})
```
여기서는 scss 를 사용합니다.

`hello-world.component.scss`
```scss
h1 {
  color: blue;
}
```

## 컴포넌트 작성
데코레이터까지 완료했다면 완성된 코드들을 살펴봅니다. 먼저 폴더구조는 다음과 같습니다.
```
src/
└─ hello-world/
    ├── hello-world.component.css
    ├── hello-world.component.html
    ├── hello-world.component.spec.ts
    ├── hello-world.component.ts
    └── hello-world.module.ts
```

`angular cli` 를 통해 쉽게 만들고 싶다면 다음과 같이 입력합니다.
```bash
$ ng generate component hello-world

# 축약형
$ ng g c hello-world
```
---
#### 완성된 파일 정리
`hello-world.component.html`
```html
<div>
  <h1>{{ message }}</h1>
</div>
```

`hello-world.component.scss`
```scss
h1 {
  color: blue;
}
```
`hello-world.component.ts`
```ts
// src/app/hello-world/hello-world.component.ts
import { Component } from '@angular/core'; // import

@Component({
  selector: 'app-hello-world',
  templateUrl: './hello-world.component.html',
  styleUrls: ['./hello-world.component.scss'],
})

export class HelloWorldComponent {
  message = 'HelloWorld';
}
```


## 컴포넌트 호출
그리고 이것을 다른 컴포넌트에서 다음과 같이 호출합니다.
```html
<app-hello-world></app-hello-world>
```

## 컴포넌트 등록
이렇게 모듈을 완성했다면 `app.module.ts` 에 모듈을 등록해줘야 합니다.

```ts
// src/app.module.ts
import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppComponent } from './app.component';
import { HelloWorldComponent } from './hello-world/hello-world.component'; // import

@NgModule({
  declarations: [
    AppComponent,
    HelloWorldComponent, // 등록
  ],
  imports: [
    BrowserModule,
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
```

## 참고문헌
* [컴포넌트 소개와 기본구조 - PoiemaWeb](https://poiemaweb.com/angular-component-basics)
