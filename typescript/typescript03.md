<div align=center>
<img src="https://pbs.twimg.com/profile_images/743155381661143040/bynNY5dJ_400x400.jpg" width="80" height="80">
</div>


# 타입스크립트 인터페이스

기존에 자바스크립트에는 인터페이스라는 개념이 없었습니다. 하지만 타입스크립트를 이용해 인터페이스를 사용할 수 있게 됐습니다. 인터페이스라는 용어에 대해서 한번 짚고 넘어갈 필요가 있습니다. 인터페이스란 간단하게 어떠한 두개의 시스템 사이에 상호작용할 수 있게 해주는 조건, 규약 같은 것입니다.

실생활에서 예를들어 '타이핑' 이라는 인터페이스가 있다고 친다면, *키보드의 K 를 누르면 알파벳 'K' 가 모니터에 출력된다.* 는 눌렀을 때 어떠한 문자가 출력된다는 '타이핑' 인터페이스를 지키고 있는 것입니다. 역으로 타이핑 인터페이스(규약)를 지키고 있다면 특정 문자가 모니터에 출력이 될 것입니다.

> 어원을 살펴보자면, inter + face = 상호작용 + 표면  
즉, 무언가 상호작용 하기 위해 표면적으로 어떠한 약속이 있다는 것입니다.

그럼 타입스크립트에서 인터페이스를 어떻게 이용하는지 알아보겠습니다.

## 📝 목차
* 인터페이스 사용
* 선택적 프로퍼티
* 읽기전용 프로퍼티
* 함수 타입
* Indexable 타입
  * Indexable 타입 예제
  * 자바스크립트 색인의 동작방식
  * Indexable 사용법
  * 주의해야할 점
  * 유니온 타입을 이용한 Index Signature
  * 제한된 리터럴문자열 셋
  * 중첩된 Index Signature
  * NestedDOM
  * readonly 프로퍼티
* 클래스 타입
* 확장 인터페이스
* Hybrid 타입
* 클래스에서의 인터페이스 확장

---

## 인터페이스 사용
타입스크립트에서 인터페이스를 사용하는 방법을 알아보겠습니다.

```ts
// TS

function createKeyboard(orderSheet: { ingredient: string, keyCount: number }) {
    console.log(`키보드 만드는중...`);
}

let orderSheet = {
    ingredient: 'plastic',
    keyCount: 40,
};

createKeyboard(orderSheet);
```

여기에 키보드를 만드는 함수가 있습니다. 이 함수는 주문서를 받는데 그 주문서에 적혀있는 내용은 성분인`ingredient`, 그리고 키보드 키의 개수인 `keyCount` 라는 항목이 있고 이 두 개를 적어줘야 만들 수 있습니다.

그런데 만약 주문서에 작성할 내용이 엄청 많아지면 코드가 너무 지저분해질것이 분명합니다. 이 때 *타입스크립트의 interface* 를 사용합니다. 다음 코드는 인터페이스를 사용했을 때의 코드입니다.

```ts
// TS

interface OrderSheet {
    ingredient: string;
    keyCount: number;
}

function createKeyboard(orderSheet: OrderSheet) {
    console.log(`키보드 만드는중...`);
}

// ...
```

확실히 가독성이 더 좋아진것을 볼 수 있습니다. 그리고 주문서의 항목란이 많아질 경우에도 문제가 없을것 같습니다.

## 선택적 프로퍼티
각인이라는 항목이 주문서에 추가가 되었습니다. 하지만 이 각인은 고객이 이름을 적어주었을 경우에만 새겨줍니다. 이렇게 선택적으로 어떠한 옵션을 주어야할 때 선택적 프로퍼티를 이용합니다. 프로퍼티 이름의 끝에 `?` 만 넣어주면 됩니다.

```ts
// TS

interface OrderSheet {
    ingredient: string;
    keyCount: number;
    name?: string;
}

function createKeyboard(orderSheet: OrderSheet) {
    console.log(`키보드 만드는중...`);
}

let orderSheet1 = {
    ingredient: 'plastic',
    keyCount: 40,
};

let orderSheet2 = {
    ingredient: 'metal',
    keyCount: 30,
    name: 'heecheolman',
};

createKeyboard(orderSheet1);
createKeyboard(orderSheet2);
```

