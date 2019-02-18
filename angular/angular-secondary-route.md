# Angular 보조라우터

앵귤러의 라우터는 몇가지 특징이 있습니다.

* 컴포넌트기반 라우팅설정
* 직관적인 라우팅 설계
* 가드(Guard) 로 조정
* 하위 라우팅

기존에 알고있는 하위 라우팅 말고도 보조라우터라는것이 있어 알아봅니다.

## Angular 라우터

Angular 의 라우터는 path에 대해 컴포넌트를 정의하고 컴포넌트가 로드될 위치를 `RouterOutlet` 디렉티브로 정의합니다.

```html
<router-outlet></router-outlet>
```

## 보조 라우터

path 를 정의할 때 outlet 이라는 속성에 이름을 부여할 수 있습니다.

```ts
@NgModule({
  imports: [
    RouterModule.forRoot([
      { path: 'foo', component: FooComponent },
      { outlet: 'outlet1', path: 'bar', component: BarComponent },
      { outlet: 'outlet2', path: 'baz', component: BazComponent },
    ])
  ]
})
```

```html
<router-outlet></router-outlet>
<router-outlet name="outlet1"></router-outlet>
<router-outlet name="outlet2"></router-outlet>
```

outlet에 이름이 없는 라우팅 설정을 기본 라우트(Primary Route) 라고 하고,
이름을 부여하여 추가 설정하는 라우트를 보조 라우트(Auxiliary Route) 또는 부수 라우트(Secondary Route) 라고 합니다.

#### 문제

라우팅 설정은 브라우저의 주소창에 URL로 표시되고 브라우저의 주소창과 표시될 수 있는 URL 은 하나입니다. 하지만 여러개의 path 를 하나의 브라우저 주소창에 표시하려하면 문제가 됩니다. 때문에 **여러 독립적인 path 를 하나의 URL 로 만들어야합니다.**


#### 보조라우트의 URL 문법

```ts
@NgModule({
  imports: [
    RouterModule.forRoot([
      { path: '', component: IndexComponent },
      { path: 'foo', component: FooComponent },
      { path: 'bar', component: BazComponent, outlet: 'otl1', },
    ])
  ]
})
```
```html
<router-outlet></router-outlet>
<router-outlet name="otl1"></router-outlet>
```

위와같은 라우트 구성일 때 아래와 같은 URL 이 구성될 수 있습니다.
```
(1)  http://localhost/(otl:bar)
(2)  http://localhost/foo(otl:bar)
```

1 번은 `IndexComponent + BarComponent` 조합이며,
2 번은 `FooComponent + BarComponent` 조합입니다.

#### 보조라우트가 여러개

```ts
@NgModule({
  imports: [
    RouterModule.forRoot([
      { path: 'foo', component: FooComponent },
      { path: 'bar', component: BarComponent, outlet: 'otl1' },
      { path: 'baz', component: BazComponent, outlet: 'otl2', },
    ])
  ]
})
```
```html
<router-outlet></router-outlet>
<router-outlet name="otl1"></router-outlet>
<router-outlet name="otl2"></router-outlet>
```

만약 위와같은 구성으로 여러개의 보조라우트를 활성화해야한다면 `//` 로 구분지어줍니다.

```
http://localhost/foo(otl1:bar//otl2:baz)
```

#### 어디에 쓰이나

보조 라우트는 하나의 애플리케이션 안에 여러개의 네비게이션을 설계할 수 있는데 대표적으로 팝업창이 있습니다.

팝업창은 보통 메인 애플리케이션 위에 Modal 형태로 띄워지는데 Modal 자체가 url 을 가지지 않기 때문에 뒤로가기의 액션을 하게되면 메인라우트가 바뀌어 원했던 동작을 기대하기 어렵습니다. 그래서 Modal 을 띄워줄때도 url을 변경시켜주는 작업을 하게되는데 이 때 보조라우트를 활용하면 될 것 같습니다.

보조라우트를 이용한 Modal 내부는 메인라우트 위에서 작동하여 뒤로가기를 한다해도 원하는 동작을 기대할 수 있습니다.

## 링크와 네비게이션

보조라우트를 등록하는방법은 위처럼 하면되는데 네비게이션 링크를 어떻게 구성하는지 알아봅니다.

```ts
RouterModule.forRoot([
      { path: 'foo', component: FooComponent },
      { path: 'bar', component: BarComponent, outlet: 'otl', children: [
          { path: 'baz', component: BazComponent },
        ] },
      { path: 'yo', component: YoComponent, outlet: 'otl2' },
    ])
```
```html
<a [routerLink]="[{outlets: { otl: ['bar'], primary: ['foo'] }}]">Foo Bar</a>
<a [routerLink]="[{outlets: {primary: ['foo'], otl: ['bar', 'baz'] }}]">Foo bar/baz</a>
<button (click)="onClick()">Routing</button>
<router-outlet></router-outlet>
<router-outlet name="otl"></router-outlet>
```
```ts
onClick() {
  let outlets = {};
  outlets[PRIMARY_OUTLET] = ['foo'];
  outlets['otl'] = ['bar'];
  this.router.navigate([{ outlets }]);
}
```

* Foo Bar 클릭: `foo(otl:bar)` 처럼 형성
* Foo bar/baz 클릭: `foo(otl:/bar/baz)` 처럼 형성
* Routing 클릭: `foo(otl:bar)` 처럼 형성

PRIMARY_OUTLET 은 `export const PRIMARY_OUTLET = 'primary'` 로 정의되어있는데 Angular 내부적으로 기본 라우트의 outlet 이름에 대해 이 상수를 이용합니다.

## 파라미터

앵귤러는 네 종류의 파라미터를 지원합니다.

* path: `http://localhost:4200/path/user/1234`
* matrix: `http://localhost:4200/path/user;id=1234`
* query: `http://localhost:4200/path/user?id=1234`
* fragment: `http://localhost:4200/path/user#admin`

> fragment 는 파라미터는 아니지만 url 에 덧붙여 정보를 제공하므로 파라미터로 취급한다 합니다.

```html
<a [routerLink]="[{ outlets: { primary: ['foo', 123], otl: ['bar', { id: 456 }]}}]"
   [queryParams]="{debug: true}"
   [fragment]="'abc'">Foo And Bar</a>

<!--
  http://localhost:4200/foo/123(otl:bar;id=456)?debug=true#abc
 -->
```

위의 결과값으로 path 파라미터와 matrix 파라미터는 outlet 별로 다르지만 Query 파라미터와 fragment 는 같다는 것을 알 수 있습니다.  ㄴ

> path 파라미터와 matrix url 파라미터는 path의 배열에 추가하지만, query 파라미터와 fragment 는 별도의 속성에 설정하고있는것으로 유추해볼 수 있습니다.


## 참고문서

* [제대로 배우는 Angular4 - 조주민](http://www.yes24.com/24/goods/42497045)
