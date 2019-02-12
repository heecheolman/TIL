# ElementRef, ViewRef, ComponentRef, ViewContainerRef

## ElementRef

엘리먼트 하나를 나타내는 간단한 객체입니다.
```ts
class ElementRef {
  constructor(nativeElement: any);
  nativeElement: any;
}
```
### 역할

특정 엘리먼트를 기반으로 작동해야 하는 어떤 기능에 대해 대상 엘리먼트를 지정해주는 역할을 합니다.

### 특징

* 다양한 환경(플랫폼)에서 실행될 수 있는것을 염두에 둔 추상화된 객체, 플랫폼에 따라 nativeElement 는 다른 객체가 됩니다.
* 생성자에 주입되는 ElementRef 는 루트 엘리먼트

다른 플랫폼에서도 실행될 가능성을 염두에 둔 부분이기 때문에 Renderer2 의 메서드를 이용하여 처리하는것이 좋습니다.

## ViewRef

```ts
class ViewRef extends ChangeDetectorRef {
  destroy(): void;
  destroyed: boolean;
  onDestroy(callback: Function): any;
}
```

### 역할

UI의 생성과 소멸을 다루는 최소 단위로 다시말해, Angular 애플리케이션의 UI 는 ViewRef 들의 조합으로 만들어집니다.

> renderer2 를 이용해 엘리먼트를 만들면 Angular 의 관리를 받지않는 상태가 됩니다.

Angular 의 UI가 해석과 관리를 받으려면 ViewRef 를 생성하는 형태로 UI 를 추가해야합니다. 먼저, `<ng-template>` 태그를 TemplateRef 객체로 래핑한뒤 ViewContainerRef.createEmbeddedView() 의 파라미터로 넘겨주면 해당 템플릿이 생성되고 생성된 템플릿은 return 되어 ViewRef 객체로 옵니다.

```ts
// ...
@ViewChild(TemplateRef) template;
constructor(private vcr: ViewContainerRef) {}
ngOnInit() {
  this.vcr.createEmbeddedView(this.vcr.createEmbeddedView(this.template));
}
```

### 특징

* viewRef 는 생성자에 주입받을 수 없습니다.
* ChangeDetectorRef 를 상속받고 있어 뷰 간의 상하 구조를 변경감지를 위한 구조로 사용합니다.

## ComponentRef

생성된 컴포넌트를 나타냅니다.

```ts
class ComponentRef {
    location: ElementRef;
    injector: Injector;
    instance: C;
    hostView: ViewRef;
    changeDetectorRef: ChangeDetectorRef;
    componentType: Type<any>;
    destroy(): void;
    onDestroy(callback: Function): void;
}
```

### 동적 컴포넌트 생성

1. ComponentFactoryResolver 를 통해 생성하려는 컴포넌트의 ComponentFactory 를 가져옴
2. ComponentFactory 를 ViewContainerRef.createComponent 에 전달

```ts
export class AppComponent {
  constructor(
    private vcr: ViewContainerRef,
    private resolver: ComponentFactoryResolver,
  ){ }

  myMethod() {
    const factory = this.resolver.resolveComponentFactory(MyComponent);
    this.vcr.createComponent(factory);
  }
}
```

```ts
@NgModule({
  declarations: [ AppComponent, MyComponent ],
  entryComponents: [ MyComponent ],
})
```
> 생성하려는 컴포넌트는 NgModule 의 entryComponents에 등록을 해야합니다.

### 특징

* `ComponentRef.instance` 속성을 통해 생성된 컴포넌트의 메서드를 호출할 수 있습니다.
* ComponentRef 또한 생성자에 주입할 수 없습니다.

## ViewContainerRef

```ts
class ViewContainerRef {
  element: ElementRef;
  injector: Injector;
  parentInjector: Injector;
  clear(): void;
  get(index: number): ViewRef | null;
  length: number;
  createEmbeddedView<C>(templateRef: TemplateRef<C>, context?: C, index?: number): EmbeddedViewRef<C>
  createComponent<C>(componentFactory: ComponentFactory<C>,
                     index?: number,
                     injector?: Injector,
                     projectableNodes?: any[][],
                     ngModule?: NgModuleRef<any>): ComponentRef<C>;
  insert(viewRef: ViewRef, index?: number): ViewRef;
  move(viewRef: ViewRef, currentIndex: number): ViewRef;
  indexOf(viewRef: ViewRef): number
  remove(index?: number): void
  detach(index?: number): ViewRef | null
}
```

### 역할

동적으로 뷰를 만들고 추적합니다. ViewRef 와 ComponentRef 를 만드는 역할을 수행합니다.

* 뷰를 생성하는 메서드: createEmbeddedView, createComponent
* 뷰의 위치를 이동하는 메서드: get, move, insert,
* 추적: length (ViewContainerRef가 관리하고 추적하는 ViewRef 의 개수)

### 특징

#### ViewChild 로 ViewContainerRef 가져오기

`@ViewChild` 는 기본적으로 ElementRef 를 가져오는데 read 속성으로 ViewContainerRef 를 기술하여 ViewContainerRef를 가져올 수 있습니다.

```ts
...
@ViewChild('div', { read: ViewContainerRef }) vc1: ViewContainerRef;
```

#### 생성자를 통해 주입

생성자를 통해 주입하게 되면 루트 엘리먼트 객체가 됩니다.
```ts
...
constructor(
  private vcr: ViewContainerRef
) {
  console.log(this.vcr) // 루트 엘리먼트
}
```

#### Sibling Element

ViewContainerRef 를 통해 생성한 뷰는 ViewContainerRef 의 Sibling 엘리먼트로 위치합니다.

## 참고문서

* [제대로 배우는 Angular4 - 조주민](http://www.yes24.com/24/goods/42497045)
