# 컬렉션 (Collection)

* Map
* Set
* WeakMap
* WeakSet
* 왜 WeakMap 과 WeakSet은 Iterable 하지 않은가?
* 메모리 누수?

일반적인 `Object` 도 `key` 와 `value` 의 쌍을 계속 추가할 수 있는 일종의 컬렉션이다. 하지만 몇가지 문제들이 있다. 기본적으로 `Object` 는
`Object` 의 `Key` 는 문자열과 `Symbol`만이 사용될 수 있고, `[Symbol.iterator]` 를 추가하지않는 한 이터러블하지 않다.  

ES6 컬렉션은 사용자의 `데이터`와 `빌트인(built-in) 메서드의 이름`이 충돌되지 않기 위해 설계되었다. 즉, 컬렉션의 `key`는 빌트인 메서드들과 분리되어있기 때문에 컬렉션 내의 멤버 데이터를 드러내지 않는다. 이러한 이유로 직접적으로 `obj.[key]` `obj.key` 를 이용해 접근이 불가하다.
## Map

#### Map 이란?
`Map` 은 `Key`-`Value` 의 쌍으로 이루어진 컬렉션이다.
```javascript
new Map([iterable])
```
`iterable` : 배열 또는 `key-value` 쌍으로 이루어진 이터러블 객체.

#### Map 은 그럼 언제 사용?
`Object` 를 써야할지 `Map` 을 써야할지 고민이라면 다음과같은 경우를 고려한다.
1. 런타임 전까지 `key` 를 알 수 없을때
2. 모든 `key` 가 동일한타입 or 모든 `value` 가 동일한 타입
3. `key-value` 가 자주 추가되거나 삭제된다
4. 문자열 `key` 이외의 다른 `key`가 필요
5. 데이터가 순회되어야 한다

위의 경우들이 있다면 `Object` 보단 `Map` 을 쓰는것을 고려해본다.

#### Map 의 주요 Method 들과 속성

* `Map.prototype.size` : `Map` 객체에 들어있는 `key-value` 쌍의 개수 반환

* `Map.prototype.clear()` : `Map` 객체의 모든 ` key-value` 제거

* `Map.prototype.has(key)` : `Map` 객체의 해당 `key` 가있는지 검사하고 `Boolean` 값 반환

* `Map.prototype.get(key)` : `Map` 객체의 해당 `key` 에 해당하는 `value` 가 있으면 반환, 없다면 `undefined` 반환

* `Map.prototype.set(key, value)` : `Map` 객체에 주어진 `key` 에 `value` 를 넣고 `Map` 객체 반환

* `Map.prototype.delete(key)` : `Map` 객체의 해당 `key` 와 `value` 를 제거하고, `Map.prototype.has(key)` 메서드로 제거되기 전의 `key`의 존재 여부를 `Boolean` 값 반환

* `Map.prototype.values()` : `Map` 객체안의 모든 `value` 들을 순서대로 가지고 있는 `Iterator`객체 반환

* `Map.prototype.keys()` : `Map` 객체안의 모든 `key` 들을 순서대로 가지고 있는 `Iterator`객체 반환

* `Map.prototype.entries()` : `Map` 객체 안의 모든 요소들을 `[key, value]` 형태의 `array`  순서대로 가지고 있는 `Iterator` 객체를 반환

* `Map.prototype[@@iterator]()` : `Map.prototype.entries()` 와 하는 역할 동일, 동일한 메서드에대한 다른 명칭

* `Map.prototype.forEach(callbackFn[, thisArg])` : `Map` 객체 안에 존재하는 각각의 `key-value` pair에 집어넣은 순서대로 `callbackFn`을 부름. 만약 `thisArg` 매개변수가 제공되면, 이것이 각 `callback의` `this` 값으로 사용

#### 예제

잡탕구리 예제 1

