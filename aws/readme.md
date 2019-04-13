# AWS (아마존 웹 서비스)

aws 는 아마존 웹 서비스(Amazon Web Service) 의 줄임말이다. 아마존은 클라우드 서비스를 제공하는데 그 중 클라우드 컴퓨팅이 있다. 클라우드 컴퓨팅에 대한 개념을 알아보고 aws 에서 사용되는 제품군들이 어떤 역할을 하는지 알아보고 싶어 정리한다.

## 클라우드 컴퓨팅

클라우드 컴퓨팅은 물리적인 컴퓨팅 리소스를 가상의 컴퓨터, 데이터베이스 스토리지, 애플리케이션 및 기타 IT 리소스들을 인터넷을 통해 제공하고 사용한 만큼 지불하는 방식이다.


### 장점

컴퓨팅 리소스가 어떻게 사용될지 얼마나 사용될 지 모르는 상태에서 서버와 데이터센터에 대규모 투자를 하게 되면 낭비이다. 클라우드 컴퓨티을 통해 컴퓨팅 리소스를 사용할 때만, 사용한 만큼의 리소스에 대해서만 비용을 지불한다.

이렇다는 뜻은 용량이 부족하다면 즉시 클라우드 컴퓨팅의 용량을 늘리면 돼서 크기가 정해져있는 실물 컴퓨터에서의 유연성과는 차별된다.

데이터센터의 운영 및 유지보수를 할 때 드는 비용을 절감할 수 있다. aws 에서 어느정도 관리를 해준다.

### 클라우드 컴퓨팅 유형

![](https://lhy.kr/images/django-eb/cloud.png)  
출처: [클라우드 서비스 모델의 종류-Ihy's blog](https://lhy.kr/cloud-model)

#### IaaS(Infrastructure as a Service) 서비스로서의 인프라

서비스로서의 인프라는 가상 서버, 스토리지, 가상 네트워크 등을 리소스 형태로 제공한다.

#### PaaS(Platform as a Service) 서비스로서의 플랫폼

서비스로서의 플랫폼은 응용프로그램을 개발할 때 필요한 플랫폼을 제공해주는데 개발자는 미들웨어를 설치하지 않고도 미들웨어에서 제공하는 API 를 사용해 소프트웨어를 개발할 수 있다.

#### SaaS(Software as a Service) 서비스로서의 소프트웨어

완전한 제품을 고객에게 제공한다. 해당 소프트웨어를 그저 사용하기만 하면 된다. 즉, 어떻게 유지관리되는지에 대해 고민할 필요가 없다.


## 알아볼 AWS 제품

* [EC2](https://github.com/heecheolman/TIL/blob/master/aws/aws-ec2.md)
* [S3](https://github.com/heecheolman/TIL/blob/master/aws/aws-s3.md)
* [RDS](https://github.com/heecheolman/TIL/blob/master/aws/aws-rds.md)
* [CloudFront](https://github.com/heecheolman/TIL/blob/master/aws/aws-cloudfront.md)
* [Lambda](https://github.com/heecheolman/TIL/blob/master/aws/aws-lambda.md)

## 참고문서

* [클라우드 컴퓨팅이란? - AWS](https://aws.amazon.com/ko/what-is-cloud-computing/)
