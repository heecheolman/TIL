# 정규표현식(정규식)

영어로는 Regular Expression 줄여서 Regex 라고 불립니다. 한글로는 정규표현식(=정규식) 입니다. 정규식을 사용하는 이유는 보통 문자열을 다루는 폼에서 유효성 검사를 할 때 많이 사용하게되는데 정규식의 사용 유무에 따라 코드량도 줄게되고 다른 언어에서도 공통적으로 쓰이기 때문에 사용합니다.


## 들어가며

MDN 문서를 보며 작성했습니다. 문서가 엄청 일치할 듯 하고 목적은 MDN 에서 설명한 것을 기준으로 실제로 코드로 적어보며 예제를 다루며 진행합니다.

## 정규식에서 특수문자 짚어보기

* [`\`]()
* [`^`](#-1)
* [`$`](#-2)
* [`*`](#-3)
* [`+`](#-4)
* [`?`](#-5)
* [`.`](#-6)
* [`(x)`](#x)
* [`(?:x)`](#x-1)
* [`x(?!y)`](#xy-1)
* [`x|y`](#xy-2)
* [`(?<=x)y`](#xy-3)
* [`(?<!x)y`](#xy-4)
* [`{n}`](#n)
* [`{n,m}`](#nm)
* [`[xyz]`](#xyz)
* [`[^xyz]`](#xyz-1)
* [`[\b]`](#b)
* [`\b`](#b-1)
* [`\B`](#b-2)
* [`\cX`](#cx-skip)
* [`\d`](#d)
* [`\D`](#d-1)
* [`\f`](#f-skip)
* [`\n`](#n-1)
* [`\r`](#r-skip)
* [`\s`](#s)
* [`\S`](#s-1)
* [`\t`](#t)
* [`\v`](#v-skip)
* [`\w`](#w)
* [`\W`](#w-1)
* [`\n`](#n-2)
* [`\0`](#0-skip)
* [`\xhh`](#xhh-skip)
* [`\uhhhh`](#uhhhh-skip)
* [참고문서](#참고문서)
* [도움 될 페이지](#도움-될-페이지)

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
`y` 가 뒤따라오는 `x` 에만 대응합니다. lookahead 라고 불립니다. 다시말해 `x`를 검색하되 `y`가 뒤에 딸려있는 `x` 를 검색합니다.
다음 예제는 `coffee` 라고 붙은 품목만 걸러낼 때입니다.

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

`x` 뒤에 `y` 가 없는 경우에만 일치시킵니다. negated lookahead 라고 불립니다. 다시말해 `x` 를 검색하되 `y` 가 뒤에 딸려있지 않은 `x` 를 검색합니다.

```ts
const regex: RegExp = /hee(?!cheol)/;

'heecheol'.match(regex); // null
'heehee'.match(regex); // [ 'hee', index: 0, input: 'heehee' ]
```

### `x|y`

`x` 또는 `y` 를 검색합니다.

```ts
const regex: RegExp = /hee|cheol/;
'heecheol'.match(regex); // 'hee'

const regex: RegExp = /hee|cheol/g;
'heecheol'.match(regex); // ['hee', 'cheol']
```

### `(?<=x)y`

`x`가 앞에 존재하는 `y` 를 검색합니다. 다시말해 `y` 를 검색하되 `x` 가 앞에있는 `y` 를 검색합니다.

```ts
const regex: RegEx = /(?<=hee)cheol/;

'heecheol'.match(regex); // 'cheol'

```

### `(?<!x)y`

`x` 가 앞에 존재하지 않는 `y` 를 검색합니다. 다시말해 `y` 를 검색하되 `x` 가 앞에 존재하지 않는 `y` 를 검색합니다.

```ts
const regex: RegExp = /(?<!kim)cheol/;

'heecheol'.match(regex) // [ 'cheol', index: 3, input: 'heecheol' ]
'kimcheol'.match(regex) // null

```

### `{n}`

앞의 표현식이 `n`번 나타나는 부분입니다. `n` 은 양의 정수입니다.

```ts
const regex: RegExp = /e{3}/;

'heeecheol'.match(regex); // [ 'eee', index: 1, input: 'heeecheol' ]
'heecheol'.match(regex); // null
```

### `{n,m}`

`n`, `m` 둘 다 양의정수 이고, `n` 이상 `m` 이하를 만족하는 문자열을 찾습니다. `m`이 생략되면 무한대입니다.

```ts
const regex: RegExp = /he{2,3}cheol/;

'heecheol'.match(regex); // [ 'heecheol', index: 0, input: 'heecheol' ]
'heeecheol'.match(regex); // [ 'heeecheol', index: 0, input: 'heeecheol' ]
'heeeecheol'match(regex); // null

const regex: RegExp = /he{1,}cheol/;
'heeeeeeeeeeeeeeeeeeeeeeeeeecheol'.match(regex);
// [ 'heeeeeeeeeeeeeeeeeeeeeeeeeecheol', index: 0, input: 'heeeeeeeeeeeeeeeeeeeeeeeeeecheol' ]
```

### `[xyz]`

문자셋입니다. `x` 또는 `y` 또는 `z` 라는 의미로 `x|y|z` 와 동일합니다. `[]`문자셋 안에서 `.` 이나 `*` 같은 특수문자는 이스케이프할 필요가 없습니다.

```ts
const regex: RegExp = /[*]\*/;

'***'.match(regex); // [ '**', index: 0, input: '***' ]

// * 그대로로 인식
```
그리고 하이픈(`-`) 을 사용해 범위를 지정할 수 있습니다.

```ts
/[a-z]/ // a에서 z
/[A-Z]/ // A에서 Z
/가-힣/  // 가에서 힣 까지  (모든한글)
```

### `[^xyz]`

부정 문자셋입니다. `[]` 내부에 등장하는 문자열 외의 모든 문자에 대응됩니다. 문자셋과 동일하게 하이픈(`-`) 을 이용해 범위를 지정할 수 있습니다.

```ts
const regex: RegExp = /[^a-c]/;

'abcd'.match(regex); // [ 'd', index: 3, input: 'abcd' ]
```

### `[\b]`

백스페이스입니다. `\b` 와는 별개이므로 주의해야합니다.

```ts
const regex: RegExp = /[\b]/;

'hello \bworld'.match(regex); // [ '\b', index: 6, input: 'hello \bworld' ]
regex.test('hello\b\b\bworld'); // true
```

### `\b`

63개의 문자(영문 대소문자 52개 + 숫자 10개 + `_`(언더바))가 **아닌** 문자에 일치하는 경계

```ts
const regex: RegExp = /\bheecheol\b/;

'heecheol'.match(regex); // [ 'heecheol', index: 0, input: 'heecheol' ]
'@heecheol'.match(regex); // [ 'heecheol', index: 1, input: '@heecheol' ]
'heecheol@'.match(regex); // [ 'heecheol', index: 0, input: 'heecheol@' ]
'@heecheol@'.match(regex); // [ 'heecheol', index: 1, input: '@heecheol@' ]
'KheecheolK'.match(regex); // null
```

### `\B`

63개의 문자(영문 대소문자 52개 + 숫자 10개 + `_`(언더바))가 문자에 일치하는 경계. `\b` 와 반대입니다.

```ts
const regex = /\Bheecheol\B/;

'heecheol'.match(regex); // null;
'@heecheol'.match(regex); // null;
'heecheol@'.match(regex); // null;
'@heecheol@'.match(regex); // null;
'KheecheolK'.match(regex); // [ 'heecheol', index: 1, input: 'KheecheolK' ]
```

### `\cX` skip

<kbd>control</kbd> 과 함께 눌려진 문자를 찾습니다.

### `\d`

숫자문자에 대응됩니다. `[0-9]` 와 동일합니다.

```ts
const regex: RegExp = /\d{1,}/;

'1234'.match(regex); // [ '1234', index: 0, input: '1234' ]
'1'.match(regex); // [ '1', index: 0, input: '1' ]
````

### `\D`

숫자 문자가 아닌 문자에 대응됩니다. `[^0-9]` 와 동일합니다.

```ts
const regex: RegExp = /\D{1,}/;

'abcd123'.match(regex); // [ 'abcd', index: 0, input: 'abcd123' ]
'aaaaa'.match(regex); // [ 'aaaaa', index: 0, input: 'aaaaa' ]
```

### `\f` skip

폼 피드 문자에 대응됩니다.

### `\n`

줄 바꿈(개행) 문자에 대응됩니다.

```ts
const regex: RegExp = /\n/;

'\n\n'.match(regex); // [ '\n', index: 0, input: '\n\n' ]
```

### `\r` skip

캐리지 리턴 문자에 대응됩니다.

### `\s`

스페이스, 탭, 폼피드, 줄 바꿈 문자등을 포함한 하나의 공백 문자에 대응됩니다.

```ts
const regex = /\sheecheol/;

// 탭
'   heecheol'.match(regex) // [ ' heecheol', index: 2, input: '   heecheol' ]
// 스페이스
' heecheol'.match(regex) // [ ' heecheol', index: 0, input: ' heecheol' ]
// 개행
'\nheecheol'.match(regex) // [ '\nheecheol', index: 0, input: '\nheecheol' ]

```

### `\S`

공백 문자가 아닌 하나의 문자에 대응됩니다.

```ts
const regex: RegExp = /\Sheecheol/;

'   heecheol'.match(regex); // null
'Aheecheol'.match(regex); // [ 'Aheecheol', index: 0, input: 'Aheecheol' ]
'1heecheol'.match(regex); // [ '1heecheol', index: 0, input: 'Aheecheol' ]
```
### `\t`

탭 문자에 대응됩니다.

```ts
const regex: RegExp = /\t[a-z]+\t/;

'\thelloworld\t'.match(regex); // [ '\thelloworld\t', index: 0, input: '\thelloworld\t' ]
```

### `\v` skip

수직 탭 문자에 대응됩니다.

### `\w`

언더바(`_`) 문자를 포함한 영문 및 숫자에 대응됩니다. 같은 의미로 `[a-zA-Z0-9-_]`와 동일합니다.

```ts
const regex: RegExp = /\w{2,4}/;

'ab_z'.match(regex); // [ 'ab_z', index: 0, input: 'ab_z' ]
'ABa1'.match(regex); // [ 'ABa1', index: 0, input: 'ABa1' ]
'$abc'.match(regex); // [ 'abc', index: 1, input: '$abc' ]
```

### `\W`

`\w` 에 포함된 문자가 아닌 문자들에 대해 대응합니다. `[^a-zA-Z0-9-_]` 와 동일합니다.

```ts
const regex: RegExp = /\W{2,4}/;

'ab_z'.match(regex); // null
'ABa1'.match(regex); // null
'$abc'.match(regex); // null
'@@$'.match(regex); // [ '@@$', index: 0, input: '@@$' ]
```

### `\n`

`n` 은 양의 정수이며, `\n` 개행문자와는 다릅니다. 정규식 내부의 `n`번째 괄호`()`에서 대응된 부분에 대한 역 참조입니다.

```ts
const regex: RegExp = /hee(,)cheol\1/; // \1는 콤마(,)를 나타내므로 다음과 같다
// /hee,cheol,/

'hee,cheol,man'.match(regex); // [ 'hee,cheol,', ',', index: 0, input: 'hee,cheol,man' ]
'hee,cheol,man'.match(/hee,cheol,/); // [ 'hee,cheol,', index: 0, input: 'hee,cheol,man' ]
```

### `\0` skip

널 문자입니다.

### `\xhh` skip

코드가 hh(두 16진 문자)인 문자에 일치합니다.

### `/uhhhh` skip

코드가 hhhh(네 개의 16진 숫자)인 문자에 일치합니다.



## 참고문서

* [정규표현식 - MDN](https://developer.mozilla.org/ko/docs/Web/JavaScript/Guide/%EC%A0%95%EA%B7%9C%EC%8B%9D#special-word-boundary)
* [자바스크립트 정규표현식의 capturing group](https://blog.rhostem.com/posts/2018-11-11-regex-capture-group)
* [정규표현식, 이렇게 시작하자! - HEROPY Tech](https://heropy.blog/2018/10/28/regexp/)


## 도움 될 페이지

* [정규식 검사](https://regexr.com/)
* [step by step 배우기](https://regexone.com/lesson/line_beginning_end?)
