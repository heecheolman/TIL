# `<ng-template>` 과 동적 뷰


## [`<template>`](https://developer.mozilla.org/ko/docs/Web/HTML/Element/template)
먼저, `<template>` 의 태그를 알아보자면 미리 정의해 둔 HTML 을 필요한 시점에 **동적으로 인스턴스화해 출력을 삽입할 수 있는 표준적인 방법** 입니다. 즉, DOM 트리에는 존재하지만 인스턴스화를 통해 화면에 출력이 된다는 것입니다.

Angular 는 `<template>` 태그를 `<ng-template>` 태그로 사용합니다.


## TemplateRef

`<ng-template>` 태그와 하위 콘텐츠들을 TemplateRef 라는 객체로 만들어줍니다.  
컴포넌트의 템플릿에 동적으로 생성할 부분을 `<ng-template>` 으로 감싼 뒤 `@ViewChild` 데코레이터의 인자로 TemplateRef 를 주면, `<ng-template>` 을 가져올 수 있습니다. 그리고 ViewContainerRef 의 메서드를 통해 가져온 템플릿을 생성할 수 있습니다.

```ts
// 생략
@Component({
  template: `
    <div>
      <ng-template>
        <h3> dynamic view </h3
      </ng-template>
    </div>

    <button (click)="onClick()">Click it</button>
  `,
})
export class MyComponent {
  @ViewChild(TemplateRef) template: TemplateRef<any>; // 템플릿 가져오기

  cosnstructor(
    private vcr: ViewContainerRef,
  ){ }

  onClick() {
    this.vcr.createEmbeddedView(this.template); // 생성
  }
}
```

> 생성자에 ViewContainerRef 를 주입하게되면 selector 로 지정한 태그 엘리먼트를 받아오므로, 위의 코드에서는 <app-root> 태그의 Sibling 으로 <ng-container> 가 만들어집니다.

#### `<ng-template>` 이 다수일 경우

`<ng-template>` 에 템플릿 참조변수를 지정해주고 `@ViewChild` 로 가져오면 됩니다.

```ts
@Component({
  template: `
    <div>
      <ng-template #ref1> ... </ng-template>
      <ng-template #ref2> ... </ng-template>
    </div>
  `
})
export class MyComponent {
  @ViewChild('ref1') ref1: TemplateRef<any>;
  @ViewChild('ref2') ref2: TemplateRef<any>;
  ...
}
```


```ts
class TemplateRef<C> {
    elementRef: ElementRef;
    createEmbeddedView(context: C): EmbeddedViewRef<C>;
}
```


## `@ViewChild` & `@ContentChild`

**ViewChild** 와 **ContentChild** 가 헷갈리는 경우가 있습니다. 다음과같은 구조가 있다고 가정합니다.

```ts
// App Component
@Component({
  template: `
    <h1>App Component</h1>

    <my-component>

      <ng-template>
        <p>something contents...</p>
      </ng-template>

    </my-component>
  `,
})
export class AppComponent {
}


/**************************/
// MyComponent
@Component({
  template: `
    <h2>My Component</h2>

    <button (click)="create()">Create</button>
  `,
})
export class MyComponent {
  @ContentChild(TemplateRef) template: TemplateRef<any>;

  constructor(private vcr: ViewContainerRef) {}

  create() {
    this.vcr.createEmbeddedView(this.template);
  }
}

```

#### `<ng-template>` 을 각각 가져오자

AppComponent 입장에서는 `@ViewChild` 가 `<ng-template>` 이지만,  
MyComponent 입장에서는 `@ContentChild` 가 `<ng-template>` 이 됩니다.

정리하자면, 다음과 같습니다.

* AppComponent 에서 `@ViewChild` 를 하면 `<ng-template>` 을 가져옴.
* MyComponent 에서 `@ContentChild` 를 하면 `<ng-template>` 을 가져옴


#### context 바인딩

`<ng-template>` 이 실제로 선언된 곳은 AppComponent 입니다. 때문에 컨텍스트 바인딩은 AppComponent 에 따라 바인딩됩니다.




## Let 문법(값 전달)


```HTML
<ng-template let-xxx="variable"></ng-template>
```
위와 같은 `let-xxx="variable"` 형태로 지정할 때, xxx 를 **템플릿 입력변수(template input variable)** 이라고 합니다. 그리고 이 변수는 템플릿 내에서 사용가능합니다.

앞서 보았던 예제에서 실제로 선언된 곳에서 바인딩이 일어난다고 하였는데, 사실 뷰를 생성하는 곳에서도 파라미터를 전달해줄 수 있습니다.  
알아보기 전에, EmbeddedViewRef 의 정의와, createEmbeddedView() 메서드를 살펴봅니다.

```ts
abstract createEmbeddedView<C>(templateRef: TemplateRef<C>, context?: C, index?: number): EmbeddedViewRef<C>;
```

```ts
export declare abstract class EmbeddedViewRef<C> extends ViewRef {
    /**
     * The context for this view, inherited from the anchor element.
     */
    abstract readonly context: C;
    /**
     * The root nodes for this embedded view.
     */
    abstract readonly rootNodes: any[];
}
```
createEmbeddedView() 의 두번째 인자로 context 를 넘겨주는 것을 확인할 수 있는데, 이 context 와 앞서 보았던 템플릿 입력변수를 매핑하여 전달합니다.

