<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 컴포넌트와 스타일
컴포넌트는 독립된 스타일 정보를 갖습니다. 때문에 A 컴포넌트에서 작성한 스타일과 B 컴포넌트에서 작성한 스타일 클래스가 겹치더라도 서로 영향을 주지 않습니다. 이 섹션에서는 컴포넌트와 스타일에 관련된 주제를 다루겠습니다.

## 📝 목차
* [컴포넌트 스타일](#컴포넌트-스타일)
  * [인라인 방식](#인라인-방식)
  * [링크 방식](#링크-방식)
* [뷰 캡슐화](#뷰-캡슐화)
* [글로벌 스타일](#글로벌-스타일)


## 컴포넌트 스타일
컴포넌트 스타일을 지정하는 방법은 두가지가 있습니다. 한가지는 인라인방식이고 다른 한가지는 링크 방식입니다. `@Component()` 데코레이터에 각각 정의하는 방법이 다릅니다.

#### 인라인 방식
직접 인라인으로 넣는 방식입니다. 웹앱이 커질 수록 링크방식을 선호하는 편입니다.
```ts
@Component({
  ...
  styles: ``;
})
```


#### 링크 방식
외부파일로 따로 빼서 링킹하는 방식입니다. 웹앱의 규모가 커질수록 파일로 따로 빼는것이 좋습니다.

```ts
@Component({
  ...
  styleUrls: ['경로'],
})
```

## 뷰 캡슐화
처음에 컴포넌트는 컴포넌트별로 스코프가 고유하다고 하였습니다. 때문에 스타일 네이밍이 겹치더라도 서로 영향을 주지 않습니다. 이것을 뷰 캡슐화라고 합니다.

`@Component` 의 `encapsulation` 프로퍼티에 `ViewEncapsulation` 옵션을 지정하여 뷰 캡슐화 전략을 설정할 수 있습니다. 3가지 전략을 살펴보겠습니다.

* Emulated : 임의의 어트리뷰트를 추가해 뷰 캡슐화 구현 -> 해당컴포넌트에만 적용(default)
* Native : 웹 컴포넌트의 Shadow DOM 을 사용해 뷰 캡슐화 구현 -> 해당컴포넌트에만 적용
* None : 스타일 캡슐화를 지원하지 않습니다 -> 모든 컴포넌트 공통 적용

> [Shadow DOM](https://developer.mozilla.org/ko/docs/Web/Web_Components/Shadow_DOM)은 뷰 캡슐화 전략과는 무관하게 사용할 수 있습니다.

## 글로벌 스타일
웹 애플리케이션 전역에 공통적으로 적용되어야할 스타일이 있을 것입니다. 적용하는 방법은 두가지가 있습니다.

* `angular.json` 의 styles 프로퍼티에 적용하기
* `src/styles.css` 에 적용하기

첫번째 방법은 `angular.json` 의 `architect.build.options.styles` 프로퍼티에 글로벌로 적용될 css 파일을 등록해주면 됩니다.
```json
"architect": {
        "build": {
          /* 생략 */
          "options": {
            /* 생략 */
            "styles": [
              "src/styles.css",
              /* 추가 */
            ],
          }
        }
      }
```

두번째 방법은 이미 전역으로 등록된 `src/styles.css` 에 작성하면 됩니다.

## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
