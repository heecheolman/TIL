#Apollo Fetch Policy

## fetch policy

graphQL 에서 쿼리가 데이터를 가져올 때 `cache` 에서 가져올 지 `API` 에서 가져올 지 정하는 정책이다. 데이터를 받아보는 상황에 따라 정책을 잘 정해줘야 의도된 데이터를 받아올 수 있고 때로는 더 빠르게 받아볼 수 있다.

### cache-first

Apollo 에서 특별히 정책을 정한것이 없다면 기본 값인 `cache-first` 로 정해진다.



## 참고문서

* [Understanding Apollo Fetch Policies - Galen Corey](https://medium.com/@galen.corey/understanding-apollo-fetch-policies-705b5ad71980)
