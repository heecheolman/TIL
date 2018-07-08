# vuejs 기초연습을 위한 계산기

![이미지](https://t1.daumcdn.net/cfile/tistory/9977694B5B423A5C08)

#### 왜 만들었나?
기존에 계산기를 만든적이 있는데 소스코드가 너무 지저분했던것도 있고, `vuejs` 를 공부하는 김에 다시 다듬어볼까 하고 만들어봤습니다.

#### 구성이 어떻게 되어있나?
* Vue instance 에 필요한 데이터들을 전부 집어넣었습니다.  
* 크게 `view-content` 와 `button-content` 로 나누었습니다
* button 을 렌더링할 때 조건을 걸어주어서 각 버튼에 맞는 css 를 적용 시켰습니다.


#### 계산방식
숫자를 담는 `numStack`, 연산자를 담는 `oprStack` 을 나누어서 연산자 우선순위에 따라 실시간으로 계산이 되는 방식입니다.


#### 공부하면 좋을 참고자료
* [Vue.js: Why Components’ Data Properties Must Be Functions -  Bo Andersen](https://codingexplained.com/coding/front-end/vue-js/why-components-data-properties-must-be-functions)
