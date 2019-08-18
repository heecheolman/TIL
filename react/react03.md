# 리액트-컴포넌트

리액트에서는 가장 작은 단위인 엘리먼트 위에 컴포넌트라는 것을 사용합니다. 다시말해, 컴포넌트는 여러 리액트 앨리먼트들로 구성된다는 뜻 입니다. 컴포넌트를 작성함으로써 재사용가능하게 분할할 수 있다는 장점이 있습니다.

## 컴포넌트 정의

컴포넌트를 정의하기에 앞서 **함수 컴포넌트** 와 **클래스 컴포넌트** 가 있습니. 그렇다면 이 둘의 차이는 무엇일까요?

### 클래스 컴포넌트 (Class Component)

컴포넌트가 상태를 갖거나, 컴포넌트 라이프사이클(Lifecycle) 훅을 이용해야할 때 사용합니다.

> 컴포넌트 라이프사이클(Lifecycle)이란, 컴포넌트가 생성되어 파괴될 때까지의 일련의 과정을 거치는데 이를 라이프사이클이라고 합니다.


#### ES6 Class 작성

ES6의 `Class` 와 상속을 통해 생성합니다.

```js
class HelloWorld extends React.Component {
  render() {
    return <h1>Hello World!</h1>
  }
}
```
위의 구문은 React 의 syntax sugar 입니다. 위의 코드는 다음과 같이 컴파일됩니다.

```js
class HelloWorld extends React.Component {
  render() {
    return React.createElement('h1', null, 'Hello World!');
  }
}
```

[Airbnb 코딩 컨벤션](https://github.com/apple77y/javascript/tree/master/react) 에서는 위와 같은 방식을 사용하지말고 JSX 문법을 이용하라고 권장하고 있다. 가독성측면에서도 위의 코드가 더 나아보입니다.

#### ES5 createClass 작성

ES5 문법을 이용할 때는 `React.createClass()` 함수를 통해 생성합니다.

```js
var HelloWorld = React.createClass({
  render: function() {
    return (
      <h1>Hello World!</h1>
    )
  }
})
```

> state 와 props 대한 부분은 다음 장에서 설명합니다.

### 함수 컴포넌트 (Functional Component)

함수 컴포넌트는 `화살표 함수(Arrow Function)` 을 통해서도 정의할 수 있습니다. 상태를 갖지 않아 공식문서에서는 `stateless functional component` 라고 불리기도 합니다.

**상태를 갖지않고, 라이프사이클을 사용하는 일이 없다면 순수하게 렌더하는 함수 컴포넌트로 작성** 합니다.

#### function 작성

```js
import React from 'react';

function Hello() {
  return (
    <div>Hello</div>
  )
}

export default Hello;
```

#### Arrow Function 작성

```js
import React from 'react';

const Hello = () => <div>Hello</div>

export default Hello;
```

## 참고문서

* [React 공식문서](https://ko.reactjs.org/docs/components-and-props.html)
* [2. Elements and Component - Jbee](https://jbee.io/react-tutorials/React-2-Elements-and-Component/)
* [React.js 뽀개기 — createClass vs extends Component - hyunjae park](https://engineering.huiseoul.com/react-js-%EB%BD%80%EA%B0%9C%EA%B8%B0-createclass-vs-extends-component-825f6b6fe898)
