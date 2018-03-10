# 웹브라우저의 역사, React 가 등장하기까지
웹 브라우저의 역사와 `React` 가 등장하기까지의 과정을 간단히 작성


### 초기 웹
초기 웹 사용자는 `NetScape` 와 `IE` 둘 중에 선택을 할 수 있었는데, `NetScape` 의 시장 점유율이 86%에 달했다. 하지만 1996년도에 `Microsoft` 가 `IE` 브라우저를 운영 체제와 통합을 해버려서 `IE` 의 점유율이 75% 까지 상승했다. 이로 인해 `NetScape` 는 쇠퇴했고 `IE` 가 거의 독점을 하는 추세였다.

상업적으로 제품 개발을 할 수 없게 된 `NetScape` 는 오픈소스를 통해 `Mozilla` 를 만들었다. (`Mozilla` 는 `NetScape` 회원들이 1998년에 설립한 free software community)  

`Mozilla` 는 `Firefox` 브라우저를 만들어냈고, 이후 `Apple` 의 `Safari`, `Google`의 `Chrome` 브라우저가 생겨났으며  
현재 `Google` 의 `Chrome` 브라우저가 점유율이 가장 높다.

[참고 : 위키피디아](https://en.wikipedia.org/wiki/History_of_the_web_browser)

웹은 초기에 C, C++, Perl 등으로 만들어진 프로그램에 사용자의 요청에 응하는 표준 출력을 브라우저에 되돌려주는 방식으로 보여졌다.
```
이런식으로
`printf(<html>...</html>);`
```

딱 봐도 작성유지가 힘들다.

### JSP

1990년대에 등장한 `JAVA` 의 열풍으로 `JSP(Java Server Pages)`언어를 이용해 동적인 웹 페이지를 만들었는데 여기에 문제가 있었다.
`JSP`는 사용자의 요청이 있으면 서버에서 전체 html을 만드는 방식이었는데 이는 비효율적이었다. `Ajax`가 등장하며 얘기가 달라졌다.

### Ajax

`AJAX` 는 `JSP` 와는 반대로 변경된 페이지의 요소만 변경이되었다.

이제는 동적으로 html 을 만드는 시대가 온 것인데, 그중 가장 간단한 방법이 `string` 을 붙이고 붙여서 특정 `DOM` 에 넣는 것이었다.  

여기서 생각해 볼 문제가 html 파일은 수많은 노드트리로 이루어져있다.
간단한 예로 다음과 같은 노드 트리가 있다고 가정해보자.
```
Document
   |
  html
   |
  body
   |
 header
   |
  nav
```
현재 `nav` 를 변경하고싶다.  
그러면 `Document - html - body - header - nav` 라는 단계를 거쳐서 바꾸는 것이다.  
노드트리가 많아지면 많아질수록 `DOM` 을 선택하고 조작하는 javascript 코드가 많아지고 이는 유지보수도 힘들뿐더러 비효율적이게 된다.

### AngularJS
이 때 `AngularJS` 가 등장하는데 `AngularJS` 는 `DOM`의 조작이나 제어하는데 초점을 둔것이아니고 data의 변화에 초점을 두었다.  
다시말하면, `Model` 과 `View`가 동기화되어 `2-way binding` 이된다. `DOM` 조작이나 제어가 초점이 되지않아 엄청 편리해졌다.

### React
여기서 새롭게 등장하는 `React` 는 `1-way binding` 으로서 `DOM` 대신 `virtual DOM` 이라는것을 사용하게되는데  
위의 노드트리에서 `nav`를 바꾸고싶다면 가벼운 버전의 `virtual DOM`을 생성하고 변경하고 이 virtual `DOM`을 삽입하는 방법이다.  

### Vue.js
`Vue.js` 와 `React` 는 유사하지만 다른데, 링크를 참조한다  
[Vue.js 와 React](https://kr.vuejs.org/v2/guide/comparison.html)

#### 참고문서
[https://subicura.com/2016/06/20/server-side-rendering-with-react.html](https://subicura.com/2016/06/20/server-side-rendering-with-react.html)  
