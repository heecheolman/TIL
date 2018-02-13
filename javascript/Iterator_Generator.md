# 이터레이터, 이터러블, 제너레이터

* for
* forEach()
* for...in
* for...of
* 심볼(Symbol)
* 인터페이스(Interface)
* 이터레이터(Iterator)
* 이터러블(Iterable)
* 제너레이터(Generator)


## for
배열루프를 순회하기위한 일반적인 방법
```javascript
for(var i = 0; i < arr.length; i++){
  console.log(arr.length);
}
```
## forEach()
``` JavaScript
arr.forEach(callback[, thisArg]){

}
```
`arr` : 순회할 배열  
`callback` : 각 요소에 대해 실행할 함수이며, 인수 세개를 가짐  
1. `currentValue` : 현재처리중인 요소
2. `index` : 현재처리중인 `index`
3. `array` : `forEach()` 를 적용중인 배열  

`thisArg` : 선택이며, `callback` 함수를 실행할 때 `this` 로서 사용되는 값  

**주의사항**  
* `break`, `return` 을 통해 `forEach()` 를 탈출할 수 없습니다.
* 최초 `callback` 전에 `forEach()` 의 처리요소의 범위가 결정


[MDN forEach() 참고](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Array/forEach)


```javascript
var arr = [1, 2, , 4];

var a = arr.forEach(function(currentValue, index, array){
    console.log(`arr[${index}] : ${currentValue},  array : ${array}`);
    // if(value === 2) break; // SyntaxError: Illegal break statement
});
console.log(a);
/* 출력값
arr[0] : 1,  array : 1,2,,4
arr[1] : 2,  array : 1,2,,4
arr[3] : 4,  array : 1,2,,4
undefined
*/
```
```javascript
function Counter() {
    this.sum = 0;
    this.count = 0;
}
Counter.prototype.add = function(array) {
    console.log(`array.length : ${array.length}`);
    array.forEach(function(entry) {
        (function(){array[6] = 5;})();
        this.sum += entry;
        ++this.count;
    }, this);
    console.log(`array.length : ${array.length}`);
};

var obj = new Counter();
obj.add([2, 5, 9]);
console.log(obj.count);
console.log(obj.sum);
/* 출력값
array.length : 3
array.length : 7
3
16
 */
```
첫번째 예제는 각 인수들이 무엇인지 알아봤고 반환값은 `undefined` 라는 것을 확인했다.   
두번째 예제에서 `this` 를 전달하는데 객체 자신을 전달하므로 값이 각각 다르게 나온다.  

또한 `forEach()` 문의 `callback` 함수 내에서 요소의 범위를 변경했지만 `count` 와 `length` 에 영향이 없는 이유는 요소의 범위 결정은 `callback` 호출 전에 결정되기 때문이다

## for ... in
```javascript
for(variable in object){
  statement
}
```

`variable` : 매 반복마다 다른 속성이름이 지정  
`object` : 매 반복을 실행할 객체  

**주의사항**
* 비열거형 속성을 가진 객체는 반복하지 않음
* `variable` 에 할당된 값들은 숫자가 아닌 문자열이다, 배열반복에 적합하지 않음
* 반복중에 이미 반복이 끝난 객체의 속성의 변경이 있다면 반복중에 변경 전의 값이 참조됨
* 반복중에 반복이 되지 않은 객체의 속성이 제거되면 제거된 속성을 제외하고 반복
* 상속받은 속성 또한 순회한다

``` JavaScript
var str = {
    a: 1,
    b: 2,
    c: 3
}
for(v in str){
    console.log(`${v} : ${str[v]}`); // 속성 출력
    delete str.a; // a 속성이 제거되었지만 이전 반복이 끝난 상태여서 이전 값을 참조
}
console.log(typeof v);
console.log(str);
/* 출력값
a : 1
b : 2
c : 3
string
{ b: 2, c: 3 }
 */
```
``` JavaScript
var str = {
    a: 1,
    b: 2,
    c: 3
}
for(v in str){
    console.log(`${v} : ${str[v]}`); // 속성 출력
    delete str.b; // 반복이 시작되지않은 b속성을 제거하면 제거한 값을 빼고 반복
}
console.log(str);
/* 출력값
a : 1
c : 3
{ a: 1, c: 3 }
 */
```
```javascript
var str = {
    a: 1,
    b: 2,
    c: 3
}

Object.defineProperty(str, 'a', {enumerable: false}); // a속성을 열거불가능하게 했다
for(variable in str){ // 열거 불가능한 요소는 반복하지않는다
    console.log(`${variable} : ${str[variable]}`);
}
console.log(str.a); // 하지만 a 속성은 존재
console.log(Object.keys(str).length);
// Object.keys() 는 열거형 속성을 문자열을 요소로갖는 배열로 반환, 반환한 배열의 length
/* 출력값
b : 2
c : 3
1
2
 */
```

