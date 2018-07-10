# 자바스크립트와 이벤트 루프
자바스크립트는 **단일쓰레드** 기반 언어이다. 이 뜻은, 동시에 하나만 처리할 수 있다는 말이다.

하지만 웹 브라우저는 애니메이션기능이 실행되면서 이벤트 효과도 받고, Node.js 기반의 웹서버는 동시에 여러개의 HTTP 요청을 처리하기도하는데  
이것을 가능하게 해주는것이 `이벤트 루프` 이다.

## ECMAscript 에는 이벤트 루프가 없다
ECMAscript 의 스펙을 자세히 보면 이벤트 루프에 관한 내용이 없다.  
사실 이벤트루프를 지원해주는 것은 브라우저나, Node.js 와 같은 자바스크립트 엔진을 구동하는 환경이다.

![이미지](https://cloud.githubusercontent.com/assets/12269489/16215491/b1493856-379d-11e6-9c16-a9a4cf841567.png)  
출처 : [자바스크립트와 이벤트 루프 - 김동우](http://meetup.toast.com/posts/89)

## 단일 호출 스택과 Run-to-Completion
```javascript
function A() {
  console.log('A');
}
function B() {
  for(let i = 0; i < 10000; i++){}
  console.log('B');
}
setTimeout(A, 10);
B();
/* output
  B
  A
*/
```
결과는 당연히 "B A" 이다. `B` 함수가 10ms 보다 오래걸린다 하더라도 B부터 실행이 될것이다.

자바스크립트는 단일호출스택이며 자바스크립트의 함수가 실행되는 방식을 `Run-to-Completion` 이라하는데  
함수가 실행되는 동안 중간에 끼어들지 못한다는것을 의미한다.

1. 위의 코드에서 `setTimeout` 이 가장 먼저 스택에 추가가 되고,  
2. 타이머 이벤트 요청을 한후에 스택에서 사라진다,  
3. 이후에 `B` 가 실행된다.
4. `B` 가 끝난 뒤에 `A` 함수가 스택에 추가되어 실행된다.

근데 어떻게 `setTimeout` 을 통해 넘겨진 `A` 가 `B` 함수가 끝나자마자 실행이 될까?

## 태스크 큐와 이벤트 루프
**태스크 큐** 는 말그대로 큐(FIFO) 형태의 배열이라 할 수 있고,  
**이벤트 루프** 는 호출 스택이 비워질때마다 큐에서 콜백함수들을 꺼내어 실행하는 역할이다.

위의 코드에서 `setTimeout` 을 통해 넘겨진 콜백함수 `A` 가 바로 실행되지 않고 태스크 큐에 들어가게 된다.  
그리고 `B` 가 실행이 끝나고 호출 스택이 비워지면 큐에서 콜백함수를 꺼내어 호출스택에 추가를 해준다.

*MDN 의 이벤트 루프 설명해주는 코드*

```javascript
while(queue.waitForMessage()){
  queue.processNextMessage();
}
```
위의 코드는  
**현재 실행중인 태스크가 없는지와 태스크 큐에 태스크가 있는지 반복적으로 확인한다.**  


![이미지](http://4.bp.blogspot.com/-MYY3w4Y_lAg/VCHi63G4DGI/AAAAAAAAA3c/FrbGjnJbPnQ/s1600/event_loop.jpg)

출처 : [http://2ality.com/2014/09/es6-promises-foundations.html](http://2ality.com/2014/09/es6-promises-foundations.html)


그리고 [이해를 돕는 영상](https://vimeo.com/96425312) 을 꼭 보면 좋을 것 같다.

## 프라미스와 이벤트 루프
```javascript
setTimeout(() => { // A
  console.log('A');
}, 0);

Promise.resolve().then(() => { // B
  console.log('B');
}).then(() => { // C
  console.log('C');
});
/* output
  B
  C
  A
*/
```
출력결과는 B C A 이다.  
왜 BCA 인지 의문이든다면 프라미스는 `마이크로 태스크` 를 사용하기 때문이다.  
> **마이크로 태스크란?**  
일반 태스크 보다 좀 더 우선순위를 갖는 태스크 큐라고 보면된다.

1. 콜백 A 를 태스크 큐에 추가
2. 프라미스의 then() 메서드는 콜백 B 를 마이크로 태스크 큐에 추가
3. 마이크로 태스크 큐에 존재하는 B 를 실행
4. 콜백 C 를 마이크로 태스크 큐에 추가
5. 마이크로 태스크 큐에 존재하는 C 를 실행
6. 태스크 큐에 있는 A 실행

## 끝으로
`자바스크립트와 이벤트 루프` 라는 글을 작성하신 첫번째 참고문서의 김동우 님께서 좀 더 자세하게 설명해주셨다.  
 저 글을 바탕으로 작성된 글인데 콜백함수가 실행되는 원리를 알게되어 기본지식이 좀 더 쌓인 느낌이다. 


## 참고문서
* [자바스크립트와 이벤트 루프 - 김동우](http://meetup.toast.com/posts/89)
* [Concurrency model and Event Loop - MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/EventLoop)
* [Philip Roberts: Help, I’m stuck in an event-loop.](https://vimeo.com/96425312)
