# 실전 SPA상태관리 톺아보기 - 김동우님
#### SPA란
싱글 페이지 어플리케이션(Single Page Application) 의 약자로 전체 페이지를 새로 로드하는 대신 동적으로 현재 페이지를 다시 작성하여 사용자와 상호작용하는 웹 응용 프로그램 또는 웹 사이트


#### SPA 는 View Library 가 필요하다
* Angular : google
* React : Facebook
* Vue : Evan You

다음은 라이브러리 및 프레임워크의 **공통점** 이다.
1. 선언적 렌더링
2. virtual DOM
3. 컴포넌트 기반

> 김동우 님은 React 를 더 좋아하시어 React 의 상태관리툴들을 살펴봅니다.

### State Management 가 필요하다.
SPA 는 상태저장소가 없으면 컴포넌트 기반이기에 props 로 필요한 값들을 전달하는 형태로 진행되는데 하위 컴포넌트가 많아진다면 불필요한 작업들이 생길 수 있다.  
그래서 상태관리 라이브러리를 사용한다.

### 어떤것들이 있는가
1. Redux
2. React Context API
3. MobX
4. MobX State Tree

#### [Redux](https://redux.js.org/)
* SPA 를 위한 예측 가능한 상태 컨테이너
  * 결정적 뷰 렌더링
  * 결정적 상태 재현

  ##### 미들웨어들
    1. redux-thunk
      * 비동기를 위한 간단한 미들웨어
    2. redux-saga
      * 사이드 이펙트를 이용한 데이터 중앙제어
      * 중앙에서 action 을 watch 하여, 액션이 일어나면 side effect 를 발생시켜 데이터 제어를 시작한다.
      * ES6 Generator 를 사용하여 동작을 제어한다.
      * **장점**
        * 일관된 비동기 처리 제어로 앱의 데이터 흐름이 견고
        * 하나의 액션에서 파생되는 여러 작업을 처리하기 수월
      * **단점**
        * saga 를 배우는 과정이 고난
        * 액션을 작성하는데 더 많은 코드가 필요해짐.

    3. redux-observable

#### [React Context API](https://reactjs.org/docs/context.html)
react 16.3 에서 추가된 context 를 쉽게 생성할 수 있는 API
##### 장점
* 간단하게 적용 가능

##### 단점
* 스토어가 쉽게 비대해짐, 분리가 어려움
* 항상 모든 컴포넌트가 다시 렌더링


#### [MobX](https://github.com/mobxjs/mobx)
MobX 는 일관성없는 상태를 만들 수 없도록 상태 관리를 간단하게 만들었다. 어플리케이션 상태로부터 파생될 수 있는 모든것들을 자동으로 파생되도록 한다.
* functional reactive programming
* React 의 `setState` 가 필요하지 않음

개념적으로 MobX 는 어플리케이션을 **스프레드 시트** 로 간주한다.
![이미지](https://mobx.js.org/getting-started-assets/overview.png)

##### 장점
* 코드가 간단해 이해하기 쉽고 생산성이 좋다.
* 비동기 액션을 만들기 쉬움

##### 단점
* 문제가 발생했을 때 디버깅 하기 어려움
* React 라이프사이클과 혼합해 사용하기 어려웠다.


#### [MobX State Tree](https://github.com/mobxjs/mobx-state-tree)
* MobX-State-Tree(이하 MST)는 형태와 상태를 가짐  
* 정적으로 런타임에서 타입체킹과 함께 보호되는 Object 를 제공
* MST 나무로부터 불변하고, 구조적으로 공유되는 스냅샷을 자동으로 생성할 수 있음.
* MST 는 복잡한 데이터를 다루는 앱에 적합
* **MobX** 와 **Redux** 의 장점을 가지고있음

##### 장점
* 관계가 복잡한 데이터를 다루는데 수월
* 견고하고 버그가 적은 개발이 가능 (with TypeScript)

##### 단점
* 모델을 작성하는 것이 학습비용도 크고 까다로움
* 이렇게 까지 견고하게 해야하는지 계속 고민하게 됨


### Redux vs MobX
NPM 다운로드는 Redux 의 압승

### 비교 및 요약
사진은 김동우님의 발표자료중 일부 이며 문제가 있을시 삭제하겠습니다!

![이미지](https://t1.daumcdn.net/cfile/tistory/99AB66435BE7B17B1A)

![이미지](https://t1.daumcdn.net/cfile/tistory/992314435BE7B17C1D)



### 마무리
* 오버 엔지니어링을 경계해야한다.
* 소잡는 칼을 닭 잡는데 쓸 수 없다.
* 해결하고자 하는 문제, 팀의 현재 수준과 구성, 사용할 수 있는 자원 등을 고려해 적정한 상태관리 도구를 사용하는 것이 좋다.
* Redux 와 MobX 는 코드가 완전히 상이하다.

### 보너스
[ReactStateMuseum](https://github.com/GantMan/ReactStateMuseum) 에 방문하면 여러가지 상태관리 툴을 볼 수 있음.


### 나의 마무리
React 를 이제 공부하기 시작했는데 상태관리 툴에대해 짚어보니 어떤 특징이있는지 알게 되었다.
