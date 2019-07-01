# React

리액트는 Facebook 에서 만든 UI 를 만드는 자바스크립트 라이브러리이다.

## 가상 돔(Virtual DOM)

SPA에서는 사용자와의 상호작용이 많은데 직접 돔(DOM)을 변형시키면 브라우저가 연산하는 횟수가 많아진다. 리액트는 가상 돔을 이용해 이런 연산 횟수를 줄인다. 가상 돔이란 기존의 돔을 추상화해 복제를 한 것인데, 브라우저에서 변경이 일어나면 가상돔에 적용을 시킨뒤에 최종적인 변경사항을 돔에 적용시켜 연산횟수를 줄이게 된다.

## JSX

JSX 라는 문법을 사용하는데 필수는 아니다. JSX 에서는 Javascript 를 확장한 문법인데, html 에서 작성하는 마크업도 작성할 수 있다. 흔히, 웹에서 컴포넌트는 뷰(View)를 담당하는 마크업언어와, 기능 및 동작을 담당하는 Javascript 가 있는데 리액트는 이 둘을 JSX 라는 문법 안에 포함시켰다.

### JSX 표현식 사용

표현식이라 하면 *평가되어 반환되는 값* 이다. JSX 에서는 `{}` 중괄호로 감싸면 표현식이 된다.

```js
const element = <div>name is {name}</div>
```

### 속성 정의

html 어트리뷰트에 표현식을 넣을 수 있다.
```js
const element1 = <div tabIndex="0"></div>
const element2 = <img src={image.path} />
```

> JSX 는 마크업언어를 쓸 수 있게 만든 **자바스크립트** 이므로 `camelCase` 를 사용하는 것이 맞다. 엘리먼트의 class 를 지정할 때도 className이 된다.

### 태그닫기

태그 내부가 비어있다면 닫는것이 원칙이다.

```js
const element = <SomeComponent />
```

### 컴파일

```js
const element = (
  <h1 className="greeting">
    Hello, React!
  </h1>
)
```
[Babel](https://babeljs.io/) 은 위의 JSX 문법을 아래와 같이 컴파일한다.

```js
const element = React.createElement(
  'h1',
  { className: 'greeting' },
  'Hello, React!'
)
```
위의 결과로 element 는 다시 다음의 **리액트 컴포넌트** 가 된다.

```js
const element = {
  type: 'h1',
  props: {
    className: 'greeting',
    children: 'Hello, React!'
  }
}
```

만약 자식컴포넌트 없이 닫는태그만 있다면 `createElement()`의 세번째 파라미터는 `null`을 넣는다.

```js
React.createElement(
  'h1',
  { className: 'greeting' },
  null
)
```
[문서참고](https://ko.reactjs.org/docs/jsx-in-depth.html)

#### 리액트 createElement 명세

```ts
// DOM Elements
function createElement(
    type: "input",
    props?: InputHTMLAttributes<HTMLInputElement> & ClassAttributes<HTMLInputElement> | null,
    ...children: ReactNode[]): DetailedReactHTMLElement<InputHTMLAttributes<HTMLInputElement>, HTMLInputElement>;
function createElement<P extends HTMLAttributes<T>, T extends HTMLElement>(
    type: keyof ReactHTML,
    props?: ClassAttributes<T> & P | null,
    ...children: ReactNode[]): DetailedReactHTMLElement<P, T>;
function createElement<P extends SVGAttributes<T>, T extends SVGElement>(
    type: keyof ReactSVG,
    props?: ClassAttributes<T> & P | null,
    ...children: ReactNode[]): ReactSVGElement;
function createElement<P extends DOMAttributes<T>, T extends Element>(
    type: string,
    props?: ClassAttributes<T> & P | null,
    ...children: ReactNode[]): DOMElement<P, T>;


// Custom components
function createElement<P extends {}>(
    type: FunctionComponent<P>,
    props?: Attributes & P | null,
    ...children: ReactNode[]): FunctionComponentElement<P>;
function createElement<P extends {}>(
    type: ClassType<P, ClassicComponent<P, ComponentState>, ClassicComponentClass<P>>,
    props?: ClassAttributes<ClassicComponent<P, ComponentState>> & P | null,
    ...children: ReactNode[]): CElement<P, ClassicComponent<P, ComponentState>>;
function createElement<P extends {}, T extends Component<P, ComponentState>, C extends ComponentClass<P>>(
    type: ClassType<P, T, C>,
    props?: ClassAttributes<T> & P | null,
    ...children: ReactNode[]): CElement<P, T>;
function createElement<P extends {}>(
    type: FunctionComponent<P> | ComponentClass<P> | string,
    props?: Attributes & P | null,
    ...children: ReactNode[]): ReactElement<P>;
```

