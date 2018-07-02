# Blocking I/O 와 NonBlocking I/O, Synchronous 와 Asynchronous

동기(Synchronous)와 비동기(Asynchronous) 그리고 블로킹과 논블로킹의 차이를 알아본다.  
많이 보게되는 단어들인데 이 용어들에 대해 정리해서 말을 할 수 없었기에 공부를 하기로 했다.  
*아래의 참고문서를 보며 정리를 했다.* 

## Blocking I/O / NonBlocking I/O
#### Blocking I/O
호출된 함수가 자신의 작업을 모두 끝낼때까지 제어권을 가지고 있어 호출한 함수가 대기하도록 만듦
#### NonBlocking I/O
호출된 함수가 바로 return 해서 호출한 함수에게 제어권을 주어 다른 일을 할 수 있게 함

**호출되는 함수가 바로 리턴하느냐 마느냐가 중점**

## Synchronous / Asynchronous

#### Synchronous (동기)
동기는 함수를 호출하고 호출된 함수의 작업이 완료된 후의 return 을 기다리거나  
return 을 받더라도 호출한 함수가 계속해서 작업완료 여부를 신경씀

```javascript
// 동기적 코드
console.log('1');
console.log('2');
console.log('3');
/* 출력 결과
1
2
3
*/
```

#### Asynchronous (비동기)
동기는 함수를 호출할 때 `callback` 함수를 같이 전달해 작업이 완료되면 callback을 실행  
작업완료를 callback이 신경씀

```javascript
// 비동기적 코드
function foo() {
  console.log('1');
}

setTimeout(foo, 2000);
console.log('2');
console.log('3');
/* 출력 결과
2
3
1
*/
```

**호출되는 함수의 작업 완료 여부를 누가 신경쓰냐가 중점**

![이미지](http://i.imgur.com/zKF0CgK.png)
출처: [Blocking-NonBlocking-Synchronous-Asynchronous - HomoEfficio](http://homoefficio.github.io/2017/02/19/Blocking-NonBlocking-Synchronous-Asynchronous/)


여기서 조합을 살펴보면  
`Blocking & Sync` 와 `NonBlocking & Async` 는 쉽게 이해가 된다.  
하지만 `NonBlocking & Sync` 와 `Blocking & Async` 는 조금 설명이 필요하다

## NonBlocking & Sync 를 알아보자
NonBlocking 은 바로 return을 해서 **제어권을 준다**고 했고, Sync 는 작업완료여부를 **호출한** 쪽에서 신경을 쓴다고했다.  
그림을 보면 호출을 하고 바로 반환이 되고 다른일을 수행한다.  
이후에 작업이 완료되었는지 계속 물어보는 일을 추가로 수행하는것이 NonBlocking & Sync 이다.


## Blocking & Async 를 알아보자
우선 Blocking 은 작업이 완료될때까지 **제어권을 호출된 쪽에서 가지고** 있고, Async 는 작업완료여부를 **호출된** 쪽에서 신경을 쓴다.  

곱씹어보면 약간 이상할 수 있다.

어차피 제어권이 없는 상태에 결과만 기다리는 Blocking & Sync 와 별 차이가 없는것 같다.  
이 방식은 특별한 장점이 없어 일부러 사용할 필요는 없다고 한다.  
보통 NonBlocking & Async 방식을 쓰는데 그 과정중 하나라도 Blocking 이 포함이되면 의도치않게 Blocking & Async 로 작동한다고한다.

### 마치며
* 동기와 비동기, 블로킹 논블로킹을 이해할 때 아래의 참고문서를 많이 봤다.  
* 정말 정리가 잘 되어있어 이해하는데 도움이 되었다.  
* 개념을 일단 알아둔 후에 실제로 무언가를 만들 때 참고하면 좋을 것 같다.
* 추가적으로 [자바스크립트와 이벤트 루프](http://meetup.toast.com/posts/89) 의 글도 읽어 보는게 도움이 된다.

## 참고 문서
[Blocking-NonBlocking-Synchronous-Asynchronous - HomoEfficio](http://homoefficio.github.io/2017/02/19/Blocking-NonBlocking-Synchronous-Asynchronous/)
