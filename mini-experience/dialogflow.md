# Dialog Flow 체험기

[어느 블로그](http://codevkr.tistory.com/77?category=748958)의 Dialog Flow 튜토리얼을 진행해봤습니다. 카카오톡까지 연동하려했는데 카카오톡이 api 서비스 대신 새로운 자기들만의 챗봇을 만든것 같아서 데모 웹으로만 테스트해봤습니다. 하지만 다른 앱들과도 연동이 쉽게 된다고합니다.

### 소소하게 안것

* Agent: 챗봇
* Intent: 의도 - 챗봇과 사람을 연결해
  * default fallback intent: 무슨말인지 모르겠을 때 사용
  * default welcome intent: 최초 1회 실행됨
  * Training Phase: 유저가 입력할만한 문장들을 입력
    * Entity: DialogFlow 가 인식하는 변수같은것, 자연어를 변수로 등록할 수 있음
      * Reference value: 기본 이름
      * Synonym: 동의어
  * Action and parameter: 행동
    * required: 필수 입력값
    * prompt: 질문을 다시할 메세지
  * Response: 최종적으로 응답할
* Context: 맥락을 짚음
  * input: 맥락이 있어야할것
  * response: 맥락이 있을 때 실행될것

```js
if(맥락) {
  // 맥락될 처리
} else {
  다른것을 먼저 해주세요 같은것
}
```
