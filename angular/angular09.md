<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 디렉티브
디렉티브(Directive) 는 DOM 의 모양이나 동작 등의 모든것을 관리하기 위한 명령입니다. 이 섹션에서는 디렉티브에 대해 자세히 살펴보겠습니다.

## 📝 목차
* [디렉티브란?](#디렉티브란)
* [디렉티브의 종류](#디렉티브의-종류)
  * [컴포넌트 디렉티브](#컴포넌트-디렉티브)
  * [어트리뷰트 디렉티브](#어트리뷰트-디렉티브)
  * [구조 디렉티브](#구조-디렉티브)
* [사용자 정의 어트리뷰트 디렉티브](#사용자-정의-어트리뷰트-디렉티브)
  * [어트리뷰트 생성](#어트리뷰트-생성)
  * [이벤트 처리](#이벤트-처리)
  * [`@Input` 데이터 바인딩](#input-데이터-바인딩)
* [사용자 정의 구조 디렉티브](#사용자-정의-구조-디렉티브)
  * [구조 생성](#구조-생성)
  * [`ng-template` 디렉티브](#ngtemplate-디렉티브)
  * [`TemplateRef`와 `ViewContainerRef`](#templateref와-viewcontainerref)
  * [`ng-container` 디렉티브](#ngcontainer-디렉티브)

## 디렉티브란?
앞서 말했듯이 지시입니다. 디렉티브는 웹애플리케이션 전역에서 사용할 수 있는것을 컴포넌트에서 분리해 구현합니다. 이로 인해 컴포넌트의 복잡도를 낮추고 가독성을 향상시키는 장점이 있습니다.

## 디렉티브의 종류
앵귤러는 3가지 유형의 디렉티브를 제공합니다.
1. 컴포넌트 디렉티브(Component Directives)
2. 어트리뷰트 디렉티브(Attribute Directives)
3. 구조 디렉티브(Structural Directives)

#### 컴포넌트 디렉티브
컴포넌트의 템플릿을 표시하기 위한 디렉티브로 `@Component` 데코레이터의 `selector` 프로퍼티에서 디렉티브 이름을 정합니다.

#### 어트리뷰트 디렉티브
DOM 요소의 어트리뷰트로 사용하여 모양이나 동작을 제어합니다. 예를들어 `ngClass`, `ngStyle` 과 같은 빌트인 디렉티브가 있습니다.

#### 구조 디렉티브
DOM 요소를 반복 생성, 조건에 의한 추가/제거 를 통해 레이아웃을 변경합니다. 예를들어 `ngFor`, `ngIf`, `ngSwitch` 와 같은 빌트인 디렉티브가 있습니다.

## 사용자 정의 어트리뷰트 디렉티브


### 어트리뷰트 생성
자신이 만드는 사용자 정의 디렉티브를 만드는 방법입니다.

```bash
# 디렉티브 생성
$ ng g d <directive name>
```

```ts
import { Directive, ElementRef, Renderer2 } from '@angular/core';

@Directive({
  selector: '[directiveName]'
})

export class CustomDirective {
  constructor(el: ElementRef, renderer: Renderer2) {
    // el.nativeElement.style.color = 'blue'
    renderer.setStyle(el.nativeElement, 'color', 'blue');
  }
}
```

그리고 `src/app/app.module.ts`의 `declarations` 에 추가합니다.


### 이벤트 처리
이벤트 처리기능도 추가할 수 있습니다. `@HostListener` 를 사용하여 이벤트를 등록합니다.

```ts
import { Directive, ElementRef, Renderer2, HostListener } from '@angular/core';

export class CustomDirective {
  @HostListener('eventname') myHandler() {
    // something
  }
  // 생략
}
```

### `@Input` 데이터 바인딩
컴포넌트에서 지정한 값을 `@Input` 을 통해 받아보는 방법입니다.
```ts
export class CustomDirective {
  @Input() foo: any;
}
```

```html
<dom-tag custom [foo]="myProperty"></dom-tag>
```

여기서 한번 더 리팩토링 한다면 다음과같이 하여 간결하게 나타낼 수 있습니다.
```ts
export class CustomDirective {
  @Input('custom') foo: any;
}
```
```HTML
<dom-tag [custom]="myProperty"></dom-tag>
```

## 사용자 정의 구조 디렉티브

### 구조 생성
어트리뷰트 디렉티브 생성과 동일합니다.

```bash
# 구조 디렉티브 생성
$ ng g d <directive name>
```

```ts
import {Directive, Input, TemplateRef, ViewContainerRef} from '@angular/core';

@Directive({
  selector: '[appMyNgIf]'
})
export class MyNgIfDirective {

  constructor(
    private templateRef: TemplateRef<any>,
    private viewContainer: ViewContainerRef
  ) { }

  @Input() set appMyNgIf(condition: boolean) {
    condition
      ? this.viewContainer.createEmbeddedView(this.templateRef) // 호스트 뷰에서 ng-template 추가
      : this.viewContainer.clear(); // 호스트 뷰에서 ng-template 제거
  }

}

```
```HTML
<h2 *appMyNgIf="condition">Hello {{ name }}</h2>
<button (click)="condition = !condition">CLICK</button>
```
예제를 통해 살펴보면 `condition` 값이 사용자 정의 구조 디렉티브의 `@Input set appMyNgIf` 에 들어와 해당 컴포넌트를 만들지 말지 결정합니다.

### `ng-template` 디렉티브
`*ngIf` 는 다음과같이 변형된다 하였습니다.

```html
<element *ngIf="expression"></element>
<!-- 변경 됨 -->
<ng-template [ngIf]="expression">
  <element></element>
</ng-template>
```
Angular 는 `*ngIf`를 만나면 원래 요소를 `ng-template` 디렉티브로 래핑하고 `ngIf`를 프로퍼티로 바인딩으로 변환합니다.

```ts
// ngIf
export declare class NgIf {
    private _viewContainer;
    private _context;
    private _thenTemplateRef;
    private _elseTemplateRef;
    private _thenViewRef;
    private _elseViewRef;
    constructor(_viewContainer: ViewContainerRef, templateRef: TemplateRef<NgIfContext>);
    ngIf: any;
    ngIfThen: TemplateRef<NgIfContext> | null;
    ngIfElse: TemplateRef<NgIfContext> | null;
    private _updateView;
    static ngTemplateGuard_ngIf<E>(dir: NgIf, expr: E): expr is NonNullable<E>;
}
```
`ngIf` 디렉티브는 의존성 주입(DI: Dependency Injection) 을 통해 주입받은 `TemplateRef` 와 `ViewContainerRef`의 인스턴스를 사용해 `ng-template` 디렉티브로 래핑된 요소를 렌더링하거나 제거합니다.

## `TemplateRef`와 `ViewContainerRef`
**`TemplateRef`** : `ng-template` 디렉티브로 래핑된 요소를 가리키는 객체를 생성  
**`ViewContainerRef`** : 하나 이상의 뷰를 포함시킬 수 있는 컨테이너로 `createEmbeddedView` 를 통해 컴포넌트를 인스턴스화하여 만든 호스트 뷰, 그리고 `createdEmbeddedView` 메서드를 통해 `ng-template`을 인스턴스화하여 포함한 임베디드 뷰.

### `ng-container` 디렉티브
구조 디렉티브는 `<ng-template></ng-template>` 으로 바뀌어서 실행되는데 기본적으로 1개의 구조 디렉티브만 사용할 수 있습니다.  
2개이상의 구조 디렉티브를 사용하고싶다면 `<ng-container></ng-container>`를 사용합니다.

```html
<ng-container *ngFor="let text of textList; let i=index;">
  <ng-container *ngIf="i === 3">
    <p>{{ text }}</p>
  </ng-container>
</ng-container>
```

## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
