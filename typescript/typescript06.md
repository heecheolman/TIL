<div align=center>
<img src="https://pbs.twimg.com/profile_images/743155381661143040/bynNY5dJ_400x400.jpg" width="80" height="80">
</div>

# 타입스크립트 제네릭
자바스크립트에는 없지만 타입스크립트에 있는 제네릭(Generics)을 알아보겠습니다. 클래스나 함수의 목적중 하나는 '재사용성'에 있습니다. 이 제네릭을 이용하게되면 재사용성이 한층 더 증가합니다. 일종의 '틀' 이라고 생각하시면 됩니다. 타입스크립트에서 제네릭을 어떻게 쓰는지에대해 알아보도록 하겠습니다.

## 📝 목차
* [기존의 문제점](#기존의-문제점)
* [클래스에서의 제네릭](#클래스에서의-제네릭)
* [함수에서의 제네릭](#함수에서의-제네릭)
* [제약조건](#제약조건)
* [마무리](#참고문헌)

---

## 기존의 문제점
예를들어 `number`, `text`, `operator(연산자)` 각 종류별로 버튼들이 존재할 때 이 버튼들을 담으려 할 때 담는 일종의 '그릇'을 각각 만들어줘야 할 것 입니다.

```ts
// TS
class NumberButton {}
class TextButton {}
class OprButton {}

class NumberButtonContainer {}
class TextButtonContainer {}
class OprButtonContainer {}
// ...
```
> 클래스 이름이 너무 길어졌습니다... 양해 부탁드립니다.

사실 위의 코드는 `Container` 라는것은 동일하고 그 내부 기능들도 동일하다고 가정을 한다면 제네릭을 이용하여 재사용성을 높이는 것이 더 좋을것 같습니다.

## 클래스에서의 제네릭
위의 코드에서 제네릭을 이용해 바꾸어보겠습니다.
```ts
// TS
class NumberButton {}
class TextButton {}
class OprButton {}

class ButtonContainer<T> {
    private container: T[];

    getButton(index: number) {
        return this.container[index];
    }

    // ...
}

const numberContainer = new ButtonContainer<NumberButton>();
const textContainer = new ButtonContainer<TextButton>();
const oprContainer = new ButtonContainer<OprButton>();
```

주목해야할 점은 `<T>` 입니다. type 의 약자로 보통 T 를 쓰지만 변경할 수 있습니다. `type` 에서 따왔듯이 타입에따라 틀이 바뀐다는 점입니다.

생성할때도 마찬가지로 `()` 전에 `<>` 꺾쇠괄호 안에 타입을 주입합니다.

#### 주의해야할 점
제네릭에서 클래스 타입의 `static` 멤버는 갖을 수 없습니다.
```ts
// TS
class ButtonConatiner<T> {
    // public static foo: T; Error!

    //  TS2302: Static members cannot reference class type parameters.

    // 생략
}
```

> 이유를 아직 못찾아서 찾게되면 추가하겠습니다.



## 함수에서의 제네릭
함수에서도 동일하게 제네릭을 사용할 수 있습니다.
```ts
// TS
function getFirst(array: any[]): any {
    return array[0];
}
```
다음코드는 배열의 첫번째 요소를 반환하는 코드입니다. `any`를 사용한것을 볼 수 있는데 이것을 제네릭으로 바꿔보겠습니다.

```ts
// TS
function getFirst<T>(array: T[]): T {
    return array[0];
}
```
함수의 이름 뒤에 `<T>` 가 들어간것을 확인할 수 있습니다. 그리고 호출할 때도 타입을 정해줍니다.

```ts
// TS
getFirst<number>([1, 2, 3]);
getFirst<string>(['h','e','e']);
```

## 제약조건
제네릭을 이용하였지만 해당 프로퍼티가 있는지 없는지에 대해 확신할 수 없습니다. 그래서 컴파일러는 다음 코드에 대해 에러를 뱉습니다.

```ts
// TS
function getHeight<T> (person: T) {
    return person.height; // Error!
    // TS2339: Property 'height' does not exist on type 'T'.
}
```
이 코드는 개발자 입장에서는 person 이 들어옴을 확신하고 작성했지만 컴파일러에서는 `.height`라는 프로퍼티가 있는지 없는지 알 수 없기 때문에 생긴 에러입니다. 때문에 컴파일러에게 확신을 주게끔 인터페이스를 생성해주고 `extends` 키워드로 제약조건을 만들어줍니다.

```ts
// TS
interface Heightwise {
    height: number;
}

function getHeight<T extends Heightwise> (person: T) {
    return person.height;
}

const myInfo = {
    name: 'heecheolman',
    height: 171,
};

const foo = {
    name: 'bar',
};

console.log(getHeight(myInfo)); // 171
// console.log(getHeight(foo));
// .height  프로퍼티가 없습니다.
```
`Heightwise` 를 상속하여 해당 인터페이스를 구현한 '타입'임을 확신해주었습니다.

## 마무리
기존의 자바스크립트에서는 없었던 제네릭을 타입스크립트에서 사용할 수 있게되었습니다. 타입스크립트의 제네릭 또한 타입을 체크해주는 타입스크립트 문법일 뿐, 직접적인 자바스크립트 코드로 트랜스파일링 해주진 않습니다.

> 아직 배우는 입장이라 구체적으로 써보진 않았지만 Jbee 님의 마무리에 따르면 실제 개발보다는 라이브러리를 개발할 때 많이 사용한다고 하십니다.  

## 참고문헌
* [Typescript 핸드북 6 - 제네릭 [번역]](https://typescript-kr.github.io/pages/Functions.html)
* [[TS] 5. Generics in TypeScript - Jbee](https://jaeyeophan.github.io/2017/12/18/TS-3-Function-in-TypeScript/)
* [TypeScrpt: 제네릭(Generic) - 이상한 모임](http://blog.weirdx.io/post/36224)
