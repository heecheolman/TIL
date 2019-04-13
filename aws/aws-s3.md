# Amazon S3

<img src="http://chittagongit.com//images/amazon-s3-icon/amazon-s3-icon-10.jpg" style="max-width: 200px">

Simple Storage Service 의 약자로 파일 저장 서비스이다. S3 에서는 'bucket(버킷)' 이라는 용어가 나오는데 일종의 저장공간을 의미한다.

> S가 3개라서 S3

### 용어
* 객체: S3에서 저장되는 기본단위로 하나의 파일
* 키: 버킷 내 객체를 저장하기 위해 사용되는 고유 식별자
* 버킷: 디렉토리와 비슷한 개념으로 버킷에 객체를 저장

### 특징

* 5TB 를 초과하지 않는 모든 종류의 데이터 저장
* 데이터를 쓴 만큼 비용 지불
* 내부적으로 3copy 를 사용하기 때문에 데이터를 잃을 가능성은 거의 없다. (99.9999999%의 내구성이라고 함)


아마존 클라우드프론트(Amazon CloudFront) 와 결합하지 않고 직접 S3 에 접근한다면 해당 리젼에서 데이터를 직접 가져오므로 데이터 접근이 느리다. S3와 CloudFront 를 결합해 많이 사용한다고 한다.

### Bucket 위치

S3의 버킷을 만들 때 애플리케이션과 같은 리젼으로 만드는것이 좋다. [다음 문서](https://blog.overops.com/aws-olypmics-speed-testing-amazon-ec2-s3-across-regions/)를 참고하면 좋다.
