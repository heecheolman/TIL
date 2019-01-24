<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# 앵귤러 프로젝트 시작하기
앵귤러 프로젝트를 시작하기 앞서 `Angular CLI` 를 설치하도록 합니다. CLI 는 Command Line Interface 의 약자로 명령어를 통해 앵귤러 프로젝트를 생성, 실행, 빌드할 수 있습니다.


## 목차
* [Angular CLI 특징](#angular-cli-특징)
* [Angular CLI 설치](#angular-cli-설치)
* [프로젝트 생성](#프로젝트-생성)
* [폴더 구조](#폴더-구조)
  * [큰 구조](#큰-구조)
  * [src 내부 구조](#src-내부-구조)
* [Angular 애플리케이션 흐름](#angular-애플리케이션-흐름)
  * [빌드 과정](#빌드-과정)
* [마무리](#마무리)
* [참고문서](#참고문서)

## Angular CLI 특징

* Angular 프로젝트 생성
* 컴포넌트, 디렉티브, 파이프, 서비스, 클래스, 인터페이스 등의 구성요소 추가
* dev server
* 테스트 환경 지원 (unit, e2e)
* 배포


## Angular CLI 설치
```bash
$ npm install -g @angular/cli
```

해당 명령어를 통해 Angular CLI 를 전역으로 설치했습니다.


## 프로젝트 생성

``` bash
$ ng new <project-name>
```
`$ ng new` 이후 프로젝트 이름을 설정합니다. 그렇게 되면 자동으로 앵귤러 프로젝트에 필요한 의존성 모듈들과 폴더 구조들이 생성됩니다.


## 폴더 구조
큰 폴더 구조는 다음과 같습니다. src 는 다음 섹션에서 자세히 다루겠습니다.

### 큰 구조
```
my-app/
├── .git/
├── e2e/
├── node_modules/
├── src/
├── .editorconfig
├── .gitignore
├── angular.json
├── package-lock.json
├── package.json
├── README.md
├── tsconfig.json
└── tslint.json
```

**`e2e/`**  
e2e 는 테스트 관련 파일입니다. e2e 테스트를 할 때 `protractor.conf.js` 가 참조됩니다.

**`node_modules/`**
`package.json` 의 의존성 모듈들이 담겨있는 폴더입니다. `install` 시 해당 폴더에 설치됩니다.

**`src/`**
프로젝트에 관련된 소스파일들이 담겨있는 폴더입니다.

**`.editorconfig`**
에디터에 대한 설정파일입니다. indent 스타일이나 사이즈와 같은것들을 설정할 수 있습니다.

**`angular.json`**
Angular CLI 를 위한 설정파일입니다. [Angular CLI Config Schecma](https://github.com/angular/angular-cli/wiki/angular-workspace) 에 자세히 나와있습니다.

**`package.json`**
프로젝트에 대한 개요 같은 파일입니다. `dependencies` 는 배포시 필요한 모듈들, `devDependencies` 에는 개발에 관련된 모듈목록이 담겨있습니다.

**`tsconfig.json`**
타입스크립트 컴파일 옵션을 설정하는 파일입니다.

**`tslint.json`**
타입스크립트 작성시 코딩컨벤션을 맞춰주는 linting 파일입니다.

### src 내부 구조
src 폴더의 내부구조입니다.
```
src/
├── app/
│   ├── app.component.css
│   ├── app.component.html
│   ├── app.component.spec.ts
│   ├── app.component.ts
│   └── app.module.ts
│
├── assets/
├── environments/
├── browserslist
├── favicon.ico
├── karma.conf.js
├── index.html
├── main.ts
├── polyfills.ts
├── styles.sass
├── test.ts
├── tsconfig.app.json
├── tsconfig.spec.json
└── tslint.json
```

#### `app/`
모든 컴포넌트의 부모 컴포넌트인 루트 컴포넌트를 구성합니다.

* app.component.ts : 루트 컴포넌트의 로직에 대한 부분입니다. 이름은 `AppComponent` 로 되어있습니다.
* app.component.css : 루트 컴포넌트에 대한 스타일입니다.
* app.component.html : 루트 컴포넌트에 대한 html 템플릿입니다.
* app.component.spec.ts : 루트 컴포넌트에 대한 유닛테스트 명세입니다.
* app.module.ts : 앵귤러 프로젝트에 필요한 모듈들의 집합을 `declarations` 에 모아놓습니다. 이름은 `AppModule` 입니다.

#### `assets/`
이미지파일들, 폰트 등 앱을 빌드할 시 필요한 자원들을 모아놓습니다.

#### `environments/`
빌드 시 개발/배포 용의 각 설정 파일을 담아놓습니다.

#### `browserslist`
프론트엔드 도구간 적용 대상 브라우저를 공유하는 라이브러리 설정 파일입니다.
> [github-browserslist](https://github.com/browserslist/browserslist) 에 자세히 나와있습니다.

#### `favicon.ico`
북마크바에 표시될 아이콘입니다.

#### `index.html`
메인 html 파일입니다. 앱에 접속시 해당 페이지를 가장 먼저 방문하는 디폴트페이지입니다. 루트 컴포넌트인 `<app-root>` 에 의해 로드되어 표시됩니다.

#### `karma.conf.js`
카르마 테스트를 위한 설정파일입니다.

#### `main.ts`
의존성 모듈 그래프의 진입점(entry)입니다.

#### `polyfill.ts`
크로스 브라우징을 위한 스크립트 파일입니다.

#### `styles.css`
앱 전역에 적용될 `css` 입니다. `sass` 나 다른 전처리언어를 사용할 수 있습니다.

#### `test.ts`
유닛테스트를위한 진입점입니다.

#### `tsconfig.app.json`, `tsconfig.spec.json`, `tslint.json`
타입스크립트 컴파일 옵션 설정 파일입니다. `my-project/tsconfig.json` 파일을 상속받습니다.


## Angular 애플리케이션 흐름

앵귤러 앱을 빌드하면 어떤과정이 일어나는지 그리고 빌드한 파일들을 살펴보고 실제로 어떻게 작동하는지 알아봅니다.

### 빌드 과정
`$ ng build` 라는 명령어를 통해 앱이 빌드됩니다.


#### 1. main.ts 읽어들이기
`angular.json` 내에 main 프로퍼티에 설정된 `main.ts` 파일을 읽어들여 빌드를 시작합니다.
```ts
// main.ts
// 생략
import { AppModule } from './app/app.module';

platformBrowserDynamic().bootstrapModule(AppModule)
  .catch(err => console.error(err));
```
`AppModule` 을 임포트합니다. 그리고 `.bootstrapModule(AppModule)`을 통해 가동합니다.  

#### 2. app.module 읽어들이기

`app.module.ts` 는 앱 전체의 설정정보를 갖고 있습니다.

```ts
// app.module.ts
// 생략
@NgModule({
  declarations: [],
  imports: [],
  providers: [],
  bootstrap: []
})
export class AppModule { }
```

##### app.module.ts -> declarations
`declarations` 속성은 배열인데 이 배열에 담을 수 있는 선언은 뷰 클래스입니다.. 즉, 컴포넌트들, 디렉티브, 파이프들 입니다.

##### app.module.ts -> imports
`imports` 속성은 배열인데 이 배열에 담을 수 있는 것은 `exports` 로 공개된 클래스를 다른 컴포넌트 템플릿의 `this` 모듈에 선언해서 사용할 때 추가해줍니다.

##### app.module.ts -> providers
`providers` 속성은 배열인데 앱에 필요한 서비스들을 넣습니다.

#### app.module.ts -> bootstrap
`bootstrap` 또한 배열입니다. 루트 컴포넌트인 메인 앱 뷰를 선언합니다.

> [Angular Bootstrapping](https://angular.io/guide/bootstrapping) 참고.

#### 3. 데이터 바인딩
각 컴포넌트는 다음과 같은 형태입니다.
```
└── mycomponent/
    ├── mycomponent.component.css
    ├── mycomponent.component.html
    ├── mycomponent.component.spec.ts
    └── mycomponent.component.ts
```
`*.component.ts` 에는 컴포넌트에 대한 로직이 들어있는 부분인데 이 부분에서 데이터 바인딩이 일어납니다. `*.component.html` 에 사용된 문법들이 `4과정의 번들링` 을 통해 바인딩됩니다.

#### 4. 번들링
`main.ts` 를 통해 `app.module`을 가동시켜 앱에 필요한 '것'들을 번들링합니다. 번들링도구는 `webpack` 을 사용합니다. 번들링하게되면 `dist` 폴더에 번들링된 자바스크립트 파일들이 생성되는데 다음과 같습니다.

* main.js
* polyfills.js
* runtime.js
* styles.js
* vendor.js

---

빌드 과정이 끝났습니다. 빌드가 성공적으로 끝났다면 프로젝트의 루트 디렉토리에 `dist` 폴더에 모이게 됩니다. 이미 한번 번들링 된 자바스크립트 파일들을 `index.html` 에서 간편하게 로드하여 앱이 실행됩니다.


## 마무리
잘못된 사항이 있다면 알려주시면 감사하겠습니다. 앵귤러를 배우는 입장에서 꼭 필요한 부분이라 생각되어 아는 선에서 최대한 깊게 파보았습니다. 테스트 관련은 아직 경험이 없어 추후에 따로 다루겠습니다. 감사합니다.

## 참고문서
* [Angular 공식 파일 구조 설명](https://angular.io/guide/file-structure)
* [Angular CLI - PoiemaWeb](https://poiemaweb.com/angular-cli)
