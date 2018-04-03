# SPA & Routing & Hash

## 1. SPA (Single Page Application) 란?
단일 페이지 어플리케이션은 모던 웹의 패러다임이며, 기본적으로 단일 페이지로 구성되어있다.  

기존의 웹은 요청시마다 새로고침이 발생하여 서버로부터 리소스들을 받아 렌더링하게 되는데  
이렇게 서버가 해당하는 `html`을 내려주는 방식을 `서버 사이드 렌더링(Server-side rendering)` 이라고 부른다.
대체로 `header` 나 `footer` 부분은 변하지않고 `contents` 부분만 변하게 되는데 변하지 않는 부분까지 렌더링을 하게되면 굉장히 비효율적이다.

하지만 `SPA` 는 처음에 모든 정적 리소스들을 처음에 한번 내려받는다.  
이렇게되면 새로운 페이지를 요청할 때 해당하는 데이터만 전달하면 되므로 필요한 부분만 렌더링되어 새로고침이 일어나지 않아 전체적으로 트래픽이 감소 된다.  

기존의 `서버 사이들 렌더링`과는 반대로 `html` 을 내려주는 방식을 `javascript`가 수행하게 된것이다. 이런 방식을 `클라이언트 사이드 렌더링(Client-side rendering)` 이라 한다.

## 2. 라우팅(Routing) 이란?
라우팅이란 출발지에서 목적지까지의 경로를 결정하는 기능이다. 사용자가 A 라는 화면에서 B 라는 화면으로 넘어가는 네비게이션을 관리하기 위한 기능을 의미한다.

브라우저가 화면을 전환하는 경우
1. 브라우저의 주소창에 URL을 입력하면 해당 페이지로 이동
2. 링크를 클릭하면 해당 페이지로 이동
3. 앞으로가기 뒤로가기를 누르면 웹페이지의 히스토리의 앞 또는 뒤로 이동

## 3. SPA 와 Routing
전통적인 웹 부터 SPA까지 발전하게 된 과정을 알아본다.

### 3-1. 전통적 링크 방식
전통적인 링크방식은 링크태그를 이용한다.  

`<a href="index.html">go main</a>`


링크를 클릭하게 되면 리소스의 경로가 URL의 path에 저장이되고, 서버는 해당 `html`을 클라이언트에 응답한다.  
이를 `서버 사이드 렌더링`이라 한다.  

##### 장점
페이지마다 URL이 존재하여 `history` 관리 및 `SEO` 대응에 문제가 없다.  

##### 단점
전체페이지를 로딩하므로 변경이 불필요한 요소도 로딩된다.  
복잡한 웹페이지라면 중복된 html, css, javascript를 계속 다운로드해야하므로 속도가 저하된다.


### 3-2. AJAX 방식
`AJAX(Asynchronous JavaScript and XML)` 는 전통적 링크방식에서 개선한 방식으로  
자바스크립트를 이용해 비동기적으로 서버와 브라우저가 데이터를 교환하는 방식이다.

`<a id="main">MAIN</a>`  

전통적 링크방식과는 반대로 `href` 를 사용하지 않는다. `AJAX` 를 통해 서버에 필요한 리소스를 요청하고 응답을 하면 `html` 내의 내용을 갈아치운다.

##### 장점
필요한 부분만 렌더링을 하므로 기존의 방식보다 속도가 빠르다.  

##### 단점
URL 의 변경이 없으므로 앞으로가기, 뒤로가기 등의 `history` 관리가 되지 않는다.  
URL이 하나이므로 `SEO` 이슈에 대해서도 자유로울 수 없다.

### 3-3. Hash 방식
Hash 방식은 URI 의 fragment identifier (예: #home )의 고유기능인 앵커(anchor) 를 사용한다.  
fragment identifier는 URI 에서 `#` 으로 시작하는 문자열인데 `hash` 또는 `hash mark` 라고 불린다.


`<a href="#home">HOME</a>`

`href` 어트리뷰트에 `hash` 를 사용한다. HOME 을 누르게 되면 `hash` 가 추가된 URI가 표시된다.
`hash` 가 추가되면 URL 이 동일한 상태에서 URI 만 바뀌므로 서버에 어떤 요청도 하지않는다.  
다시말하면, `hash` 가 변경되어도 요청이 보내지지않으므로 페이지의 새로고침이 발생하지 않는다.

> [URL 과 URI 의 차이](http://sunychoi.github.io/java/2015/04/27/uri-url.html)

`hash` 는 페이지가 새로고침이 되지않지만 논리적으로 페이지를 분리한다. 그렇기 때문에 히스토리 관리가 되는것이다.  
`hash` 방식은 `hashchange` 이벤트를 통해 `hash` 값 변경을 통해 `AJAX` 요청을 수행한다.

##### 장점
기존의 `AJAX` 방식에서 히스토리 관리가 안됐다면 `hash` 방식은 히스토리 관리가 된다.

##### 단점
여전히 `SEO` 이슈이다. 크롤러는 `javascript` 를 실행시키지 않기 때문에 `hash` 방식으로 만들어진 콘텐츠를 수집할 수 없다.


### 3-4. PJAX 방식
`hash` 방식의 가장 큰 단점인 `SEO`이슈인데 이를 보완한 방법이 `PJAX(pushstate + ajax)` 이다.  
`pushstate` 와 `popstate` 를 사용한다. 하지만 두 메서드는 `IE10` 이상에서 작동한다.

`<a href="/home">HOME</a>`

`href` 방식에 path 를 사용하고있다. HOME 을 클릭하면 path 가 추가된 URI 가 서버로 요청된다.  
그리고 이벤트를 캐치 한 후 `preventDefault` 를 사용해 서버로의 요청을 방지한다.  
이후에 `href` 속성에 path 를 사용해 `AJAX` 요청을 한다.  

`AJAX` 요청은 주소창의 URL을 변경시키지않아 히스토리 관리가 안되는데  
이 때 `pushstate`를 사용하면 주소창의 URL은 변경되고 히스토리가 남지만 요청을 하지 않으므로 페이지가 갱신되진 않는다.

`hash` 방식에서는 URL이 변경되지않아 `SEO` 가 문제가 되지만  
`PJAX` 는 페이지마다 고유의 URL 이 존재하기 때문에 아무 문제가 없다.  



## 마무리지으며

* 자세한 사항은 `SEO`에 관해 더 공부해야 할 것 같다.
* 첫번째 참고문서를 통해 많이 배운듯 하다.
* PJAX 는 첫번째 참고문서를 보는게 더 설명이 좋다

#### 참고 문서
[Single Page Application & Routing](http://poiemaweb.com/js-spa)  
[SPA와 SPA라우팅의 원리](http://reimaginer.tistory.com/entry/spa-and-spa-routing)  
[SPA의 원리](https://isme2n.github.io/devlog/2017/05/19/about-spa/)  
[클라이언트사이드 렌더링, 서버사이드 렌더링](http://asfirstalways.tistory.com/244)  
