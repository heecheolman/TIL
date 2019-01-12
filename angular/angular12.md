<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 서비스
컴포넌트는 뷰(view) 를 생성하고 관리하는것이 주된 역할입니다. 컴포넌트를 만들 때 주 관심사(뷰를 관리) 이외의 서버 통신 등과 같은 기능들이 들어가있다면 독립적이지 못하게됩니다. 때문에 서비스로 따로 빼는것이 컴포넌트의 재사용성을 높여줍니다.

이 장에서는 서비스에 대해서 알아보겠습니다.

## 📝 목차
* 서비스란?
* 의존성 주입
* 서비스 생성과 사용
* 인젝터와 인젝터 트리
  * 인젝터
  * 인젝터 트리
* 프로바이더
  * 클래스 프로바이더
  * 값 프로바이더
  * 팩토리 프로바이더

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


### 값 프로바이더

### 팩토리 프로바이더

## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
* [Angular 공식 홈페이지 - services](https://angular.io/guide/architecture-services)
* [Angular - Service](https://moon9342.github.io/angular-lecture-data-share-service)
