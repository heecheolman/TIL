<div align=center>
<img src="https://pbs.twimg.com/profile_images/743155381661143040/bynNY5dJ_400x400.jpg" width="80" height="80">
</div>

# 타입스크립트 함수
타입스크립트의 함수(Functions) 에 대해 알아봅니다. ES6와 작성하는 방법은 크게 다르지 않습니다. 좀 더 타입에 대해 명확해졌을 뿐입니다.

## 📝 목차
* [함수작성](#함수작성)
* [Default Parameter](#default-parameter)
* [Optional Parameter](#optional-parameter)
* [Rest Parameter](#rest-parameter)
* [Union Type](#union-type)
* [Overloading](#overloading)
* [this](#this)

## 함수작성
타입스크립트에서 함수작성하는 방법을 살펴보면 ES6와 크게 다르지않습니다. 매개변수의 타입과 return 타입에 대해 정해줄 뿐입니다.

```ts
// ES6
function add(num1, num2) {
    return num1 + num2;
}

// TS
function add(num1: number, num2: number): number {
    return num1 + num2;
}
```

ES6 문법에서도 함수의 역할을 잘(?) 하고있습니다. 하지만 의도치않게 string 이 넘어와버리면 문자열로 인식하여 concat 이 되어버려 기상천외한 값이 나오게됩니다.  

타입스크립트에서는 이를 막기위해 컴파일타임에 타입을 검사합니다. `num1` 과 `num2` 는 number 타입이며 반환값도 number 타입임을 알려줍니다.

이렇게도 쓸 수 있습니다.
```ts
// TS
const add = (num1: number, num2: number): number => num1 + num2;
```

## Default Parameter
기본 매개변수입니다. 매개변수에 값을 전달하지 않았을 시 나타나는 `undefined` 대신 기본 값으로 초기화를 해줍니다. 타입스크립트에서도 지원합니다.

```ts
// TS
function add(num1: number = 0, num2: number = 0): number {
    return num1 + num2;
}
```

## Optional Parameter
선택적 매개변수입니다. 인터페이스에서의 선택적 프로퍼티처럼 매개변수의 값이 있을수도 있고 없을수도 있는 상황에서 사용합니다. `?` 를 이용하여 선택적인 매개변수로 지정할 수 있습니다.

```ts
// TS
function greet(lastName: string, firstName?: string): string {
    let message = `my name is ${ lastName }`;
    if(firstName) {
        message += firstName;
    }
    return message;
}

console.log(greet('heecheol', 'kim')); // my name is heecheolkim
console.log(greet('heecheol')); // my name is heecheol
```

주의할점이 있다면 선택적 매개변수는 오른쪽 정렬하여 등록해줘야 합니다.

```ts
// TS
function greet(lastName: string, firstName?: string): string { ... } // (O)
function greet(firstName?: string, lastName: string): string { ... } // (X)
```

## Rest Parameter
나머지 매개변수입니다. ES6 에서의 `...(스프레드 연산자)` 를 통해 타입스크립트에서도 동일하게 사용할 수 있습니다. 스프레드 연산자는 배열이므로 타입을 지정해줄 때 배열임을 명시해줍니다.

```ts
// TS
function nameListBuilder(...nameList: string[]) {
    // ...
}
```

## Union Type
타입스크립트에서는 함수의 매개변수나 리턴타입을 정할 때 두가지 이상의 타입일 수 있습니다. 이럴 때 유니온타입을 사용합니다.
```ts
// TS
function numberOrString(data: number | string) {
    if(typeof data == 'number') {
        // ...
    } else if(typeof data == 'string') {
        // ...
    }
}
```
아직까지는 어떻게 사용되는지 잘 모르겠습니다. 타입스크립트로 프로젝트를 진행하며 필요한 경우가 있다면 추후 포스팅하겠습니다.

## Overloading
자바스크립트는 원래 오버로딩이 구현이 안되었습니다. 타입스크립트를 쓴다고 구현이 되는것은 아니지만 비슷하게 구현할 수 있습니다.

```ts
// TS
function greetBuilder(firstName: string, age?: number): void;
function greetBuilder(firstName: string, age: string): void;
function greetBuilder(firstName: string, age: number | string): any {
    let message = `Hi My Name is ${ firstName }`;
    if(typeof age == 'number') {
        message += `, ${ age + 1 } years old at next year`;
    } else if(typeof age == 'string') {
        message += `, ${ age } years old.`;
    }
    return message;
}

console.log(greetBuilder('kim')); // Hi My Name is kim
console.log(greetBuilder('kim', 24)); // Hi My Name is kim, 25 years old at next year
console.log(greetBuilder('kim', '24')); // Hi My Name is kim, 24 years old.
```
`greetBuilder` 라는 함수 시그니쳐가 세개이지만 구현은 마지막에서 하고 있습니다. 구현에서 각 타입에 맞게 분기를 타 반환하는 것을 볼 수 있습니다.

## this
자바스크립트에서 `this` 는 어떻게 사용하는지에 따라 각각 다릅니다. 대표적으로 4가지가 있습니다.

1. 생성자의 this
2. 함수실행의 this
3. 객체의 메서드로서의 this
4. call, bind, apply 에서의 this

여기서 함수실행의 this 와 객체의 메서드로서의 this 의 차이를 잘 알아야합니다.
다음 코드는 에러를 뱉습니다.
```ts
// TS
const lotDrawing = {
    nameList: ['kim', 'hee', 'cheol', 'man'],
    drawing: function() {
        return function() {
            let pickedName = Math.floor(Math.random() * 4);
            return {
                name: this.nameList[pickedName],
            };
        }
    }
};

let nameGenerator = lotDrawing.drawing();
let who = nameGenerator();
console.log(who);
```
`console.log(who)` 가 나오기전에 런타임 에러가 나오는것을 볼 수 있습니다.

#### 에러의 원인
에러의 원인은 `drawing` 메서드 내에 있습니다. `drawing` 내부에서 함수를 반환합니다. 이 '함수'를 반환하는것이 원인입니다. **자바스크립트에서 함수실행에서의 this 는 `global 객체` 입니다.** 그렇기 때문에 기대했던 `this`는 `lotDrawing.nameList` 가 아니라는 것입니다.

#### 화살표 함수
ES6 에서 [화살표함수](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Functions/%EC%95%A0%EB%A1%9C%EC%9A%B0_%ED%8E%91%EC%85%98)를 통해 `this` 를 바인딩합니다.

```ts
// TS
const lotDrawing = {
    nameList: ['kim', 'hee', 'cheol', 'man'],
    drawing: function() {
        return () => {
            let pickedName = Math.floor(Math.random() * 4);
            return {
                name: this.nameList[pickedName],
            };
        }
    }
};

let nameGenerator = lotDrawing.drawing();
let who = nameGenerator();

console.log(who); // {name: "hee"}
// lotDrawing.nameList 중 하나가 랜덤으로 출력
```

화살표 함수를 통해 `this` 를 바인딩하여 넘겨줍니다.

#### this 파라미터
this 를 파라미터로 지정할 수 있습니다. 이렇게 하면 명시적으로 해당 함수에서의 this 가 어떤 것을 가리키는지 알 수 있습니다. **interface** 를 같이 사용하면 다음과 같습니다.

```ts
// TS
interface Person {
    name: string;
}

interface LotDrawing {
    nameList: string[];
    drawing(this: LotDrawing): () => Person;
}

const lotDrawing: LotDrawing = {
    nameList: ['kim', 'hee', 'cheol', 'man'],
    // 해당 메서드에서 this 는 LotDrawing 으로 예상됩니다.
    drawing: function(this: LotDrawing) {
       // 반환타입은 Person
        return (): Person => {
            let pickedName = Math.floor(Math.random() * 4);
            return {
                name: this.nameList[pickedName],
            };
        }
    }
};

let nameGenerator = lotDrawing.drawing();
let who = nameGenerator();

console.log(who); // {name: "hee"}
// lotDrawing.nameList 중 하나가 랜덤으로 출력
```

## 참고문헌
* [Typescript 핸드북 5 - 함수[번역]](https://typescript-kr.github.io/pages/Functions.html)
* [[TS] 3. Function in Typescript](https://jaeyeophan.github.io/2017/12/18/TS-3-Function-in-TypeScript/)
