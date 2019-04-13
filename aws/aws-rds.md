# Amazon RDS

<img src="https://cdn2.iconfinder.com/data/icons/amazon-aws-stencils/100/Database_copy_Amazon_RDS-512.png" style="max-width: 300px;">

아마존의 RDS 는 Amazon Relational Database Service 의 약자로 아마존 웹서비스가 서비스하는 분산 관계형 데이터베이스이다. MySQL, Oracle, SQL Server 전용 서비스.


## 특징

* 다중 AZ 복제: 다중 가용성 존 복제로 인스턴스에 장애가 발생했을 시 다른 데이터센터에 있는 데이터베이스 서버를 올려줌
* 읽기 복제(Read Replica): 트래픽이 많이 발생될 때 스케일아웃 하고, 하나의 master 서버에서는 쓰기만 하고 slave 서버들에서는 읽기로 부하를 분산 - 아마존에서 서비스신청시 자동으로 해준다.
* 백업 자동화: 데이터를 정기적으로 저장해 백업을 해줌
* DB 스냅샷: 데이터베이스 상태를 그대로 스냅샷으로 이미지화 시켜 다른 데이터베이스 인스턴스를 만들 때 사용 가능, 일종의 백업
* 프로비저닝된 IOPS: RDS 에 인스턴스를 만들 때 그 인스턴스가 얼마나 빠른속도로 처리해야하는지 지정해줄 수 있음. 빠를수록 비용이 발생 (Input Output Per Second)




## 참고 문서
* [RDS - 생활코딩](https://opentutorials.org/course/608/3007)