``` javascript
var arr = [1, 2, 3];
let map = new Map([[NaN, "Not a Num"], [arr, "array"]]);
console.log(typeof arr); // object, object도 키가 됨

console.log(map); // Map { NaN => 'Not a Num', [ 1, 2, 3 ] => 'array' }
console.log(map.size); // 2
console.log(map.NaN); // undefined 접근불가
console.log(map.get(NaN)); // Not a Num, get()을 통해서만 접근

console.log(map.set("name", "heecheol"));
/* 해당 키와 값을 넣고 그 map을 반환
Map {
  NaN => 'Not a Num',
  [ 1, 2, 3 ] => 'array',
  'name' => 'heecheol' }
 */

console.log(map.delete(arr)); // true 반환
console.log(map); // Map { NaN => 'Not a Num', 'name' => 'heecheol' }

map.forEach(function(value, key){
   console.log(`${key} = ${value}`);
});
/* 출력값
NaN = Not a Num
name = heecheol
*/
console.log(map); // Map { NaN => 'Not a Num', 'name' => 'heecheol' }
map.clear(); // 키와 값들 제거!
console.log(map); // Map {}
```
잡탕구리 예제 2
```javascript
const map = new Map([[1, "first"], [2, "second"], [3, "third"]]);

// keys(), values() 는 이터레이터 반환
const vals = map.values();
const keys = map.keys();

console.log(vals); // MapIterator { 'first', 'second', 'third' }
console.log(keys); // MapIterator { 1, 2, 3 }

const arr = [...vals];
console.log(arr); // [ 'first', 'second', 'third' ]

console.log(keys.next());
console.log(keys.next());
console.log(keys.next());
console.log(keys.next());
/* 출력값
{ value: 1, done: false }
{ value: 2, done: false }
{ value: 3, done: false }
{ value: undefined, done: true }
 */
```
잡탕구리 예제 3
``` javascript
const map = new Map([[1, "first"], [2, "second"], [3, "third"]]);

map.forEach(function(value, key){
    console.log(`${key} : ${value}`);
});
/*
1 : first
2 : second
3 : third
 */

const iterator = map[Symbol.iterator]();
console.log(typeof iterator.next == "function");
// true, 키와 값이 쌍으로 이루어진 이터레이터 반환

for(const val of iterator){
    console.log(val);
}
// 쌍으로 들어있음을 확인
/* 출력값
[ 1, 'first' ]
[ 2, 'second' ]
[ 3, 'third' ]
 */
```
## Set
#### Set 이란?
`Set` 은 `value` 들로 이루어진 컬렉션.
```JavaScript
new Set([iterable]);
```
`iterable` : 이터러블 객체의 모든 요소가 Set에 추가, 단 값이 중복된다면 하나의 값만 추가되고 매개변수를 명시하지않거나 `null`또는 `undefined` 를 전달하면 비어있는 Set객체 생성

#### 내부에서 일어나는 일!
반환된 이터레이터는 `new Set()` 이 될 때 내부에서 `next()` 함수를 호출해 `done: true` 일때까지 반복합니다. `Set`객체의 `value` 에는 이터레이터가 순회할때 반환된 `value` 값을 저장하게되는데 이때 중복되는 값이 있다면 한개만 저장합니다.

다음코드를 1번, 2번, 3번에 디버깅을 걸면 callStack 부분에 `next()` 함수가 호출되고 `value` 가 반환되는 것을 확인할 수 있다.  
`NaN`, `null`, `undefined` 도 값이 될수 있으며, `-0` 과 `+0` 은 같은 `0` 으로 처리됩니다.

```javascript
const obj = {
    [Symbol.iterator](){return this;},
    array: [1, 2, 3, 4, NaN, null, undefined, -0, +0],
    next(){
        return { // 2번
            done: this.array.length == 0,
            value: this.array.pop()
        };  // 3번
    }
};

const iter = obj[Symbol.iterator]();
const s1 = new Set(iter); // 1번
console.log(s1);
/* 출력값
Set { 0, undefined, null, NaN, 4, 3, 2, 1 }
 */
```



#### Set의 특징

* 같은 `value` 가 중복되지 않음

* 어떤 데이터가 자신의 멤버인지 확인하는 작업을 빨리 처리함

* `index` 값으로 데이터 조회를 할 수 없음

#### Set의 주요 메서드와 속성
* `Set.prototype.size` : `Set` 객체 내의 `value` 개수 반환

* `Set.prototype.add(value)` : `Set` 객체에 `value` 요소를 추가하고 추가된 `Set` 객체를 반환

* `Set.prototype.clear()` : `Set` 객체내의 모든 `value` 값을 제거, 반환은 `undefined`

* `Set.prototype.has(value)` : `Set` 객체내의 `value` 값이 있다면 `true`, 없으면 `false` 를 반환