## for...of
```JavaScript
for(variable of iterable){
  statement
}
```
`variable` : 각 반복에 서로다른 속성값  
`iterable` : 반복되는 열거가능(enumerable)한 속성이 있는 객체  

 엄밀히 말하면, `[Symbor.iterator]` 속성이 있는 모든 컬렉션 요소에대해 반복


let 이외에 const도 사용가능.  
단, 블록 내부에서 변수를 수정하지 않는 경우
###### Array
```javascript
var iterable = [1, 2, ,3];
for(const value of iterable){
    console.log(value);
}
/* 출력값
1
2
undefined
3
 */
console.log(iterable[Symbol.iterator]()); // next() 존재
```
###### String
```JavaScript
var iterable = "hello";
for(let value of iterable){
    console.log(value);
}
/* 출력값
h
e
l
l
o
 */
console.log(iterable[Symbol.iterator]());
// StringIterator {} 내에 next() 존재
```
###### Map
```javascript
var iterable = new Map([["a", 1], ["b", 2], ["c", 3]]);

for(let entry of iterable){
    console.log(entry);
}
for(let [key, value] of iterable){ // 디스트럭쳐링에 관해 따로 commit
    console.log(`${key} : ${value}`);
}
/* 출력값
[ 'a', 1 ]
[ 'b', 2 ]
[ 'c', 3 ]
a : 1
b : 2
c : 3
 */
console.log(iterable[Symbol.iterator]());
//next() 존재
```
###### Object.keys() 이용
```javascript
var non_iterable = {
    name: "heecheol",
    age: 24
}
// for(let value of non_iterable){
//     console.log(value); // error! non_iterable is not iterable
// }
for(let key of Object.keys(non_iterable)){
    console.log(`${key}: ${non_iterable[key]}`);
}
for(let key in non_iterable){
    console.log(`${key}: ${non_iterable[key]}`);
}
/* 출력값
name: heecheol
age: 24
name: heecheol
age: 24
 */
var foo = Object.keys(non_iterable)[Symbol.iterator]();
console.log(foo); // next() 존재
```

## 심볼 (Symbol)

```JavaScript
Symbol([description])
```
`description` : 선택적으로 문자열을 넣을 수 있으며, 디버깅을위해 사용가능하나 심볼에 접근하는 용도로는 불가능

심볼(Symbol)은 ES6의 새로운 원시타입이다
* Object
* Null
* Undefined
* String
* Number
* Boolean
* Symbol

```javascript
console.log(typeof Symbol()); // symbol
```

심볼의 특징은 고유하고 변하지 않는다는 것이다.  
다음 코드를 보자.

```JavaScript
var str1 = "hello";
var str2 = "hello";
console.log(str1 === str2); // true

var symbol1 = Symbol();
var symbol2 = Symbol();
console.log(symbol1 === symbol2); // false

var symbol3 = Symbol('mySymbol');
var symbol4 = Symbol('mySymbol');
console.log(symbol3 === symbol4); // false
// var symbol5 = new Symbol();
// error! TypeError: Symbol is not a constructor
```
`Symbol()`은 매호출마다 고유한 심볼을 만든다.

심볼을 사용하는 이유는 무엇일까?

심볼은 고유하다고했다. 그러므로 `description`이 같아도 충돌하지 않는다.  
다시 말하면, 설령 다른사람의 코드의 속성과 내 속성의 이름이 같아도 충돌하지 않는다는 것이다

```JavaScript
Symbol.for(key)
```
`key` : String이며 필수

