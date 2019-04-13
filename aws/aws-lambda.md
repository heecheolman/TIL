# AWS Lambda

![](https://blog.storagecraft.com/wp-content/uploads/2018/02/lambda-icon.jpg)

AWS 람다는 서버를 준비하고나 관리할 필요 없이 코드를 실행해주는 컴퓨팅 시스템이다. 클라우드상에서 코드를 실행하게 해주는 이벤트기반 시스템인데 코드가 실행되는 만큼만 비용을 지불하면 된다.

람다를 보다보면 서버리스(Serverless)라는 용어가 나오는데 '서버가 없다' 라는 뜻보다는 '서버를 신경쓸 필요가 없다' 라는 뜻으로 이해했다.

## FaaS(Function as a Service)

함수로 이루어진 서비스, 서버 대신 함수를 사용하는것이다. 함수는 input 에 대해 process 를 처리하고 output 을 되돌려준다. 마치 REST API 와 비슷하다. 서비스와 endpoint 들을 분리해서 마이크로서비스로 나눈다. 마이크로서비스로 나누고 실행된 함수를 기준으로 비용을 지불한다.

> 마이크로 서비스 아키텍쳐 패턴이란?  독립적인 역할을 수행하는 작은 단위의 서비스로 분리하여 설계하는 패턴. 독립적인 역할이란 '사용자관리', '주문관리' 등과 같이 기능적인 요소를 의미한다.

## 람다의 장점

* 인프라에 대한 걱정없이 코드 실행 가능
* 코드가 트리거되는 횟수를 측정해 요금이 부과됨


## 사용사례

* 실시간 파일처리
  - S3를 사용해 업로드하면, 이미지 썸네일, [리사이징](https://engineering.huiseoul.com/lambda-%ED%95%9C%EA%B0%9C%EB%A1%9C-%EB%A7%8C%EB%93%9C%EB%8A%94-on-demand-image-resizing-d48167cc1c31?fbclid=IwAR06c5s80C62jNP18lFDunfMIGpCIY8UnmZu2PGOyd2VZGhicyVYuzTzi6c) 등과 같은 작업을 할 수 있음

다른 사용사례들은 아직 와닿지 않는다.

![](https://sarc.io/images/article_aws/lambda_howto.png)

## 참고문서

* [[번역] 빠르게 배워보는 Node.js 를 이용한 서버리스(Serverless) - Jiwon Yeom](https://medium.com/@jwyeom63/%EB%B9%A0%EB%A5%B4%EA%B2%8C-%EB%B0%B0%EC%9B%8C%EB%B3%B4%EB%8A%94-node-js%EB%A5%BC-%EC%9D%B4%EC%9A%A9%ED%95%9C-%EC%84%9C%EB%B2%84%EB%A6%AC%EC%8A%A4-serverless-503ee61539d4)
* [마이크로서비스 아키텍쳐. 그것이 뭣이 중헌디? - GURUBLE BLOG](http://guruble.com/%EB%A7%88%EC%9D%B4%ED%81%AC%EB%A1%9C%EC%84%9C%EB%B9%84%EC%8A%A4microservice-%EC%95%84%ED%82%A4%ED%85%8D%EC%B2%98-%EA%B7%B8%EA%B2%83%EC%9D%B4-%EB%AD%A3%EC%9D%B4-%EC%A4%91%ED%97%8C%EB%94%94/)
