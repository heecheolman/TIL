<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 서비스
컴포넌트는 뷰(view) 를 생성하고 관리하는것이 주된 역할입니다. 컴포넌트를 만들 때 주 관심사(뷰를 관리) 이외의 서버 통신 등과 같은 기능들이 들어가있다면 독립적이지 못하게됩니다. 때문에 서비스로 따로 빼는것이 컴포넌트의 재사용성을 높여줍니다.

이 장에서는 서비스에 대해서 알아보겠습니다.

## 📝 목차
* [서비스란?](#서비스란)
* [의존성 주입](#의존성-주입)
* [서비스 생성과 사용](#서비스-생성과-사용)
* [인젝터와 인젝터 트리](#인젝터와-인젝터-트리)
  * [인젝터](#인젝터)
  * [인젝터 트리](#인젝터-트리)
* [프로바이더](#프로바이더)
  * [클래스 프로바이더](#클래스-프로바이더)
  * [값 프로바이더](#값-프로바이더)
    * [인젝션 토큰](#인젝션-토큰)
  * [팩토리 프로바이더](#팩토리-프로바이더)
* [선택적 의존성 주입](#선택적-의존성-주입)
* [서비스 중재자 패턴](#서비스-중재자-패턴)

## 서비스란?
컴포넌트의 주요 관심사(뷰를 관리) 이외의 기능은 애플리케이션의 공통 관심사인 경우가 많습니다. 이렇게 애플리케이션의 공통 관심사를 '서비스'라고 합니다. 서비스로 분리하게되면 컴포넌트는 명확히 자신의 관심사에 집중되고 서비스는 서비스대로 분리되어 일관성있는 애플리케이션이 만들어집니다.

**재사용성 up, 복잡도 down**

## 의존성 주입

의존성 주입(DI: Dependency Injection)을 들어가기에 앞서 서비스가 분리되어 있고 해당 서비스를 가져다 쓰는 코드를 보겠습니다.

```ts
class MyComponent {
  constructor() {
    MyService myService = new MyService();
    myService.getSomethingData();
  }  
}
```
컴포넌트의 생성자 내부에서 서비스를 생성하여 이용하고 있습니다. 이렇게되면 컴포넌트는 서비스에 의존하게 됩니다. 이런 용어를 '의존관계(Dependency Relationship)에 있다' 라고 합니다.

이런 의존관계를 해결하는 방법 '의존성 주입' 입니다. 앵귤러 프레임워크에서는 컴포넌트가 직접 서비스를 `new` 하여 사용하는것이 아니라 **'서비스를 컴포넌트가 이용할 수 있도록 객체를 생성해서 컴포넌트에 넣어주는(주입) 방식'** 입니다.

## 서비스 생성과 사용

```bash
$ ng generate service my-service
# 축약형
$ ng g s my-service
```
위의 코드를 실행하면 아래와 같은 서비스가 만들어집니다.

```ts
// my-service.service.ts
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class MyService {
  constructor() { }
}
```
* `@Injectable` 데코레이터 아래의 `MyService` 클래스는 의존성 주입이 가능한 클래스임을 나타냅니다.
* `providedIn` 프로퍼티를 'root' 로 설정하면 애플리케이션의 모든 구성요소에 싱글턴 전역 서비스를 주입할 수 있습니다.

그리고 이렇게 의존성 주입 가능한 서비스가 만들어졌다면 사용할 컴포넌트에서 다음과 같이 사용합니다.
```ts
// MyComponent.component.ts
import { MyService } from 'path'; // MyService 임포트
// ...
export class MyComponent {
  constructor(
    private myService: MyService, // MyService 를 이용할 프로퍼티 등록
  ) { }
}
```
기존에 `constructor` 내부에서 `new` 키워드를 통해 서비스를 생성해 이용하는 방법과는 다릅니다.

앵귤러 프레임워크는 내부적으로 해당 서비스(Injectable)를 컴포넌트가 사용할 수 있도록 주입해줍니다. 그리고 컴포넌트의 `constructor` 에서 받아줍니다. 그리고 해당 서비스를 이용합니다 :)

![이미지](https://angular.io/generated/images/guide/architecture/dependency-injection.png)

> 서비스를 컴포넌트에 주입하는 그림  
출처: 앵귤러 공식 사이트  


> 필요한 의존성을 요청하고 프레임워크가 제어권을 갖는 주체로 동작해 요청받은 인스턴스를 생성하여 전달하는 것을 **제어권의 역전(IoC: Inversion of Control)** 라고 합니다.

```ts
import { MyService } from 'path'; // MyService 임포트
// ...
export class MyComponent {
  constructor(
    private myService: MyService, // MyService 를 이용할 프로퍼티 등록
  ) { }

  // 서비스를 이용하는 메서드
  myMethod() {
    this.myService.somethingService();
  }
}
```

## 인젝터와 인젝터 트리
### 인젝터
앵귤러는 내부적으로 의존성 주입 요청에 의해 주입되어야할 인스턴스가 있다면 인젝터(Injector)에게 요청합니다. 그리고 인젝터는 컴포넌트와 모듈 레벨로 존재하며 요청에 의해 '프로바이더'를 검색하고 인스턴스를 생성하여 의존성 인스턴스를 주입합니다.

**그렇다면 매번 생성하면 비효율적이지 않은가?**  
비효율적입니다. 그래서 인젝터는 의존성 주입 요청을 받으면 프로바이더를 참조해 '요청'된 인스턴스가 있는지 **검색** 합니다.  
인젝터가 **어떻게 검색** 하는지 살펴보면 다음과 같습니다.

1. 검색 시 프로바이더의 `provide` 프로퍼티값을 토큰으로 사용합니다. (기존에 생성된 인스턴스는 프로바이더의 토큰을 키로 컨테이너에 저장되어 있습니다.)
2. 만약 컨테이너에 요청한 인스턴스가 존재한다면 해당 인스턴스를 주입합니다.
3. 그렇지 않다면 `useClass` 프로퍼티를 참조해 인스턴스를 생성하고 토큰을 키로 컨테이너에 추가한 후, 해당 인스턴스를 주입 합니다.

```ts
// pseudo code 표현한다면...

if (Injector.hasToken(req.token)) {
  return Injector.getService(req.token);
} else {
  const newService = new ServiceName();
  Injector.registContainer(req.token, newService);
  return Injector.getService(req.token);
}
```


![이미지](https://angular.io/generated/images/guide/architecture/injector-injects.png)

> 인젝터는 프로바이더를 키로 갖는 인스턴스들을 컨테이너 안에 갖고 있습니다. 그리고 요청된 토큰이 컨테이너 안에 존재한다면 해당 인스턴스를 주입시켜줍니다.  
출처: 앵귤러 공식 사이트  

### 인젝터 트리
컴포넌트는 트리구조입니다. 그리고 모든 컴포넌트는 각각 하나의 인젝터를 가지고 있기 때문에 컴포넌트 트리와 동일한 구조의 인젝터 트리가 생성됩니다.

인젝터 트리구조를 통해 인젝터가 프로바이더를 찾는 과정을 알아보겠습니다.

<img src="https://poiemaweb.com/img/injector-tree.png" style="width: 400px;">  
출처: PoiemaWeb

1. ChildComponent 인젝터가 ChildComponent 에서 주입대상 프로바이더를 검색 -> 실패 -> 상위컴포넌트로 이동
2. ParentComponent 인젝터가 ParentComponent 에서 주입대상 프로바이더를 검색 -> 실패 -> 상위컴포넌트로 이동
3. AppComponent 인젝터가 AppComponent 에서 주입대상 프로바이더를 검색 -> 실패 -> **AppModule 에게 주입 요청**
4. 프로바이더를 찾았으므로 해당 프로바이더를 사용해 인스턴스를 검색해 ChildComponent 에 주입


#### 알수있는 사실
1. 컴포넌트의 프로바이더에 등록되어 있는 서비스는 자신과 하위 컴포넌트에 주입할 수 있는 로컬 서비스
2. 루트 모듈의 프로바이더에 등록된 서비스는 애플리케이션 '전역'에서 주입할 수 있는 전역 서비스


## 프로바이더

앵귤러에서 서비스가 되는 '파일만' 생성하고는 알지 못합니다. 해당 서비스를 앵귤러에게 알려 주입을 지시해야하는데 이러한 지시를 '프로바이더' 라고합니다.

프로바이더를 사용하는 3가지 종류를 알아보겠습니다.
* 클래스 프로바이더(Class provider)
* 값 프로바이더(Value provider)
* 팩토리 프로바이더(Factory provider)

### 클래스 프로바이더
providers 프로퍼티는 제공할 인스턴스의 클래스 리스트로 구성된 배열을 값으로 갖습니다.
```ts
// 주입할 인스턴스의 클래스 리스트
providers: [MyService]
```
```ts
providers: [{
  provide: MyService, // 토큰
  useClass: MyService // 의존성 인스턴스를 새엇ㅇ할 클래스
}]
```

아래의 코드는 위의 코드와 동일합니다. 풀어서 사용했을 뿐입니다.

### 값 프로바이더
클래스의 인스턴스가 아닌 문자열이나 객체 리터럴과 같은 값을 의존성 주입하기 위한 설정을 등록합니다.
예를들어,
```ts
export class AppConfig {
  url: string;
  port: string;
}

// 주입할 값
export const MY_APP_CONFIG: AppConfig = {
  url: 'https://';
  port: '5000';
}
```
객체 리터럴을 값으로 갖습니다.

```ts
import { AppConfig, MY_APP_CONFIG } from 'path';

@Component({
  ...
  providers: [
    {
      provide: AppConfig,
      useValue: MY_APP_CONFIG
    }
  ]
})
export class MyComponent {
  constructor(
    private appConfig: AppConfig // 주입
  ) { }
}
```

값이 여러개일수도 있다.
```ts
providers: [
  { provide: 'API_URL', useValue: 'https://...'},
  { provide: 'API_PORT', useValue: 5000 },
  { provide: 'API_PROD', useValue: false },
]
```
**클래스 이외의 토큰은 명시적으로 `@Inject` 데코레이터를 선언해야합니다.**
```ts
constructor(
  @Injector('API_URL') public apiUrl: string,
  @Injector('API_PORT') public apiPort: number,
  @Injector('API_PROD') public apiProd: boolean,
) { }
```

#### 인젝션 토큰
값 프로바이더를 사용할 경우에는 중복된 토큰이 있을 수 있습니다. 때문에 인젝션 토큰(Injection Token) 을 이용해서 프로바이더에 등록해야합니다.

> 인터페이스를 프로바이더의 토큰으로 등록하려하면 에러가 납니다. 그 이유는 TS 의 interface 는 자바스크립트로 트랜스파일링 되지 않기 때문입니다. 때문에 런타임에러가 나게 됩니다. --> 인젝션 토큰을 사용하자!

인젝션 토큰의 사용법입니다.
```ts
import { InjectionToken } from '@angular/core';

// 인터페이스
export interface AppConfig {
  url: string;
  port: string;
}

// 주입 값
export const MY_APP_CONFIG: AppConfig = {
  url: 'https://...',
  port: '5000',
};

// 인젝션 토큰 생성
export const APP_CONFIG = new InjectionToken<AppConfig>('app.config');

// 프로바이더
export const AppConfigProvider = {
  provide: APP_CONFIG,
  useValue: MY_APP_CONFIG
}
```
그리고 다음과 같이 주입대상의 토큰을 설정합니다.

```ts
import { AppConfig, APP_CONFIG, AppConfigProvider } from 'path';

@Component({
  ...
  providers: [ AppConfigProvider ]
})
export class MyComponent {
  constructor(
    @Inject(APP_CONFIG) public appConfig: AppConfig,
  ) { }
}
```

### 팩토리 프로바이더
인스턴스를 생성할 때 어떠한 로직을 거쳐야 한다면 팩토리함수를 사용합니다.
```
개발모드일시 -> 가상유저
배포모드일시 -> 실제유저
```

위의 과정을 거치는 팩토리 프로바이더를 만든다면

```ts
// 실제 유저를 반환하는 서비스
@Inectable()
export class UserService {
  getUser(): User {
    return new User('name', 'age');
  }
}
```
```ts
// 가상 유저를 반환하는 서비스
@Inectable()
export class MockUserService {
  getUser(): User {
    return new User('name', 'age');
  }
}
```

**user.service.provider.ts**
```ts
import { MockUserService } from 'path';
import { UserService } from 'path';

// 팩토리 함수 (로직)
const userServiceFactory = (isDev: boolean) => isDev
    ? new MockUserService()
    : new UserService();

// 팩토리 프로바이더
export const UserServiceProvider = {
  provide: UserService, // 최종적으로 생성될 인스턴스 타입
  userFactory: userServiceFactory, // 인스턴스 생성을 담당할 팩토리 함수
  deps: ['idDev'] // 팩토리 함수에 주입할 값 프로바이더의 토큰
}

// '팩토리 함수'에 주입할 값의 프로바이더
export const isDevProvider = {
  provide: 'isDev',
  useValue: false
} // isDev = false;
```

**deps 프로퍼티에는 팩토리 함수에 주입할 의존성의 토큰을 '배열'로 설정합니다.**
```ts
deps: ['idDev', ...] // 팩토리 함수에 주입할 값 프로바이더의 토큰
```

그리고 팩토리 프로바이더에 의해 주입될 서비스를 사용하는 컴포넌트는 다음과 같이 작성합니다.
```ts
import { isDevProvider, UserServiceProvider } from 'path';
import { UserService } from 'path';

@Component({
  ...
  providers: [
    isDevProvider,
    UserServiceProvider,
  ]
})
export class MyComponent {
  constructor(
    public userService: UserService
  ) { }
}
```

## 선택적 의존성 주입
프로바이더를 등록하지않으면 의존성 주입이 되지않아 런타임 에러가 발생하게 됩니다. 의존성 주입이 필수가 아닌경우는 `@Optional` 데코레이터를 사용하여 선택적임을 알려줍니다.

```ts
@Component({
  ...
  // providers: [MyService] -> 선택사항
})
class MyComponent {
  constructor(
    @Optional public myService: MyServices // @Optional 데코레이터 사용
  ){ }
}
```

## 서비스 중재자 패턴
부모-자식간 통신이 아닌 비-부모-자식간 통신이 있을 수 있습니다. 기존의 부모-자식간 컴포넌트의 상태 공유 방법은 `@Input` 데코레이터를 통한 프로퍼티 바인딩과 `@Output` 과 `EventEmitter` 를 사용하여 전달하였습니다.

컴포넌트는 트리구조를 이룹니다. 비-부모-자식간 통신을 할 때에는 두개의 컴포넌트의 공통 부모까지 가서 데이터를 공유해야하는데 이렇게 되면 불필요한 작업들(프로퍼티바인딩, 이벤트 등...)이 생기게 됩니다.

두 컴포넌트 사이에 공유되는 데이터를 서비스 내에 위치하게하면 해당 서비스를 통해 공유받고자하는 데이터를 주고받을 수 있습니다. 이를 '서비스 중재자 패턴' 이라고 합니다.

구조를 살펴보자면 다음과 같습니다.

```
        (데이터 공유)
        MyService
         /      \
        /        \
       /          \
      /            \
Component1     Component2
```
MyService 내에는 Component1 과 Component2 가 공유하고싶은 데이터를 갖고있으며 Component1 과 Component2 는 해당 서비스를 주입받아 이용합니다.

```ts
// myService.service.ts
@Injectable({
  providedIn: 'root' // 애플리케이션 전역 서비스임을 알림
})
export class MyService {
  sharedData: any; // 공유될 데이터
}
```

```ts
// Component 1
export class MyComponent1 {
  constructor(
    private myService: MyService
  )
  get data() {
    return this.myService.sharedData;
  }
  set data(newData: any) {
    this.myService.sharedData = newData;
  }
}
```

컴포넌트 1은 `getter/setter` 를 통해 서비스에 존재하는 공유될 데이터를 받아옵니다. 컴포넌트 2도 동일하게 작성하면 서로 데이터는 공유됩니다.


## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
* [Angular 공식 홈페이지 - services](https://angular.io/guide/architecture-services)
* [Angular - Service](https://moon9342.github.io/angular-lecture-data-share-service)
