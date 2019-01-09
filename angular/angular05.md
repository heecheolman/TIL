<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 빌트인 디렉티브, 템플릿 참조변수, 세이프 네비게이션 연산자
디렉티브는 DOM 의 모양이나 동작을 관리하기 위한 명령입니다. `~~ 를 해라` 라고 시키는것입니다. Angular 는 3가지 유형의 디렉티브가 있습니다.

* 컴포넌트 디렉티브 : 컴포넌트의 '템플릿'을 표시하기 위한 디렉티브
* 어트리뷰트 디렉티브 : HTML 요소의 어트리뷰트와 같이 사용하여 요소의 모양이나 동작을 제어 (ngClass, ngStyle)
* 구조 디렉티브 : DOM 요소를 반복생성(ngFor), 조건에 의한 추가제거(ngIf, ngSwitch)를 통해 DOM 레이아웃 변경

그리고 템플릿 참조변수와 세이프 네비게이션 연산자를 알아보겠습니다.

## 📝 목차
* [빌트인 어트리뷰트 디렉티브](#빌트인-어트리뷰트-디렉티브)
  * [ngClass](#ngclass)
  * [ngStyle](#ngstyle)
* [빌트인 구조 디렉티브](#빌트인-구조-디렉티브)
  * [ngIf](#ngif)
  * [ngIf else](#ngif-else)
  * [ngSwitch](#ngswitch)
* [템플릿 참조 변수](#템플릿-참조-변수)
* [세이프 네비게이션 연산자](#세이프-네비게이션-연산자)


## 빌트인 어트리뷰트 디렉티브
Angular 가 제공하는 어트리뷰트 디렉티브

### ngClass
여러개의 CSS 클래스를 추가 제거합니다. 한개일 때는 클래스 바인딩이 더 좋습니다.
```html
<element [ngClass]="문자열 | 배열 | 객체"></element>
```

#### 문자열
CSS 클래스 이름을 공백으로 구분하여 작성합니다.
```html
<div [ngClass]="'foo bar baz'"></div>
```

#### 배열
CSS 클래스 이름을 문자열 배열로 구분하여 작성합니다.
```html
<div [ngClass]="['foo', 'bar', 'baz']"></div>
```

#### 객체
`key: value` 로 작성하고 `key` 에는 CSS 클래스 이름, `value` 에는 boolean 타입을 값으로 갖는 객체로 작성합니다.
```html
<div [ngClass]="{ 'foo': true, 'bar': false, 'error': isError }"></div>
```

### ngStyle
여러개의 인라인 스타일을 추가 또는 제거합니다.
```html
<element [ngStyle]="객체"></element>
```

사용예는 다음과 같습니다.
```html
<div [ngStyle]="{
  color: 'black',
  'height.px': 100,
  'visibility': isShow ? 'visible' : 'hidden'
}">
</div>
```

---

## 빌트인 구조 디렉티브
구조 디렉티브는 `*` 를 접두사로 추가하고 `[]` 를 사용하지 않습니다. 그리고 하나의 요소에 하나의 구조 디렉티브만 사용 가능합니다.

### ngIf
```html
<element *ngIf="expression"></element>
```

`*` 는 syntax sugar 입니다. 위의 코드는 아래의 코드와 동일합니다.
```html
<ng-template [ngIf]="expression">
  <element></element>
</ng-template>
```

`template` 태그로 래핑하고 `*ngIf` 를 프로퍼티 바인딩으로 변환합니다. `ngFor` 와 `ngSwitch` 도 동일합니다.

### ngIf else
Angular 4 부터 `ngIf else` 가 추가되었습니다. `ngIf` 의 표현식이 참인경우 그 요소를 DOM에 추가하고 그렇지 않은경우 `else` 이후에 기술한 `ng-template` 디렉티브의 자식을 DOM 에 추가합니다.

```html
<!-- if else, 참일경우 ng-template  안쓰기 -->
<element *ngIf="expression"; else elseBlock>true block</element>
<ng-template #elseBlock>false block</ng-template>

<!-- if else 참일경우 ng-template  쓰기 -->
<element *ngIf="expression"; then thenBlock else elseBlock></element>
<ng-template #thenBlock>true block</ng-template>
<ng-template #elseBlock>false block</ng-template>

<!-- if -->
<element *ngIf="expression"; then thenBlock></element>
<ng-template #thenBlock>true block</ng-template>
```

### ngFor
컴포넌트 클래스의 이터러블 객체를 반복해 하위 요소를 DOM 에 추가합니다.

```html
<element *ngFor="let item of items">...</element>
<element *ngFor="let item of items; let i=index; let odd=odd; trackBy: trackById">...</element>
```
이 또한 syntax sugar 로 아래와 같이 변환됩니다.

```html
<ng-template ngFor let-item [ngForOf]="items" let-i="index" let-odd="odd" [ngForTrackBy]="trackById">
  <element></element>
</ng-template>
```

#### 퍼포먼스 trackBy
`ngFor` 를 사용하여 이터러블객체를 반복하게되는데 그 객체가 변경되면 생성되었던(반복하여 생성된) DOM 요소가 모두 제거된 후 다시 생성합니다. 때문에 매우 큰 이터러블객체를 다룰 때는 `trackBy` 를 사용합니다.

```html
<div *ngFor="let item of items; let i=index; trackBy: trackByUserId"></div>
```
```ts
// 생략
export class AppComponent {
  trackByUserId(index: number, user: User) {
    // 유저 id 를 기준으로 변경을 트래킹합니다.
    return user.id;
  }
}
```
> [trackBy 유무 차이](http://bennadel.github.io/JavaScript-Demos/demos/track-by-ngrepeat-angularjs/)

### ngSwitch
`switch` 조건에 따라 여러 요소중 하나를 선택해 DOM 에 추가합니다.
```html
<element [ngSwitch]="expression">
  <element *ngSwitchCase="'case1'"></element>
  <element *ngSwitchCase="'case2'"></element>
  <element *ngSwitchDefault></element>
</element>
```

`*` 또한 syntax sugar 이며 다음과 같이 변환됩니다.

```html
<element [ngSwitch]="expression">
  <ng-template [ngSwitchCase]="'case1'">
    <element></element>
  </ng-template>
  <ng-template [ngSwitchCase]="'case2'">
    <element></element>
  </ng-template>
  <ng-template ngSwitchDefault>
    <element></element>
  </ng-template>
</element>
```

## 템플릿 참조 변수
템플릿 참조 변수는 DOM 요소에 대한 참조를 담고 있는 변수입니다. `#` 이라는 해시기호를 추가해 참조 변수를 추가합니다.

템플릿 내의 자바스크립트 코드에서는 해시기호(#) 없이 참조할 수 있습니다. 주의사항으로는 템플릿 내에서만 유효하며 컴포넌트 클래스에서 사용할 수 없지만 템플릿 참조 변수의 값을 이벤트 바인딩을 통해 전달할 수 있습니다.
```html
<element #myElement></element>
```

## 세이프 네비게이션 연산자
세이프 네비게이션 연산자인 `?` 는 컴포넌트 클래스의 프로퍼티값이 `null` 이거나 `undefined` 일때 발생되는 에러를 피하기위해 사용합니다.
```html
<!-- 1 -->
{{ obj }}

<!-- 2 -->
{{ obj.id }}

<!-- 3 -->
{{ obj?.id }}
```
* 1번 : `null` 또는 `undefined` 일 경우 아무것도 표시하지 않습니다.
* 2번 : TypeError 가 발생합니다.
* 3번 : 세이프티 연산자를 이용했기 때문에 처리를 종료하고 에러를 발생시키지 않습니다.

## 참고문서
* [빌트인 디렉티브 - PoiemaWeb](https://poiemaweb.com/angular-component-built-in-directive)
