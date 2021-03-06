# 리액트-엘리먼트

> 엘리먼트는 리액트의 가장 작은단위이다.

리액트에서는 `<div id="root"></div>` 라는 루트(root) 돔 노드가 존재하는데, 루트 돔 노드 안에 들어가는 모든 엘리먼트를 React DOM에서 관리한다. 리액트 엘리먼트를 루트 돔에 렌더링하려면 `ReactDOM.render()` 를 사용해 렌더한다.

```js
const element = <h1>React</h1> // 엘리먼트
ReactDOM.render(element, document.getElementById('root'));
```

## 불변객체

불변객체란 풀이 뜻 그대로 변할 수 없는 객체이다. 객체를 생성한 이후에 내부의 데이터나 상태를 변경할 수 없다는것을 뜻한다. 리액트 엘리먼트는 불변객체이기 때문에, 엘리먼트를 생성한 이후에는 자식이나 속성을 변경할 수 없다. 그렇다면 어떻게 상태가 변한걸 리액트는 알고있을까? 이는 리액트가 가상 돔(Virtual DOM) 을 사용하고 있기 때문이다.

> 가상 돔(Virtual DOM) 은 기존의 DOM을 추상화하여 복사본을 만든것이다. 리액트는 변경사항에 대해 가상 돔에 먼저 적용을 시키고, 최종적으로 변경사항에 대해서만 실제 DOM 업데이트를 합니다.
