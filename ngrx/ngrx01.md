
<div align=center>
  <img src="https://ngrx.io/assets/images/badge.svg" style="max-width: 100px">
</div>

# ngrx
ngrx 는 redux 의 영향을 받은 상태관리 라이브러리, NgRx 도큐멘트를 보고 작성합니다.

* **Actions**: 액션은 컴포넌트와 서비스로부터의 이벤트를 설명
* **State**: 상태변화는 reducers 함수에 의해 다뤄집니다. 그리고 그 최근 상태변화를 감지
* **Selectors**: 셀렉터는 상태를 선택


## redux 아키텍쳐
redux 의 영향을 받은 ngrx 의 흐름을 살펴보기전에 redux 에 영감을 받았다고 하니 redux의 아주 간단한(?) 흐름을 살펴봅니다.

1. 애플리케이션이 행동(action) 을 함
2. 행동(action)이 발송(dispatch)
3. reducer가 store 의 상태(state)를 변경
4. 해당 state 의 변화를 감지하여 state를 가져옴

## Actions

액션들은 NgRx 에서 주요 요소중 하나입니다. 페이지에서 유저와의 상호작용, 네트워크 요청 등등에 대한 애플리케이션에서 일어날 수 있는 고유한 이벤트들을 표현합니다. 즉, 이러한 많은 이벤트들은 액션에 의해 설명됩니다.

**액션 인터페이스**
```ts
interface Action {
  type: string;
}
```
액션의 인터페이스를 `implements` 하여 type 을 구하고 액션에 필요한 payload 가 필요할경우 생성자에 넣어줍니다.

```ts
import { Action } from '@ngrx/store';

export enum ActionsTypes {
  Login = '[Login Page] Login';  // 이벤트를 설명 -> [Source] Event
}

export class Login implements Action {
  readonly type = ActionsTypes.Login;

  constructor(
    public payload: { username: string, password: string } // 로그인에 필요한 정보를 전달받음
  ) { }
}
```
컴포넌트에서는 위의 로그인액션을 하고 사용시에는 `dispatch` 메서드를 통해 호출하고 파라미터로 사용하고자하는 액션 인스턴스를 전달합니다. 그리고 액션에 필요한 정보들을 페이로드로 넘겨줍니다.

```ts
...
click(username: string, password: string) {
  // new Login 행동에 필요한 username 과 password 전달
  store.dispatch(new Login({ username, password }));
}
```

### 액션을 작성할 때 팁

* Devide - 이벤트 소스를 기반으로 액션들을 카테고리화
* Many - 액션을 많이 쓰면 애플리케이션의 흐름을 설명하기 좋습니다.


## Reducers

Reducers 는 애플리케이션에서 어느 상태에서 다음 상태로 넘어가기 위한 '변이' 입니다.(상태변화를 일으킨다) 이 때 중요한것은 일관성있게 행동해야 한다는것입니다. 즉, 동일한 input에 대하여 동일한 output을 내놓는다는 특징이 있습니다. 먼저, 예시를 위해 다음과 같은 actions 를 작성합니다.

```ts
// scoreboard-page.actions.ts
import { Action } from '@ngrx/store';

export enum ActionTypes {
  IncrementHome = '[Scoreboard Page] Home Score',
  IncrementAway = '[Scoreboard Page] Away Score',
  Reset = '[Scoreboard Page] Score Reset',
}

export class IncrementHome implements Action {
  readonly type = ActionTypes.IncrementHome;
}

export class IncrementAway implements Action {
  readonly type = ActionTypes.IncrementAway;
}

export class Reset implements Action {
  readonly type = ActionTypes.Reset;

  constructor(public payload: { home: number; away: number }) {}
}

export type ActionsUnion = IncrementHome | IncrementAway | Reset;
```

#### 1. state 형태 정의

각각의 리듀서는 액션이 필요합니다. 각 액션에대한 상태변화가 다르기때문입니다.

```ts
import * as Scoreboard from '../actions/scoreboard-page.actions'; // 임포트

// 상태 정의
export interface State {
  home: number;
  away: number;
}
```

#### 2. state 초기화
상태에 대한 초기값을 정해줍니다. 마치 변수 초기화같습니다.
```ts
export const initialState: State = {
  home: 0,
  away: 0,
};
```


#### 3. reducer 함수 작성
이제 액션에 따른 상태변화를 작성합니다.
```ts
export function reducer(
  state = initialState, // 디폴트 파라미터
  action: Scoreboard.ActionsUnion, // 올 수 있는 액션들
): State {
  switch (action.type) { // 액션 타입에 따라 분기
    case Scoreboard.ActionTypes.IncrementHome: {
      return {
        ...state,
        home: state.home + 1,
      };
    }

    case Scoreboard.ActionTypes.IncrementAway: {
      return {
        ...state,
        away: state.away + 1,
      };
    }

    case Scoreboard.ActionTypes.Reset: {
      return action.payload;
    }

    default: {
      return state;
    }
  }
}
```
`Scoreboard.ActionsUnion` 을 통해 스코어보드에 올 수 있는 행동들을 제한하여 타입세이프하게 되었습니다.

