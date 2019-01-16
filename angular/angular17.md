<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 라우팅과 네비게이션
라우팅과 네비게이션에 들어가기전에 Angular, React, Vue 와 같은것들이 왜 생겨났는지에 대해 알아 볼 필요가 있습니다. 현재 모바일로 인터넷을 접속하는 일이 많아지고, 웹이 더이상 '문서'에 국한되지않고 마치 네이티브 앱처럼 하나의 애플리케이션으로 자리잡고 있습니다. 사용자와의 인터랙션들이 많아지고 사용자들을 웹에서도 네이티브 앱처럼 반응성, 트래픽 감소, 속도 등을 느끼고 싶었을 겁니다.

> 예를들어 트위터나 페이스북 같은 SNS 는 '문서'라기보단 '앱'에 가까운 웹입니다. 최초의 SPA 는 Gmail 입니다.

어떻게 기존의 정적페이지보다 빠르게 구동될 수 있는지 그리고 앵귤러는 어떻게 라우팅 하는지에대해 알아보겠습니다.

## 📝 목차
* [SPA란?](#spa란)
* [라우팅](#라우팅)
* [앵귤러의 라우팅](#앵귤러의-라우팅)
* [위치 정책](#위치-정책)
  * [PathLocationStrategy](#pathlocationstrategy)
  * [HashLocationStrategy](#hashlocationstrategy)
* [라우터 구성요소](#라우터-구성요소)
  * [1. 라우트 구성](#1-라우트-구성)
  * [2. 라우트 등록](#2-라우트-등록)
  * [3. 뷰의 렌더링 위치 지정](#3-뷰의-렌더링-위치-지정)
  * [4. 네비게이션 작성](#4-네비게이션-작성)
    * [RouterLink](#routerlink)
    * [RouterLinkActive](#routerlinkactive)
    * [routerLinkActiveOptions](#routerlinkactiveoptions)
    * [navigate 메서드](#navigate-메서드)
* [라우터 상태](#라우터-상태)
  * [라우트 파라미터 전달](#라우트-파라미터-전달)
  * [라우트 파라미터 취득](#라우트-파라미터-취득)
    * [옵저버블로 취득](#옵저버블로-취득)
    * [특정 시점 취득](#특정-시점-취득)
  * [라우트 정적 데이터](#라우트-정적-데이터)
* [자식 라우트](#자식-라우트)
* [모듈의 분리와 모듈별 라우터 구성](#모듈의-분리와-보듈별-라우터-구성)
  * [1. 자식 라우팅 모듈 구성](#1-자식-라우팅-모듈-구성)
  * [2. 자식 모듈에 자식 라우팅 모듈 등록](#2-자식-모듈에-자식-라우팅-모듈-등록)
  * [3. 루트 라우팅 모듈 구성](#3-루트-라우팅-모듈-구성)
  * [4. 루트 모듈에 라우팅 모듈들 등록](#4-루트-모듈에-라우팅-모듈들-등록)
* [라우트 가드](#라우트-가드)
  * [CanActivate](#canactivate)
  * [CanActivateChild](#canactivatechild)
  * [CanLoad](#canload)
  * [Resolve](#resolve)
  * [CanDeactivate](#candeactivate)


## SPA란?
단일 페이지 애플리케이션(SPA: Single Page Application) 의 약자입니다. 모던 웹의 패러다임으로 네이티브 앱과 유사한 UX 를 제공할 수 있다는 장점이 있습니다.

#### 기존의 문제
기존의 서버사이드 렌더링 방식은 요청에 응하는 새로운 페이지를 다시 그려서 제공합니다. 모바일퍼스트인 현 시대에 쓸데없는 네트워크 비용과 속도는 너무나도 중요합니다. 그리고 사용자들의 요구사항이 많아지면서 인터랙션도 많아지니 기존의 방식은 사용자들이 기다리다가 접속을 종료하게 될 것입니다.

#### 해결점
**'처음에 모든 리소스를 다 내려받고 그 안에서 동작하게 하자'** 라는게 SPA 입니다. 이렇게 되면 처음의 구동속도는 상대적으로 느릴테지만 한 번만 받게된 이후에는 속도는 압도적으로 빠를 것입니다. 그리고 필요한 데이터들은 부분적으로 요청하여 업데이트하는것입니다. 이렇게되면 속도와 네트워크 비용측면에서도 좋은 방안입니다.

#### 새로운 문제점
얻는게 있다면 잃는게 있듯이, 초기구동속도와 SEO(검색 엔진 최적화) 문제입니다. 아무래도 앱처럼 동작하기 위해 리소스들을 한번에 받으려면 당연히 처음에 느릴 수 밖에 없습니다. 그 다음은 SEO 문제입니다. 한 번만 로드하고 내부적으로 돌기 때문에 문제가 됩니다. 하지만 SPA 는 정보를 제공하는 측면보단 애플리케이션에 적합한 기술일 뿐 아니라 차차 SEO 이슈들을 해결해 나가고 있는것으로 알고 있습니다.

## 라우팅
라우팅(Routing) 이란 출발지에서 목적지까지의 경로를 결정하는 기능입니다. 즉 웹에서는 `화면 -> 화면` 으로 전환하는 네비게이션 기능입니다. 본래 라우팅을 할 시 `<a>` 태그의 `href` 어트리뷰트를 통해 URL 을 변경하고 다른페이지로 넘어가는 방식이였습니다.

하지만, AJAX 요청에 의해 서버로부터 데이터를 받아 화면을 생성하는 경우에는 URL이 변경되지 않습니다. 이로 인해 SEO 문제가 야기되는 것입니다.

## 앵귤러의 라우팅
앵귤러는 SPA 를 위한 클라이언트 사이드 네비게이션으로, Angular 라우터를 제공합니다. URL 과 컴포넌트의 쌍으로 라우트 설정을 참고하여 뷰를 렌더링합니다.

```ts
// 라우트 설정 예
const routes: Routes = [
  { path: '', redirectTo: '', pathMatch: 'full' },
  { path: 'home', component: HomeComponent },
  { path: 'foo', component: FooComponent },
]
```

## 위치 정책
SPA 이기 때문에 새로고침을 하면 당연히 첫페이지가 로드됩니다. 그리고 앞서 말했듯이 URL 이 변경되지않아 SEO 문제가 있다고 하였습니다. 그래서 Angular 는 2가지 해결점을 제시합니다.

1. PathLocationStrategy
2. HashLocationStrategy

### PathLocationStrategy
HTML5 History API **[pushState 메서드](https://developer.mozilla.org/ko/docs/Web/API/History_API)** 를 사용하는 정책으로 **Angular 라우터의 기본 정책입니다.**

> [Angular Universal](https://angular.io/guide/universal)을 사용하여 서버 사이드 렌더링을 도입하려면 이 정책을 사용해야 한다고 합니다.

### HashLocationStrategy
해시기반 네비게이션 정책으로 URL 경로에 프래그먼트 식별자(fragment identifier, 해시뱅이라고도 부름)의 고유 기능인 앵커(anchor) 를 사용하는 정책으로 `/#/service`, `/#/about` 과 같이 해시뱅을 기반으로 합니다.

해시기반 네비게이션을 사용하려면 루트모듈의 imports 프로퍼티를 다음과 같이 변경합니다.

```ts
@NgModule({
  imports: [
    BrowserModule,
    RouterModule.forRoot(routes, { userHash: true }),
  ]
})
```
## 라우터 구성요소
라우터를 구성하는 방법은 다음의 순서로 진행합니다.

1. 라우트 구성
2. 라우트 등록
3. 뷰의 렌더링 위치 지정
4. 네비게이션 작성

### 1. 라우트 구성
`Route` 인터페이스의 배열을 사용하여 요청 URL의 경로와 컴포넌트를 매핑합니다.

라우트의 구성 예는 다음과 같습니다.
```ts
const routes: Routes = [
  { path: 'home', component: HomeComponent },
  { path: 'service', component: ServiceComponent },
  { path: 'about', component: AboutComponent },
  { path: '**', component: NotFoundComponent },
];
```

그리고 위의 구성에 대한 설명입니다.

|요청 URL 경로|URL 범례|활성화될 컴포넌트|
|:---------:|:-----:|:-----------:|
|home|localhost:4200/home|HomeComponent|
|service|localhost:4200/service|ServiceComponent|
|about|localhost:4200/about|AboutComponent|
|위의 경로 외 다른 경로|localhost:4200/foo|NotFoundComponent|

* **path: '**'** 는 반드시 라우트 구성의 맨 마지막에 넣어주어야합니다. 그 이유는 처음에 적어주게 되면 모든 경우에 매칭되기 때문에 정상적으로 라우트가 되지 않습니다.
* **redirectTo** 는 요청을 리다이렉트 할 때 사용하고 보통 `pathMatch` 프로퍼티와 함께 사용합니다.
* **pathMatch 프로퍼티에 'full'을 설정** 하면 path 프로퍼티 경로와 URL 경로 전체가 정확하게 매칭할 때 리다이렉트합니다.
* **pathMatch 프로퍼티에 'prefix'를 설정** 하면 path 프로퍼티의 경로와 요청 URL 경로가 앞부분만 매칭하여도 리다이렉트 합니다.

예를들어 다음과 같습니다.
```ts
const routes: Routes = [
  { path: '', redirectTo: 'home', pathMatch: 'full' },
  { path: 'home', component: HomeComponent },
  ...
];
```

### 2. 라우트 등록
라우트는 모듈 단위로 구성합니다. 그리고 구성된 라우트는 모듈에 등록합니다.

`Routes` 와 `RouterModule` 을 임포트하고 라우트 구성도 추가해줍니다.
```ts
// app.module.ts
...
import { Routes, RouterModule } from '@angular/router';
import { SomeComponent, ... } from 'path'; // 컴포넌트 임포트

// 라우트 구성
const routes: Routes = [
  { path: '', redirectTo: 'home', pathMatch: 'full' },
  { path: 'home', component: HomeComponent },
  ...
];

@NgModule({
  declarations: [
    SomeComponent, // 컴포넌트들 등록
    ...
  ],
  imports: [
    RouterModule.forRoot(routes) // 라우터 모듈 생성 후 등록
  ]
})
```

루트 모듈에 작성할 수도 있지만 애플리케이션이 복잡해지면 별도의 라우팅 모듈을 작성합니다.

```ts
// app-routing.module.ts
import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { SomeComponents } from 'path'; // 컴포넌트 임포트

// 라우트 구성
const routes: Routes = [
  { path: '', redirectTo: 'foo', pathMatch: 'full' },
  { path: 'bar', component: FooComponent, },
  { path: 'baz', component: BarComponent, },
];


@NgModule({
  // 모든 라우트 구성을 포함한 모듈을 생성하고 라우팅 모듈에 추가
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule],
})
export class AppRoutingModule {}
```
```ts
// app.module.ts
...
import { AppRoutingModule } from './app-routing.module'; // 라우팅모듈 임포트
import { SomeComponents } from 'path'; // 컴포넌트 임포트

@NgModule({
  declarations: [
    SomeComponents // 컴포넌트 정의
  ],
  imports: [
    BrowserModule,
    AppRoutingModule, // 라우팅 모듈 등록
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }

```

### 3. 뷰의 렌더링 위치 지정
2번과 3번을 완료했다면 라우터의 구성과 등록을 마친 것입니다. 이제 라우트 될 뷰의 위치를 정하면 됩니다.

#### RouterOutlet
RouterOutlet 은 라우터가 컴포넌트를 렌더링하여 뷰를 표시할 영역인 `<router-outlet>`을 구현한 디렉티브로 컴포넌트의 뷰를 렌더링할 위치를 설정합니다.

```html
<router-outlet></router-outlet>
```
이제 `<router-outlet>` 위치에 뷰가 렌더링됩니다.

### 4. 네비게이션 작성
RouterLink 디렉티브를 사용한 HTML `a` 요소를 사용하여 네비게이션을 작성하는 방법과 native 메서드를 이용한 방법이 있습니다.

#### RouterLink
뷰의 전환을 위한 네비게이션은 기본적으로 `<a>` 태그의 `href` 어트리뷰트를 사용하는데 이것 대신 RouterLink 디렉티브를 사용하여 라우트합니다.
```html
<nav>
  <a routerLink="/home">Home</a>
  <a routerLink="/service">Service</a>
  <!-- <a href="/foo">Nope</a> -->
</nav>
```
> `href` 어트리뷰트를 사용하게되면 서버로 페이지 요청이 가게 되어 사용하면 안됩니다.

**RouterLink 디렉티브는 자신의 값을 라우터에게 전달하고, 라우터는 이를 전달받아 해당 컴포넌트를 활성화하여 뷰를 렌더링합니다. 렌더링 되는 위치는 `<router-outlet>`에 표시됩니다.**

```HTML
<nav>
  <a routerLink="/home">Home</a>
  <a routerLink="/service">Service</a>
  <a routerLink="/about">About</a>
</nav>
<router-outlet></router-outlet>
```

#### RouterLinkActive
RouterLinkActive 는 현재 브라우저의 URL 경로가 RouterLink 디렉티브에서 지정한 URL 경로의 '트리'에 포함되는 경우 RouterLinkActive 클래스명을 DOM 에 자동으로 추가합니다.

```HTML
<a routerLink="/service" routerLinkActive="active">Service</a>
```
경로가 '/' 또는 '/service' 인 경우 등록된 'active' 클래스가 DOM 에 추가됩니다.

#### routerLinkActiveOptions
만약, RouterLink 디렉티브에서 지정한 URL 경로와 정확히 일치할 때만 활성화 시키고 싶다면 `routerLinkActiveOptions` 디렉티브를 사용합니다.

```HTML
<a routerLink="/service"
   [routerLinkActiveOptions]="{ exact: true }"
   routerLinkActive="active">Service</a>
```

지정할 클래스가 여러개일 경우는 다음과 같이 지정합니다.
```html
<a routerLink="/service" routerLinkActive="class1 class2">Service</a>
<a routerLink="/service" routerLinkActive="['class1', 'class2']">Service</a>
```

#### navigate 메서드
템플릿의 `<a>` 가 아니라 컴포넌트 클래스의 코드만으로 화면을 전환(프로그래밍 방식)하고 싶다면 navigate 메서드를 사용합니다.

```ts
// mycomponent.component.ts
export class MyComponent {
  constructor(
    private router: Router, // 의존성 주입
  ) { }
  goto() {
    this.router.navigate(['path']); // 경로 지정
  }
}
```

## 라우터 상태
### 라우트 파라미터 전달
화면 전환 시 라우트 파라미터(Route Parameter) 를 사용해 활성화될 컴포넌트에 데이터를 전달할 수 있습니다.
```HTML
<a routerLink="/todo">...</a>
```
`/todo` 로 라우팅 할 때 URL 경로가 **`/todo/:id` 일경우 `:id` 는 라우터 파라미터이며 컴포넌트에게 전ㄷ라하고자 하는 값을 할당합니다.**

```HTML
<a routerLink="/todo/:id">...</a>
```
라우트 구성을 아래라고 가정한다면,
```ts
const routes: Routes = [
  { path: '', component: TodosComponent },
  { path: 'todo/:id', component: TodoDetailComponent }, // id 가 파리미터
]
```
라우터의 파라미터는 대부분 동적값인데 이럴 경우, 다음과 같이 디렉티브를 구성합니다.
```HTML
<a [routerLink]="['/todo', todoId]">...</a>
<!-- 아래와 같이 구성됩니다. -->
<a routerLink="/todo/10">...</a>
```
RouterLink 디렉티브에 URL 경로의 세그먼트로 구성된 **배열을 할당** 합니다. 만일 navigate 메서드를 사용한다면(프로그래밍 방식) 다음과 같습니다.
```ts
this.router.navigate(['/todo', todoId]);
```

### 라우트 파라미터 취득
`<router-outelet>` 영역에 렌더링된 컴포넌트는 `ActivatedRoute` 객체를 통해 라우터 상태(router state) 에 접근할 수 있습니다.

**[ActivatedRoute 클래스 내부](https://angular.kr/guide/router)**
```ts
export declare class ActivatedRoute {
    /*  */
    url: Observable<UrlSegment[]>;
    /*  */
    params: Observable<Params>;
    /* 라우팅 규칙에 정의된 라우팅 변수를 map 타입의 Observable로 표현합니다. 맵을 사용하면 라우팅 규칙에 포함된 라우팅 인자를 한 번에 모두 가져올 수도 있습니다. */
    queryParams: Observable<Params>;
    fragment: Observable<string>;
    data: Observable<Data>;
    outlet: string;
    component: Type<any> | string | null;
    snapshot: ActivatedRouteSnapshot;
    /** The configuration used to match this route */
    readonly routeConfig: Route | null;
    /** The root of the router state */
    readonly root: ActivatedRoute;
    /** The parent of this route in the router state tree */
    readonly parent: ActivatedRoute | null;
    /** The first child of this route in the router state tree */
    readonly firstChild: ActivatedRoute | null;
    /** The children of this route in the router state tree */
    readonly children: ActivatedRoute[];
    /** The path from the root of the router state tree to this route */
    readonly pathFromRoot: ActivatedRoute[];
    readonly paramMap: Observable<ParamMap>;
    readonly queryParamMap: Observable<ParamMap>;
    toString(): string;
}
```
|프로퍼티|설명|
|:--|:--|
|url|라우팅 경로를 Observable 타입으로 표현합니다. 이 프러파티를 참조하면 라우팅 경로를 구성하는 각 문자열을 배열 형태로 확인할 수 있습니다.|
|data|라우팅 규칙에 data 객체가 지정되었을 때 이 데이터를 Observable 타입으로 표현합니다. 이 객체에는 라우터 가드에서 처리된 내용이 포함될 수도 있습니다.|
|paramMap|라우팅 규칙에 정의된 라우팅 변수를 map 타입의 Observable로 표현합니다. 맵을 사용하면 라우팅 규칙에 포함된 라우팅 인자를 한 번에 모두 가져올 수도 있습니다.|
|queryParamMap|라우팅 규칙에서 접근할 수 있는 모든 쿼리 변수를 map 타입의 Observable로 표현합니다. 맵을 사용하면 라우팅 규칙에 포함된 쿼리 변수를 한 번에 모두 가져올 수도 있습니다.|
|fragment|모든 라우팅 규칙에 포함된 URL 조각을 Observable 형태로 표현합니다.|
|outlet|라우팅 영역으로 사용되는 RouterOutlet을 지정할 때 사용합니다. 라우팅 영역에 이름을 지정하지 않으면 primary 가 기본 이름으로 지정됩니다.|
|routeConfig|현재 사용된 라우팅 규칙의 설정을 표현합니다. 이 객체에는 URL 주소에 대한 정보도 포함됩니다.|
|parent|현재 라우팅된 것이 자식 라우팅 규칙이라면, 이 라우팅 규칙의 부모 ActivatedRoute를 표현합니다.|
|firstChild|현재 라우팅 규칙의 자식 라우팅 규칙 중 첫 번째 ActivatedRoute를 표현합니다.|
|children|현재 활성화된 라우팅 규칙에 있는 모든 자식 라우팅 규칙을 표현합니다.|


`ActivatedRoute`를 컴포넌트에 의존성주입(DI) 합니다.

```ts
...
import { ActivatedRoute } from '@angluar/router';

...
export class MyComponent {
  constructor(
    private route: ActivatedRoute, // 의존성 주입
  ){ }
  ...
}
```

#### 옵저버블로 취득

URL 경로가 변경되었지만, 활성화 대상 컴포넌트가 변경되지 않는 경우, 만약 활성화 대상 컴포넌트가 존재하면 다시 생성하지 않고 재사용합니다.  
**즉, 컴포넌트가 소멸되지 않은 상태에서 라우터 파라미터만 변경된 라우터 상태를 연속으로 수신할 수 있습니다.**

> 예를들어, 사용자의 입력에의해 URL 이 실시간으로 변경될 때 (검색과 같이) 해당 검색어에 필터링된 요소들을 나타낼 때에도 사용합니다. debounceTime 을 적용시키면 비용을 좀 더 최소화할 수 있을것 같습니다.

먼저 `:id` 로 라우트가 구성되어 있을 때 취득 하는 방법은 다음과 같습니다.

```ts
...
export class MyComponent implements OnInit {
  constructor(
    private route: ActivatedRoute, // 의존성 주입
  ) { }
  ngOnInit() {
    this.route.paramMap
      .subscribe((params) => this.id = +params.get('id')) // params.get('key') 을 통해 취득
  }
}
```

> **[Unary plus(+)](https://scotch.io/tutorials/javascript-unary-operators-simple-and-useful#toc-unary-plus-)**  
이 연산자는 number 로 바꾸어줍니다.

#### 특정 시점 취득
특정 시점의 상태만 조회하는 경우에는 `snapshot` 프로퍼티를 이용합니다. `snapshot` 프로퍼티는 옵저버블로 래핑되지 않은 `paramMap` 객체를 반환합니다.
```ts
ngOnInit() {
  ...
  this.id = +this.route.snapshot.paramMap.get('id'); // 스냅샷으로 획득
}
```

### 라우트 정적 데이터

Route 인터페이스의 data 프로퍼티는 컴포넌트로 전송할 라우트 정적 데이터(Route static data)로서 애플리케이션 운영에 필요한 데이터를 전달할 때 사용합니다.

예를들어 화면의 타이틀과 사이드바의 표시 여부를 전달하고싶을 때 라우트 구성을 다음과 같이 설정합니다.
```ts
const routes: Routes = [
  {
    path: 'foo',
    component: FooComponent,
    data: { // 데이터 설정
      title: 'Foo',
      sidebar: true,
    },
  },
];
```
라우트 파라미터와 라우트 정적 데이터를 둘다 받는 방법을 최종적으로 정리하면 다음과 같습니다.
```ts
...
// 라우트 파라미터 취득
this.id = +this.route.snapshot.paramMap.get('id');

// 라우트 정적 데이터 취득
this.data = this.route.snapshot.data;
```

## 자식 라우트
루트 컴포넌트 뿐 아니라 자식 컴포넌트들도 자신의 자식 컴포넌트들을 위한 `<router-outlet>` 을 가질 수 있습니다.
```
AppComponent <router-outlet>
 ├─ FooComponent <router-outlet>
 │   ├─ FooChild1Component
 │   ├─ FooChild2Component
 │   └─ ...
 │
 └─ BarComponent <router-outlet>
     ├─ BarChild1Component
     ├─ BarChild2Component
     └─ ...
```
AppComponent 의 `<router-outlet>` 에는 Foo, Bar 가 라우팅에 따라 렌더링되고, 각각의 Foo, Bar 컴포넌트도 자신의 자식들을 렌더링할 `<router-outlet>` 을 갖을 수 있습니다.

이러한 형태의 라우트 구성은 다음과 같습니다.
```ts
const routes: Routes = [
  {
    path: '',
    redirectTo: '/foo',
     pathMatch: 'full'
  },
  {
    path: 'foo',
    component: FooComponent,
    children: [ // 자식 라우트 구성
      { path: ':id', component: FooChild1Component, },
      { ... },
    ],
  },
  { ... },
]
```
**`children`프로퍼티를 통해 자식 라우트를 구성한것을 확인합니다.**

구성이 끝났으면 자식 라우팅이 필요한 위치에 `<router-outlet></router-outlet>` 을 넣습니다. 그러면 해당 위치에 자식 컴포넌트들이 렌더링됩니다.

## 모듈의 분리와 모듈별 라우터 구성

라우트도 모듈 단위로 구성이 가능합니다. 어떻게 분리를하고 합치는지 알아보겠습니다.

#### 1. 자식 라우팅 모듈 구성
모듈 단위로 라우팅 구성을 분리할 경우에는 `RouterModule.forChild` 메서드의 인자로 라우트 구성을 등록합니다.
```ts
// child-routing.module.ts
const routes: Routes = [...] // 자식 라우트 구성
@NgModule({
  ...
  imports: [ RouterModule.forChild(routes) ], // forChild 메서드 사용
})
```

#### 2. 자식 모듈에 자식 라우팅 모듈 등록
자식 모듈에 앞서 만들어 놓은 자식 라우팅 모듈을 임포트하여 등록합니다.
```ts
// child.module.ts
import { ChildRoutingModule } from 'path';
...
@NgModule({
  declarations: [ Components... ],
  imports: [ ChildRoutingModule ] // 라우팅 모듈 등록
})
export class ChildModule { }
```

#### 3. 루트 라우팅 모듈 구성
루트 라우팅 모듈을 `RouterModule.forRoot` 메서드를 이용해 루트 라우트 구성을 등록합니다.
```ts
// app-routing.module.ts
const routes: Routes = [...] // 루트 라우트 구성
@NgModule({
  ...
  imports: [ RouterModule.forRoot(routes) ], // forRoot 메서드 사용
})
```

#### 4. 루트 모듈에 라우팅 모듈들 등록
마지막으로 루트 모듈에 앞서 작성하였던 라우팅 모듈들을 등록해줍니다.

```ts
// app.module.ts
import { ChildRoutingModule } from 'path';
import { AppRoutingModule } from 'path';
...

@NgModule({
  ...
  imports: [
    AppRoutingModule,
    ChildRoutingModule,
    ...
  ]
  ...
})
...
```

## 라우트 가드
라우트 가드(Route Guard) 는 라우터를 통해 **컴포넌트나 모듈을 활성화할 때 / 컴포넌트에서 빠져나갈 때 권한 등을 체크하여 접근을 제어하는 방법입니다.**  
예를들어, 메인페이지로 넘어가기 전에 유저가 로그인을 했는지의 여부에 따라 redirect 를 할 수 있습니다.

Angular 는 가드를 위해 [5개의 인터페이스](https://angular.io/api/router#structures)를 제공합니다.

* [CanActivate](https://angular.io/api/router/CanActivate)
* [CanActivateChild](https://angular.io/api/router/CanActivateChild)
* [CanLoad](https://angular.io/api/router/CanLoad)
* [Resolve](https://angular.io/api/router/Resolve)
* [CanDeactivate](https://angular.io/api/router/CanDeactivate)

### CanActivate
CanActivate 가드는 해당 뷰(컴포넌트)로의 접근 권한을 제어합니다.

```ts
// auth.guard.ts
...
@Injectable()
export class AuthGuard implements CanActivate { // CanActivate 인터페이스
  constructor(
    private route: Router,
    private auth: AuthService,
  ){ }

  CanActivate() {
    if (!this.auth.isAuthenticated) {
      // 유효하지 않을 경우
      this.router.navigate(['login']);
      return false;
    }
    return true;
  }
}
```
```ts
// 라우트 구성
...
{
  path: 'user',
  component: UserComponent,
  canActivate: [ AuthGuard ] // 접근제한
}
```
라우트 구성에 canActivate 프로퍼티로 가드를 선언합니다. 이렇게 되면 해당 컴포넌트를 활성화 하기 전에 canActivate 에 등록된 가드를 실행시키고 그 결과값에 따라 라우팅 여부를 따집니다.

### CanActivateChild

CanActivateChild 가드는 자식 라우트를 활성화할 수 있는지를 결정합니다. 다시말해서 자식 컴포넌트로의 접근을 제어합니다.

```ts
// auth.guard.ts
...
@Injectable()
export class AuthChildGuard implements CanActivateChild {
  CanActivateChild () {
    ...
  }
}
```
```ts
// 라우트 구성
...
{
  path: 'user',
  component: UserComponent,
  canActivateChild: [ AuthChildGuard ], // 접근제한
  children: [ ... ]
}
```
마찬가지로 라우트 구성에 canActivateChild 프로퍼티로 가드를 선언하게되면 자식 컴포넌트를 활성화하기 전에 가드가 실행되고 그 결과값에 따라 라우팅 여부를 따집니다.

### CanLoad
CanLoad 가드는 모듈이 로드되기 전에 모듈을 활성화할 수 있는지 결정합니다. 애플리케이션을 실행할 때 모든 모듈을 미리 컴파일하지 않고 호출 시점에 컴파일하는 지연로딩(lazy loading) 을 사용하는 경우에 CanLoad 가드는 접근 권한이 없는 모듈을 컴파일하지 않습니다.

예를들어, 메인페이지는 로그인한 경우에만 들어갑니다. 앞에서 배운 `canActivate` 를 이용해 로그인페이지로 리다이렉트할 수 있지만 로그인이 되지 않은 상태임에도 불구하고 메인페이지 모듈은 로드되었습니다.(뷰에만 접근을 불가했기 때문) 로그인 했을 경우에만 로드를 하려면 `canLoad` 가드를 사용합니다.

```ts
// foo-guard.service.ts
...
@Injectable()
export class FooGuardService implements CanLoad {
  canLoad() {
    // ...
  }
}
```

```ts
// 라우트 구성
...
{
  path: 'foo',
  loadChildren: 'path/#FooModule', // 지연로딩 라우팅 규칙 설정
  canLoad: [ FooGuardService ] // canLoad 프로퍼티 등록
}
```

 **[지연로딩 라우팅 규칙 설정](https://angular.kr/guide/router#%EC%A7%80%EC%97%B0%EB%A1%9C%EB%94%A9-%EB%9D%BC%EC%9A%B0%ED%8C%85-%EA%B7%9C%EC%B9%99-%EC%84%A4%EC%A0%95)** 에 따르면 지연로딩을 사용할 때 children 프로퍼티 대신 loadChildren 을 사용히여 모듈 위치를 지정합니다. 그 위치는 애플리케이션 최상위 폴더부터 시작되는 위치이고 파일경로지정 후에는 `#` 구분자를 통해 모듈이름을 지정해줍니다.

### Resolve
Resolve 가드는 라우트의 뷰가 렌더링되기 전에 뷰렌더링에 반드시 필요한 데이터를 로드할 때 사용합니다. 주의할점은 반환하는 타입이 `true`, `false` 가 아니라 뷰 렌더링에 필요한 데이터를 반환합니다.

```ts
// foo-guard.service.ts
...
@Injectable()
export class FooGuardService implements Resolve {
  resolve() {
    // ...
    return someData; // 데이터 반환
  }
}
```

### CanDeactivate
CanDeactivate 가드는 뷰에서 빠져나갈 때(컴포넌트가 비활성화될 때) 사용합니다.

```ts
interface CanDeactivate<T> {
  canDeactivate(component: T, currentRoute: ActivatedRouteSnapshot, currentState: RouterStateSnapshot, nextState?: RouterStateSnapshot): Observable<boolean | UrlTree> | Promise<boolean | UrlTree> | boolean | UrlTree
```

예를들면 실수로 뒤로가기나 다른 링크를 눌러서 작성중인 페이지가 있다고 해보면, 해당 가드를 통해 유저에게 한번 더 물어볼 수 있습니다.

## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
