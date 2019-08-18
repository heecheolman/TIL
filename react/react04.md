# 리액트 - State 와 Props

리액트의 State 와 Props 를 컴포넌트가 어떻게 다루는지 그리고 사용법에 대해 설명합니다.

## Props

컴포넌트 외부에서 전달받은 값으로 내부에서 접근할 수 있습니다. 외부에서 전달받은 값이기 때문에 immutable(불변)한 속성입니다. 즉, `readonly` 입니다.

### 사용법

#### 클래스 컴포넌트

```js
class Hello extends React.Component {
  constructor(props) {
    super(props);
  }
  render() {
    return (
      <h1>Hello! {this.props.name}</h1>
    )
  }
}

ReactDOM.render(<Hello name="heecheolman" />, document.getElementById('root'));
```

`Hello! {이름}` 을 표현하는 Hello 컴포넌트입니다. 사용하는 방법은 `this.props` 와 전달받은 key 값으로 접근하고 Hello 컴포넌트를 외부에서 props로 전달하는 방법입니다.

#### 함수 컴포넌트

함수 컴포넌트도 클래스 컴포넌트와 다를건 별로 없습니다.

```js
function Hello(props) {
  return (
    <h1>Hello! {props.name}</h1>
  )
}

ReactDOM.render(<Hello name="heecheolman" />, document.getElementById('root'));
```

여기서 더 깔끔한 코드를 원한다면 ES6의 구조분해할당(Destructuring) 을 적용할 수 있습니다.

```js
function Hello({ name }) {
  return (
    <h1>Hello! {name}</h1>
  )
}
...
```

### PropTypes

전달받은 props 들에 대한 타입을 지정해 줄 수 있습니다.

> MS의 타입스크립트를 이용하는 것도 하나의 방법입니다.