`Symbol.for()`는 전역 심볼레지스트리 리스트에 심볼을 만든다.  
`Symbol()` 과는 다르게 매 호출시 고유한 심볼을 만들지 않고, 전역 심볼레지스트리 리스트에 해당 `key`가 있는지 검사를 한다. 검사를 하고 해당 `key` 가 존재하면 그 심볼을 반환. 없으면 새로운 전역 심볼생성
```javascript
var saveSym1 = Symbol.for('foo'); // 새로운 전역심볼 생성
var saveSym2 = Symbol.for('foo'); // 이미 만들어진 심볼을 검색하고 있다면 그 심볼 반환

console.log(saveSym1 === saveSym2); // true
```
심볼을 키로 갖는 속성은 점(dot) 을 이용해서 접근 할 수 없다. 반드시 []를 통해 접근한다.
```JavaScript
var prop2 = Symbol('prop2');

var obj = {
    prop1: "hello",
    [prop2]: "world"
}
for(var key in obj){
    console.log(obj[key]);
}
console.log(obj[prop2]); // 괄호를 이용해 접근
/* 출력값
hello
world
 */
```
또한 심볼은 `for...in`과 같은 객체의 속성을 순회하는 문법에 걸리지 않는다.

`Object.getOwnPropertySymbols(object)` : 해당 `object` 의 심볼 키를 갖는 객체 반환
`Reflect.ownKeys(object)` : 해당 `object` 의 문자열 키, 심볼 키를 갖는 객체 반환

``` JavaScript
var sym1 = Symbol();
var sym2 = Symbol('sym2');
var sym3 = Symbol('sym3');

var obj = {
    [sym1] : 1,
    [sym2] : 2,
    [sym3] : 3,
    name: "heecheolman"
}

console.log(Object.getOwnPropertySymbols(obj));
console.log(Reflect.ownKeys(obj));


var foo = Object.getOwnPropertySymbols(obj);
var foo2 = Reflect.ownKeys(obj);
console.log(typeof foo);
console.log(typeof foo[0]);
console.log(foo.length);
console.log("====");
console.log(typeof foo2);
console.log(typeof foo2[0]);
console.log(typeof foo2[1]);
/* 출력값
[ Symbol(), Symbol(sym2), Symbol(sym3) ]
[ 'name', Symbol(), Symbol(sym2), Symbol(sym3) ]
object
symbol
3
====
object
string
symbol
 */
```
결론은 심볼은 객체에 고유한 속성을 만듦으로써 다른 라이브러리와의 충돌을 막기 위함이다.
## 인터페이스(Interface)
##### 인터페이스란?
1. 사양에 맞는 값과 연결된 속성키의 세트
2. 어떤 `Object` 라도 인터페이스의 정의를 충족
3. 하나의 `Object` 는 여러개의 인터페이스를 충족 가능


 ```JavaScript
{
  a: 정수
}
 ```
 > a 라는 키를 가지고있고 a 에는 정수가 들어있어야 한다.

 이것은 a 인터페이스 인것이다. 어떤 `Object`라도 a 라는 키를 가지고있고 a에 정수가 들어있다면 a 라는 인터페이스를 따르고 있다는 것을 뜻한다. 그렇기 때문에 하나의 `Object`에 여러개의 인터페이스를 충족하는것이 가능하다

#### 이터레이터 인터페이스 (Iterator Interface)

이터레이터 인터페이스는 `next` 라는 키를 갖고있고 인자를 받지 않으며 `value` 와 `done` 이라는 키를 `객체`를 반환한다. 이터레이터 인터페이스는 다음과 같다.
```JavaScript
{
  next: function(){
    return {value: 1, done: false};
  }
}
```

`done` : 순회를 마치면 `true`, 아닐시 `false`  
`value` : 콜렉션의 현재 요소 값



```JavaScript
var obj = {
    array: [1, 2, 3, 4],
    next: function(){
        return {
            done: this.array.length == 0,
            value: this.array.pop()
        };
    }
}

console.log(obj.next());
console.log(obj.next());
console.log(obj.next());
console.log(obj.next());
console.log(obj.next());
/* 출력값
{ done: false, value: 4 }
{ done: false, value: 3 }
{ done: false, value: 2 }
{ done: false, value: 1 }
{ done: true, value: undefined }
 */
```


