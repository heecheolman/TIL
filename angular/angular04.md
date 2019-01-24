<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 데이터 바인딩

웹앱을 구축할 때 뷰와 모델의 분리가 필수인데 데이터바인딩을 통해 뷰와 모델을 '연결' 시켜줍니다.
앵귤러는 7가지의 데이터 바인딩을 제공하는데 바인딩의 흐름을 알아보고 또 종류별로 알아보도록 하겠습니다.

## 📝 목차

* [데이터 바인딩이란?](#데이터-바인딩이란)
* [바인딩 종류](#바인딩-종류)
  * [인터폴레이션](#인터폴레이션)
  * [프로퍼티 바인딩](#프로퍼티-바인딩)
  * [어트리뷰트 바인딩](#어트리뷰트-바인딩)
  * [클래스 바인딩](#클래스-바인딩)
  * [스타일 바인딩](#스타일-바인딩)
  * [이벤트 바인딩](#이벤트-바인딩)
  * [양방향 데이터 바인딩](#양방향-데이터-바인딩)
* [참고문서](#참고문서)


## 데이터 바인딩이란?
앵귤러에서는 템플릿과 컴포넌트 클래스가 분리되어있는데 템플릿의 데이터와 컴포넌트 클래스가 갖고 있는 데이터를 묶어 일치시켜줍니다. 이것을 데이터 바인딩이라하는데 앵귤러는 '단방향 바인딩'과 '양방향 바인딩'을 모두 지원합니다.

## 바인딩 종류
앵귤러에서는 7가지의 데이터바인딩이 존재합니다. 하나하나 알아보도록 하겠습니다.

### 인터폴레이션
사용법은 다음과 같습니다.
```html
{{ expression }}
```

`{{}}` 로 감싸져 있는 부분이 평가되어 반환된 값이 문자열로 대체됩니다.

### 프로퍼티 바인딩
컴포넌트 클래스의 프로퍼티와 템플릿 간의 단방향 바인딩에 사용되는 템플릿 문법으로 표현식의 표현 결과를 DOM 프로퍼티에 바인딩합니다.

```html
<element [property]="expression"></element>
```

#### 프로퍼티 vs HTML 어트리뷰트
두개는 다른것입니다. 프로퍼티는 DOM 노드 객체가 갖는 속성이고 HTML 어트리뷰트는 HTML 요소가 갖는 어트리뷰트(속성)입니다. 때문에 어트리뷰트는 HTML 문서에 존재하여 값이 변하지 않습니다. 하지만 프로퍼티는 동적으로 변합니다.

#### 인터폴레이션 다시보기
```html
<p>{{ expression }}</p>
```
위의 인터폴레이션은 사실 뷰를 렌더링 하기전에 프로퍼티로 변환합니다. 다음 코드와 같습니다.

```HTML
<p [innerHTML]="expression"></p>
```

## 어트리뷰트 바인딩
```html
<element [attr.attribute-name]="expression"></element>
```
HTML 의 속성으로 바인딩됩니다.

## 클래스 바인딩
클래스 바인딩을 사용해 HTML 의 class 어트리뷰트에 클래스를 첨삭할 수 있습니다.
```html
<element [class.class-name]="booleanExpression"></element>

<element [class]="class-name-list"></element>
```

위의 코드는 하나의 클래스인 단항, 아래코드는 여러 클래스인 다항입니다.

```html
<div class="foo bar" [class.error]="isError"></div>
<div [class]="classList"></div>
```
```css
.error { ... }
```
```ts
// ...
export class AppComponent {
  isError = true;
  classList = 'yellow-bg color-blue';
}
```

위의 코드는 `isError` 가 참일경우 `.error` 클래스가 바인딩되고 그렇지 않을 경우에는 바인딩되지 않습니다. 여러 클래스를 바인딩하고 싶을경우에는 문자열로 적되 공백으로 구분지어줍니다.

## 스타일 바인딩
스타일 바인딩을통해 HTML 의 style 어트리뷰트에 스타일을 지정해줍니다.
```HTML
<element [style.style-property]="expression"></element>
```
단위를 지정해주고싶을 때는 css 프로퍼티에 단위를 추가해줍니다.
```html
<div [style.background-color]="'white'" [style.font-size.px]="'16'"></div>
```

## 이벤트 바인딩
이벤트 바인딩은 이벤트가 발생하면 이벤트 핸들러를 호출하는것입니다. 지금까지 알아본 바인딩은 `컴포넌트클래스 -> 템플릿` 으로 데이터가 이동했지만 이벤트 바인딩은 `템플릿 -> 컴포넌트 클래스` 로 데이터가 이동합니다.

```html
<input type="text" [value]="name" (input)="setName($event)">
```
```ts
// 생략
export class HelloWorldComponent implements OnInit {
  name: string;

  constructor() {
    this.name = '';
  }

  ngOnInit() {
  }

  setName(event) {
    console.log(event);
    this.name = event.target.value;
    console.log(this.name);
  }
}
```

`input` 이벤트가 발생하면 `setName` 을 호출하게 되는데 이때 이벤트객체 `$event` 를 전달합니다. 그리고 `setName` 에서 이벤트 객체를 받아 처리를합니다.

## 양방향 데이터 바인딩
```html
<element [(ngModel)]="property"></element>
```

`[(ngModel)]` 디렉티브를 사용하기위해서는 `FormsModule` 을 `src/app/app.module.ts` 에 추가해줘야합니다.

```ts
// src/app/app/module.ts

// 생략
import { FormsModule } from '@angular/forms'; // 임포트

@NgModule({
  imports: [...,FormsModule] // FormsModule 추가
})
```

양방향 바인딩은 단방향과 다르게 **뷰가 변화하면 컴포넌트 클래스의 상태도 변하고, 컴포넌트 클래스의 상태가 변하면 뷰도 변화하는것** 입니다.

```html
<input type="text" [(ngModel)]="name">
```

```ts
export class AppComponent {
  name = '';
}
```
input 요소의 `value` 가 변하면 컴포넌트 클래스의 `name` 도 변하고 반대로 `name` 이 변해도 input 의 `value` 도 변합니다.

#### 양방향의 다른표현
사실 앵귤러는 양방향 바인딩을 지원하지않는다고 합니다. 위의 `[(ngModel)]` 을 풀어서 쓴다면 다음과 같습니다.
```html
<input type="text" [(ngModel)]="name">
<input type="text" [value]="name" (input)="name=$event.target.value">
```

#### ngModelChange
```html
<input [ngModel]="name" (ngModelChange)="name=$event">
```
프로퍼티 바인딩인 `[ngModel]` 은 사용자 입력에 관련된 DOM 요소의 프로퍼티를 업데이트하고, 이벤트바인딩인 `(ngModelChange)`는 이벤트를 수신하고 이벤트 핸들러를 통해 DOM 변화를 외부에 알립니다.

`(ngModelChange)` 는 `$event` 에서 사용자 입력에 관련된 프로퍼티의 값(여기서는 target.value) 을 내부적으로 추출해 `emit` 합니다.

## 참고문서
* [데이터 바인딩 - PoiemaWeb](https://poiemaweb.com/angular-component-data-binding)
