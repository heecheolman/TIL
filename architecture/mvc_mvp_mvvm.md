# MVC, MVP, MVVM
프로그램을 잘 섞어서 처리를 해도 잘 동작한다. 하지만 분리하지 않고 프로그램을 짠다면 규모가 커질 시  
유지보수도 힘들 뿐더러 협업시에 많은 어려움이 있다.  

이러한 이유를 포함해 많은 이유가 있지만 결론적으로는 관리를 효율적으로 함에 있어서 다음의 패턴들을 이용한다.
다음 설명을위해 공통적으로 사용하는 용어의 의미

##### Model
데이터를 가진 객체
##### View
사용자에게 보여지는 UI

## MVC(Model View Controller)
![이미지1](https://magi82.github.io/images/2017-2-24-android-mvc-mvp-mvvm/mvc.png)
출처 : [마기의 개발블로그](https://magi82.github.io/android-mvc-mvp-mvvm/)

##### Controller
사용자에게 입력을 받은 후 해당하는 입력에 따른 `Model` 을 선택해 처리.  
입력에 따라 `Model` 을 업데이트 하고 결과에 따른 `View` 를 선택

##### 데이터플로우
1. `Controller` 로 Client의 입력이 들어온다.
2. `Controller` 는 `Model` 을 데이터 업데이트 후 로딩
3. `Model` 은 해당 데이터를 보여줄 `View` 를 선택해 보여준다.

##### 특징
* `View` 는 `Controller` 의 존재를 모른다 -> `Controller` 가 `View` 를 선택하는것임
* `Controller` 는 `Model` 을 조작하고 `View` 를 선택하지만 `View` 를 직접 업데이트를 하지는 않는다.

##### 단점
* `View` 와 `Model` 이 서로 의존적임
* 프로그램의 규모가 커지면 `View` 를 관리하는 `Controller` 가 커진다.


## MVP(Model View Presenter)
![이미지2](http://startandroid.ru/images/stories/blog/493/x010.png.pagespeed.ic.QC26kF2Y20.png)
출처 : [TechYourChacne](https://www.techyourchance.com/mvp-mvc-android-1/)

MVC에서 파생된 패턴으로 MVC패턴의 의존적인 문제를 해결하고자 나온 패턴이다.  
사용자의 입력을 `View` 에서 받는다.

##### Presenter
사용자의 이벤트에 대한 로직을 처리하고 `Model` 을 관리한다.  
`Model` 의 상태 변화를 `View` 에게 알려주는 역할도 함

##### 데이터플로우
1. `View` 에 사용자 입력이 들어온다.
2. `View` 는 `Presenter` 에 작업 요청을 한다.
3. `Presenter` 에서 필요한 데이터를 `Model` 에 요청.
4. `Model` 은 요청에 필요한 데이터를 `Presenter` 에 전달.
5. `Presenter` 가 `View` 에 전달
6. `View` 출력

##### 특징
* `View` 와 `Model` 은 서로 알필요가 전혀 없다 => MVC의 의존성 해결

##### 단점
* `View` 와 `Presenter` 가 1:1 로 강한 의존성을 가짐
* 각 `View` 를 위한 `Presenter` 가 필요하여 코드수가 증가함

## MVVM(Model View ViewModel)
![이미지3](http://www.dotnetcurry.com/images/xamarin/mvvm/mvvm-schema.png)
출처 : [dotnetcurry](http://www.dotnetcurry.com/xamarin/1382/mvvm-in-xamarin-forms)

현재 많은 변화를 요구하는 사용자 인터페이스로 인해 `View` 를위한 `View` 가 중심이 되는 패턴

##### ViewModel
`View` 를 표현하기위해 만들어진 `View` 를 위한 `Model`.  

##### 데이터플로우
1. `View` 에 입력이 들어온다면 `Command 패턴` 으로 인해 `ViewModel` 에 명령.
2. `ViewModel` 은 필요한 데이터를 `Model` 에 요청.
3. `Model` 은 `ViewModel` 에 필요한 데이터를 응답.
4. `ViewModel` 은 응답 받은 데이터를 가공해서 저장.
5. `View` 는 `ViewModel` 과의 `Data Binding` 으로 인해 자동으로 갱신 됩니다.

##### 특징
* `Command 패턴` 과 `Data Binding(2-way binding, Binding propagation)` 으로 인해 `View` 와 `ViewModel` 의 의존성이 사라짐
* `DataBinding` 으로 인해 `ViewModel` 의 값이 변하면 `View` 에서도 바로 바뀐다.

## Command 패턴 이란?
* 메서드 호출을 캡슐화 하는것
* 메서드 호출을 캡슐화 -> 호출한 객체에서 어떤식으로 처리해야하는지는 몰라도 됨.

## Data Binding
##### 단방향 데이터 바인딩(1-way data binding)
단방향 데이터 바인딩은 처음 `Model` 이 가진 값을 `View` 에 표현하고 나중에 `Model` 이 변경되더라도 업데이트 되지 않는다.
##### 양방향 데이터 바인딩(2-way data binding)
양방향 바인딩은 모델을 `View` 에 바인딩함과 동시에 이후 `Model` 이 변경되는 경우를 감지하여 지속적으로 `View` 를 업데이트 해준다.

이렇게 되면 양방향이 좋지 않냐는 의문이 드는데 계속해서 데이터 변화를 감지한다면  
불필요한 리소스 및 성능 저하로 이어지므로 각 상황에 맞게 사용하는것이 중요하다.

### 결론
어느 패턴이 무조건 안좋다라고 보는 것보다 상황에 맞게 적절한 패턴을 쓰는것이 좋다.

### 참고문서
[http://coding-dragon.tistory.com/4](http://coding-dragon.tistory.com/4)  
[http://blog.javarouka.me/2013/06/understanding-mvc-mvp-and-mvvm.html](http://blog.javarouka.me/2013/06/understanding-mvc-mvp-and-mvvm.html)  
[https://magi82.github.io/android-mvc-mvp-mvvm/](https://magi82.github.io/android-mvc-mvp-mvvm/)  
[데이터 바인딩](https://webisfree.com/2017-01-25/angularjs-one-way-two-way-%EB%B0%94%EC%9D%B8%EB%94%A9-%EC%95%8C%EC%95%84%EB%B3%B4%EA%B8%B0)  
[커맨드 패턴](http://moonshoo.tistory.com/5)
