# [ng-feedback](https://github.com/RickonChen/feedback#readme) + [dom-to-image](https://github.com/tsayen/dom-to-image) 결합

결합하기 전에 먼저 html 을 캡쳐하는 부분이 문제였습니다.

사실 html 을 이미지로 바꾸는것을 구글링하면 대부분이 html2canvas 를 추천해줍니다. html2canvas 모듈도 좋지만 css 들을 제대로 변환하지 못한다는 단점이 존재합니다.

> html2canvas 가 지원하는 [css 명세들](https://html2canvas.hertzen.com/features)

## dom-to-image 는 깨지지 않습니다

dom-to-image 를 이용해보니 99.99퍼센트 유지가되어 캡쳐가 됩니다.

#### [동작원리](https://github.com/tsayen/dom-to-image#how-it-works)

1. 캡쳐하려는 영역을 recursive 하게 복사
2. 복사 시 노드의 스타일들을 전부 계산해 복사
3. 웹 폰트를 삽입
4. 이미지들을 삽입
5. 복사된 노드들을 xml로 serialize 합니다.
6. xml 을 `<foreignObject>` 태그로 넣고 dataURL 을 만듭니다.

> 번역이 잘못되었을 수도 있습니다...

## ng-feedback 은 html2canvas 를 사용합니다


### 스크린 뜨는 서비스
ng-feedback 모듈에서 스크린을 뜨는 구현부를 보자면,

```ts
// feedback.service.ts
// ... 생략

public initScreenshotCanvas() {
    const that = this;
    const body = document.body;
    html2canvas(body, {
      logging: false,
      width: document.documentElement.clientWidth,
      height: document.documentElement.clientHeight,
      x: document.documentElement.scrollLeft,
      y: document.documentElement.scrollTop,
      allowTaint : true
    }).then(bodyCanvas => {
      this.screenshotCanvasSource.next(bodyCanvas);
    });
  }
```

처음 스크린샷을 뜰 때 html2canvas 를 사용합니다. 때문에 기대하고있던 스크린샷이 나올 수 없습니다.
그래서 이부분을 dom-to-image 모듈로 바꿔치기하면 어떨까 생각해 바꿔보았습니다.

```ts
// feedback.service.ts
// ... 생략

public initScreenshotCanvas() {
    const that = this;
    /**
     * 스크린샷하는 부분의 노드들을 돌며, 캡쳐를 무시할 id 를 정하고 캡쳐
     * 1. 캡쳐도구 dialog 를 무시
     */
    const captureArea = document.body;
    domToImage.toPng(captureArea, {
        filter: node => node.id !== 'dialog'
      })
      .then(function(dataUrl) {
        const img = new Image();
        img.src = dataUrl;
        that.screenshotImageSource.next(img);
      });

  }
```

캡쳐할 영역을 지정해주고(전체캡쳐: body), `screenshotImageSource.next(img)` 로 보내줍니다.

그리고 다음에 나오는 `getImgEle()` 메서드는 다음 절에 나오는 dialog 컴포넌트에서 쓰일 예정이니 잠깐 짚고 넘어갑니다.
```ts
// feedback.service.ts
// ...생략

public getImgEle(image): HTMLElement {
    Object.assign(image.style, {
      position: 'absolute',
      top: '50%',
      right: '0',
      left: '0',
      margin: '0 auto',
      maxHeight: '100%',
      maxWidth: '100%',
      transform: 'translateY(-50%)'
    });
    return image;
  }
```
이미지 element 를 만들고 스타일들을 지정해 반환해주는 메서드입니다.

### dialog 컴포넌트

dialog 컴포넌트로부터 클라이언트가 해당 서비스를 이용할 수 있게되니, 해당 컴포넌트를 둘러보면

```ts
// feedback-dialog.component.ts
// ...생략
public ngAfterViewInit() {
    this.feedbackService.screenshotImage$.subscribe((image) => {
      this.showSpinner = false;
      this.feedback.screenshot = image;
      this.screenshotEle = this.feedbackService.getImgEle(image);
      this.screenshotEle = image;
      this.appendScreenshot();
    });
    // ...
  }
```
`feedback.service.ts` 에서 emit 된 image DOM을 받아서 저장하고, DOM 을 추가해주는 부분입니다. 기존엔 canvas 로 되었었지만 image 로 변경해주었습니다.

### Renderer2

Angular 의 Renderer2 를 이용해 appendChild 를 하지 않기 때문에 Renderer2 로 바꾸어주었습니다.

```ts
// feedback-dialog.component.ts
// ...생략
public expandDrawingBoard() {
  // ...
  // this.el.nativeElement.appendChild(this.drawCanvas);
  this.renderer.appendChild(this.el.nativeElement, this.drawCanvas);
}

private appendScreenshot() {
    if (this.screenshotParent) {
       // this.screenshotParent.nativeElement.appendChild(this.screenshotEle);
       this.renderer.appendChild(this.screenshotParent.nativeElement, this.screenshotEle);
    }
  }
```

## 마무리지으며

모듈을 바꿔치기하려면 코드분석을 먼저 해야하는데 생각보다 오래걸리지 않아서 금방 할 수 있었습니다. 오픈소스를 고쳐서 쓰는걸 처음해봤는데 재미도있을 뿐더러 다른사람의 코드도 분석하며 생각을 많이 하게된 것 같습니다.
