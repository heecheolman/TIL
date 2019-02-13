# 구조적 디렉티브 활용

구조적 디렉티브의 활용이지만 사실 `*ngFor` 를 연구합니다.


## ngFor

```html
<li *ngFor="let item of list"></li>
```
```html
<ng-template ngFor [ngForOf]="list" let-item>
  <li>
    <span>{{ item.title }}</span>
  </li>
</ng-template>
```

위의 `*ngFor` 문법은 아래의 형태로 변환됩니다. 눈여겨볼 점은 다음과 같습니다.

* ngFor 디렉티브
* [ngForOf] 어트리뷰트의 list 속성 바인딩


### angular 의 ngForOf 디렉티브

```ts
@Directive({selector: '[ngFor][ngForOf]'})
export class NgForOf<T> implements DoCheck {
  @Input()
  set ngForOf(ngForOf: NgIterable<T>) {
    this._ngForOf = ngForOf;
    this._ngForOfDirty = true;
  }
  // ...
}
```
`ngFor` 와 `ngForOf` 가 selector 에 정의되어있고, **ngForOf 에 데이터바인딩이 됩니다.** 그리고 ngForOf 는 `NgIterable<T>` 타입으로 정의되고 있습니다.

#### 반복가능한 것

```ts
export type NgIterable<T> = Array<T>| Iterable<T>;
/**********/
interface Iterable<T> {
    [Symbol.iterator](): Iterator<T>;
}
/*********/
interface Iterator<T> {
    next(value?: any): IteratorResult<T>;
    return?(value?: any): IteratorResult<T>;
    throw?(e?: any): IteratorResult<T>;
}
```
Iterable 타입이란, 반복할 수 있는 인터페이스(반복기: Iterator)를 갖추고 있다면 Iterable 하다 라고 합니다.

#### 생성자

```ts
constructor(
      private _viewContainer: ViewContainerRef,
      private _template: TemplateRef<NgForOfContext<T>>,
      private _differs: IterableDiffers
  ) {}
```

ngForOf 의 생성자를 보면 위와 같이 주입받습니다.

* ViewContainerRef: 동적 뷰 생성 위치 지정
* TemplateRef<NgForOfContext<T>>: 생성될 요소
* IterableDiffers: 비교함수

#### 변경 감지

```ts
ngDoCheck(): void {
    if (this._ngForOfDirty) {
      this._ngForOfDirty = false;
      // React on ngForOf changes only once all inputs have been initialized
      const value = this._ngForOf;
      if (!this._differ && value) {
        try {
          this._differ = this._differs.find(value).create(this.ngForTrackBy);
        } catch {
          throw new Error(
              `Cannot find a differ supporting object '${value}' of type '${getTypeName(value)}'. NgFor only supports binding to Iterables such as Arrays.`);
        }
      }
    }
    if (this._differ) {
      const changes = this._differ.diff(this._ngForOf);
      if (changes) this._applyChanges(changes);
    }
  }
```
ngDoCheck 라는 라이프사이클 훅은 변경이 될 때마다 호출되는 함수입니다.

1. 만약 변경이 있다면,
2. IterableDiffers 에 의해
3. 어떤 아이템이 생성되고 이동되고 삭제되었는지 앎
4. 뷰를 생성/ 삭제/ 이동


#### 내부에서 일어나는 일

```ts
private _applyChanges(changes: IterableChanges<T>) {
    const insertTuples: RecordViewTuple<T>[] = [];

    // 1
    changes.forEachOperation(                                                                                 
        (item: IterableChangeRecord<any>, adjustedPreviousIndex: number, currentIndex: number) => {

          /* 새로운 아이템이 추가된 경우  */
          if (item.previousIndex == null) {
            const view = this._viewContainer.createEmbeddedView(
                this._template, new NgForOfContext<T>(null !, this._ngForOf, -1, -1), currentIndex);
            const tuple = new RecordViewTuple<T>(item, view);
            insertTuples.push(tuple); // push


          /* 아이템이 제거된 경우  */
          } else if (currentIndex == null) {
            this._viewContainer.remove(adjustedPreviousIndex); // remove

          /* 아이템의 위치가 이동한 경우  */
          } else {
            const view = this._viewContainer.get(adjustedPreviousIndex) !;
            this._viewContainer.move(view, currentIndex); // move
            const tuple = new RecordViewTuple(item, <EmbeddedViewRef<NgForOfContext<T>>>view);
            insertTuples.push(tuple);
          }
        });

    for (let i = 0; i < insertTuples.length; i++) {
      this._perViewChange(insertTuples[i].view, insertTuples[i].record);
    }

    // 2
    // <template> 컨텍스트의 객체에 index 와 count 세팅
    for (let i = 0, ilen = this._viewContainer.length; i < ilen; i++) {
      const viewRef = <EmbeddedViewRef<NgForOfContext<T>>>this._viewContainer.get(i);
      viewRef.context.index = i;
      viewRef.context.count = ilen;
      viewRef.context.ngForOf = this._ngForOf;
    }

    // 3
    // $implicit 를 통해 item 변수 세팅
    changes.forEachIdentityChange((record: any) => {
      const viewRef =
          <EmbeddedViewRef<NgForOfContext<T>>>this._viewContainer.get(record.currentIndex);
      viewRef.context.$implicit = record.item;
    });
  }
```

1. item 의 `currentIndex`, `previousIndex` 를 이용해 아이템이 삭제, 추가되었는지 확인합니다.  
2. 그리고나서 각 아이템에 index 와 count 를 설정해주고,
3. Let 문법에 의해 이름없는 로컬 변수에 값을 넣어주는 작업을 합니다.



3 번을 다시 살펴보면 속성 바인딩 없는 `let-xxx` 어트리뷰트에 들어갈 값을 넣어주는 것입니다.

```ts
@Component({
  ...
  template: `
    <template let-foo let-bar>
      <div>{{ foo }}</div>
      <div>{{ bar }}</div>
    </template>
  `,
})
export class AppComponent implements OnInit {
  @ViewChild(TemplateRef) template: TemplateRef<any>;

  constructor(
    private vcr: ViewContainerRef,
  ) {}

  ngOnInit() {
    this.vcr.createEmbeddedView(this.template, {
      $implicit: "Hello", // context 에 $implicit 값 설정
    });
    /*
      속성값이 없는 foo, bar 는 아래와같이 바인딩

      <template let-foo="$implicit" let-bar="$implicit">
        <div>{{ foo }}</div>
        <div>{{ bar }}</div>
      </template>
    */
  }
}
```

**핵심**

1. ngFor 에서 $implicit 에 각 아이템에 대한 객체를 넣어두고,
2. 속성값 없이 선언된 내부 변수에 해당 아이템들이 들어가고,
3. 뷰 내부에서는 로컬 변수 이름으로 아이템을 액세스합니다.

```html
<div *ngFor="let item of list; let idx=index; let cnt=count">
  Item {{ idx }} - {{ cnt }}
</div>
```

그래서 위와 같이 뷰 내부에서 로컬 변수 이름으로 값을 취할 수 있습니다.

## 참고문서

* [제대로 배우는 Angular4 - 조주민](http://www.yes24.com/24/goods/42497045)
* [Understanding Angular Structural Directives - Tomasz Kula](https://netbasal.com/understanding-angular-structural-directives-659acd0f67e)
* [stackoverflow](https://stackoverflow.com/questions/45055384/what-is-implicit-in-angular-2?answertab=votes#tab-top)
