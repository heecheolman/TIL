<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 모듈
앵귤러의 모듈(NgModule) 은 관련이 있는 구성요소(컴포넌트, 디렉티브, 파이프, 서비스 등)를 하나의 단위로 묶는 메커니즘을 말합니다. 이 장에서는 모듈에 대해 다뤄보겠습니다.

## 📝 목차
* [모듈 살펴보기](#모듈-살펴보기)
* [`@NgModule` 데코레이터](#ngmodule-데코레이터)
* [라이브러리 모듈](#라이브러리-모듈)
* [모듈 분리](#모듈-분리)
  * [기능 모듈](#기능-모듈)
  * [공유 모듈](#공유-모듈)
  * [핵심 모듈](#핵심-모듈)
  * [폴더 구조](#폴더-구조)

## 모듈 살펴보기
레고를 조립하면 다양한 모양과 다양한 사이즈들이 나옵니다. 이것은 레고가 '재사용성'이 뛰어나기 때문입니다. 만약 레고의 한 블럭단위가 '창문', '집모양' 같은 형태였다면 만들 수 있는 결과물은 한정적이었을 것입니다. 애플리케이션 개발도 마찬가지입니다. **결합도를 낮추고 응집도를 높여야 바람직한 애플리케이션** 이 나올 수 있을 뿐 아니라 **더 많은 유연성을 갖습니다.**

앵귤러로 만든 애플리케이션은 적어도 하나 이상의 모듈들이 결합되어 만들어집니다. 적어도 하나 이상의 모듈을 갖는다는 것은 최상위 모듈이 존재한다는 것이며, 앵귤러에서는 이를 루트 모듈이라하고 실제로 루트 모듈은 `AppModule` 로 되어있습니다.

```ts
...
@NgModule({
  declarations: [...],
  imports: [...],
  providers: [...],
  bootstrap: [...]
})
export class AppModule { }
```

AppModule 을 export(내보내기) 하고 있습니다. 이 AppModule 즉, 루트모듈을 `main.ts` 에서 부트스트랩(가동) 합니다.

```ts
// main.ts
...
platformBrowserDynamic().bootstrapModule(AppModule) // 가동
  .catch(err => console.error(err));
```

## [`@NgModule` 데코레이터](https://angular.io/api/core/NgModule)
모듈 클래스는 `@NgModule` 데코레이터로 장식된 클래스인데 모듈의 설정 정보가 담겨있는 메타데이터 객체를 전달받아서 모듈을 생성합니다.

```ts
@NgModule({
  providers?: Provider[]
  declarations?: Array<Type<any>|any[]>
  imports?: Array<Type<any>|ModuleWithProviders|any[]>
  exports?: Array<Type<any>|any[]>
  entryComponents?: Array<Type<any>|any[]>
  bootstrap?: Array<Type<any>|any[]>
  schemas?: Array<SchemaMetadata|any[]>
  id?: string
})
```
이 중에서 중요한 4가지만 알아보겠습니다.
**providers** : 주입 가능한 객체(injectable object)입니다. 서비스 리스트들을 넣어 놓습니다.  
**declarations** : component, directive, pipe list 를 선언합니다.  
**imports** : 의존관계에 있는 Angular 라이브러리 모듈, 기능 모듈이라 불리는 하위 모듈, 라우팅 모듈, 서드파티 모듈들을 선언합니다.  
**bootstrap** : 루트 모듈에서 사용하는 프로퍼티입니다. App 의 entry point 인 루트 컴포넌트를 선언합니다.

## 라이브러리 모듈
라이브러리 모듈은 앵귤러가 제공하는 빌트인(내장) 모듈입니다.
```json
"dependencies": {
    "@angular/animations": "~7.1.0",
    "@angular/common": "~7.1.0",
    "@angular/compiler": "~7.1.0",
    "@angular/core": "~7.1.0",
    "@angular/forms": "~7.1.0",
    "@angular/platform-browser": "~7.1.0",
    "@angular/platform-browser-dynamic": "~7.1.0",
    "@angular/router": "~7.1.0",
    "core-js": "^2.5.4",
    "rxjs": "~6.3.3",
    "tslib": "^1.9.0",
    "zone.js": "~0.8.26"
  }
```
웹 애플리케이션의 경우 필수적으로 BrowserModule 을 import 해야합니다.
```ts
@NgModule({
  declarations: [...],
  imports: [BrowserModule],
  providers: [...],
  bootstrap: [...]
})
```
BrowserModule 은 필수 빌트인 디렉티브, 빌트인 파이프를 제공하는 CommonModule 을 내부에서 임포트합니다.

## 모듈 분리
애플리케이션이 복잡해지면 유지보수 측면에서 힘들어질 수 있습니다. 때문에 모듈을 잘 분리하는것이 중요한데 앵귤러는 모듈을 **기능 모듈, 핵심 모듈, 공유 모듈로 분리합니다.**

**기능 모듈(feature module)** : 관심사가 유사한 구성요소로 구성한 모듈 (예: 특정 화면)  
**공유 모듈(shared module)** : 애플리케이션 전역에서 공유할 구성요소 (예: 애플리케이션 전역에서 사용하는 컴포넌트, 디렉티브, 파이프 등)  
**핵심 모듈(core module)** : 애플리케이션 전역에서 공통으로 사용할 구성요소 (예: 데이터 서비스, 인증 서비스, 인증 가드 등)

### 기능 모듈
관심사가 유사한 구성요소들을 **그룹화** 한 하위 모듈을 생성하고 상위 모듈은 생성된 하위 모듈들을 import 하여 사용합니다. 일반적으로 기능 모듈은 특정 화면 단위를 기준으로 구성합니다.

**생성**
```bash
$ ng generate module <module-name>
# 축약형
$ ng g m <module-name>
```

```ts
// mymodule.module.ts
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

@NgModule({
  declarations: [],
  imports: [
    CommonModule
  ]
})

export class MyModule { }
```
angular-cli 를 통해 명령어를 입력하면 위의 코드처럼 `mymodule.module.ts` 파일이 생성됩니다. 루트 모듈에 BrowserModule 이 있으므로 내부에서는 CommonModule 을 임포트합니다.

> CommonModule 에는 ngIf ngFor 와 같은 필수 빌트인 디렉티브들이 들어있습니다.

```
RootModule
  ├─ imports: Another Modules
  ├─ ...
  └─ bootstrap: 가동할 컴포넌트 등록

    Another Modules
      ├─ declarations: Using Components
      ├─ imports: 필수 빌트인 디렉티브가 있는 CommonModule imports
      └─ exports: 다른곳에서 사용될 컴포넌트들 등록
```

대략적인 구조는 위의 구조 입니다.

### 공유 모듈
애플리케이션 전역에서 공유할 구성요소들로 구성한 모듈, 다른 모듈에서 공통으로 사용됩니다. 전역에서 사용되는 컴포넌트, 디렉티브, 파이프 등이 대상입니다. 공유모듈은 루트 모듈에 직접 임포트 되지 않고 기능 모듈에 의해 필요한경우 임포트되어 사용됩니다.

> 만약, 웹앱 전체에서 사용되어야할 사이드바 혹은 헤더들 같은 경우는 공유되는 컴포넌트이므로 공유모듈 안에 넣습니다.

```bash
$ ng generate module shared
# 축약형
$ ng g m shared
```

그러면 이제 shared 폴더에는 `shared.module.ts` 파일이 생성됩니다. 이 공유 모듈을 앞서 말했듯이 공유되는 컴포넌트들을 모아놓습니다.

```ts
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

@NgModule({
  declarations: [공유될 컴포넌트 선언],
  imports: [
    CommonModule
  ],
  exports: [공개될 컴포넌트]
})
export class SharedModule { }
```

### 핵심 모듈
핵심 모듈(core module) 은 애플리케이션 전역에서 공통 사용할 구성요소들로 구성한 모듈로써 **루트 모듈에 등록합니다.** 공유모듈과 유사하지만 차이점은 핵심 모듈은 전역에서 관리되어 싱글톤이고 공유모듈은 기능 모듈에서 필요한경우 import 하여 사용합니다.

```bash
$ ng generate module core
# 축약형
$ ng g m core
```

> 핵심 모듈에서 만약 빌트인 디렉티브나 파이프를 사용하지 않는다면 `CommonModule` 을 제거합니다.

### 폴더 구조
```
src
 └─ app
     ├─ core
     │   ├─ services/
     │   └─ core.module.ts
     ├─ shared
     │   ├─ pipes/
     │   ├─ directives/
     │   ├─ components/
     │   └─ shared.module.ts
     ├─ components
     │   └─ my-component/
     ├─ interfaces
     │   └─ my-interface.ts
     ├─ app.component.ts
     └─ app.module.ts
```

제가 생각하는 구조입니다. 하지만 이것이 절대 정답은 아닙니다. 폴더 구조는 협업의 요소도 고려해야합니다. 그렇기 때문에 각자 프로젝트에 맞는 폴더구조를 사용하는것이 좋다고 생각합니다.


## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
