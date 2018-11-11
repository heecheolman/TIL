# 모던 브라우저는 어떻게 동작하는가 ? - 방진호님

## Chromium 이란?
* 크롬 브라우저의 오픈소스
> 소스코드만 13GB 이고 iMAC 5K 기준 빌드시간만 3시간이라고 하심 ㄷ ㄷ

## 내부 동작을 알아서 뭐하나?
* 브라우저 및 웹 플랫폼 개발에 참여할 수 있다.
* 웹 표준 개발에 참여
* 프론트엔드 개발시 성능 향상에 도움이 됨
* 다양한 소프트웨어 개발 분야에 활용될 수 있음.


## Chromium은 Multi-Process Architecture 이다.

### Process 와 Thread 의 차이
#### Process
메모리 공간이 독립적
#### Thread
메모리 공간을 공유

#### 크롬의 장점
1. Crash 가 발생해도 죽지 않는다.
2. [Site Isolation (OOPIF)](https://www.chromium.org/Home/chromium-security/site-isolation)

Site Isolation 의 경우에는 예를들어 피싱 사이트가 있을 때  
피싱 사이트 내의 다른 진짜 도메인에 무언가 하려할 때 독립된 프로세스이므로 접근이 안된다고 하심.

> 이렇게 말하는것이 맞나... 어쨋든 보안적으로 좋다.

#### 대표적인 Process

* ###### Browser Process : 외부와의 소통(System call 등) 을 한다.
* ###### Renderer Process : 웹 컨텐츠를 담는다.

## 크롬 브라우저를 이루는 엔진들
* Rendering Engine (Blink Rendering)
* Javascript Engine (V8)
* Graphics Library (SKIA)

### Blink renderer 에서 일어나는 일

##### 1. Parsing
  * HTMLDocumentParser 가 파싱을 하며 DOM 을 만듦
  * DOM

##### 2. Style (DOM 파싱이 일어나는 중간에)
  * CSSParser 가 StyleSheetContents 로 빌드하고 CSSSelectorList 와 CSSPropertyList 를 만들어냄
  * `Document::UpdateStyle` --> `ComputedStyle`
  * `getComputedStyle(element)`
  * CSS Parsing 은 DOM 을 생성하는 중간에, Style Update 는 DOM 생성 후에 일어난다.


  ```html
...
<body>
  <p class="temp-p">Hello</p>
  <p class="temp-p">World</p>
  <style> .temp-p{ background: royalblue; }</style>
</body>
...
```

![이미지](https://t1.daumcdn.net/cfile/tistory/99ADB5335BE7EA630D)


다음과 같은 결과를 내는 이유는 CSS Parsing 은 DOM 을 생성하는 중간에 만들어지고,  
Style Update 는 DOM 생성 후에 일어나기 때문이다.

##### 3. Layout
* 실제로 화면에 표시 될 Object 를 결정
* DOM Tree 와 Layout Tree 는 1:1 로 맵핑됨
* LayoutTree 는 **화면에 표시될 노드들만 생성됨** (display: none; 은 생성되지 않음 )
* LayoutTree를 만들고 나면 어떤위치에 어떤 사이즈로 배치할지를 결정
* `LocalFrameView::UpdateLayout` 이부분이 Front-End 개발자가 말하는 **Reflow**

##### 4. Layerization

##### 5. Paint
* PaintLayer 라는 트리의 정보가 화면에 표시될 각각의 정보들을 가지고 있는 Object 가 SKIA 그래픽 라이브러리를 통해 Paint 됨


지금까지 살펴본 모든 렌더링은 모두 `Main-thread` 에서 일어난다.

여기서 문제가 있다.

##### V-Sync Timeline
보통 모니터의 주사율이 60Hz 이고 그 신호가 V-Sync 인데 주사율 하나당 `16.7ms` 에 그려져야하는데 보통 시간이 오버 된다.

다시말하면, 프레임드랍이 일어난다는것이다.

#### 어떻게 프레임드랍없이 표현?
메인스레드 말고 다른 스레드에 위임을하자.

락이 걸릴 수 있으니 실제로는 그림을 그리지 않고 뻥을 친다.
> 예를들어 포스트잇 같은 메모지를 적어놓는데, 이것을 Recording 이라고 함

기록된 `Recording` 을 다른스레드에 넘겨준다!  
**이제 다른 스레드에게 넘겨줌으로써 메인스레드에 일을 줄이고 주사율을 맞출 수 있다.**

#### Rendering 관련 용어 정리
* **Painting:**  넓은의미로 Rendering 과정 전체, 좁은 의미로 Recording
* **Recording:** Blink 관점에서 Painting, 그림 그리는 연산을 기록하는 행위
* **Rasterization:** Pixel Buffer 에 그림을 실제로 그리는 행위
* **Compositing:** 여러장의 그림을 합성하는 행위
* **Drawing:** 그림을 사용자가 볼 수 있는 화면에 출력하는 행위


### [GPU Acceleration (GPU 가속)](https://www.chromium.org/developers/design-documents/gpu-accelerated-compositing-in-chrome)
* 모던 브라우저의 대부분은 GPU 가속을 사용한다.
* GPU 가속은 OpenGL(Operating System) 을 사용해 가속

##### 장점
* Graphics Primitive 를 빠르게 그릴수 있다.
* 각종 변환(Transformation)을 빠르게 할 수 있다.
* 텍스쳐를 빠르게 합성할 수 있다.

#### 어떻게 작동되나?
먼저 용어를 알아보자.  
**Compositing** 이란 각각의 병렬의 레이어들을 그려 한방에 합친다는 뜻이다.  
**GPU Compositing** 은 이미지를 GPU 메모리에 Cache 해두었다가 필요할 때마다 합성하는것이다.

GPU Compositing 의 단계를 알아보면 다음과 같다.
1. Record
2. Raster
3. Upload
4. Draw


##### 1단계 : Record (Main Thread)
위에서 그린다고 뻥을 치는 작업을 한다. (포스트잇에 해야할일을 적는 것처럼) 그리고 **Raster Thread** 에 넘겨준다.

##### 2단계 : Raster (Raster Thread)
병렬적으로 이미지를 해석하고 공유되는 메모리에 적재

##### 3단계 : Upload (Raster Thread)
GPU 프로세스에 업로드

##### 4단계 : Draw (Compositor Thread)
그리라는 명령을 GPU 프로세스에게 전달

![이미지](https://t1.daumcdn.net/cfile/tistory/99CA373F5BE7D7CB27)

*사진 출처는 방진호님의 발표자료입니다! 문제가될시 삭제하겠습니다!*

> 해석이 이게 맞는지 잘 모르겠다. 사진을 참고하는것이....


GPU 에게 위임을 하게되면 GPU Process 에서 OpenGL 작업을 하게된다.

결론적으로, GPU Memory 에 Texture Upload 가 되면, 그것을 합성하거나, 변환하는 것은 매우 빠르다.


#### 3단계 의 Upload 에서 복사를 하지않고 접근하면되지 않나?
복사하지않고 다이렉트로 접근하면 좋은데 구조성 GPU Process 가 다른 프로세스에 접근할 수 없으니 복사를 한것.

#### GPU Compositing 의 효과
실제 자료는 변경되지않으니 버벅이지 않음
* 레이어 이동
* 스크롤링
* Pinch Zoom

어떤 Element 의 width 를 변경하면 Layout, Paint, Composit 모두 발생하게되는데  
GPU 가속을 사용하면 Composit 만 발생해서 빠르다.

> [CSS Triggers](https://csstriggers.com) 에 접속하면 각 속성들이 어떤 작업이 이루어지는지 볼 수 있다.

## 나의 마무리
사실 정리하다보니 이것저것 찾아보는데, 대략적인 흐름은 파악한것 같았다.  
세션 듣는 내내 집중해서 듣긴했는데 못알아듣는것도 있어서 듬성듬성 메모한걸 기준으로 맞춰보았다.

잘못된 점이 있으면 Contact 해주시면 감사하겠습니다.


#### 읽어보면 좋을만한 자료
* [웹에서 최대 FPS : WebRender가 끊김을 없애는 방법 - codepink
](https://goo.gl/g5uwkN)
