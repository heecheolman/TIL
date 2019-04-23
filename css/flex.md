# flexbox 개념잡기

flexbox 는 모던 웹페이지를 구성할 때 빼놓을 수 없는 레이아웃방식이다. 데스크탑을 비롯해 태블릿, 모바일 등 다양한 화면크기들이 나오면서 기존의 레이아웃 방식으로는 유연하게 대체하기 힘들다는 점이 있는데, flexbox 를 이용하면 좀 더 쉽게 대처할 수 있다.


### flexbox 의 장점

* 수직, 수평정렬의 편리함
* 일정한 간격조절
* 변하는 뷰포트에 효율적으로 대처 가능

## flex-container

```css
.flex {
  display: flex;
}
```

display 프로퍼티를 flex 로 지정하면 해당 엘리먼트는 `flex container` 가 된다. `flex container` 안의 요소들은 `flex item` 이 된다. 즉, 컨테이너가 되는 요소에는 `display: flex;` 속성을 주면 되는것이고 그 안의 요소들은 자동적으로 `flex item` 이 된다. `flex container` 에 주는 속성들이 따로 있고, `flex item` 에 줄 수 있는 속성들이 따로 존재한다. `flex item` 은 이후에 다루도록 한다.

먼저, `flex container` 에는 '축' 이라는것이 존재한다. 그 축에는 두 가지가 있는데, 주축(main axis)과 교차축(cross axis) 가 있다.

```
<flex-container>

주축(main axis) -------->
------------------------
|                      | |
|                      | |  교차축(cross axis)
|                      | |
------------------------ |
                         ∨
```

`flex item` 은 주축(main axis) 방향으로 '흐르는 것'이 중요하다. 흐르는 방향을 제어해주는 속성은 `flex-direction` 인데 기본 값이 `row` 이므로 따로 설정을 해주지 않으면 왼쪽에서 오른쪽으로 요소들이 '흐르게' 된다. 자세한 속성은 아래에서 다룬다.

### flex-container 속성들

* flex-direction
* flex-wrap
* flex-flow
* justify-content
* align-items
* align-content

**flex-direction**  
`flex item` 이 흐르는 방향을 정해준다. 즉, 주축(main axis) 를 변형시킬 수 있다. 기본값은 `row` 이다.

* `flex-direction: row;`: 주축이 왼쪽에서 오른쪽
* `flex-direction: row-reverse`: 주축이 오른쪽에서 왼쪽
* `flex-direction: column`: 주축이 위에서 아래
* `flex-direction: column-reverse`: 주축이 아래에서 위로

**flex-wrap**  
`flex container` 안에 있는 `flex item` 들이 해당 컨테이너의 요소를 넘치게 되면 한줄로 표현할 지, 여러 줄로 표현할 지 결정해준다. 기본값은 `nowrap` 으로 한 줄로 정렬이된다. 만약 컨테이너의 width 값을 넘게되면 넘치게된다. 이 때, `overflow: auto;` 를 주면 가로 스크롤이 생긴다.

* `flex-wrap: nowrap;`: 한줄로 표현
* `flex-wrap: wrap;`: 컨테이너의 width 보다 크면 아이템을 다음 줄로 배치
* `flex-wrap: wrap-reverse`: `wrap`과 동일하나 아래에서 위로 배치

**flex-flow**  
`flex-direction`과 `flex-wrap`속성을 지정해주는 shorthand 이다. 기본값은 당연히 각 속성의 기본값인 `row nowrap`

```css
.flex-container {
  flex-flow: [flex-direction] || [flex-wrap];
}

/* 예시 */
.flex-container {
  flex-flow: column wrap;
}
```

**justify-content**
컨테이너의 주축(main axis) 를 기준으로 **수평 정렬** 한다. 기본값은 `flex-start`이다. 주의깊게 봐야할 점이 **주축을 기준으로 수평정렬** 이다. 다시말해, `flex-direction: column;` 인 경우에는 주축(main-axis)이 세로(편의상 표현)이므로 세로의 수평은 세로다. (당연한 말) 직접 해보면 이해가 될 것이다.

* `justify-content: flex-start;`: 주축의 좌측을 기준으로 정렬
* `justify-content: flex-end;`: 주축의 우측을 기준으로 정렬
* `justify-content: center;`: 주축의 중앙으로 정렬
* `justify-content: space-between;`: 주축을 기준으로 좌우 측면에 요소를 각각 딱 붙여서 놓고, 나머지 요소는 간격이 동일하게 정렬
* `justify-content: space-around;`: 주축을 기준으로 좌우로 모든 요소의 간격이 동일하게 정렬

**align-items**  
컨테이너의 교차축(cross axis) 를 기준으로 **수직 정렬** 한다. 기본값은 `stretch` 이다.

* `align-items: stretch;`: `flex item` 들이 컨테이너의 높이(교차축의 시작점과 끝점)에 꽉 차게 퍼진다.
* `align-items: flex-start;`: 교차축(cross axis) 의 시작점을 기준으로 정렬
* `align-items: flex-end;`: 교차축(cross axis) 의 끝점을 기준으로 정렬
* `align-items: center;`: 교차축(cross axis) 의 중앙에 정렬
* `align-items: baseline;` 컨테이너의 baseline 을 기준으로 정렬한다.

**align-content**


### flex-item





## 참고문서

* [flexbox로 만들 수 있는 10가지 레이아웃 - NAVER-D2](https://d2.naver.com/helloworld/8540176)
*
