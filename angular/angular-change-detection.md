# 변경감지 전략

## ChangeDetectionStrategy

Angular 의 컴포넌트 감지전략이 시작되면 컴포넌트는 다음 두개의 메서드가 호출됩니다.

* OnChanges
* DoCheck

OnChanges 는 `@Input` 멤버변수의 레퍼런스가 변경될 때만 호출이 된다고 하였는데, 데이터의 레퍼런스가 변경되지 않았음에도 어쨌든 컴포넌트의 데이터가 변경되었는지 확인을 하는 작업을 수행합니다.

앵귤러의 컴포넌트는 트리구조로 되어있기 때문에, 상위 컴포넌트의 데이터가 변경이 되지 않았다면 하위 컴포넌트들은 당연히 데이터가 변경되지 않습니다. Angular 는 컴포넌트의 변경 감지 순회를 중단하는 방법을 제공합니다.

```ts
ChangeDetectionStrategy {
  OnPush, // Input 멤버변수의 레퍼런스가 바뀔때만 순회
  Default, // 변경감지 프로세스마다 그 컴포넌트와 하위를 순회 (default)
}
```

상위 컴포넌트의 `@Component` 데코레이터에 다음을 추가해주어 조절할 수 있습니다.

```ts
@Component({
  ...
  changeDetection: ChangeDetectionStrategy.OnPush
})
```

#### 주의사항

ChangeDetectionStrategy.OnPush 설정이 된 컴포넌트는 ngDoCheck 가 변경감지 프로세스마다 호출됩니다. 왜냐하면 하위컴포넌트를 순회할지 말지를 최소한 판단을 해야하기 때문입니다.

#### 동적으로 바꿀 수 없는 전략

ChangeDetectionStrategy 는 컴포넌트의 데코레이터에 의해 설정된 값으로 동적으로 변경할 수 없습니다. 만약 좀 더 세밀하게 조절해야한다면 **ChangeDetectorRef** 를 사용합니다.


## ChangeDetectorRef

앞서서는 컴포넌트를 순회한다고 하였는데, 사실 앵귤러의 모든 UI 는 ViewRef 인데 해당 ViewRef 는 ChangeDetectorRef 를 상속받고 있습니다. 그래서 컴포넌트를 순회하는것이 아닌 ViewRef 와 ChangeDetectorRef 를 순회하는것입니다.

```ts
export declare abstract class ViewRef extends ChangeDetectorRef {
   ...
}
```
```ts
export declare abstract class ChangeDetectorRef {
    markForCheck(): void;
    detach(): void;
    detectChanges(): void;
    checkNoChanges(): void;
    reattach(): void;
}
```

특징이라면, ChangeDetectorRef 는 ViewRef 와는 다르게 생성자를 통해 주입받을 수 있습니다.

#### 변경감지트리에서의 분리

ChangeDetectorRef 를 생성자를 통해 주입받으면 메서드들을 사용할 수 있는데 그중 `detach()` 를 하면 변경감지 트리에서 분리가되어 데이터가 변경되어도 감지할 수 없습니다.

```ts
...
constructor(private cdr: ChangeDetectorRef) {
  this.cdr.detach(); // 분리
}
```

#### 변경감지트리로 합치기

분리된 ChangeDetectorRef 를 `reattach()` 메서드를통해 다시 붙일 수 있습니다.

```ts
constructor(private cdr: ChangeDetectorRef) {
  this.cdr.reattach();
}
```

#### 임의로 변경감지 수행

필요할 때 변경감지를 해야하는 경우에 `detectChanges()` 를 호출합니다.

```ts
constructor(private cdr: ChangeDetectorRef) {
}

// 클릭시 변경감지 수행
onClick() {
  this.cdr.detectChanges();
}
```

## 파이프

파이프는 내부적으로 원본데이터와 원본 데이터를 변형한 데이터를 캐시합니다.

* 순수 파이프 : 입력 데이터의 레퍼런스가 변경되지 않으면 데이터도 변경이 안된다고 판단하는것
* 비순수 파이프 : 변경감지 순회 때마다 변형 (주의해서 사용)

```ts
@Pipe({
  name: 'foo',
  pure: true // default
})
```

pure 속성을 `false` 로 설정하면 비순수 파이프가 됩니다. 비순수 파이프가 요긴하게 쓰일 때가 있는데 바로 AsyncPipe 입니다.

AsyncPipe 를 사용하게 되면 Observable 이나 Promise 로 받는 데이터를 뷰에 전달합니다.
```html
<div>{{ foo | async }}</div>
```

## 참고문서

* [제대로 배우는 Angular4 - 조주민](http://www.yes24.com/24/goods/42497045)