#### 이터러블 인터페이스 (Iterable Interface)
이터러블(Iterable) 이란 순회가능한 자료구조이다. 이터러블 인터페이스란 `[Symbol.iterator]` 키를 갖고있고, 값으로 인자를 받지 않고  `이터레이터 객체`를 반환한다.
```javascript
{
  [Symbol.iterator]: function(){
    return {
      next: function(){
        return {value: 1, done: false};
      }
    };
  }
}
```
`[Symbol.iterator]` 키를 가지고있고 인자를 받지 않는다. 또한 `이터레이터 객체`를 반환한다
#### 공급과 소비
```javascript
let arr = [1, 2, 3, 4];
while(arr.length >= 0){
  console.log(arr.pop());
}
```
`while` 문을 살펴보도록 하자
```
while( 계속 반복할지 판단 ) {
  반복시마다 처리할 것
}
```
데이터에 대한 공급 : `계속 반복할지 판단` 부분과 `반복시마다 처리할 것`  
데이터에 대한 소비 : `while`문 자체는 데이터 공급에대한 소비이다.

`이터레이터 인터페이스` 에 맞춰서 본다면

``` javascript
var obj = {
    array: [1, 2, 3, 4],
    next: function(){
        return {
            done: `계속 반복할지 판단`
            value: `반복시마다 처리할 것`
        };
    }
}
```
> es6 부터는 객체리터럴을 쓰면 위에서 아래로 해석이 된다

현재 위의 코드는 데이터에대한 공급이 준비가 된 것이다.

`이터레이터`를 다시 한번 살펴보자
1. 반복자체를 하지는 않음
2. 외부에서 반복을 하려할 때
3. 반복에 필요한 조건과 실행을
4. 미리 준비해둔 객체

다시말하면, 반복행위와 반복을위한 준비를 분리했다.

이터레이터는 미리 반복에대한 준비를 해두고 필요할 때만큼 반복할 수 있다. 그리고 반복을 재현할 수 있다.

`while`과는 다르게 이터레이터는 `next()` 메서드를 호출 할때만 반복이 되고, `이터레이터`를 여러번 준비해두면 똑같은 반복을 언제든 재현할 수 있다

직접 이터레이터 반복처리기를 만들어본다면 다음과 같다. 보기 편하게 코드를 나누었지만 합쳐진 코드이다
```JavaScript
const loop = (iter, f) => {

    // iterable 이면 iterator 획득
    if(typeof iter[Symbol.iterator] == 'function'){
        iter = iter[Symbol.iterator]();
    }

    //iterator가 아니라면 건너뜀, 이런 패턴을 쉴드패턴(Shield pattern)
    if(typeof iter.next != 'function') return;

    while(true){
        const val = iter.next();
        if(val.done) return; // val.done 이 true 라면 종료
        f(val.value); // 아닐 시 val.value 전달
    }
};
```
하나의 `Object` 에는 여러개의 인터페이스를 구현 가능하다. 다음의 `obj` 객체는 이터러블 인터페이스와, 이터레이터 인터페이스를 동시에 구현하고있다.

```JavaScript
var obj = {
    [Symbol.iterator](){return this;},
    array: [1, 2, 3, 4],
    next(){
        return {
            done: this.array.length == 0,
            value: this.array.pop()
        };
    }
};

loop(iter, console.log);
/* 출력값
4
3
2
1
*/
```

사실 `for...of` 의 작동방식은 `[Symbol.iterator]()` 메서드를 먼저 호출해서 `이터레이터 객체` 를 얻고 `next()` 메서드를 호출 하는 방식으로 반복된다.

즉,  `for...of` 는 `이터러블 인터페이스` 를 갖추고있는 모든 컬렉션에 대해 반복 가능하다.


다음코드를 다시 보자.
```javascript
var obj = {
    [Symbol.iterator](){return this;},
    array: [1, 2, 3, 4],
    next(){
        return {
            done: this.array.length == 0,
            value: this.array.pop()
        };
    }
};
```
`obj` 를 반복하기 위해 `for...of` 구문을 쓰면 반복이 된다. 여기서 눈여겨봐야 할 점은 `array: [1, 2, 3, 4]` 구문이다.  
`for...of` 는 `next()` 메서드가 호출면서 반복을하는데, 적어도 `next()` 메서드가 실행되기 전까지는 데이터를 준비할 필요가 없다는 것이다.  
`next()` 함수가 실행되는 시점에 값을 만들어놔도 무방하다는 말이다.  

