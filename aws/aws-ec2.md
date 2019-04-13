# Amazon EC2

<img src="https://miro.medium.com/max/836/1*7zbh4xoxgD8UneyVo65UOg.jpeg" style="max-width: 300px;">

Amazon Elastic Compute Cloud 의 약자이다. 아마존 웹서비스에서 가장 먼저 생성되었으며 주요 서비스 중 하나다. 더 간단히, 독립된 컴퓨터 한 대를 통채로 주는 서비스이다.

> Amazon 빼고, E 그리고 C가 2개라 EC2

## 인스턴스(Instance)

아마존에서 독립된 가상의 컴퓨터를 인스턴스라고 부른다. EC2 인스턴스는 아마존 머신 이미지(AMI) 로 부팅해 인스턴스에서 원하는 소프트웨어를 포함해 구성할 수 있게 하는 웹 서비스를 제공한다.

![AMI 선택 화면](https://user-images.githubusercontent.com/35059687/56074927-06904680-5df5-11e9-94b6-e39f58f4da35.png)

가상 컴퓨터는 컴퓨터의 리소스를 선택하고 늘릴 수 있다고 했다. 사용한만큼 지불하니말이다. 여기에 AutoScaling 개념이 나온다.

## AutoScaling

EC2 인스턴스에 트래픽이 갑자기 늘어날 경우가 있다. 이럴 땐 EC2 가 유연하게 리소스의 용량을 늘려 버틸 수 있게 해줘야하는데 이것을 가능하게 하는것이 AutoScaling 이다.

* EC2 인스턴스의 규모를 자동으로 확대/축소
* 처리량의 증가에 빠르게 대응가능
* 미리 만들어진 AMI를 이용해 인스턴스를 자동 생성


### AutoScaling 타입

CPU의 점유율 즉, 부하에 따라 자동으로 규모를 변경하거나, 정해놓은 시간에 따라 변경 가능하게 설정이 가능하다. 오토스케일링이 확장하는 방법에는 크게 두가지가 있다.

1. Vertical Scaling (수직 확장)
2. Horizontal Scaling (수평 확장)

![scaleup과 scaleout](https://www.devteam.space/wp-content/uploads/2018/04/scale-ut.png)

#### Vertical Scaling - 수직확장

성능이 좋고 더 좋은 서버가 기존의 서버를 대체하는것으로 스케일-업(Scale-up) 이라고 부른다. 즉, 기존의 서버의 사이즈를 늘리는것이다.

#### Horizontal Scaling - 수평확장

기존 서버 옆에 추가 서버를 배치하는것을 말하는 것으로 스케일-아웃(Scale-out) 이라고 부른다.


#### 어떤것을 선택?

기본적인 스케일-업, 스케일-아웃 의 개념을 알고 선택하는것이 좋을듯 하여 정리한다.

||스케일-업|스케일-아웃|
|:---:|:---:|:--:|
|확장성   |기존 서버의 하드웨어 장비의 성능을 높이는것 | 기존 서버에서 부담되던 일을 여러 장비에 나누어 처리하는것  |
|서버 비용   | 성능 증가에 따른 비용 증가폭이 높다  | 비교적 저렴한 서버를 사용해 부담이 상대적으로 적다  |
|운영 비용   | 큰 변화가 없다.  |  대수가 늘어나면서 운영비용 및 편의성이 떨어진다 |
|장애   | 한대로 운영되므로 장애 발생 시 장애 영향도가 크다  | 읽기/쓰기 가 여러대에 분산되어 있어 장애시 전체 장애 가능성이 적다  |


### 로드밸런싱 (Load Balancing)
한글로는 부하 분산으로 말 그대로 **부하를 분산시키는 작업** 이다. 스케일-아웃 시 서버가 여러대 있는데 부하가 걸릴 시 여러대의 서버로 나누어주는 역할을 하는것이 **로드 밸런서(Load Balancer)** 이다.

![aws 웹서비스 다이어그램](https://www.appliedtrust.com/sites/default/files/blog/aws-load-balancing.jpg)

## 참고문서
* [EC2 모니터링, 오토스케일링, 일래스틱 로드 밸런싱](https://ora-sysdba.tistory.com/entry/AWS-EC2-%EB%AA%A8%EB%8B%88%ED%84%B0%EB%A7%81-%EC%98%A4%ED%86%A0-%EC%8A%A4%EC%BC%80%EC%9D%BC%EB%A7%81-%EC%8A%A4%ED%8B%B1-%EB%A1%9C%EB%93%9C-%EB%B0%B8%EB%9F%B0%EC%8B%B1)
* [로드 밸런서 - Nesoy Blog](https://nesoy.github.io/articles/2018-06/Load-Balancer)
