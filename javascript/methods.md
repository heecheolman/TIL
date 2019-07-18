# 쓸만한 메서드 정리

## Array

배열과 관련된 유용한 메서드들

### map

배열 내 모든 요소가 주어진 콜백함수를 돌고 그 결과를 모아 새로운 배열을 return 한다. 호출한 배열의 값을 변경하지 않아 함수형 프로그래밍이 가능하다.

```js
const array = [1, 2, 3, 4, 5, 6];
const newArray = array.map(value => value * 2);
console.log(newArray);
// output: [ 2, 4, 6, 8, 10, 12 ]
```

순회하고있는 요소의 `index` 를 알고싶다면 콜백함수의 두번째 parameter 로 받을 수 있다.

```js
[1, 2, 3, 4, 5].map((value, index) => {
   // ...
   // index 변수에는 현재 요소의 index 가 들어있다. 
})
```


### filter

해당 배열이 주어진 콜백함수에 대한 테스트를 통과하는 요소들을 모아 새로운 배열을 반환한다.
`true` 를 반환하면 통과가 되는것이고 `false` 를 반환하면 해당 요소는 버린다.

```js
[1, 2, 3, 4, 5, 6].filter(value => value < 4);
// output: [1, 2, 3]
```
현재 순회하고 있는 요소의 index 를 얻고 싶다면 두번째 parameter로 받을 수 있다.

### find

해당 배열중에 전달한 콜백함수에서 `true`를 만족하는 첫 번째 요소를 반환한다. 만약 찾지 못할 시 `undefined` 를 반환한다.

```js
[1, 2, 3, 4, 5, 6].find(value => value === 3);
// output: 3
[1, 2, 3, 4, 5, 6].find(value => value === 7);
// output: undefined
```

### every

배열의 모든 요소가 전달한 콜백함수의 테스트를 모두 통과하는지 확인합니다. 만약 하나의 요소라도 통과하지못한다면 false 를 반환합니다.

```
[2, 4, 6, 8, 10].every(value => value % 2 === 0);
// output: true
```

현재 순회하고 있는 요소의 index 를 알고 싶다면 두번째 parameter 로 받을 수 있다.