설명을 위해 `class` 개념을 잠깐 도입한다.
```javascript
const N2 = class {
    constructor(max){
        this.max = max;
    }
    [Symbol.iterator](){
        let cursor = 0, max = this.max;
        return {
          done: false,
          next() {
              if(cursor >= max){
                  this.done = true;
              }else{
                  this.value = cursor * cursor;
                  cursor++;
              }
              return this;
          }
        };
    }
};
console.log([...new N2(5)]);

for(const v of new N2(5)){
    console.log(v);
}
/* 출력값
[ 0, 1, 4, 9, 16 ]
0
1
4
9
16
*/
```
여기서 우리는 `value` 에 대한 값을 미리 정의하지 않았다. `next()` 함수를 호출하고 나서야 `value` 의 값이 정해졌다.

## 제너레이터 (Generator)
다음과 같이 생긴 함수를 `Generator Function` 이라 한다
```javascript
function* name(parameter) {
   statements
}
```
`name` : 함수명  
`parameter` : 함수에 전달되는 인수, 최대 255개  
`statement` : 함수의 본체

제너레이터 함수는 일반 함수와는 다르다. 일단 키워드 `function` 뒤에 `*` 를 찍는다. 또한 일반함수는 스스로 실행을 멈출 수 없는데 비해 제너레이터 함수는 `yield` 구문을 통해 `return` 과 같이 구문 뒤의 값을 반환한다. 이 때, 값을 생략하면 `undefined` 가 반환된다. `return`과 다르게 `yield`는 함수를 종료시키지 않는다.

`function * name`  
`function* name`  
`function *name`  
세개의 문장 전부 동일한 문장이다. 편한 방법을 쓰면 되겠다.

사용방법은 이렇다.
1. `Generator Function` 을 호출되고 `Generator Object` 가 반환

2. `Generator Object` 는 `이터러블 인터페이스` 와 `이터레이터 인터페이스` 를 갖춘다.

3. `Generator Object` 에 `next()` 메서드를 호출, 위치를 기억

4. `Generator Function` 실행

5. `yield` 구문을 만나면 정지하고 기억된 위치의 `next()` 의 반환 객체인 `Iterator Object` 의 `value` 에 `yield` 구문의 뒤의 값이 저장되고,   `done` 에는 반복이 가능한지 `Boolean` 값으로 저장. 이 때, 함수는 끝나지않고 `yield`의 위치를 기억한다.

6. `next()` -> `yield` -> `next()` -> `yield` _... 반복_

7. 반복 중간에 `Generator Function` 내부의 `return` 문이 있다면 `return`문 뒤의 행(line)들은 무시된다.

8. 또한 `Generator Function` 외부에서 `GeneratorObject.return(parameter)` 문을 만나면 `parameter` 값이 `Iterator Object`의 `value` 에 반환되고 `done` 은 `true`

9. `Generator Function` 의 모든 반복이 끝나고 나서도 `next()` 를 호출하면 `value: undefined, done: true` 속성을 가진 `Iterator Object` 반환

장황하지만 요약하자면 반복시 `yield` 를 만나면 그 다음 `next()` 가 실행되기 전까지 멈추는 것이다.

`yield` 와 `next()` 는 서로 데이터를 주고 받을 수 있다.  
5번을 보면 `yield`가 `IteratorObject` 의 `value` 에 값을 전달한다.  

위의 순서를 기반으로 예제 코드를 보자.

