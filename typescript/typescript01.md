<div align=center>

<img src="https://pbs.twimg.com/profile_images/743155381661143040/bynNY5dJ_400x400.jpg" width="80" height="80">

</div>



# Typescript
동적타입언어인 자바스크립트에서는 타입에러를 만나는경우가 많은데 타입스크립트를 이용하여 컴파일단계에서 미리 타입체크를 하여 타입오류를 최소화 할 수 있고, 클래스기반 언어에 익숙한 개발자들에게 좀 더 친숙하게 다가갈 수 있기에 공부를 시작한다.

## Typescript 란?
> "Typescript is a typed superset of Javascript that compiles to plain Javascript" - [타입스크립트 공식 홈페이지 소개란](https://www.typescriptlang.org/index.html)

해석해보면 타입스크립트는 순수 자바스크립트로 컴파일되는 자바스크립트의 슈퍼셋이다. 슈퍼셋이란 상위확장을 말한다.

## Typescript 탄생배경
HTML5 가 등장하기 전까지 웹은 플래시, 실버라이트, 엑티브엑스와 같은 플러그인에 의존해 인터랙티브한 웹페이지를 구축했는데 HTML5 가 등장하며 자바스크립트로 대체되었다. 그리고 AJAX의 등장으로 하나의 앱처럼 작동하는 SPA(Single Page Application)가 대세가 되었다. 이 때문에 클라이언트측에 무게가 실리게 되었다.

우리가 사용하는 자바스크립트에는 한계가 있다. 다른 언어들(C, C++, Java 등)과는 다르게 다음과같은 다른점을 가지고 있다.

* 프로토타입기반 언어
* 함수단위 스코프를 갖는 scope, 호출방식에 따라 다른 this
* 동적타입언어

클래스 기반 언어를 사용한 개발자들에게는 혼란스러울 수 있다. 그래서 이를 대체하고자 CoffeeScript 와 같은 대체언어들이 나오게 되었는데 타입스크립트 또한 대체 언어중 한가지이다.

## 왜 사용하나요?

#### 1. 정적 타이핑
```javascript
function plusOne(number) {
  return 1 + number;
}

console.log(plusOne("1")); // 11
```
문자열 1을 넘겨주었더니 문자열을 합해 11을 반환했다. 타입스크립트를 이용하면 이러한 모순을 최소한 컴파일 단계에서 잡아낼 수 있다.


#### 2. 객체지향 프로그래밍 지원 및 ES6 이상 문법 지원
우선 타입스크립트에서는 Class, Interface 등과 같은 일반 객체지향프로그래밍에서 흔히 사용했던 문법들을 사용할 수 있다. 그리고 이것들을 완벽하게 Javascript to Javascript 로 변환이 가능하다. 사실 Babel 을 통해서도 변환이 가능하지만 타입스크립트는 타입까지 체크해주니 얼마나 좋은가?

핵심이 되는 이유들을 우선적으로 적었다.
이제 본격적으로 타입스크립트를 시작해보자.

### [타입스크립트 플레이그라운드](https://github.com/heecheolman/typescript-playground)

> [Jbee 님의 Typescript Playground](https://jaeyeophan.github.io/2017/12/06/TS-TypeScript-Playground/) 를 참고하여 만들었습니다.

## 참고 문헌
* [타입스크립트 공식 사이트](https://www.typescriptlang.org/index.html)
* [타입스크립트 소개와 개발환경 구축 - PoiemaWeb](https://poiemaweb.com/typescript-introduction)
