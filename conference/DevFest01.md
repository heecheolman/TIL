# Chrome Devtools를 활용한 성능측정과 개선 - 한재엽님

### 성능이란 UX다
무조건 빠른게 아니라 사용자에게 끊기는 느낌이 없도록 부드럽게 보여져야한다.  
**측정할 수 없다면 개선할 수 없다.**

> 한재엽님이 생각하는 주관적인 성능에대한 짤막한 글이었습니다.

## 어떻게 측정할것인가?
어떻게 측정할 것인가에대해 RAIL 모델을 기반한다고 말씀하셨습니다.

### RAIL 모델이란?
사용자 중심 성능 모델로 요약할 수 있는데 RAIL 은 다음을 축약한 단어이다.

![이미지](https://developers.google.com/web/fundamentals/performance/images/rail.png?hl=ko)

* **응답** : 100ms 이내에 응답
* **애니메이션** : 10ms 이내에 프레임 생성
* **유휴** : 유휴시간 극대화
* **로드** : 콘텐츠를 1000ms 이내에 전달

위와 같은 조건을 만족해야하지만 아쉬운점이 있다.  
##### 아쉬운점
* 귀찮다.
* 이슈를 발견해도 파악이 어렵다.
* 해결한 후 다시 측정해야 한다.



### Audits 도구 이용
크롬 개발자 도구의 `audits` 를 이용해 측정한다.  
이 도구를 이용해 성능을 측정하면 다음과같은 수치들이 도식으로 나오게 된다.

* Performance
  * RAIL 모델 기반 수치들이 나온다.
  * First Contentful Paint, Time To Interactive(TTI) 등
* Accessibility
  * 접근성
* Best Practices
  * 모범 사례 점수?
* SEO(Search Engine Optimization)
  * 검색엔진 최적화가 잘되어있는지에 대한 측정



위의 도구를 이용해서 어느정도 측정을 할 수 있다.

### 그래서 어떻게 개선할껀가?
##### 로딩 과정
  1. Connection
  2. TTFB(Time To First Byte) : 최초응답을 기다리는데 보낸 시간
  3. DOM 트리 파싱 과정

##### 3R
  1. **R**equest 횟수
    * Lazy Loading : 리퀘스트의 절대적인 수를 줄여주진 않지만 첫번째 페이지 로딩시간에 영향을 줌.
  2. **R**esource 사이즈 줄이기
    * Webpack 이용
      * Minify
      * Tree-shaking
      * Code-Splitting
  3. **R**endering 시간 단축
    * Reflow 최소화
    * 부드러운 애니메이션


#### Lazy Loading
먼저 잘못된 예시가 있다고한다.  
`react-lazyload` 인데 이 모듈은 스크롤이 될 때마다 `getBoundingClientRect()` 를 호출하게 되는데 이 함수는 대놓고 Reflow 를 한다고 한다.

> Reflow 를 줄이려하는데 오히려 Reflow 를 하고있음

그래서 [IntersectionObserver API](https://developer.mozilla.org/en-US/docs/Web/API/Intersection_Observer_API) 를 이용한다고 한다. 해당 API 는 비동기 API 이다.

> IE 와 Safari 가 지원을 안해서 그냥 Polyfill 로 추가한다고 하셨다.   


사용법 및 설명은 아래의 링크에 정말 자세히 나와있다. 꼭 읽어보길 바란다.
 * [너는 나를 본다: 지연 방법, 레이지 로드와 IntersectionObserver의 동작](https://github.com/codepink/codepink.github.com/wiki/%EB%84%88%EB%8A%94-%EB%82%98%EB%A5%BC-%EB%B3%B8%EB%8B%A4:-%EC%A7%80%EC%97%B0-%EB%B0%A9%EB%B2%95,-%EB%A0%88%EC%9D%B4%EC%A7%80-%EB%A1%9C%EB%93%9C%EC%99%80-IntersectionObserver%EC%9D%98-%EB%8F%99%EC%9E%91)

#### 부드러운 애니메이션
두가지가 있다.

1. 하드웨어가속
2. 스크롤 이벤트 튜닝

##### 먼저 하드웨어 가속
* CPU 보다 GPU 가 잘하는 일은 GPU 에게 위임
* 크롬 개발자도구의 `Layer` 로 확인
* 하드웨어 가속은 다른 세션에 설명이 잘 되어있음.

##### 스크롤 이벤트 튜닝
`onScroll = { ... }` 이러한 코드를 통해 스크롤마다 이벤트를 발생하는데

```javascript
document.addEventListener('scroll', function(){
  console.log('scroll');
})
```
이렇게 된다면 아주 많은 이벤트가 발생되어 사용하면안됨.
> 위의 [너는 나를 본다: 지연 방법, 레이지 로드와 IntersectionObserver의 동작](https://github.com/codepink/codepink.github.com/wiki/%EB%84%88%EB%8A%94-%EB%82%98%EB%A5%BC-%EB%B3%B8%EB%8B%A4:-%EC%A7%80%EC%97%B0-%EB%B0%A9%EB%B2%95,-%EB%A0%88%EC%9D%B4%EC%A7%80-%EB%A1%9C%EB%93%9C%EC%99%80-IntersectionObserver%EC%9D%98-%EB%8F%99%EC%9E%91) 의 글에 따르면 `Event` 와 `Observer` 는 다르다고 했다.  
전자는 발생할 때마다 동기적으로 반응해 메인스레드의 응답성에 영향을 주고, 후자는 성능에 많은영향을 주지않으며 비동기적으로 반응한다고 했다.  
자바스크립트는 메인스레드 하나이니 위의 코드처럼한다면 아주 느려질것이다.

###### [requestAnimationFrame](https://developer.mozilla.org/ko/docs/Web/API/Window/requestAnimationFrame) 을 사용하자

* 초당 60회 rendering 하는 디바이스의 브라우저에 최적화
* animation queue 를 사용

![이미지](http://sculove.github.io/blog/2018/01/18/javascriptflow/browser-structure.png)

위의 사진은 **[자바스크립트의 이벤트 루 프](http://sculove.github.io/blog/2018/01/18/javascriptflow/)** 이다.  
`animation Frames` 의 queue가 별도로 있는것을 확인한다.

이 함수를 이용하게되면 예를들어 스크롤시마다 동기적으로 반응되는 `Event` 와는 다르게 `Animation Queue` 에 들어가게되되는데, 60프레임을 맞추기 위해 브라우저가 노력을 한다.  
하지만 1개의 프레임을 그리기위해선 약 `16.7ms` 가 소요되는데 이를 넘어가게 되면 뒤에 호출될 `requestAnimationFrame` 이 생략된다.

> 각 queue 의 우선순위 : MicroTask -> AnimationFrames -> Task 순서이지만 브라우저에 따라 다를 수 있음


### 발표자님의 마무리
* Case by Case 인 성능 튜인
  * 프론트는 너무 많은 변수가 있기에...
* 개발이 어느정도 완료된 후 진행하길 권장
  * 개발하면서 성능 개선을 하면 over engineering임

### 나의 마무리
* 중간중간 내가 공부한것들도 끼워넣긴 했다.  
* 핵심은 Webpack 을 이용하면 대부분의 최적화가 된다는 것이었다.
* 나의 개인 웹 프로젝트 진행시에 최적화에도 상당한 공부를 해야할 듯 하다.


## 참고문서
* [RAIL 모델로 성능 측정 - WebFundamentals](https://developers.google.com/web/fundamentals/performance/rail?hl=ko)
* [성능 좋은 웹 애니메이션과 인터렉션: 60 FPS 달성 - codepink](https://github.com/codepink/codepink.github.com/wiki/%EC%84%B1%EB%8A%A5-%EC%A2%8B%EC%9D%80-%EC%9B%B9-%EC%95%A0%EB%8B%88%EB%A9%94%EC%9D%B4%EC%85%98%EA%B3%BC-%EC%9D%B8%ED%84%B0%EB%A0%89%EC%85%98:-60-FPS-%EB%8B%AC%EC%84%B1#requestanimationframe)