``` JavaScript
function* generatorFunc(){
    console.log("제너레이터 함수 시작!");
    yield 1; // a 에는 yield 1; 이 할당되므로 undefined
    const a = yield 5;
    console.log(a);
    const b = yield (6 + a);
    const c = yield 1 + b;
    const d = yield 2 + c;
    return b + c + d;
    yield 10;
}

const gnObj = generatorFunc();

console.log(typeof gnObj[Symbol.iterator] === 'function'); // true, 이터러블 인터페이스를 갖춤
console.log(typeof gnObj.next === 'function'); // true, 이터레이터인터페이스를 갖춤
console.log(gnObj === gnObj[Symbol.iterator]()); // true, 제너레이터객체는 이터레이터
// 제너레이터 함수는 이터러블 인터페이스와 이터레이터 인터페이스를 동시에 갖추고있다.

console.log(gnObj.next());
//      출력: 제너레이터 함수 시작!
// yield 문 뒤의 1이 value 에 반환
//      출력: { value: 1, done: false }

console.log(gnObj.next());
// yield 문 뒤의 5가 value 에 반환
//      출력: { value: 5, done: false }

console.log(gnObj.next());
// next() 를 호출할때 아무 인자도 넣지 않았으므로, const a 는 undefined
//      출력: undefined
// 6 + a 인데 a 가 undefined 이므로 NaN 반환
//      출력: { value: NaN, done: false }

console.log(gnObj.next(50));
// 50을 parameter로 전달, const b = 50;
// yield 50 + 1이 반환
//      출력: { value: 51, done: false }

console.log(gnObj.next(100));
// 100을 parameter로 전달, const c = 100;
// yield 100 + 2 반환
//      출력: { value: 102, done: false }

console.log(gnObj.next(200));
// 200을 parameter로 전달, cont d = 200;
// return b + c + d = 350 반환, return 문을 만났으므로 done: true
//      출력: { value: 350, done: true }

console.log(gnObj.next());
//return문 뒤에 yield 가 있지만 return으로 done: true 라서 undefined 반환
//      출력: { value: undefined, done: true }
```
다음 예제는 외부에서 `GeneratorObject.return(parameter)` 를 호출할 때이다.

```JavaScript
function* gnFunc(){
    yield console.log("hello");
    yield console.log("heecheol");
}
const gnObj = gnFunc();

console.log(gnObj.next());
// console.log("hello") 메서드가 실행이 된 후 console.log()의 반환값인 undefined 이 value에 반환
//          출력: hello
//          출력: { value: undefined, done: false }

console.log(gnObj.return(5));
// 제너레이터함수 외부에서 return()을 호출하여 제너레이터함수가 종료
// parameter가 IteratorObject 의 value 값에 저장되며 return() 호출로 반복을 종료했으므로 done은 true
//          출력: { value: 5, done: true }

console.log(gnObj.next());
//  next()를 호출하면 반복이 종료됐으므로 undefined와 true를 반환
//          출력: { value: undefined, done: true }

```

`yield *` 라는 키워드도 있는데 이 키워드는 구문이 아닌 표현이며 표현은 값이된다.

```javascript
yield* expression;
```
`expression` : `Iterable Object`를 반환하는 표현식  
`yield *` 표현자체가 다른 `IterableObject`를 순회한다는 뜻  
`yield *`의 값은 `Iterator Object` 의 `done`키가 `true` 일 때 반환되는 값이다.

조금 길더라도 `next()` 메서드를 하나씩 실행해보면서 눈으로 확인하는게 빠르다