> React v15.5부터 React.PropTypes 는 별도 패키지로 옮겨졌습니다. 대신 prop-types 라이브러리를 사용하시길 바랍니다. - [Proptypes를 이용한 타입 체크](https://reactjs-kr.firebaseapp.com/docs/typechecking-with-proptypes.html)

먼저 [`prop-types`](https://github.com/facebook/prop-types) 의존성을 설치합니다.

```bash
# Use NPM
npm install prop-types

# Use Yarn
yarn add prop-types
```

```js
...
import PropTypes from 'prop-types';

class Hello extends React.Component {
  ...
}

Hello.propTypes = {
  name: PropTypes.string, // 선택적 문자열
  foo: PropTypes.string.isRequired, // 필수 문자열
  onClick: PropTypes.func, // 함수
}

export default Hello;
```

### DefaultProps

기본 props 를 지정할 수 있으며, 동일하게 타입체킹이 이루어집니다.

```js
...
Hello.defaultProps = {
  name: 'heecheolman',
  foo: '',
  onClick: function () {
    alert('Clicked!')
  }
}
...
```

## State

상태를 갖는 컴포넌트는 클래스 컴포넌트를 사용합니다. 클래스 컴포넌트의 `constructor()` 내부에 state 를 정의해주기만 하면 됩니다. 그리고 상태를 업데이트하고 싶을 땐 `this.setState({ ... })` 를 통해 업데이트 해주면됩니다.

```js
import React from 'react';

class Hello extends React.Component {
  constructor(props) {
    super(props);
    /* 상태 정의 */
    this.state = {
      name: ''
    };
    this.handleClick = this.handleClick.bind(this);
  }

  handleClick() {
    this.setState({
      name: 'heecheolman'
    });
    console.log(this.state.name); // heecheolman
  }

  render() {
    return (
      <div>
        <button onClick={this.handleClick}></button>
      </div>
    );
  }
}
```

### 이벤트 메서드 bind

위의 코드에서 클래스 내부 메서드를 `.bind(this)` 처리를 해준것을 주의깊게 보면, 기본적으로 Class 의 메서드는 `this` 를 바인딩 해주지않습니다. 이벤트를 호출하더라도 `this` 는 `undefined` 이기 때문에 에러를 뱉습니다. 이러한 현상을 해결하기 위해서는 몇가지 방법이 존재합니다.

#### bind(this)

위의 방법처럼 생성자에서 `.bind(this)` 로 바인딩 시켜주는 방법입니다. 왜 바인딩이 일어나야하는가? 에 대해서 설명하자면, 메서드 내부에서 정의한 `this` 와 `constructor` 에서 정의한 `this` 의 문맥이 달라서 생기는 문제입니다. 다음은 예제입니다.

```js
const person = {
  name: 'heecheolman',
  greeting: function() {
    console.log('My name is ' + this.name);
  }
};

person.greeting(); // My name is heecheolman
const foo = person.greeting;
foo(); // My name is undefined
```

객체 person 의 `this` 는 객체 자신을 가리킵니다. 때문에 `this.name` 은 `heecheolman` 이 되는것입니다. 해당 함수를 참조하는 `foo` 는 `obj` 에 존재하는 `this` 를 알지 못합니다. 때문에 `.bind(obj)` 를 통해 연결시켜줘야합니다.

> bind 함수는 전달받은 문맥을 첫번째 인자로 받으며, 바인딩된 새로운 함수를 return 합니다.

```js
...
const foo = person.greeting.bind(obj);
foo(); // My name is heecheolman;
```

일회성으로 사용하고싶다면 `call()`, 이나 `apply()` 를 사용하는것도 방법입니다.

```js
const foo = person.greeting;
foo.call(obj); // My name is heecheolman
foo.apply(obj); // My name is heecheolman
```

> call 과 apply 는 첫번째 인자로 문맥을 받는것은 동일하지만 그 뒤의 parameter 를 개별요소로 받느냐, 배열로 받느냐에 차이가 있습니다. - [관련 정리](https://github.com/heecheolman/TIL/blob/master/javascript/bind.md)


#### 클래스 필드 문법

클래스필드에 화살표함수를 정의하면 됩니다.

```js
class Hello extends React.Component {
  ...
  handleClick = () => {...}
}
```

#### 콜백 화살표 함수

클래스필드에 정의하는 것이 별로라면, 콜백의 화살표함수로 전달하는 것도 방법입니다.

```js
class Hello extends React.Component {
  ...
  handleClick() {
    ...
  }

  render() {
    return (
      <button onClick={() => this.handleClick()}>버튼</button>
    )
  }
}
```

### setState 는 비동기

React 의 state 를 업데이트할 때 `setState({ ... })` 메서드를 이용합니다. 리액트는 `setState` 메서드를 비동기로 실행합니다. 하나의 요청이라고 생각하면 됩니다. **업데이트하려는 값으로 `this.state` 를 참조하게되면 원하지않은 값이 나옵니다.**

```js
class Counter extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      value: 0
    };
    this.addThree = this.addThree.bind(this);
  }

  addThree() {
    this.setState({
      value: this.state.value + 1
    });
    this.setState({
      value: this.state.value + 1
    });
    this.setState({
      value: this.state.value + 1
    });
    console.log(this.state.value);
  }

  render() {
    return (
      <button onClick={this.addThree}>3씩더하기</button>
    )
  }
}

/*
 클릭 1: 0
 클릭 2: 1
 클릭 3: 2
 클릭 4: 3
 클릭 5: 4
*/
```

이를 방지하려면 Updater 함수를 전달해줍니다.

```js
class Counter extends React.Component {
  ...
  addThree() {
    /* 보장된 state */
    this.setState((prevState) => ({
      value: prevState.value + 1
    }));
    this.setState((prevState) => ({
      value: prevState.value + 1
    }));
    this.setState((prevState) => ({
      value: prevState.value + 1
    }));
    console.log(this.state.value);
  }
}

/*
 클릭 1: 0
 클릭 2: 3
 클릭 3: 6
 클릭 4: 9
 클릭 5: 12
*/
```

## 마무리

리액트에서 State 와 Props 의 사용법에 대해 알아보고, 작성시 주의사항인 **이벤트 메서드 바인딩**, **readonly props**, **비동기로 작동하는 `setState`** 를 알아봤습니다.


## 참고문서

* [컴포넌트와 props - React 공식문서](https://ko.reactjs.org/docs/components-and-props.html)
* [이벤트 제어하기 - React 공식문서](https://reactjs-kr.firebaseapp.com/docs/handling-events.html)
* [3. Props and State in Component - Jbee](https://jbee.io/react-tutorials/React-3-Props-and-State-in-Component/)
* [React를 본격적으로 하기 전 알면 좋은 6가지 - Jbee](https://jaeyeophan.github.io/2018/01/02/React-tips-for-beginners/)
