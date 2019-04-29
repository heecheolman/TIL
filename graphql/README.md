# GraphQL

<img width="200px" src="https://graphql.org/img/logo.svg">

## 목차

* [들어서며](#들어서며)
* [GraphQL 이란?](#GraphQL-이란)
* [참고문서](#참고문서)

## 들어서며

웹을 처음에 구축할 때 가장 먼저 REST API 라는것을 사용해 API 를 구현을 했었습니다. REST API 는 정보의 자원을 표한하는데 집중했습니다.  
예를들어, 어떠한 유저의 정보를 얻어오려한다면 메서드는 먼저 `GET` 일것이며, api설계는 다음과 같을 것입니다. `/api/users/3` 이런식으로 생길 것 입니다. REST API 를 사용할 때, 클라이언트에서 서버로 요청을 보낸다고하면 자원을 선택해서 주는쪽은 서버에 맡겨집니다. REST API 의 장점도 많지만 단점이 있다면 이렇게 **자원을 '선택해서 주는 쪽'이 서버에 있게되면 클라이언트에서 필요한 자원의 형태가 다르다면 다른만큼의 api 를 따로 만들어줘야 합니다. api 가 많아지면 관리도 힘들어지고, 매번 만들기도 애매할 것입니다.**

페이스북에서 만들어 공식적으로 릴리즈 된 GraphQL 은 REST API 와는 다르다고 하는데, 구체적으로 왜 다른지 GraphQL 을 써야하는상황이 무엇인지 알고싶어 공부하려합니다.

## GraphQL 이란?

페이스북에서 공식적으로 릴리즈 된 GraphQL 은 API 에 대한 쿼리언어입니다. 아까 REST API 는 자원을 '선택해서 주는 쪽'이 서버에 있었다면 **GraphQL 은 필요한 정보들을 쿼리로 만들어(선택) 서버로 전달하면 클라이언트가 요청한 형태로 받을 수 있습니다.**

이렇게되면 장점은 형태가 다르다고 불필요하게 많은 api 가 생성될 필요도 없고 원하는 정보보다 더 많거나 더 적은 데이터를 얻을 필요도 없습니다. 딱 원하는 만큼 얻으면 된다는 것입니다.

> 가려운곳을 정확히 긁어준 느낌

## Install

```bash
npm install graphql express express-graphql
```

## 필드 정해주기
```js
const geoType = new gq.GraphQLObjectType({
  name: 'geo',
  fields: {
    lat: { type: gq.GraphQLFloat },
    lng: { type: gq.GraphQLFloat },
  }
});
```
```js
const addressType = new gq.GraphQLObjectType({
  name: 'address',
  fields: {
    street: { type: gq.GraphQLString },
    suite: { type: gq.GraphQLString },
    city: { type: gq.GraphQLString },
    zipcode: { type: gq.GraphQLString },
    geo: { type: geoType },
  }
});
```
```js
const userType = new gq.GraphQLObjectType({
  name: 'user',
  fields: {
    id: { type: gq.GraphQLInt },
    name: { type: gq.GraphQLString },
    username: { type: gq.GraphQLString },
    email: { type: gq.GraphQLString },
    address: { type: addressType },
    phone: { type: gq.GraphQLString },
    website: { type: gq.GraphQLString },
  }
});
```

## 쿼리타입 정하기

각 필드에 맞게 `graphql` 의 변수 타입을 정해줍니다.

```js
const queryType = new gq.GraphQLObjectType({
  name: 'Query',
  fields: {
    user: {
      type: userType,
      args: {
        id: { type: gq.GraphQLInt }, // user 의 인자로 id 값을 받고 그 id 값의 타입은 Int
      },
      resolve: (_, { id }, ...other) => { // 쿼리 실행시 실제로 호출되는 메서드
        const data = Object.keys(fakedata)
          .filter(ele => fakedata[ele].id === id);
        return fakedata[data];
      },
      allUser: {
        type: new gq.GraphQLList(userType),
        resolve: () => fakedata,
      }
    },
  },
});
```
 보다보면 JSON 처럼 생긴것을 볼 수 있는데 앞서 말했듯이 REST API 와는 다르게 데이터에 대해 클라이언트가 선택해서 받아볼 수 있습니다.

## 받아보기
`graphql-express` 서버를 키고 쿼리를 날릴 수 있습니다.

```
{
  user(id: 1) {
    id
    name
    username
    address {
      street
      suite
      city
      zipcode
      geo {
        lat
        lng
      }
    }
    phone
    website
  }
}
```
위와 같은 쿼리는 id 가 1인 유저에서 작성한 필드들을 가져오겠다는 쿼리입니다. 앞서 말했듯이 REST api 와는 다르게 데이터를 준비만 해놓은다면 클라이언트에서 데이터를 선택해서 가져올 수 있기때문에 엔드포인트가 적어질 수 있습니다. 특히 JSON 을 많이 다루는 쪽이라면 graphql 로 통신하는것이 더 좋을 수 있습니다.


## 참고문서

* [GraphQL Document](https://graphql.org/learn/queries/#fields)
* [GraphQL 강좌 1편: GraphQL이 무엇인가? - velopert](https://velopert.com/2318)
* [한단계씩 배워보는 graphql - Huiseoul Engineering](https://engineering.huiseoul.com/%ED%95%9C-%EB%8B%A8%EA%B3%84%EC%94%A9-%EB%B0%B0%EC%9B%8C%EB%B3%B4%EB%8A%94-graphql-421ed6215008)
