# 쿼리스트링을 저장하자

앵귤러 라우팅을 공부하고 적용하다가 쿼리스트링을 저장하고 이에 대한 활용방안에 대해 적어보려합니다.

## query string

쿼리스트링은 url 의 마지막에 `?` 를 붙여 일종의 데이터를 붙여넣는 방식입니다. 예를들어

```
http://localhost:4200/users?page=1&type=admin
```

이렇게 `users` 뒤에 `?` 를 붙이고 `변수명=값` 으로 데이터를 표현합니다. 쿼리스트링들의 구분자는 `&` 를 이용합니다.

## 앵귤러 적용

간단한 예로 검색시 검색필터값을 유지시키고 싶을 때 사용하는데 angular 에서는 다음과 같이 사용될 수 있습니다.
```ts
@Component({...})
export class MyComponent {
  inputString: string;
  constructor(
    private router: Router, // 의존성 주입
  ) {}

  // value 로 input 값이 들어옴
  searchQuerySet(value) {
    this.inputString = value;
    this.router.navigate([], {
      queryParams: {
        query: this.inputString, // 쿼리 설정
      },
      replaceUrl: true, // url replace
    })
  }

}
```

첫번째로 Router 를 의존성주입시키고, 입력값이 있다면 입력값을 데이터에 저장합니다. 이후에 Router 의 navigate 메서드를 이용하여 url 을 변경시켜주는데, queryParams 를 지정해주면 쿼리스트링들이 url 뒤에 붙게됩니다. 예를들어 위와 같은 상황에서 'hello' 라는 문자열을 입력했다면 url 은 다음과 같을것입니다.
```
http://localhost:4205/search?query=hello
```
`/search` url 뒤에 `query=hello` 라는 것이 붙습니다.

#### [replaceUrl](https://angular.io/api/router/NavigationExtras#replaceUrl)
url 을 대체시키고 url 히스토리에는 남지않아 쿼리를 적용시키는데 제격입니다. 만약 `false` 로 해둔 상태로 입력을 했다면 뒤로가기시 한글자한글자 지워지는것을 볼 수 있습니다.

## 활용방안

유저의 입력값이나, 관리자페이지의 필터값을 유지시키는 등 어떠한 입력데이터를 유지시키고 싶을 때 사용할 것 같습니다.
