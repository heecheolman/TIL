
# React 컴포넌트

## UnControlled Component 와 Controlled Component

State 를 갖지 않고, 클래스의 필드로 갖고 있다면, `render` 가 실행되지 않습니다. state 에 업데이트가 일어나지 않아 re-render 를 하지 않는것입니다. state 값이 존재 하지 않아서 state를 제어하지 못해 React 가 컨트롤할 수 없는 상태이기 때문에 UnControlled Component 입니다. 

렌더링이 계속 일어날 필요가 없다면 UnControlled Component를 사용하는 것이 좋습니다.

### re-render

state 와 state 변경사항을 상위 컨테이너 컴포넌트에 정의하고, 하위 컴포넌트에 props로 state 를 전달하게 되면 하위 컴포넌트는 props 가 새로운 값임을 알고 re-render 가 일어납니다. 보통 컨테이너 컴포넌트에는 하위컴포넌트가 여러 개 있을 수 있는데, 특정 state 의 변경사항이  일어나면 모든 하위 컴포넌트들이 re-render 가 일어나  성능이슈가 발생 할 수  있습니다.

**해결책: state 를 하위 컴포넌트에 정의**

state 를 상위 컴포넌트가 아닌 하위 컴포넌트 자체가 가지고 있다면, 하위 컴포넌트 자체의 state변경 사항들에 대해서만 re-render가 일어납니다.

    /** ContainerComponent */
    class MainPage extends React.Component<any, any> {
    
    	email: string = '';
    	password: string = '';
    
    	render() {
    		return (
    			<div>
    				<h1>MainPage</h1>
    				<div>
    					<Input
    						type={'email'}
    						placeholder={'이메일'}
    						onChange={this.handleChangeEmail}
    					/>
    				</div>
    				<div>
    					<Input
    						type={'password'}
    						placeholder={'비밀번호'}
    						onChange={this.handleChangePassword}
    					/>
    				</div>
    			</div>
    		);
    	}
    
    	/** props로 넘긴 함수의 callback 함수를 통해 멤버변수 업데이트 */
    	handleChangeEmail = (value: string) => {
    		this.email = value;
    	};
    
    	handleChangePassword = (value: string) => {
    		this.password = value;
    	}
    }

    /** Input 컴포넌트 */
    class Input extends React.Component<any , any> {
    	/** 컴포넌트 내부에 state 설정 */
    	state = {
    		value: '',
    	};
    
    	render() {
    		const { value } = this.state;
    		console.log(this.props.placeholder,  'render');
    		return (
    			<input
    				type={this.props.type}
    				placeholder={this.props.placeholder}
    				value={value}
    				onChange={this.handleChange}
    			/>
    		);
    	}
    
    	handleChange = (event: any) => {
    		this.setState({
    			value: event.target.value,
    		}, () => {
    			/** state 변경 후 callback */
    			this.props.onChange(this.state.value);
    		});
    	};
    }

**초기화**

먄약 상위 컴포넌트에서 하위 컴포넌트에 대한 초기화 작업을 진행해야 한다면, state 를 변경해야하는데 접근할 방법이 따로 없습니다. 때문에 Node 의 key 변경으로 컴포넌트를 파괴하고 다시 생성해 초기화 하는것처럼 구현할 수 있습니다.