선택적으로 이름을 넣어주었습니다.

## 읽기전용 프로퍼티
주문을 했는데 고객이 각인될 내용을 바꾸고 싶다합니다. 주문이 들어가면 바꿀 수 없는 시스템이라 가정을 한다면 읽기전용으로 하고싶은 프로퍼티앞에 `readonly` 만 붙여주면 됩니다.

```ts
// TS

interface OrderSheet {
    ingredient: string;
    keyCount: number;
    readonly name?: string;
}

function createKeyboard(orderSheet: OrderSheet) {
    console.log(`키보드 만드는중...`);
    // orderSheet.name = 'heecheol';
    // Error : TS2540: Cannot assign to 'name' because it is a read-only property.
}

// ...
```

`readonly` 는 `const` 와 동일한 역할을 수행합니다. **변수일 경우엔 `const` 를 사용하고  프로퍼티일 경우에는 `readonly` 로 사용하시면 됩니다.**

추가적으로 배열을 읽기전용으로 하고싶다면 `Readonly<type>` 으로 선언을 해줍니다.
```ts
// TS
let keyElements: ReadonlyArray<string> = ['a', 'b', 'c', 'd'];
let newKeyElements: string[];

// Errors!

// keyElements.push(1);
// keyElements[0] = 'A';
// let temp: string[] = keyElements;
// newKeyElements = keyElements;


// Ok!
newKeyElements = keyElements as string[];

newKeyElements.push('e');
```
push, 인덱스 접근 후 할당, 새로운 string 배열인 temp 에 할당같은 것들이 전부 불가능하지만 *Type Assertion* 을 이용하면 가능합니다.

---

## 함수 타입
인터페이스의 프로퍼티로 함수 시그니쳐를 정의할 수 있습니다.

