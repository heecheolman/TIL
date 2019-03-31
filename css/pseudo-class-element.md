# 가상클래스와 가상요소 (Pseudo Class와 Pseudo Element)

css로 html 의 스타일을 지정해주는 방법에는 몇가지 있는데 예전부터 그렇구나만 하고 넘겼던 '가상클래스' 와 '가상요소'에 대해 알아보려한다.

## 가상클래스 (Pseudo Class)

가상 클래스는 선택이 될 요소에 대해 특별한 **상태** 에 대한 스타일을 입혀줍니다. 흔히 사용하는 `:active`, `:hover` 와 같이 특정 상태에 대한 `:가상 클래스명` 을 적어주고 그 아래에 '그 상태' 에 대한 스타일을 기술해줍니다.

```CSS
selector:pseudo-class {
  property: value;
}
```

> `:pseudo-class` 에 들어갈 클래스는 [다음 명세](https://developer.mozilla.org/ko/docs/Web/CSS/Pseudo-classes)에 자세히 적혀있습니다. 이는 CSS 명세이기때문에 임의의 이름을 적용시킬 수 없습니다.


## 가상요소 (Pseudo Element)

가상 요소는 특정한 부분에 스타일을 입히고 싶을 때 사용한다. 가상 클래스는 특정 상태에대한 스타일이라면, 가상 요소는 특정 콘텐츠에 대한 스타일을 적용시키기위해 사용한다.

```CSS
selector::pseudo-element {
  property: value;
}
```

콜론(`:`) 이 한개일 때와 두개일 때가 있다. 두 개는 (`::`)  CSS3 의 명세이며 한 개는(`:`) CSS3 이전 버젼이다. IE 8 에서는 두 개짜리 콜론을 지원하지 않기 때문에 [크로스브라우징 이슈를 처리할 때 참고](https://developer.mozilla.org/ko/docs/Web/CSS/Pseudo-elements)하면 좋을 듯 하다.

#### 자주쓰는 가상요소

* [`::after`](https://developer.mozilla.org/ko/docs/Web/CSS/::after): 콘텐츠 뒤에 위치하는 공간 선택
* [`::before`](https://developer.mozilla.org/ko/docs/Web/CSS/::before): 콘텐츠의 앞에 위치하는 공간을 선택
* [`::selection`](https://developer.mozilla.org/ko/docs/Web/CSS/::selection): 드래그한 콘텐츠를 선택 지원하지 않는 브라우저가 있어 체크해야한다. 그리고 `::` 콜론은 두 개만 지원한다고한다.



## 참고문서
* [CSS3-셀렉터 - poiemaweb](https://poiemaweb.com/css3-selector)
* [가상클래스 - MDN](https://developer.mozilla.org/ko/docs/Web/CSS/Pseudo-classes)
* [가상요소 - MDN](https://developer.mozilla.org/ko/docs/Web/CSS/Pseudo-elements)