> [https://reactjs.org/blog/2018/06/07/you-probably-dont-need-derived-state.html#recommendation-fully-uncontrolled-component-with-a-key](https://reactjs.org/blog/2018/06/07/you-probably-dont-need-derived-state.html#recommendation-fully-uncontrolled-component-with-a-key)

    class MainPage extends React.Component<any, any> {
    	state = {
    		reset: 0,
    	};
    	email: string = '';
    	password: string = '';
    
    	render() {
    		const { reset }  = this.state;
    		return (
    			<div>
    				<h1>MainPage</h1>
    				<div>
    					<Input
    						type={'email'}
    						key={reset + 'email'}
    						placeholder={'이메일'}
    						onChange={this.handleChangeEmail}
    					/>
    				</div>
    				<div>
    					<Input
    						type={'password'}
    						key={reset + 'password'}
    						placeholder={'비밀번호'}
    						onChange={this.handleChangePassword}
    					/>
    				</div>
    				<div>
    					<button onClick={this.handleReset}>초기화</button>
    				</div>
    			</div>
    		);
    	}
    
    	handleReset = () => {
    		this.setState({
    			reset: this.state.reset + 1,
    		});
    	};
    
    	handleChangeEmail = (value: string) => {
    		this.email = value;
    	};
    
    	handleChangePassword = (value: string) => {
    		this.password = value;
    	}
    
    }

`초기화` 버튼을  누르면 `Input` 컴포넌트에  등록된 key 가 변경되어  컴포넌트가  파괴되고, 다시 생성되어 초기화와 동일한 효과를 낼 수 있습니다.

> 컴포넌트에 hidden property 로 `key` 라는 것이 존재하는데, 이는 리액트 컴포넌트의 고유 Node 값을 나타내는 값으로 `key` 가 변경되면 리액트는 다른컴포넌트로 인식해 다시 생성합니다.

## Pure Component

Pure Component 는 React Component 와 다르게 props 나 state 의 값을 얕은비교해서 값이 다르다면 render 를 실행합니다. 반대로 값이 다르지 않다면 렌더링 하지 않는다는 점에서 성능 개선을 할 수 있습니다. 

반대로, re-render 가 항상 일어나는 컴포넌트임을 보장하는데, PureComponent 로 쓴다면 불필요한 비교로직때문에 오히려 성능상 이슈가 발생할 수 있습니다.

**실수1: 인라인 함수**

    <Input 
    	... 생략
    	onChange={(event) => this.setState({ value: event.target.value })}
    />

인라인함수가 아닌, 인스턴스 함수를 통해 매번 렌더링 되는 것을 막을 수 있습니다.

> [https://gist.github.com/ihoneymon/652be052a0727ad59601](https://reactjs.org/docs/render-props.html#be-careful-when-using-render-props-with-reactpurecomponent)

## Portal Component

Dialog 또는 Modal 컴포넌트는 DOM 트리구조상에서 root와 동일한 레벨에 존재해야, 잘리지 않고 잘 표현될 수 있습니다. 때문에 React 는 `React.createPortal()` 함수를 이용해 상위 노드에 렌더링할 수 있게 도와줍니다.

먼저, index.html에서  `<div id="root"></div>` 와 동일레벨로  다른 `div` 를 만들어 id 를 등록해줍니다.

    <div id="root"></div>
    <div id="dialog"></div>

Dialog 컴포넌트의 render 함수는 이렇게 됩니다.

    // DialogComponent
    // ...
    render() {
    	return React.createPortal(
    		<div>Dialog Component</div>,
    		document.getElementById('dialog'),
    	);
    }

두번째 인자로 dialog  를 id 로 갖는 DOM 을 넣어줬습니다.

## Component Composition (컴포넌트 합성)

컴포넌트 합성은 props 를 통해 상위 컴포넌트에서 전달한 것들을 렌더링할 수 있습니다. 

    /** Parent */
    <Dialog>
    	<p>dialog</p>
    </Dialog>
    
    /** Child(Dialog) */
    render() {
      const { children } = this.props;
    	return (
    		<div>
    			{children}
    		</div>
    	)
    }

위의 방식으로 렌더링하면 `{children}` 자리에 상위 컴포넌트에서 전달한 `<p>dialog</p>`  가 위치하게 됩니다. 굳이 children 이 아니더라도, 다른 props key 를 통해 전달할 수 있습니다

    /** Parent */
    <Dialog
    	header={someHeader}
    	body={someBody}
    	footer={someFooter}
    />
    
    /** Child(Dialog) */
    render() {
      const { header, body, footer } = this.props;
    	return (
    		<div>
    			{header}
    			{body}
    			{footer}
    		</div>
    	)
    }

Angular 에서의  `<ng-content>` 나 Vue 의 `slot` 과 동일한 개념인 것 같습니다.

만약 Dialog 를 렌더링하고있는 컴포넌트에서 state 변경을 하게되면,  Dialog는 매 번 re-render 가 일어나 성능문제를 야기합니다. ㄱ

## Specialization (특수화)

위의 Dialog 를 일반 컴포넌트로 변경하고, 이를 한번 감싼 별도의 컴포넌트를 만듭니다. 그리고 그 컴포넌트를 PureComponent 로 만들어주면 state 가 변경되어도 re-render 되는 일은 없습니다.

이렇게 일반 컴포넌트를 특수한 목적에 맞게 대응하는 컴포넌트로 만드는 것을 특수화 라고 합니다.

    class SomeDialog extends React.PureCompoennts {
    	render() {
    		return (
    			<Dialog 
    				header={someHeader}
    				body={someBody}
    				footer={someFooter}
    			/>
    		)
    	}
    }
    
    /** 상위 컴포넌트 */
    render() {
    	return (
    		<SomeDialog />
    	)
    }

## Functional Component

리액트는 클래스 컴포넌트가 아니라 함수형 컴포넌트로도 작성할 수 있습니다. React 16.8 버전에 Hooks 라는 기능이 추가되었기 때문입니다.

### useState

class 컴포넌트에서 사용했던 state 를 함수형 컴포넌트에서는 `useState()` 를 이용해 state를 생성합니다.

    const [state, setState] = useState(initialState);

state 를 이용해 값을 접근할 수 있고 setState 를 이용해 값을 설정할 수 있습니다. state에 대해 초기 값을 전달해 주고 싶다면 `useState` 에 값을 넘겨주면 초기값이 설정됩니다.

### React.memo

PureComponent 의 함수형 버전입니다. 입력받은 state 나 props 를 얕은비교해서 다르면 re-render 하고, 그렇지 않으면 render 하지 않습니다. 이름 그대로, 이전 값을 *memo* 해둔다는 뜻으로 보입니다.  두번째 입력값으로 비교기를 넣고, 그렇지 않는다면 기본적으로 얕은 비교만 수행합니다. 비교기는 동일한 값일경우 `true` 를 return 하고, 그렇지 않을경우 `false` 를 return 해 render 여부를 결정합니다.

> [https://ko.reactjs.org/docs/react-api.html#reactmemo](https://ko.reactjs.org/docs/react-api.html#reactmemo)

    function SomeComponent(({ someValue }) => {
    	return <div>someComponent {someValue}</div>
    })
    
    export default React.memo(SomeComponent);

### useCallback

함수형 컴포넌트는 본문 자체가 render 함수라 어디서 이벤트 핸들러를 만들던간 새로운 함수를 만듭니다. `useCallback` 함수는 이 이벤트 핸들러 함수를 메모해 두었다가, 콜백함수가 사용되는 값들이 변경됐을 때만 변경해줍니다. `useCallback` 을 이용해 불필요한 render를 막아 성능을 최적화 할 수 있습니다.

    const memoizedCallback = useCallback(
      () => {
        doSomething(a, b);
      },
      [a, b], // callback 함수 내에 의존되는 값들
    );

### useMemo

컴포넌트 컴포지션의 경우에 props 로 ReactNode 를 넘겨주는데 이 때 항상 새로운 ReactNode 를 넘겨주기 때문에  렌더링이 계속 발생해 불필요한 작업이 수행될 수 있습니다. `useMemo` 를 이용해  불필요한 렌더링을 막아줍니다.

    const emailAccessory = useMemo(() => {
    	return email !== '' && <button>X</button>
    }, [email]);

### useEffect

렌더링 이후에 실행되는 콜백입니다. `ComponentDidMount` 와 `ComponentDidUpdate` 를 합친 시점이라고 생각하면 됩니다. 만약 `useRef` 로 Input Element 를 autoFocus 하는 코드를 보면 다음과 같습니다.

    // 생략
    
    const renderCount = useRef<number>(0);
    const inputElement = useRef<HTMLInputElement>(null);
    
    useEffect(() => {
    /** 컴포넌트 렌더링 이후에 autoFocus 값이 true 라면 focusing */
    	if (autoFocus && inputElement.current) {
    		/** 타입스크립트 null 체크 */
    		inputElement.current.focus();
    	}
    }, [autoFocus]);

**ComponentWillUnmount**

`ComponentWillUnmount`  는 컴포넌트가 파괴될 때 실행되는 훅입니다. useEffect 의 return 콜백으로 지정한 함수는 컴포넌트가 Unmount 되면서 실행됩니다. 리액트는 이러한 작업을 ***CleanUp*** 이라고 부릅니다.

    // 생략
    useEffect(() => {
    /** 컴포넌트 렌더링 이후에 autoFocus 값이 true 라면 focusing */
    	if (autoFocus && inputElement.current) {
    		/** 타입스크립트 null 체크 */
    		inputElement.current.focus();
    	}
    	return () => {
    		console.log('Unmount');
    	}
    }, [autoFocus]);

**React Lifecycle 참고**

![https://miro.medium.com/max/3348/1*cEWErpe-oY-_S1dOaT1NtA.jpeg](https://miro.medium.com/max/3348/1*cEWErpe-oY-_S1dOaT1NtA.jpeg)

### customHook 만들기

중복되는 로직을 묶고, 재사용 가능하게 만들 수 있게 Hook 을 구현할 수 있습니다. 

    /* useInputState.ts */
    
    import { ChangeEvent, Dispatch, SetStateAction, useCallback, useState } from 'react';
    
    function useInputState(defaultState: string | (() => string)): [
    	string,
    	Dispatch<SetStateAction<string>>,
    	(event: ChangeEvent<HTMLInputElement>) => any,
    ] {
    	const [state, setState] = useState(defaultState);
    	const handleChangeState = useCallback((event: ChangeEvent<HTMLInputElement>) => {
    		setState(event.target.value);
    	}, []);
    
    	return [
    		state,
    		setState,
    		handleChangeState,
    	];
    }
    
    export default useInputState;

이 customHook 을 import 해서 사용합니다.

    // 생략
    
    const [email, setEmail, handleChangeEmail] = useInputState('');
    const [password, setPassword, handleChangePassword] = useInputState('');

## 마무리

React Hooks 의 글들 중에서 [이현섭님의 컴포넌트 제대로 만들기](https://hyunseob.github.io/2019/06/02/react-component-the-right-way/) 글을 보며 익혔습니다. 내용도 좋고, 예제를 따라서 잘 설명해 주셔서 이해가 잘 됐습니다. 저는 타입스크립트를 가미해 최대한 타입을 맞춰 예제를 따라했습니다. 인상 깊었던 부분은 customHook 을 이용해 같은 관심사인 코드들을 한 곳에 모아 관리할 수 있다는 점이었습니다.

## 참고 문서

* [컴포넌트 제대로 만들기](https://hyunseob.github.io/2019/06/02/react-component-the-right-way/)

* [Hook의 규칙 - React](https://ko.reactjs.org/docs/hooks-rules.html)