```ts
// AppComponent
@Component({
  template: `
    <app-my-frame>

    <ng-template let-msg2="message" let-click2="handler">
      <div>{{ msg }}</div>
      <div>{{ msg2 }}</div>
      <button (click)="click()">Click1</button>
      <button (click)="click2()">Click2</button>
    </ng-template>

  </app-my-frame>
  `
})
export class AppComponent {
  msg = 'hello'
}

/*********************************/

// MyFrameComponent
@Component({
  template: `
  <h2>My Frame Component</h2>
  <button (click)="create()">Create</button>
  `
})
export class MyFrameComponent {

  @ContentChild(TemplateRef) template: TemplateRef<any>;

  constructor(
    private vcr: ViewContainerRef,
  ) { }

  create() {
    const context = {
      message: 'world',
      handler() {
        alert('world');
      },
    };
    this.vcr.createEmbeddedView(this.template, context); // context 전달
  }
}
```

살펴보면 `let-msg2="message"`, `let-click2="handler"` 는 context 와 매핑되는 것을 알 수 있습니다.


## 생성위치 조정

먼저, ViewContainerRef 를 생성자를 통해 주입받게 되면 해당 컴포넌트의 태그 엘리먼트를 가리킵니다. 그래서 그 위치에서 뷰를 생성하게되면 해당 컴포넌트와 형제(Sibling) 컴포넌트로 위치하게 됩니다.


#### 참조변수를 이용해 가져오기

템플릿 참조 변수를 이용해 ViewContainerRef 를 가져옵니다.

```ts
...
@Component({
  template: `
    <div #view1></div>
  `,
})
export class MyComponent {
  @ViewChild('view1', { read: ViewContainerRef }) view1: ViewContainerRef; // ViewContainerRef 로 가져오기
  @ViewChild('view1') el: ElementRef; // read 속성을 지정하지않으면 기본으로 ElementRef 를 가져옵니다.
}
```

#### 컴포넌트나 디렉티브의 클래스 타입으로 가져오기

`@ViewChild` 에서 컴포넌트나 디렉티브의 클래스타입을 이용해 가져오는 방법이 있습니다.

```ts
@Directive({
  selector: 'my-directive',
})
export class MyDirective {}

@Component({
  selector: 'app-root',
  template: `
    <h1>App Component</h1>

    <my-directive></my-directive

    <ng-template>
        <h2>Template Content</h2>
    </ng-template>
  `,
})
export class AppComponent implements OnInit {

  @ViewChild(MyDirective) myDirective: MyDirective;
  @ViewChild(MyDirective, { read: ViewContainerRef }) myDirectiveVcr: ViewContainerRef;

  constructor() {
  }

  ngOnInit(): void {
    console.log(this.myDirective); // MyDirective
    console.log(this.myDirectiveVcr); // ViewContainerRef
  }

}
```

## 디렉티브로 TemplateRef 가져오기

```ts
@Directive({ selector: '[myFrameHeader]' }) export class MyFrameHeader {}
@Directive({ selector: '[myFrameBody]' }) export class MyFrameBody {}
@Directive({ selector: '[myFrameFooter]' }) export class MyFrameFooter {}

@Component({
  selector: 'my-frame',
  template: `
    <div #frameHeader></div>
    <div #frameBody></div>
    <div #frameFooter></div>
  `
})
export class MyFrameComponent {
  /* 디렉티브로 가져오기 */
  @ContentChild(MyFrameHeader, { read: TemplateRef }) headerTempRef: TemplateRef<any>;
  @ContentChild(MyFrameBody, { read: TemplateRef }) bodyTempRef: TemplateRef<any>;
  @ContentChild(MyFrameFooter, { read: TemplateRef }) footerTempRef: TemplateRef<any>;

  /* ViewContainerRef 가져오기  */
  @ViewChild('frameHeader', { read: ViewContainerRef }) headerVcr: ViewContainerRef;
  @ViewChild('frameBody', { read: ViewContainerRef }) bodyVcr: ViewContainerRef;
  @ViewChild('frameFooter', { read: ViewContainerRef }) footerVcr: ViewContainerRef;

  ngAfterViewInit() {
    /* 생성 */
    this.headerVcr.createEmbeddedView(this.headerTempRef);
    this.bodyVcr.createEmbeddedView(this.bodytempRef);
    this.footerVcr.createEmbeddedView(this.footerTempRef);
  }
}

/*************************************/
@Component({
  selector: 'app',
  template: `
    <h1>App Component</h1>
    <my-frame>

      <ng-teamplte myFrameHeader>
        <h2>Header</h2>
      </ng-template>

      <ng-teamplte myFrameBody>
        <h2>Body</h2>
      </ng-template>

      <ng-teamplte myFrameFooter>
        <h2>Footer</h2>
      </ng-template>

    </my-frame>
  `,
})
export class AppComponent {}
```


템플릿 참조변수로 하는것과 다른것이 없지만 AppComponent 의 `<ng-template>` 에 디렉티브를 이용해 지정하면 보다 명시적으로 알 수 있기 때문에 선호됩니다.