```javascript
function* gnFunc1(){
    const a = yield* gnFunc2();
    yield a;
    const attention = yield* [4, 5];
    console.log(attention);
    const attention2 = yield* (function*(){yield 6; yield 7;})();
    // yield* function*(){yield 8; yield 9;}; // 제너레이터함수를 선언한것이지 이터러블객체를 반환하는 표현이 아님
    console.log(attention2);
    const result = yield function*(){yield 8; yield 9; return "NotFinish"; }
    return result;
}
function* gnFunc2(){
    yield 1;
    yield 2;
    return "foo";
    yield 4;
}
const gnObj = gnFunc1();

console.log(gnObj.next());
// gnFunc2()가 호출되면서 나온 이터러블객체(= 제너레이터객체)를 next()로 호출함으로서 순회하고 반환되는 값을 yield
// 제너레이터객체의 첫번째 yield 뒤의 1이 gnObj이터레이터 value키의 값이 되고 yield
//      출력: { value: 1, done: false }

console.log(gnObj.next());
// 제너레이터객체의 두번째 yield 뒤의 2가 gnObj이터레이터 value키의 값이 되고 yield
//      출력: { value: 2, done: false }

console.log(gnObj.next());
// 제너레이터객체는 이때 return을 만나서 { value: "foo", done: true }
// done키가 true인 value "foo"가 yield*의 값이됨
// yield*의 값인 "foo"가 a에 할당
// a가 gnObj이터레이터의 value가 됨
//      출력: { value: 'foo', done: false }

console.log(gnObj.next());
// 이터러블객체인 Array를 next()로 호출함으로서 순회하고 반환되는 값을 yield
// 4가 반환되고 yield
//      출력: { value: 4, done: false }

console.log(gnObj.next());
// 5가 반환되고 yield
// 여기서 진짜 주의해야 할 점은 아직 Array의 속성은 { value: 5, done: false } gnObj이터레이터의 속성과는 별개
// gnObj이터레이터의 value는 5가 되고 yield, 아직 done이 false이므로 yield*의 값이 정해지지않음
//      출력: { value: 5, done: false }

console.log(gnObj.next());
// 이때의 next() 호출로 Array의 마지막이터레이터 속성은 { value: undefined, done: true } done이 true이므로
// yield*의 값은 undefined로 정해짐
// yield*의 값인 undefined가 attention에 할당
//      출력: undefined
// 제너레이터객체가 반환되는 제너레이터즉시실행함수 호출
// 제너레이터객체의 첫번째 yield문 뒤의 6이 gnObj이터레이터의 value가 되고 yield
//      출력: { value: 6, done: false }

console.log(gnObj.next());
// 제너레이터객체의 두번째 yield문 뒤의 7이 gnObj이터레이터의 value가 되고 yield
// 여기서도 주의, 이 때 제너레이터객체의 이터레이터 속성은 { value: 7, done: false } done이 false이므로
// yield*의 값이 정해지지않음
//      출력: { value: 7, done: false }

const gnFunc3 = gnObj.next().value;
// 이때 제너레이터객체의 이터레이터 속성은 { value: undefined, done: true } done이 true이므로
// yield*의 값은 undefined로 정해짐
//      출력: undefined

// 여기서 gnFunc1()의 마지막 yield 는 제너레이터 함수를 반환한다.
// 반환된 제너레이터 함수는 gnObj 이터레이터의 value키에 저장되므로 .value를 통해 접근
// gnFunc3에 제너레이터 함수 저장
// 물론 .value()를 통해 바로 제너레이터 객체를 얻을 수 있지만 천천히 개념을 잡기위해 이렇게함

console.log(typeof gnFunc3);
//      출력: function

const gnObj2 = gnFunc3();
// gnFunc3() 를 호출해서 반환된 제너레이터 객체를 gnObj2에 할당

console.log(gnObj2.next());
// gnObj2 이터레이터의 value에 8 저장 후 yield
//      출력: { value: 8, done: false }


console.log(gnObj2.next());
// gnObj2 이터레이터의 value에 9 저장 후 yield
//      출력: { value: 9, done: false }
// 여기서 done이 false 인 이유는 아직 yield로 정지 되어있기 때문임

console.log(gnObj2.next());
// return 구문을 만나 gnObj2의 마지막 이터레이터 속성이 { value: "NotFinish", done: true }
//      출력: { value: "NotFinish", done: true }
// 그러나 아직 gnObj는 yield 되어있음

console.log(gnObj.next('Finish'));
// parameteter로 'Finish' 를 전달해 result에 할당
// return 구문을 만나서 result가 gnObj 마지막 이터레이터의 value가 되고
// 반복이 끝나서 done은 true
//      출력: { value: 'Finish', done: true }
```
##### 참조링크
[http://nomad.works/study/front-end/javascript/es6-3/](http://nomad.works/study/front-end/javascript/es6-3/)  
[http://www.bsidesoft.com/?p=2913](http://www.bsidesoft.com/?p=2913)  
[http://hacks.mozilla.or.kr/2015/08/es6-in-depth-iterators-and-the-for-of-loop/](http://hacks.mozilla.or.kr/2015/08/es6-in-depth-iterators-and-the-for-of-loop/)
[http://hacks.mozilla.or.kr/2015/08/es6-in-depth-generators/](http://hacks.mozilla.or.kr/2015/08/es6-in-depth-generators/)
[http://meetup.toast.com/posts/73](http://meetup.toast.com/posts/73)  
[https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Generator](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Generator)
[https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Statements/function*](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Statements/function*)  
[https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Operators/yield*](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Operators/yield*)  
[https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Generator](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Generator)

> 개인적으로 [http://www.bsidesoft.com/?p=2913](http://www.bsidesoft.com/?p=2913) 여기있는 GDG DevFest 2016 유튜브 자료는 꼭 보길 바란다.