> 시그니처(signature) 란?  
[MDN-signature 에 따르면](https://developer.mozilla.org/ko/docs/Glossary/Signature/Function) functions 그리고 methods 의 입력과 출력을 정의합니다. 시그니처는 다음을 포합합니다.
* parameters 와 그들의 types
* 반환값과 타입
* 던져지거나 콜백으로 반환되는 exceptions
* OOP 에서 메서드의 접근 권한에 대한 정보(public, static, 혹은 prototype와 같은 키워드들)  


```ts
// TS

interface TypingSpec {
    (sound: string, weight: number): boolean;
}

const checkCreatedKeyboard: TypingSpec = (s: string, w: number): boolean => w < 10;

console.log(checkCreatedKeyboard('took', 11)); // false;
console.log(checkCreatedKeyboard('tok', 3)); // true
```

만들어진 키보드를 체크하는 인터페이스에는 sound(누르는 소리) 와 weight(누르는 가중치)를 파라미터로 받습니다. 만약 누르는 힘이 10 이상 든다면 제품을 쓸 수 없다고 가정했습니다.

인터페이스 프로퍼티로 정해준 함수 시그니쳐의 파라미터의 이름과 구현하는 부분의 파라미터 이름이 꼭 동일할 필요는 없습니다. `s` 와 `w` 로 정해준것을 확인할 수 있습니다.

## Indexable 타입

#### Indexable 타입 예제
```ts
interface StringArray {
    [index: number]: string;
}

let myArray: StringArray;
myArray = ['bob', 'fred'];

let myStr: string = myArray[0];

console.log(myStr); // bob
```
StringArray 가 number 로 인덱스 될 때 string을 리턴합니다.

#### 자바스크립트 색인의 동작방식
타입스크립트로 들어가기전에 자바스크립트의 객체 프로퍼티를 접근하는 방법을 살펴봅니다. 자바스크립트는 객체의 프로퍼티에 접근을 할 때 문자열로 접근할 수 있습니다. `[]` 를 이용하여 접근이 가능합니다.

```js
// ES6
let obj = {};
obj['str'] = 'string';

console.log(obj['str']); // string
```
 그리고 객체로도 객체의 프로퍼티로 지정할 수 있습니다.

```js
// ES6
let obj = {};
let foo = {};

foo[obj] = 'Key is obj';
console.log(foo[obj]); // Key is obj
```
**자바스크립트 색인의 동작방식에 의해 객체의 색인에 접근할 때 내부적으로 `toString()` 메서드를 호출하여 문자열로 변형된 값을 통해 접근합니다.**

```js
// ES6
let obj = {
    toString() {
        console.log('toString() called');
    }
};
let foo = {};

foo[obj] = 'Key is obj'; // toString() called
console.log(foo[obj]);
// toString() called
// Key is obj
```
`toString()` 메서드를 호출해 문자열로 바뀌는것을 콘솔로 확인하였습니다. 위의 예제에서는  `toString()` 에 대한 콘솔로그를 두번 호출하는데 그 이유는 **접근할 때마다** `toString()` 이 호출되기 때문입니다.

#### Indexable
자바스크립트에서 사용하듯 타입스크립트에서 객체를 하나 만들어보겠습니다.
```js
// ES6
const obj = {
  a: '에이',
  b: '비',
};

Object.keys(obj).forEach(key => console.log(obj[key]));
```

하지만 이 코드는 타입스크립트에서는 에러를 발생합니다.
```text
 TS7017: Element implicitly has an 'any' type because type '{ a: string; b: string; }' has no index signature.
```
`index signature` 가 없다는 에러메세지가 보입니다. 이유인 즉슨, 프로퍼티에 접근할 때 어떤 타입인지 확인할 수 없어 암묵적으로 any 타입을 사용하기 때문입니다.

> 이는 tsconfig 의 `"noImplicitAny": true` 이기 때문에 발생하는 에러입니다.  
noImplicitAny 의 default 는 true 입니다.

해결방법은 index signature 를 사용하면 됩니다.  
*다음 예제의 index signature 의 의미는 key 값은 string 이고 반환값도 string 이다. 라는 뜻입니다.*

```ts
// TS
interface IndexSignature {
    [key: string]: string;
}

const obj: IndexSignature = {
  a: '에이',
  b: '비',
};

Object.keys(obj).forEach(key => console.log(obj[key]));
```

#### 주의해야할 점

##### 1. index signature 의 타입은 문자열 또는 숫자만 가능합니다.
```ts
// TS

// Error!
interface Interface {
    [key: boolean]: string;
}
//  TS1023: An index signature parameter type must be 'string' or 'number'.
```

##### 2. 문자열 색인과 숫자 색인이 모두 존재할 경우, 숫자로 된 색인의 값의 타입은 문자열로 색인 된 값 타입의 서브타입이어야 합니다.

```ts
// TS
class Animal {
    name: string;
}
class Dog extends Animal {
    breed: string;
}
// Error: "문자열"로 색인을 생성하면 가끔 "Dog"가 생깁니다.
interface NotOkay {
    [x: number]: Animal;
    [x: string]: Dog;
}
```
위의 코드가 에러인 이유는 처음에 말씀드렸던 자바스크립트가 색인을 할 때 `toString()` 을 먼저 호출하기 때문입니다. 가령, `obj[1]` 로 접근을 하면 우리가 기대했던 Animal 이 값으로 나올 것 같지만 `1` 은 문자열 `'1'` 로 변환이 되기 때문에 Dog 가 나올수도 있다는 예제입니다.
```js
// ES6
console.log((1).toString() === '1') // true
```


> [Typescript Handbook - Interfaces](https://www.typescriptlang.org/docs/handbook/interfaces.html) 에서는 문자열 Index Signature 은 'Dictionary' 패턴을 설명하는 강력한 방법이지만 모든 프로퍼티가 리턴 타입과 일치 해야한다고 말하고 있다.


#### 유니온 타입을 이용한 Index Signature
```ts
// TS
interface UnionTypeSignature {
    [key: string]: number | string;
    name: string;
    age: number;
}

const me: UnionTypeSignature = {
  name: 'heecheolman',
  age: 24,
};

console.log(me.name); // heecheolman
console.log(me.age); // 24

console.log(me['name']); // heecheolman
console.log(me['age']); // 24
```
유니온 타입을 이용하려면 인덱서는 그 아래 프로퍼티의 속성들을 모두 가지고 있어야한다.

#### 제한된 리터럴문자열 셋
매핑된 유형을 사용해 index signature 가 문자열 조합의 구성원이어야 사용할 수 있게끔 제약할 수 있다.
```ts
// TS
type Index = 'a' | 'b' | 'c';
type FromIndex = {
    [k in Index]?: number;
}

const good: FromIndex = {
    a: 1,
    b: 2,
    c: 3,
};


/* TS2322: Type '{ b: number; c: number; d: number; }' is not assignable to type 'FromIndex'.
Object literal may only specify known properties, and 'd' does not exist in type 'FromIndex'. */

const bad: FromIndex = {
    b: 2,
    c: 3,
    d: 4, // Error
};
// d 속성이 없음
```

#### 중첩된 Index Signature
```ts
// TS
interface NestedCSS {
    color?: string;
    [selector: string]: string | NestedCSS;
}

const example: NestedCSS = {
    color: 'black',
    '.subclass': {
        color: 'white',
    },
};
```
이렇게 했을 경우 다음과 같은 오타는 잡지 못합니다.
```ts
// TS
const failsSiently: NestedCSS = {
    colour: 'gold',
};
```

해결책은 다음과 같습니다. nest, children, subnodes 등등과 같은 이름을 갖는 프로퍼티를 만들고 그 안에 내장시킵니다.
```ts
// TS
interface NestedCSS {
    color?: string;
    nest?: {
        [selector: string]: NestedCSS;
    };
}

const example: NestedCSS = {
    color: 'black',
    nest: {
        '.subclass': {
            color: 'white',
        }
    }
};
```
이제 다음과 같은 코드는 에러를 뱉습니다.
```ts
// TS
const failsSiently: NestedCSS = {
    colour: 'gold',
};
/*
TS2322: Type '{ colour: string; }' is not assignable to type 'NestedCSS'.
 Object literal may only specify known properties, but 'colour' does not exist in type 'NestedCSS'. Did you mean to write 'color'?
*/
```

#### NestedDOM
다음 코드는 위의 NestedCSS 를 응용해 만들어봤습니다.

NestedDOM 에 대한 인터페이스입니다.
```ts
// TS
interface NestedDOM {
    tag: string;
    textNode?: string;
    children?: NestedDOM[];
}
```
NestedDOM 인터페이스를 구현한 객체입니다.
```ts
// TS
const domGroup: NestedDOM = {
    tag: 'div',
    children: [
        {
            tag: 'h1',
            textNode: 'Introduction',
        },
        {
            tag: 'ul',
            children: [
                {
                    tag: 'li',
                    children: [
                        {
                            tag: 'text',
                            textNode: 'Hello',
                        },
                    ],
                },
                {
                    tag: 'li',
                    children: [
                        {
                            tag: 'text',
                            textNode: 'heecheolman',
                        },
                    ],
                },
                {
                    tag: 'li',
                    children: [
                        {
                            tag: 'text',
                            textNode: 'World!',
                        },
                    ],
                },
            ],
        },
    ],
};
```
위의 코드는 다음 html 로 기대됩니다.
```html
<div>
    <h1>Introduction</h1>
    <ul>
        <li>Hello</li>
        <li>heecheolman</li>
        <li>World!</li>
    </ul>
</div>
```
NestedDOM 을 파싱하는 `createComponent()` 함수입니다.
```ts
function createComponent(domGroup: NestedDOM, closeTags: string[] = [], nodes: string = ''): string {
    let nodeString: string = nodes || '';
    let cTags: string[] = closeTags || [];

    if(typeof domGroup !== 'object' || !domGroup) {
        while(cTags.length !== 0) {
            nodeString += cTags.pop();
        }
        return nodeString;
    }

    const tag = domGroup.tag;
    nodeString += `<${ tag }>`;
    cTags.push(`</${ tag }>`);

    if(domGroup.textNode) {
        nodeString += domGroup.textNode;
    }

    if(domGroup.children) {
        domGroup.children.forEach((child) => {
            nodeString = createComponent(child, cTags, nodeString);
        });
    } else {
        nodeString += cTags.pop();
        return nodeString;
    }
    return nodeString;
}

document.body.innerHTML = createComponent(domGroup);
```

#### readonly 프로퍼티
```ts
// TS
interface ReadonlyStringArray {
    readonly [index: number]: string;
}
let myArray: ReadonlyStringArray = ["Alice", "Bob"];
myArray[2] = "Mallory"; // error!
```
readonly 를 앞에 붙이게되면 읽기전용이됩니다.

## 클래스 타입
클래스에서도 인터페이스를 사용할 수 있습니다. `implements` 라는 키워드를 통해 구현합니다.

```ts
// TS
interface ClockInterface {
    currentTime: Date;
}

class Clock implements ClockInterface {

}
```
위의 코드는 에러를 뱉습니다.
```text
TS2420: Class 'Clock' incorrectly implements interface 'ClockInterface'.
 Property 'currentTime' is missing in type 'Clock' but required in type 'ClockInterface'.
```

`implements` 라는 키워드가 있다면 해당 인터페이스를 무조건 구현해야합니다.  
또한 **인터페이스를 구현하는 클래스는 `public` 만을 사용할 수 있는데** 그 이유는 `private` 로 구현을 하면 인터페이스를 구현했는지 안했는지 모르기 때문입니다.  

추가적으로 인터페이스를 구현한 클래스의 타입은 인터페이스가 될 수 있습니다.

```ts
// TS
interface ClockInterface {
    currentTime: Date;
}

class Clock implements ClockInterface {
    public currentTime: Date;
    // private _currentTime: Date; // Error!
}

const digital: ClockInterface = new Clock();
```

## 확장 인터페이스
인터페이스도 클래스처럼 `extends` 키워드를 통해 확장할 수 있습니다. 인터페이스를 분리함으로써 재사용성이 뛰어나게 됩니다.
```ts
// TS
interface DOM {
    display: string;
    tag: string;
}

interface TextNode extends DOM {
    text: string;
}

interface InputNode extends DOM {
    type: string;
}

const textNode: TextNode = {
    display: 'inline',
    tag: 'text',
    text: 'heecheolman',
};

const InputNode: InputNode = {
    display: 'inline-block',
    tag: 'input',
    type: 'button',
};
```

## Hybrid 타입
자바스크립트의 프로퍼티에는 함수도 포함될 수 있습니다. 확장 인터페이스에서의 예제를 응용해본다면 InputNode 는 click 메서드를 통해 사용자의 이벤트를 받을 수 있어야할 것 같습니다.
```ts
// TS
// ... 생략
type eventDOM = object;

interface InputNode extends DOM {
    type: string;
    click(eventDOM: object): void;
}

const InputNode: InputNode = {
    display: 'inline-block',
    tag: 'input',
    type: 'button',
    click(eventDOM: object) {
        console.log(`${ eventDOM } was clicked!`);
    }
};
```
`click` 이라는 메서드는 `DOM` 을 받아서 클릭이벤트를 수행합니다.  
`type eventDOM = object` 를 통해 `click()` 메서드의 파라미터에 대한 타입을 명시적으로 잡아줬습니다.

## 클래스에서의 인터페이스 확장

추가예정


## 참고문서
* [Typescript 핸드북 3 - 인터페이스[번역]](https://infoscis.github.io/2017/05/20/TypeScript-handbook-interfaces/)
* [Typescript - 인터페이스 - PoiemaWeb](https://poiemaweb.com/typescript-interface)
* [[TS] 4. Interface in Typescript - Jbee](https://jaeyeophan.github.io/2017/12/28/TS-4-Interface-in-TypeScript/)
* [4.2 색인 가능 타입 - ts-for-jsdev](https://ahnheejong.gitbook.io/ts-for-jsdev/04-interface-and-class/indexable-types)
* [타입스크립 기초강의(2) - Woongjae Lee](http://slides.com/woongjae/deck-8-14)
* [[Typescript] Index Signatures(Indexable types) - 금광캐는광부](http://itmining.tistory.com/87)
* [typescript interface 완 - jsdev](https://jsdev.kr/t/typescript-interface/3168)
* [How to Define an Interface in Typescript - WebDevZone](https://dzone.com/articles/how-to-define-an-interface-in-typescript)
