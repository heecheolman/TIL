# Javascript
Javascript 는 4가지로 세분화할 수 있다

| 분류  | 설명 |
| :------------ | :-----------: |
| 자바스크립트 Core문법     | 기본문법, 데이터타입, 조건문 등이 포함          |
| 자바스크립트 Core라이브러리    | 내장함수들이 포함되어있음, Date, Math 등      |
| 자바스크립트 DOM    | 노드(node), 스타일, 속성, 이벤트 등을 다룰 수 있는 다양한 기능 포함|
|자바스크립트 BOM| 브라우저와 관련된 Window, Navigator, Location, History, Document, Screen 객체가 포함|


# BOM (Browser Object Model)
BOM(브라우저 객체 모델) 은 **브라우저와 컴퓨터 스크린에 접근** 할 수 있는 객체의 모음.  
`window` 객체를 통해 접근 가능  

### window 객체모델
* `navigator` : 브라우저명과 버전정보를 속성으로 가짐  
* `window` : 최상위 객체로, 각 프레임별로 하나씩 존재  
* `document` : 현재문서에 대한 정보  
* `location` : 현재 URL에 대한 정보, 브라우저에서 사용자가 요청하는 URL  
* `history` : 현재의 브라우저가 접근했던 URL history  
* `screen` : 브라우저의 외부환경에 대한 정보를 제공


# DOM (Document Object Model)

DOM(문서 객체 모델) 은 HTML 문서를 노드트리로 나타내는데  
그렇기 때문에 DOM트리의 모든 노드는 객체이다

##### 노드(Node)?
노드(Node) 란 트리구조에서 데이터의 상하위 계층을 나타내는 위치의 항목

예를들어
```
<html>은 모든 요소의 부모이며
<head> 와 <body> 는 <html>의 자식이다
이러한 형태를 노드트리라고 부른다
```

### 참고문서
[http://www.deadfire.net/jscript/jscript22.html](http://www.deadfire.net/jscript/jscript22.html)  
[http://ohgyun.com/292](http://ohgyun.com/292)  
[http://webclub.tistory.com/218](http://webclub.tistory.com/218)
