# Angular 의존성 주입 (Dependency Injection)

## 1. use Class

가장 일반적인 프로바이더로 클래스의 인스턴스를 의존성 주입하기 위한 설정 등록.

```ts
// 주입할 인스턴스 리스트
providers: [MyService1, MyService2, ...],

// 아래의 코드와 같음
providers: [
  {
    provider: MyService1,
    useClass: MyService1,
  },
  {
    provider: MyService2,
    useClass: MyService2,
  },
]
```

**'useClass' 로 생성한 인스턴스를 'prov{ider' 이름의 토큰으로 인젝터의 컨테이너에 등록하고, 검색할 것이라는 뜻입니다.**


## 2. use Value

클래스의 인스턴스가 아닌 문자열이나 객체 리터럴과 같은 값을 의존성 주입하기 위한 설정 등록.


#### 객체리터럴의 경우
```ts
export class AppConfig  {
  url: string;
  port: string;
}
export const MY_APP_CONFIG: AppConfig = {
  url: 'https://~~',
  port: '5000',
}

// foo.component.ts
...
constructor(public appConfig: AppConfig) {
  ...
}
```

#### 객체리터럴이 아닌 문자열, 숫자, 함수일 경우

```ts
providers: [
  { provide: 'API_URL', useValue: 'http://somewhere.io' },
  { provide: 'API_PORT', useValue: 5000 },
  { provide: 'API_PROD', useValue: false },
]

// foo.component.ts
export class FooComponent {
  constructor(
//  private apiUrl: 'API_URL'  ----> API_URL 은 타입이 아닙니다.
    @Inject('API_URL') private apiUrl: string,
    @Inject('API_PORT') private apiPort: number,
    @Inject('API_PROD') private apiProd: boolean,
  ) { }
}
```
> 주입 대상 타입이 클래스이면 Angular에 의해 암묵적으로 클래스를 `@Inject` 데코레이터로 전달하기 때문에 생략해도 됩니다.

#### 인젝션 토큰

단순히 문자열로 구분하려한다면 중복의 위험성이 있기때문에 중복을 피하기 위해서는 인젝션 토큰(Injection Token) 을 사용합니다.

```ts
import { InjectionToken } from '@angular/core';

export interface AppConfig {
  url: string;
  port: number;
}
export const MY_APP_CONFIG: AppConfig = {
  url: 'https://~~',
  port: '5000',
}

// es6 의 symbols 와 같은 기능 (유니크한 값)
export const APP_CONFIG = new InjectionToken<AppConfig>('app.config');
export const AppConfigProvider = {
  provide: APP_CONFIG,
  useValue: MY_APP_CONFIG,
};
```

## 3. use Factory

의존성 인스턴스를 생성할 때 어떠한 로직을 거쳐야하면 팩토리함수를 이용합니다.

```ts
providers: [
  {
    provide: MyService,
    useFactory: (isDev: boolean) => isDev
      ? new MockUserService()
      : new UserService(),
    deps: ['isDev'] // 팩토리 함수에 주입할 프로바이더의 토큰
  }
]
```
`isDev` 값이 true 라면 가짜데이터를 주입시키고, 그렇지 않다면 진짜데이터를 주입

## 4. use Existing

이미 존재하는 provider 를 새로운 provide 토큰으로 사용하려면 `useExisting` 을 사용합니다.
```ts
providers: [
  { provide: MyService, useClass: MyService },
  { provide: MyFooService, useClass: MyService },
]
```

> 근데 이렇게 사용해야하는 적절한 상황을 잘 모르겠다.
