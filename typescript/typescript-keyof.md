# 인덱스타입 (Index types)

인덱스 타입을 사용해 동적 프로퍼티이름을 사용하는 코드를 컴파일러가 검사하도록 할 수 있다.

예시 코드
```ts
function pluck<T, K extends keyof T>(o: T, names: K[]): T[K][] {
  return names.map(n => o[n]);
}

/*

o: T
names: K[]
keyof T 는 T의 키들

*/
```

## 인덱스 타입 쿼리 연산자

`keyof T` 는 인덱스 타입 쿼리 연산자이다. 어떤 타입의 T에 대해 T의 public 프로퍼티 이름들이다.
```ts
interface Person {
  name: string;
  age: number;
}

let personProps: keyof Person;
// 'name' | 'age'
```
Person 에 키값이 추가된다면 자동으로 추가된 해당 키가 `keyof T` 에 업데이트된다. 타입검사이기때문에 미리 해당 키가 무엇인지는 알 수 없다. 컴파일러가 알맞은 프로퍼티를 전달했는지 체크유무정도 할 수 있다.

## 인덱스 접근 연산자

`T[K]` 는 인덱스 접근 연산자이다. `K extends keyof T` 로 기술을 해줘야 어떤키가 있는지 알 수 있는듯 하다.

> T의 키들을 갖는 K 즉, person 의 키들을 갖는 name 헷갈리니 잘 되짚어보자

```ts
function getProperty<T, K extends keyof T>(o: T, name: K): T[K] {
  return o[name];
}
```
* `o: T`
* `name: K`
* `o[name]: T[K]`

```ts
let name: string = getProperty(person, 'age'); // 나이


let name: string = getProperty(person, 'foo');
// TS2345: Argument of type '"foo"' is not assignable to parameter of type '"name" | "age"'.
```
