# 정규표현식(정규식)

영어로는 Regular Expression 줄여서 Regex 라고 불립니다. 한글로는 정규표현식(=정규식) 입니다. 정규식을 사용하는 이유는 보통 문자열을 다루는 폼에서 유효성 검사를 할 때 많이 사용하게되는데 정규식의 사용 유무에 따라 코드량도 줄게되고 다른 언어에서도 공통적으로 쓰이기 때문에 사용합니다.


## 들어가며

MDN 문서를 보며 작성했습니다. 문서가 엄청 일치할 듯 하고 목적은 MDN 에서 설명한 것을 기준으로 실제로 코드로 적어보며 예제를 다루며 진행합니다.

## 정규식에서 특수문자 짚어보기

* `\`
* `^`
* `$`
* `*`
* `+`
* `?`
* `.`
* `(x)`
* `(?:x)`
* `x(?!y)`
* `x|y`
* `{n}`
* `{n,m}`
* `[xyz]`
* `[^xyz]`
* `[\b]`
* `\b`
* `\B`
* `\cX`
* `\d`
* `\D`
* `\f`
* `\n`
* `\r`
* `\s`
* `\S`
* `\t`
* `\v`
* `\w`
* `\W`
* `\n`
* `\0`
* `\xhh`
* `\uhhhh`

### `\`

특수문자 앞에 나오는 `\` 는 해당 특수문자는 특수하게 사용되지 않고 그대로 사용되어야 한다는 뜻을 의미합니다.

```ts
const regex: RegExp = /ab*c/;
/*
  abc       (O)
  abbbbbc   (O)
  ac        (X)
*/

const regex: RegExp = /abc\*/;
/*
  abc*      (O)
  abc       (X)
*/
```

> `*` 은 앞의 표현식이 0 회 이상 연속으로 반복된다는 의미

### `^`

입력의 시작 부분을 나타냅니다. 다중행 플래그(`/정규식/m`) 가 적용되어 있다면 다음 행들도 같이 검사를 합니다.

```ts
const regex: RegExp = /^abc/;
/*
  abc         (O)
  abcdefg     (O)
  Abc         (X)

  acacac
  acacaca
*/
const regex: RegExp = /^abc/m; // 다중플래그
/*
  Abc
  abcdefg     (O)

  azaz
  zzaza
  abcdefg     (O)
*/
```

만약 `^`가 문자셋 (`[abc]`) 패턴의 첫글자로 쓰이면 다른 의미로 적용이 됩니다.

### `$`
입력의 끝 부분을 나타냅니다. 다중행 플래그(`/정규식/m`) 가 적용되어 있다면 다음 행들도 같이 검사를 합니다.

```ts
const regex: RegExp = /abc$/;
/*
  abc         (O)

  abe
  abfabc
  wef         (X)

  abece       (X)
*/

const regex: RegExp = /abc$/m;
/*

  abe
  abfabc
  wef         (O)

*/
```

멀티라인이 적용되어있기 때문에 2번째 행의 끝은 `abc` 라는 문자열이 존재하기 때문에 해당 문자를 찾게됩니다.


### `*`

앞의 표현식이 0회 이상 연속으로 반복되는지 검사합니다. `{0,}` 과 같은 의미입니다.

```ts
const regex: RegExp = /he*llo/;
/*
  hello       (O)
  heeeeeello  (O)
  hllo        (O)
*/

const regex: RegExp = /he{0,}llo/;
/*
  hello       (O)
  heeeeeello  (O)
  hllo        (O)
*/
```
문서에서 말한대로 동일하다는 것을 알 수 있습니다.

### `+`

앞의 표현식이 1회 이상 연속으로 반복되는지 검사합니다. `{1,}`과 같은 의미입니다.

```ts
const regex: RegExp = /he+llo/;

/*
  hello       (O)
  heeeeeello  (O)
  hello       (X)
*/

const regex: RegExp = /he{1,}llo/;

/*
  hello       (O)
  heeeeeello  (O)
  hello       (X)
*/
```
문서에사 말한대로 동일하다는 것을 알 수 있습니다.


### `?`

앞의 표현식이 0 또는 1회이상 반복되는지 검사합니다. `{0,1}` 과 같은 의미입니다.

```ts
const regex: RegExp = /h?aloha/;

/*
  haloha        (O)
  aloha         (O)
  loha          (X)
*/
```

### `.`

개행 문자를 제외한 모든 단일 문자와 대응됩니다.

```ts
const regex: RegExp = /.hello/;

/*
  heecheolhello   (O)  --> lhello
  hhello          (O)  --> hhello
  hello           (X)

  (개행된)hello           (X)
*/
```

### `(x)`

`x` 를 기억합니다. 캡쳐링이라고도 합니다. 예를들어 `/(abc) (efg)/` 가 있다면 abc 는 `$1` 에 저장이 되고 efg 는 `$2` 에 저장이 됩니다.

```ts
const regex: RegExp = /(abc) (efg)/;
const str = 'abc efg';

console.log(str.match(regex));
/*
  ["abc efg", "abc", "efg", index: 0, input: "abc efg", groups: undefined]

  첫번째 요소는 전체 매칭 문자열
  두번째부터는 캡쳐링 된 문자열이 차례대로
*/

console.log(str.replace(regex, '$2 $1'));
/*
  efg abc

  $2 에는 efg
  $1 에는 abc 가 들어감
*/

```

### `(?:x)`

`x` 를 기억하지 않습니다. 위의 캡쳐링과는 반대입니다. 예를들어 `gihub` 도메인의 유저 이름을 추출해서 해당 유저의 `github.io` 를 얻어내는 방법을 보겠습니다.


```ts
/** 캡쳐링 하는 경우*/
const regex: RegExp = /^(https?:\/\/)github\.com\/(\w*)\/?.*$/;
const url: string = 'https://github.com/heecheolman/TIL';

url.replace(regex, '$1$2.github.io');
// https://heecheolman.github.io


/** https 는 논 캡쳐링 하는 경우 */
const regex: RegExp = /^(?:https?:\/\/)github\.com\/(\w*)\/?.*$/;
const url: string = 'https://github.com/heecheolman/TIL';

url.replace(regex, '$1.github.io');
// heecheolman.github.io
```

### `x(?=y)`
`y` 가 뒤따라오는 `x` 에만 대응합니다. lookahead 라고 불립니다. 다음 예제는 `coffee` 라고 붙은 품목만 걸러낼 때입니다.

```ts
const regex: RegExp = /(\w*)(?=coffee)/;

regex.test('americano coffee') // true
regex.test('espresso coffee')  // true
regex.test('chocolate cake');  // false

const regex: RegExp = /(\w*)(?=coffee|cake)/;
regex.test('americano coffee') // true
regex.test('espresso coffee')  // true
regex.test('chocolate cake');  // true
```

`(?=coffee|cake)` 커피 또는 케이크 라는 의미입니다.

### `x(?!y)`

`x` 뒤에 `y` 가 없는 경우에만 일치시킵니다. negated lookahead 라고 불립니다.


## 참고문서

* [정규표현식 - MDN](https://developer.mozilla.org/ko/docs/Web/JavaScript/Guide/%EC%A0%95%EA%B7%9C%EC%8B%9D#special-word-boundary)
* [자바스크립트 정규표현식의 capturing group](https://blog.rhostem.com/posts/2018-11-11-regex-capture-group)


## 도움 될 페이지

* [정규식 검사](https://regexr.com/)
* [step by step 배우기](https://regexone.com/lesson/line_beginning_end?)