#### 4. root state 에 등록
리듀서를 전역으로 등록하고 싶다면 `StoreModule.forRoot()` 메서드를 통해 imports 합니다.
```ts
...
import { StoreModule } from '@ngrx/store';
import { scoreboardReducer } from 'path';

@NgModule({
  imports: [
    StoreModule.forRoot({ game: scoreboardReducer }),
    ...
  ]
})
...
```
```
{
  game:
}
```
`forRoot()` 메서드를 이용하면 `key: value` 형태로 상태가 정의되고, `global providers` 가 됩니다. 보통 `forRoot()` 을 이용하게되면 애플리케이션 시작과 동시에 정의되어 일반적으로 애플리케이션이 시작과 동시에 필요한 상태일경우 등록해줍니다.


#### Feature state 로 등록하는 방법

Feature state 도 root state 와 동일하게 작동하지만 앱 내에 특정 기능영역으로 등록하고 싶을 때 사용합니다. 그리고 객체의 `key: value` 형태를 갖습니다.

`스코어보드 모듈`을 작성하고 `StoreModule.forFeature()` 메서드를 통해 `scoreboardReducer` 를 `game` 이라는 키로 저장합니다.
```ts
// scoreboard.module.ts
...
import { StoreModule } from '@ngrx/store';
import { scoreboardReducer } from './reducer';

@NgModule({
  imports: [StoreModule.forFeature('game', scoreboardReducer)], // 등록
})
export class ScoreboardModule {}
```
이제 `ScoreboardModule` 을 `AppModule` 에 등록해줍니다.
```ts
// app.module.ts
...
@NgModule({
  imports: [StoreModule.forRoot({}), ScoreboardModule],
})
```
그러면 state 는 다음과 같이 관리됩니다.
```ts
{
  game: { home: 0, away: 0 }
}
// game 이라는 키로 등록됨
```

애플리케이션이 방대해질 경우 모듈단위로 나누어 `feature` 로 등록해야합니다.

## Selectors

`createSelector` 와 `createFeatureSelector` 함수를 이용하면 selector 함수가 호출 된 가장 최근 state 를 가져옵니다. 메서드 이름 그대로 셀렉터를 만들어주는 함수

```ts
import { createSelector } from '@ngrx/store';

export interface FeatureState {
  counter: number;
}

export interface AppState {
  feature: FeatureState;
}

export const selectFeature = (state: AppState) => state.feature;

export const selectFeatureCount = createSelector(
  selectFeature, // 호출 후 state 는 FeatureState 임
  (state: FeatureState) => state.counter,
)
```

### createSelector
`createSelector` 는 최대 8개의 선택기 함수를 파라미터로 갖을 수 있습니다. `createSelector` 의 마지막 파라미터인  `projector()` 콜백함수는 props 를 매개변수로 받습니다.
```ts
export function createSelector<State, S1, S2, S3, Result>(
  s1: Selector<State, S1>,
  s2: Selector<State, S2>,
  s3: Selector<State, S3>,
  ...
  s8: Selector<State, S8>,
  projector: (s1: S1, s2: S2, s3: S3) => Result
): MemoizedSelector<State, Result>;
```

```ts
// example
export const getSelectorFooBar = createSelector(
  getFoo,
  getBar,
);

export const getSelectorFooBarPizzaResult = createSelector(
  getFoo,
  getBar,
  getPizza,
  (foo, bar, pizza) => { // projector()
    // some code
    return result;
  }
)
```

### createFeatureSelector

`createFeatureSelector` 를 이용해 feature 단위로 구성된 상태의 셀렉터를 생성합니다.

```ts
import { createSelector, createFeatureSelector } from '@ngrx/store';

export interface FeatureState {
  counter: number;
}

export interface AppState {
  feature: FeatureState;
}

export const selectFeature = createFeatureSelector<AppState, FeatureState>('feature');

export const selectFeatureCount = createSelector(
  selectFeature,
  (state: FeatureState) => state.counter
);
```


### memoization(computed)

셀렉터는 게산한 값을 캐싱합니다. createSelector 는 `defaultMemoized` 함수를 이용해 이전값과 현재값이 같은지 비교후 다를경우 계산을 합니다. 때문에 selector 를 이용해 컴포넌트에서 받아서 사용하는것이 더 좋습니다.

```ts
// platform : selector.ts
export function defaultMemoize(
  projectionFn: AnyFn,
  isArgumentsEqual = isEqualCheck,
  isResultEqual = isEqualCheck
): MemoizedProjection { ... }
```

```ts
// platform : selector.ts
export function isEqualCheck(a: any, b: any): boolean {
  return a === b;
}
```

## 마무리

아직 실사용을 많이 안해봐서 이해가 안되는부분이나 어색한 부분이 있지만 차근차근 해나가면서 이 개념들을 바탕으로 정리해나가야겠다. 

## 참고문서
* [Ngrx 공식문서](https://ngrx.io/guide/store/selectors)
* [NGRX Store: Understanding State Selectors](NGRX Store: Understanding State Selectors)
* [NgRx selectors 풍부하게 활용하기 - Kyungmin Na](https://medium.com/pplink/ngrx-selectors-%ED%92%8D%EB%B6%80%ED%95%98%EA%B2%8C-%ED%99%9C%EC%9A%A9%ED%95%98%EA%B8%B0-564743c56d08)
* [ngrx architecture를 이용하여 angular 앱을 더 기분 좋게 만들기 - hyeonseok Ahn](https://medium.com/pplink/ngrx-architecture%EB%A5%BC-%EC%9D%B4%EC%9A%A9%ED%95%98%EC%97%AC-angular-%EC%95%B1%EC%9D%84-%EB%8D%94-%EA%B8%B0%EB%B6%84-%EC%A2%8B%EA%B2%8C-%EB%A7%8C%EB%93%A4%EA%B8%B0-9182c582a113)
