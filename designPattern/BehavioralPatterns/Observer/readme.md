# 감시자 패턴 (Observer Pattern)

## 의도

객체와 객체 사이에 일대 다의 의존관계를 정의해 어떤 객체의 상태가 변할 때 해당객체에 의존적인 다른 객체들이 변화를 통지받아 갱신되늘 수 있게 한다.

## 다른이름

* 종속자(Dependent)
* 게시-구독(Publish-Subscribe): 흔히 뉴스를 구독하면 구독자는 뉴스를 받아본다는 예제가 많아 이해하기 쉬울 것이다.

## 동기

어떠한 데이터가 주어졌다.
```
a: 50%
b: 30%
c: 20%
```

해당 데이터를 바탕으로 데이터를 표현하는 방법이 N 개 존재한다. 예를들어 '표', '차트 바 그래프', '파이 그래프'에 표현을 해야한다. 차트나 표는 일종의 데이터를 '표현'하는 역할을 한다. 그리고 원본 데이터는 데이터가 무슨데이터이고 얼마나 존재하는지만 '정의'해주면된다.

그러면 데이터를 표현하는 역할을 하는 '차트'들은 원본 데이터가 변화할 때 동시에 같이 변화하면 좋을 것이다. 표현에 집중을 하는것이고 데이터는 변화에 집중을 한다. 여기서 표현을 하는 차트들을 '감시자(Observer)' 라고 하며 변화하는 데이터인 원본 데이터를 '주체(Subject)' 라고 한다.

이렇게 두 상호작용을 '게시-구독(Publish-Subscribe) 관계'라고 한다. 반응형 프로그래밍에서 많이 사용하는 방법이기도하다.(예: RxJS 등) Subject 는 데이터 변화를 **알려주고** 해당 데이터를 구독하고 있는 옵저버들은(차트들) Subject 가 알려준 변화를 **통보 받으면** 된다. 그리고 통보받은 데이터를 가지고 표현을 해주면된다.

## 활용성

* 어떤 추상 개념이 두 가지 양상을 갖고 하나가 다른 하나에 **종속적** 일 때
* 한 객체의 변화에 대해 다른 객체를 변경해야하고, 프로그래머들은 얼마나 많은 객체들이 변경되어야하는지 신경쓰고 싶지 않을 때


## 구조

![observer pattern architecture](https://paginas.fe.up.pt/~aaguiar/as/gof/hires/Pictures/observer.gif)  
출처: [paginas - GoF](https://paginas.fe.up.pt/~aaguiar/as/gof/hires/pat5gfso.htm)

## 참여자

* **Subject**: 감시자(Observer) 들을 알고 있는 주체, N개의 감시자(Observer) 객체는 주체를 감시(구독)할 수 있다. 때문에 주체는 감시자(Observer) 객체를 붙이거나 떼는 데 필요한 인터페이스를 제공해야한다.
* **Observer**: 주체를 감시하고 있으며, 주체(Subject)에 생긴 변화를 갱신하는 데 필요한 인터페이스를 정의해야  한다.
* **ConcreteSubject**: ConcreteObserver 객체에게 알려줘야 하는 상태를 저장하고, 상태가 변경될 때 Observer에게 변경을 통보한다.
* **ConcreteObserver**: ConcreteSubject 객체에 대한 '참조자'를 관리한다. 주체(Subject)의 상태와 감시자의 상태를 유지하는데(업데이트) 사용하는 갱신 인터페이스를 구현해야한다.


## 협력방법

* ConcreteSubject 는 Observer 상태와 자신의 상태가 달라지는 변경이 발생할 때마다 `notify()` 해준다.
* ConcreteSubject가 `notify()` 한 후에, ConcreteObserver는 정보를 얻어온다. 그리고 해당 정보를 이용해 Subject가 방출한 데이터를 자신의 데이터에 일치시킨다.

![concreteSubject-concreteObserver](https://paginas.fe.up.pt/~aaguiar/as/gof/hires/Pictures/obser022.gif)  
출처: [paginas - GoF](https://paginas.fe.up.pt/~aaguiar/as/gof/hires/pat5gfso.htm)

## 결과

### 1. Subject 와 Observer 는 추상적인 결합만이 존재할 뿐

Subject 는 구독하고있는 Observer 리스트들을 가지고있다. 그리고 Observer 들에게 데이터 변화가 되었다고 **알림** 을 줄 수 있다. 하지만 인터페이스를 통해 알림만 줄 뿐이지 구체적으로 어떤 Observer 들이 존재하는지 알지 않아도 된다.

### 2. 브로드캐스트(broadcast) 방식의 교류를 가능하게 한다

우리가 TV 를 볼 때, 방송국에서 방송을 전파한다. 방송국은 방송을 전파할 뿐이고 우리는 전파된 방송을 무조건 봐야하는 것이아니라 방송을 볼 것인지 아니면 다른 것을 할지 선택할 수 있다. 여기서 각자의 역할에만 충실하면 된다. 마찬가지로 Subject 는 데이터가 변화했다고 알림을 보내주고 Observer 는 해당 알림을 받지만 처리는 자체적으로 선택한다.


## 구현

`source.ts` 참고
