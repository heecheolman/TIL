# 웹팩 트리쉐이킹

## 트리 쉐이킹(Tree Shaking)이란?

트리 쉐이킹이라는 용어는 '나무를 흔들어 필요없는 것들을 떨어트리는 것' 이다. 코드에서 트리쉐이킹이란 불필요하게 사용되고 있는 코드들을 버려 용량을 최적화하는데 있다. 보통 유저가 웹 서비스를 진입할 때 빠르게 콘텐츠를 보여주고 인터랙션을 해야하는데, 불필요한 코드가 들어있다면 용량도 늘어나게 되고 그에 따라 응답도 느려져 서비스 이탈율이 증가하게 된다. 트리쉐이킹은 불필요한 코드양을 줄여 속도를 개선시키는데 목적이 있다.

## 예제 폴더 구조

```js
// some-module.js

export function foo () {
  console.log('foo');
}

export function bar () {
  console.log('bar');
}
```

위의 `some-module.js` 이라는 파일이 있다. 여기서 `foo()` 함수만 사용하고 싶어 es6의 디스트럭쳐링 문법으로 `foo()` 만 import 시켜준다.

```js
// index.js
import { foo } from './some-module.js';

foo();
```