* `Set.prototype.delete(value)` : `value` 값 제거 후 `Set.prototype.has(value)` 메서드로 제거되기 이전 `value`의 존재를 판단 후 `Boolean` 이 반환

* `Set.prototype.entries()` : `Set` 객체 내의 값에 대한 `[value, value] 배열` 이 포함되는 `Iterator`객체 반환

* `Set.prototype.forEach(callbackFn[, thisArg])` : `Set` 객체 내에 있는 각 값에 대해 한 번 `callbackFn`을 호출. `thisArg` 매개변수가 `forEach` 에 전달되면, 이는 각 콜백에 대해 `this` 값으로 사용

* `Set.prototype.keys()` : 삽입 순서대로 `Set` 객체 내의 각 `value` 에 대한 요소들이 포함되는 `Iterator` 객체 반환

* `Set.prototype.values()` : 삽입 순서대로 `Set` 객체 내의 각 `value` 에 대한 요소들이 포함되는 `Iterator` 객체 반환

* `Set.prototype[@@iterator]()` : 삽입 순서대로 `Set` 객체 내의 각 `value` 에 대한 요소들이 포함되는 `Iterator` 객체 반환

거의 [mozilla document](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Set) 를 보고 공부했으며 사실 document 만큼 정확한게 없다...  
혼란을 틈타 예제로 넘어간다

잡탕구리 예제 1
```JavaScript
const obj = {
    [Symbol.iterator](){return this;},
    array: [1, NaN, null, undefined, -0, +0, {}],
    next(){
        return {
            done: this.array.length == 0,
            value: this.array.pop()
        };
    }
};

const iter = obj[Symbol.iterator]();
const o = {};
// 이터러블 객체를 통해 이터레이터 객체 획득

const set = new Set(null);
console.log(set);
// Set{} , null 이나 undefined를 넣어도 빈 Set객체 생성

var refer = iter.next().value; // 빈객체를 참조하기위한 구문
set.add(refer); // 빈객체가 추가
set.add(o);
console.log(set); // {} 추가 object도 값이 됨
// 똑같이 빈 객체 o 와 refer 빈객체가 같음에도 추가되었다.
// 이러한것이 가능한 이유는 서로 다른 객체를 참조하기때문이다.


set.add(iter.next().value);
console.log(set); // 0 추가

set.add(iter.next().value);
console.log(set); // -0 과 +0 은 동일한 값임, ECMAScript 2015에서 변경

set.add(iter.next().value);
console.log(set); // undefined 추가

set.add(iter.next().value);
console.log(set); // null 추가

set.add(iter.next().value);
console.log(set); // NaN 추가

set.add(iter.next().value);
console.log(set); // 1 추가,
// 이 때 아직 done: false 임

set.add(iter.next().value); // 이 때 반환값은 undefined
console.log(set); // undefined 는 이미 set객체에 존재하므로 추가되지않음

console.log(set.delete({})); // false
// 엥? false 라니?!
// 해당 요소를 가리키고있는 객체를 전달
console.log(set.delete(o)); // true
console.log(set); // Set { {}, 0, undefined, null, NaN, 1 }
console.log(set.delete()); // 아무 매개변수도 넣지않아서 undefiend가 제거
console.log(set);// Set { {}, 0, null, NaN, 1 }

console.log(set.delete(refer)); // refer가 남아있는 빈 객체를 참조
console.log(set); // Set { 0, null, NaN, 1 }
console.log(set.size); // 4
console.log(set.has(null)); // true
```
예제 1에 이어서 진행되는  
잡탕구리 예제 2
``` javascript
set.forEach(function(value, key, setObj){
   console.log(`${key} : ${value} <= ${setObj}`);
}); // set객체는 value만 저장하므로 value와 key 가 동일
/*
0 : 0 <= [object Set]
null : null <= [object Set]
NaN : NaN <= [object Set]
1 : 1 <= [object Set]
 */

for(const val of set){
    console.log(val);
}
/*
0
null
NaN
1
 */
var array = Array.from(set);
console.log(array); // [ 0, null, NaN, 1 ]
var array2 = [...set];
console.log(array2); // [ 0, null, NaN, 1 ]
```
## WeakMap
#### WeakMap 이란?
`WeakMap` 은 `Map` 과 비슷하지만 차이점이 있다. `WeakMap` 의 `key` 에는 항상 `Object`가 온다. `WeakMap` 은 `Iterable` 이 아니다
#### WeakMap Method
* `WeakMap.prototype.delete(key)` : `WeakMap` 객체내의 해당 `key`와 관련된 값을 제거, 제거 후엔 `WeakMap.prototype.has(value)` 메서드가 제거되기 이전의 `value` 가 존재했는지의 여부를 `Boolean` 값으로 반환

