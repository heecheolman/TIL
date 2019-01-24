<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 부모 컴포넌트에서 자식 요소로의 접근
부모 컴포넌트에서 자식 컴포넌트에 접근이 필요한 경우가 있는데, 이 때 템플릿 참조 변수를 사용해 접근할 수 있다.

부모 컴포넌트
```html
<child #child></child>
<button (click)="counter.handler()">
```

자식 컴포넌트
```ts
export class ChildComponent {
  foo: any;
  handler() {
    // something
  }
}
```

하지만 템플릿 참조변수를 사용할 수 없는 상황에서는 아래 4가지의 데코레이터를 사용하게 됩니다.

* `@ViewChild`
* `@ViewChildren`
* `@ContentChild`
* `@ContentChildren`

4가지 데코레이터를 통해 자식 컴포넌트 또는 네이티브 DOM 요소에 접근이 가능한데 자세  살펴보겠습니다.

## 📝 목차
* [`@ViewChild`](#viewchild)
* [`@ViewChildren`](#viewchildren)
  * [QueryList](#querylist)
* [네이티브 DOM 접근](#네이티브-dom-접근)
* [콘텐트 프로젝션](#콘텐트-프로젝션)
  * [싱글 프로젝션](#싱글-프로젝션)
  * [멀티 프로젝션](#멀티-프로젝션)
* [`@ContentChild`, `@ContentChildren`](#contentchild-contentchildren)

## `@ViewChild`
`@ViewChild` 는 탐색 조건에 해당되는 1개의 요소를 갖습니다.

```ts
@ViewChild(탐색 대상 클래스명) 프로퍼티명: 탐색 대상 클래스명;
```

## `@ViewChildren`
`@ViewChildren` 은 탐색 조건에 해당되는 여러 개의 자식 요소를 모두 갖습니다. 그리고 그 타입은 [`QueryList`](https://angular.io/api/core/QueryList) 입니다.

```
@ViewChildren(탐색 대상 클래스명) 프로퍼티명: QueryList<탐색 대상 클래스명>;
```

#### QueryList

```ts
// query_list.d.ts
export declare class QueryList<T> {
    readonly dirty = true;
    private _results;
    readonly changes: Observable<any>;
    readonly length: number;
    readonly first: T;
    readonly last: T;

    map<U>(fn: (item: T, index: number, array: T[]) => U): U[];
    filter(fn: (item: T, index: number, array: T[]) => boolean): T[];
    find(fn: (item: T, index: number, array: T[]) => boolean): T | undefined;
    reduce<U>(fn: (prevValue: U, curValue: T, curIndex: number, array: T[]) => U, init: U): U;
    forEach(fn: (item: T, index: number, array: T[]) => void): void;
    some(fn: (value: T, index: number, array: T[]) => boolean): boolean;
    toArray(): T[];
    toString(): string;
    reset(res: Array<T | any[]>): void;
    notifyOnChanges(): void;
    /** internal */
    setDirty(): void;
    /** internal */
    destroy(): void;
}
```

QueryList 의 내부 구현부입니다. QueryList 의 `_results` 프로퍼티에 결과를 담아 놓고 있습니다. 그리고 자바스크립트 배열처럼 쓸 수 있도록 `map`, `filter`, `find`, `reduce`, `forEach`, `some` 등의 메서드를 사용할 수 있습니다. 또한, iterable 인터페이스를 구현하였기 때문에 `for ... of` 루프에도 사용가능하고 `ngFor`또한 사용 가능합니다.

## 네이티브 DOM 접근
`@ViewChild`와 `@ViewChildren` 데코레이터의 인자로 탐색 대상으로 지정된 '템플릿 참조 변수를 문자열 형태로 지정' 하게되면 네이티브 DOM 객체를 래핑한 `ElementRef`타입의 인스턴스를 획득할 수 있습니다.

```html
<!-- ViewChild -->
<dom-tag #any></dom-tag>

<!-- ViewChildren -->
<dom-tag #any2></dom-tag>
<dom-tag #any3></dom-tag>
```
```ts
@ViewChild('any') 프로퍼티명: ElementRef;
@ViewChildren('any2, any3') 프로퍼티명: QueryList<ElementRef>;
```
#### Renderer2
직접 DOM 에 접근할 수 있지만 지양하는것이 좋습니다. 그 이유는 앵귤러의 컴포넌트 흐름때문인데 `컴포넌트 클래스 상태 변경 -> 템플릿 뷰 상태 변경 -> DOM 변경` 과 같이 작동합니다. 그런데 직접 DOM 을 조작하게 되면 이러한 로직이 꼬일 수 있습니다. 그리고 [Angular ElementRef](https://angular.io/api/core/ElementRef) 에 따르면 직접 조작하게되면 보안에 취약할 수 있다고 합니다. 때문에 과거에는 `Renderer`, 현재는 `Renderer2` 를 사용해 조작하라고 권장하고 있습니다.https://angular.io/api/core/ElementRef

## 콘텐트 프로젝션
콘텐츠는 태그와 태그 사이에 있는 내용을 콘텐츠라 합니다.
```html
<p>Hello</p>
```
여기서는 Hello 가 콘텐츠가 되는데, 부모컴포넌트에서 자식컴포넌트의 콘텐츠를 지정할 수 있습니다.
```html
<child>
  <p>Contents</p>
</child>
```
여기서 `<p>Contents</p>` 자체가 콘텐츠가 됩니다. 그리고 자식 컴포넌트는 `ngContent` 디렉티브를 사용하여 전달받은 콘텐츠로 치환합니다.
```html
<ng-content></ng-content>
```

#### 싱글 프로젝션
부모 컴포넌트
```html
<child>
  <p>Single Projection</p>
</child>
```
자식 컴포넌트
```HTML
<ng-content></ng-content>
```

그러면 `<ng-content></ng-content>`는 `<p>Single Projection</p>` 로 치환되어 표시됩니다.

#### 멀티 프로젝션
네이밍있는 싱글 프로젝션이라 생각하면 편할 것 같습니다. `select` 어트리뷰트를 사용해 슬롯을 만들어줍니다.

자식 컴포넌트
```html
<ng-content select="foo"></ng-content>
<ng-content select="bar"></ng-content>
<ng-content select=".baz-class"></ng-content>
```

부모 컴포넌트
```html
<child>
  <foo>...</foo>
  <bar>...</bar>
  <div class="baz-class">...</div>
</child>
```

## `@ContentChild`, `@ContentChildren`

`ViewChild`의 시작태그와 종료태그 사이에 있는 콘텐츠를 `ContentChild` 라 합니다. `@ContentChild` 는 탐색하려는 요소가 한개일 때 사용하고 `@ContentChildren` 은 탐색하려는 모든 요소를 가져오고 싶을 때 사용합니다.

```ts
// 부모 컴포넌트가 지정한 콘텐츠중 템플릿 참조변수 first 를 가진 콘텐츠를 가져옴
@ContentChild('first') firstChild: UserComponent;

// 부모 컴포넌트가 지정한 콘텐츠들 중 UserComponent 모두를 가져옴
@ContentChildren(UserComponent) children: QueryList<UserComponent>;
```


## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
