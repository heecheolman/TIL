# Amazon CloudFront

<img src="https://askvsk.com/wp-content/uploads/2018/11/logo-amazon-cloudfront.png" style="max-width: 300px;">

아마존의 클라우드프론트는 AWS 에서 제공하는 CDN(Content Delivery Network) 서비스이다. 먼저 CDN 을 짚고 넘어가자.

## CDN

*콘텐츠를 효율적으로 전달하기 위해 여러 노드를 가진 네트워크에 데이터를 저장해 제공하는 시스템. [출처: 위키백과]* 즉 CDN의 목표는 사용자가 더 빠르게 콘텐츠를 전달받을 수 있게 하는것이다.


## CloudFront

정적 및 동적 웹 콘텐츠를 사용자에게 더 빨리 배포하도록 만든 서비스이고 목적은 당연히 콘텐츠 전송속도 향상이다. 그러면 어떻게 CloudFront 는 더 빠르게 제공하는것일까?

### CloudFront 콘텐츠 제공법

1. 유저가 요청
2. DNS가 요청을 최적으로 서비스할 수 있는 CloudFront 엣지 로케이션으로 요청 라우팅
3. 엣지 로케이션에서 CloudFront는 해당 캐시에 요청된 파일이 있는지 확인
4. 만약 없다면, 파일 형식에 적절한 오리진 서버로 전달
5. 오리진 서버는 CloudFront 로 파일을 보냄
6. 오리진에서 첫번째 바이트가 도착하면 CloudFront가 파일을 사용자에게 전달하기시작. 이 때 해당 파일을 캐시에 추가

보통 S3 와 많이 결합해 사용하는 것 같다.

## 참고문서
* [S3와 CloudFront 연동하기 - 이재홍](http://pyrasis.com/book/TheArtOfAmazonWebServices/Chapter12/02)
* [CloudFront란? - taehyun-kim](https://happyer16.tistory.com/entry/CloudFront%EB%9E%80)
