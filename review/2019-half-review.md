# 2019년 상반기 리뷰

어느덧 2019년의 반절이 순삭당했다. 핀테크 회사에서의 신입생활도 어느덧 6개월차에 접어들면서 배웠던 것, 좋았던 것들 아쉬운점들을 적어 하반기를 더 보람차게 보내고 싶어 리뷰한다.

## 메모 📝

메모를 하는것을 습관적으로 하고 있다. 사실 메모를 더 신중히 하는이유는 개발을 하며 로직들을 그림으로 그려보는 것을 연습삼아 내 생각을 정리하는 것이다. 내가 다른 사람에게 내가 짠 코드를 구두로 설명하려할 때면 내가 말하고자 하는 방향을 잃고 있는 모습을 발견한다. 내 생각을 잘 전달 못한 것도 문제지만, 더 신경쓰이는 것은 내 생각을 들으려고 한 상대방의 시간이 허투루 됐다는 부분이다. 나의 문제점을 인지하고 있고, 메모를 하며 말을 하기전에 그림들을 떠올리며 차례대로 설명해나가는 연습을 하고 있다.

> 디지털로 문서를 작성하는 것도 좋지만 난 연필이나 볼펜이 종이에 그어지는 소리와 느낌이 좋다.

## 대화와 의견 🗣

서로 의견을 나누다보면 잘못하면 상대방의 기분을 상하게 할 요소가 크다. 상대방이 잘 못 생각했다고 공격성을 띄거나 무시하는듯한 말을 건네면 큰일난다. 결코 내가 그렇게 행동을 하진 않지만 항상 머릿속에 염두하고 말을 건넬 때 0.3초만이라도 상대방의 입장에서 한번 더 내뱉을 말을 생각해보고 뱉어보자.

## 개발 👨‍💻

### 읽기 좋은 코드

코드가 문서라고도 한다. 주석 대신 변수명이나 메서드명으로 충분히 그 의미를 내포하는것이 중요하다. 읽기 좋은 코드는 코딩컨벤션을 지키는것도 중요하지만 **좋은변수명, 좋은 메서드명에서부터 시작되는것이 아닐까 싶다.**

프론트엔드에서는 작성하는 코드가 가장 크게 `html`, `css`, `js` 가 있는데 각 파일마다 성질이 달라서 변수명 짓기가 그리 쉬운 편은 아니다. 특히 `css` 나 `html` 은 계층구조가 도드라지기 때문에 규칙을 잘 정해줘야한다. 예를들어 `wrap`, `container`, `box`, `card` 등등(흔히 많이 쓰이는 일종의 컨테이너?) 에 대해서도 말이다.

좋은 변수명 짓기, 메서드명 짓기는 경험과 어느정도 비례하지 않을까 싶다. (영단어도 중요 ㅋㅋ) 내가 처음 개발 공부를 시작할 때 썻던 변수명들을 지을 때를 되짚어보면 영단어의 양의 범위가 매우 좁았고 또 내포하는 범위가 컸다. `data`, `list` 와 같이 말이다.

지금은 나름 영단어 양이 늘었고, 될 수 있으면 변수명이 내포하는 의미를 더 좁히려고한다. 예를들어 `list` 를 쓰더라도 `무슨 list 인데?` 라고 한 번 더 내 자신에게 물어보면 한 단계 높은 변수 명을 지을 수 있다. `updatedTodoList` 와 같이 말이다.

나는 변수명을 풀어서 쓰는 편이다. 조금 길어지더라도 풀어서 쓴다. 예를들어 `getNum` 보다는 `getNumber` 를 선호한다. 줄인표현이 허용되는 부분은 모두가 통상적으로 쓰는 단어라던지, 사내 코딩컨벤션 이라던지, 특정 그룹에 의해 약속된 이름만 줄일 수 있다고 생각한다. 남의 코드를 볼 때 이상하게 앞글자만 따서 줄여진 표현들을 보면 무슨의미인지 해석하는데 더 많은 시간을 들인다. 이것은 장기적으로 볼 때 손해라고 생각한다. 그래서 변수명이 조금 길어지더라도 명확한 표현을 선호한다.

### 고차함수

자바스크립트의 내장함수들을 많이 활용하려한다. `reduce`, `map`, `filter`, `every`, `some`, `forEach`, `entries`, `find`, `join`, `slice` 등등. 전에는 겨우 `filter` 와 `forEach` 정도만 사용할 줄 알았다면 지금은 위에 리스트된 것들을 잘 쓸 수 있게 됐다. (생존하기 위한 배움이라고도 한다.) 이런 고차함수들을 잘 이용하면 위에서 언급한 코드의 가독성도 높아지고 간결해진다. **고차함수는 꿀이다**

### 모험

회사 업무 외에 집에서 여러가지들을 해보려한다. 최근에는 정적사이트생성기인 `gatsby` 를 이용해봤다. 물론 `gatsby` 는 리액트 기반인데 난 리액트를 해보지 않아 고생좀 했다. 그래도 SPA 프레임워크들이 대부분 비슷한 개념들을 가지고있어 조금(?) 할 만 했다. 그리고 배포는 `now.sh` 로 했다. 지금 작업중인건 `GraphQL + React` 를 이용해 웹 채팅을 구현해보는것을 하고있는데 리액트를 좀 더 깊게 공부하고싶어 차근차근 밟아가고있다.

## 놓치지마! ✅

### 최소한의 테스트코드

프론트에서 정규표현식을 사용하는일은 매우 흔한 일이다. 회원가입, 로그인 처리 등 폼(Form) 쪽에서 아주 많이 사용한다. 내가 작성하고 수정한 정규표현식 때문에 상용서비스에서 회원가입이 안되는 사태가 발생했다. 식은땀나며 `Git History` 를 살펴보니 문제는 이러했다. 정규표현식 `[]` 안에 문자셋을 등록하면 해당 문자셋들은 통과하는 것이었는데 파이프 문자인 `|` 와 한글 `ㅣ` 를 잘못보아 파이프문자 `|` 가 아닌 한글 `ㅣ` 를 지워 정규식의 `.test()` 에 통과가 되지않아 회원가입이 안되는 것이었다.

> X 됐다.

이후에 최소한의 테스트코드를 작성해야겠다고 다짐을 했고, 다시는 이런 실수를 하지 않도록 주의를 기울이고있다. 설령 테스트코드를 작성하지 않고 배포를 했다 하더라도 내가 실제로 테스트를 안해본 것 부터가 문제이니 고쳐야한다.

### 책

출퇴근 시간에 지하철(지옥철) 에서 보내는시간이 대략 1시간 15분 정도 되는데 너무 허투루 보낸 시간들이 많은 것 같다. 적어도 두달에 한권씩이라도 책을 읽어야겠다. 책을 많이 읽으면 나의 문제점인 _상대방에게 내 생각을 잘 정리해서 말하기_ 를 많이 고칠 수 있을 것 같다. 두달에 한 권씩 책읽기 도전한다.