* `WeakMap.prototype.get(key)` : `WeakMap` 객체내의 해당 `key`의 값을 반환, 없으면 `undefiend`

* `WeakMap.prototype.has(key)` : `WeakMap` 객체내의 해당 `key`가 있는지 확인하고 `Boolean` 값을 반환

* `WeakMap.prototype.set(key, value)` : `WeakMap` 객체 내 `key` 와 그에 관련된 `value` 를 설정하고 `WeakMap` 객체를 반환합니다.

간단한 사용법
```javascript
const weakMap = new WeakMap();

const obj1 = {};
const obj2 = function(){};

// weakMap.set("weakMap?", "error");  // 문자열이 키가 될수 없음
weakMap.set(obj1, "emptyObject");
weakMap.set(obj2, "function");
console.log(weakMap); // WeakMap{} 출력
// WeakMap 은 Iterable 하지 않다. 하지만 키:값 은 존재

console.log(weakMap.get(obj1)); // emptyObject
console.log(weakMap.get(obj2)); // function, 함수는 실제로 객체

console.log(weakMap.delete(obj1));// true, 해당 key가 제거된후
// weakMap.has(obj1)가 제거되기전의 해당 key 존재여부를 알려줌
```
## WeakSet
#### WeakSet 이란?
`WeakSet` 은 `Set` 과 비슷하지만 `WeakMap` 의 `value` 에는 항상 `Object` 가 온다.  
`WeakSet` 은 `Iterable` 이 아니다
#### WeakSet Method
* `WeakSet.prototype.has(value)` : `WeakSet` 객체 내에 `value` 가 존재하는지 `Boolean` 값을 반환  

* `WeakSet.prototype.delete(value)` : `value` 제거 후 `WeakSet.prototype.has(value)` 메서드로 제거되기 이전 `value`의 존재를 판단 후 `Boolean` 이 반환

* `WeakSet.prototype.add(value)` : `WeakSet` 객체에 주어진 `value`를 추가하고 객체 반환

간단한 사용법
```javascript
const weakSet = new WeakSet();

const obj1 = {},
      obj2 = function(){};

// weakSet.add("error"); // WeakSet은 object 만 들어갈수 있음
weakSet.add(obj1);
weakSet.add(obj2);

console.log(weakSet); // WeakSet{}
// WeakSet객체는 Iterable 하지 않다.

console.log(weakSet.has(obj1));// true
console.log(weakSet.has(obj2));// true

console.log(weakSet.delete(obj1)); // true
// 해당 value가 제거된 후 weakSet.has(obj1)이 제거되기전의 해당 value의 존재유무를 반환
console.log(weakSet.has(obj1)); // false, 지워져서 사라짐
```

## 왜 WeakMap 과 WeakSet 은 Iterable 하지않은가?
`WeakMap` 과 `WeakSet` 의 각각 `value` 와 `key`는 내부의 멤버 객체가 메모리에서 제거되면 `GarbageCollection`에 의해서 `WeakMap`과 `WeakSet` 에서도 제거가 된다, 언제든 `GarbageCollection` 에 의해 제거가 될 수 있기에 `Iterable` 하지 않은 것이다.

`Iterable` 하지 않기에 열거되는 메서드나 속성을 이용할 수 없는것이다.

## 메모리 누수?

그렇다면 `Map` 과 `Set` 객체는 컬렉션 내의 `key`와 `value`를 참조하는 다른 `Object` 가 제거가 되더라도 `Map` 컬렉션과 `Set` 컬렉션에서 제거가 되지 않는다면, 메모리누수(memory leak) 가 발생할 수 있다.

#### 메모리누수(memory leak) 확인하는 방법!
메모리 누수가 되는것을 눈으로 보겠다.  
참고로`Shallow size` 는 객체 자체가 보유한 메모리 크기라고 한다.  
메모리 관련지식은 조만간 공부하도록하고 스냅샷에 찍힌 메모리만 보도록 한다.


