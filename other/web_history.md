# 웹브라우저의 역사와 웹 프레임워크
웹 브라우저의 역사와 웹 프레임워크의 등장 배경을 작성


## 초기 웹
초기 웹 사용자는 `NetScape` 와 `IE` 둘 중에 선택을 할 수 있었는데, `NetScape` 의 시장 점유율이 86%에 달했다. 하지만 1996년도에 `Microsoft` 가 `IE` 브라우저를 운영 체제와 통합을 해버려서 `IE` 의 점유율이 75% 까지 상승했다. 이로 인해 `NetScape` 는 쇠퇴했고 `IE` 가 거의 독점을 하는 추세였다.

상업적으로 제품 개발을 할 수 없게 된 `NetScape` 는 오픈소스를 통해 `Mozilla` 를 만들었다. (`Mozilla` 는 `NetScape` 회원들이 1998년에 설립한 free software community)  

`Mozilla` 는 `Firefox` 브라우저를 만들어냈고, 이후 `Apple` 의 `Safari`, `Google` 의 `Chrome` 브라우저가 생겨났으며  
현재 `Google` 의 `Chrome` 브라우저가 점유율이 가장 높다.

[참고 : 위키피디아](https://en.wikipedia.org/wiki/History_of_the_web_browser)

웹은 초기에 C, C++, Perl 등으로 만들어진 프로그램에 사용자의 요청에 응하는 표준 출력을 브라우저에 되돌려주는 방식으로 보여졌다.
```
이런식으로
`printf(<html>...</html>);`
```

딱 봐도 작성유지가 힘들다.

## JSP

1990년대에 등장한 `JAVA` 의 열풍으로 `JSP(Java Server Pages)`언어를 이용해 동적인 웹 페이지를 만들었는데 여기에 문제가 있었다.  
`JSP`는 사용자의 요청이 있으면 서버에서 전체 html을 만드는 방식이었는데 이는 네트워크 속도가 아무리 빨라도 비효율적이었다.  
이러한 문제를 해결하기 위해 `Ajax` 가 등장했다.

## Ajax
`Ajax` 란 Asynchronous Javascript And XML 의 약자로 비동기적 자바스크립트와 XML 이며, 자바스크립트를 통한 비동기적 통신이다.  

가장 두드러지는 특징은 페이지 전체를 리프레쉬 하지않고 수행되는 `비동기성` 이다.  
다시말해, 페이지의 전체가 아닌 일부분을 업데이트 할 수 있다는 것이다.

`Ajax` 를 이용해 만든 최초의 웹이 `SPA(Single Page Application)`로 만든 `G-mail` 이다.  
`SPA`가 대두됨에 따라 `front-end` 단에 무게가 실려졌다.  

> SPA란 하나의 페이지에서 리소스들을 다룰 수 있는 기법이다.

이후에 여러가지 웹 프레임워크가 등장한다.  
크게 1세대, 2세대, 3세대로 나누었다.

## 1세대 프레임워크 AngularJS, Backbone.js
`SPA`를 작성하기위한 프레임워크 등장.
`AngularJS`, `Backbone.js` 이라는 1세대 웹 프레임워크가 등장하게되는데
특징은 `양방향 데이터 흐름` 과 `MVC` 형태를 갖추고있는 `MVC 및 MVVM 프레임워크` 이다.


## 2세대 프레임워크 React
2세대 프레임워크인 `React` 는 1세대 프레임워크들과는 다르게 철저하게 `View` 에만 집중된다.  
DOM 을 효과적으로 처리하기 위해 `단방향 데이터 흐름`, `Virtual DOM` 의 특징을 갖는다.


#### 양방향 데이터흐름 vs 단방향 데이터 흐름
1세대 프레임워크의 `양방향 데이터 흐름` 은 자체 실행 코드내에 데이터 변화가 생기면 DOM 객체 전체를 렌더링하거나,  
데이터를 바꿔주는 등의 실행으로 성능이 감소되는 경우가 있다.

하지만 `단방향 데이터 흐름` 은 데이터에 변화가 있으면 특정 함수를 실행해 DOM 객체를 갱신해준다.

#### Virtual DOM
기존의 MVC 프레임워크는 DOM 객체 자체에서 데이터 변화를 감지하고 DOM 객체를 수정하여 업데이트하는데  
성능 저하가 일어날 수 밖에없다.  

그렇기 때문에 가상의 DOM 을 생성해 변경에 관련된 DOM 객체만 바꿔주는 알고리즘을 사용해 효율적으로 DOM을 갱신한다.  

[참고영상 DOM vs Virtual DOM](https://www.youtube.com/watch?v=BYbgopx44vo)

## 3세대 프레임워크 Vue.js
`Vue.js` 와 `React` 는 유사하지만 다른데, 링크를 참조한다  
[Vue.js 와 React 차이](https://kr.vuejs.org/v2/guide/comparison.html)



#### 참고문서
[https://subicura.com/2016/06/20/server-side-rendering-with-react.html](https://subicura.com/2016/06/20/server-side-rendering-with-react.html)  
[Virtual DOM 이란](https://velopert.com/3236)  
[리액트가 뭐지?](https://trustyoo86.github.io/react/2017/11/18/what-is-react.html)  
[https://trustyoo86.github.io/react/2017/11/18/what-is-react.html](https://trustyoo86.github.io/react/2017/11/18/what-is-react.html)