```JavaScript
// Map
function Obj(){
    this.val = new Array(10000000).join("---")
}

window.obj = new Obj();
var map = new Map();
map.set(window.obj, 123);
delete window.obj;
```
>`WeakMap` 과 `Map` 을 예로 들겠다.

1. 먼저 위의 소스코드를 `Chrome` 에서 실행
2. `개발자도구`의 `Memory`를 확인
3. `Take heap snapshot` 선택
4. `Take snapshot`

이렇게 진행한다면 `힙 스냅샷` 의 이미지파일이 나올텐데 그 아래의 숫자는  
`연결 가능한 자바스크립트 객체의 총 크기` 라고 한다  
어찌됐던 `Map` 이용시 메모리 사용량이 무려 약 34MB 정도가 나온다


```JavaScript
// WeakMap
function Obj(){
    this.val = new Array(10000000).join("---")
}

window.obj = new Obj();
var map = new WeakMap();
map.set(window.obj, 123);
delete window.obj;
```

`WeakMap` 이용시 메모리 사용량이 약 5.4MB 정도로 현저히 줄어든 것을 확인할 수 있다.  
`delete` 를 함으로써 더 이상 `WeakMap` 객체 내의 참조가 끊기므로 `GarbageCollection` 에 의해 제거 된 것이다.

#### 이걸 어디에 써먹나?

`let` 으로 `private`한 `WeakMap` 을 만들고 `WeakMap` 을 이용해 `this` 와 연관된 `private` 데이터를 조회할 수 있게한다.
또한 객체에대한 참조를 잃더라도 `WeakMap` 특징으로 `GarbageCollection`에 의해 제거되므로 메모리누수(memory leak)가 일어나지 않게 된다.


```javascript
let Person = (() => {
    let privateWM = new WeakMap();
    class Person {
        constructor(name, age) {
            this.name = name;
            privateWM.set(this, {age: age});
        }

        showInfo() {
            console.log(`name: ${this.name}, age: ${privateWM.get(this).age}`);
        }
    }
    return Person;
})();

let hee = new Person("heecheol", 24),
    girlfriend =  new Person("unknown", undefined);

hee.showInfo();
girlfriend.showInfo();
/*
name: heecheol, age: 24
name: unknown, age: undefined
 */
```

##### 참조링크
[http://hacks.mozilla.or.kr/2015/12/es6-in-depth-collections/](http://hacks.mozilla.or.kr/2015/12/es6-in-depth-collections/)  
[https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Map](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Map)  
[https://developer.mozilla.org/ko/docs/Web/JavaScript/Guide/Keyed_collections](https://developer.mozilla.org/ko/docs/Web/JavaScript/Guide/Keyed_collections)  
[https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Set](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Set)  
[http://chanlee.github.io/2016/08/15/hello-es6-part-3/](http://chanlee.github.io/2016/08/15/hello-es6-part-3/)  
[http://www.mattzeunert.com/2017/01/31/weak-maps.html#comment-3131210529](http://www.mattzeunert.com/2017/01/31/weak-maps.html#comment-3131210529)


### 아무말 대잔치

* 솔직히 책에는 ES6의 이터레이터와 제너레이터에 짤막하게 소개가 되어있었는데 해당 자료들을 인터넷에서 찾아보니 머리가 좀 아팠다.

* 참조링크를 진짜 수도없이 봤다. 머리가 너무 안좋은듯 하다.

* 메모리 관련 글은 미숙한 점도 있을것이고, `Weak...` 을 사용하는 이유도 있지만 지금까지 배운것에서는 두루뭉술하게 이해되는 부분이다. 나중에 다시 확실히 해야겠다.

* 힙스냅샷을 이미지로 보여주고싶었지만 나중에 내가 따라해보고 싶기도하고 볼진 모르겠지만 다른 사람이 따라해봤으면 좋겠다는 심정으로 글로 썻다.

* 설연휴가 있는데 (어차피 대학생이고 방학이지만) 푹 자고싶기도한데 배우는 재미가 더 크다.

* 마크다운으로 쓰니깐 예쁘다. 마크다운 추천

* 15인치 맥으로 바꾸고싶다. 취업하면 취업선물로 바꿔야지
