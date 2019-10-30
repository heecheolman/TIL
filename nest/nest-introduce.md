# NestJS
NestJS 는 Node.js 를 이용한 서버 프레임워크이다. Node.js 기반 서버 프레임워크중에서 Express 를 많이 썼을텐데 NestJS 는 Express 에 Angular 구조를 입힌 형태이며 당연히 타입스크립트를 지원한다. 

장점으로는 Front가 Angular 로 이루어져 있다면 Back 과 Front 가 동일한 형태를 갖는 프레임워크로 통일되어 생산성이 높아진다.

## Controller

컨트롤러는 클라이언트의 요청을 받아 응답해주는 핸들러이다. 실질적인 처리 로직은 서비스에서 담당한다.

![](https://docs.nestjs.com/assets/Controllers_1.png)

### Routing

데코레이터 `@Controller()` 를 이용해 생성한다. 데코레이터 안에 라우팅 경로가 될 값을 넣어주면 된다.
```ts
    @Controller()
    export class SomeController {
    	/* 컨트롤러들 */
    }
    
    
    @Controller('users')
    export class UserController {
    	@Get()
    	allUsers() {
    	 //	...
    	}
    }
```

Express 에서는 `users` 의 하위 경로들을 작성하려 하면 동일한 코드가 반복되었다. `users` 에 맞는 하위 라우팅들은 내부 메서드로 작성하면 된다.

### Request Object

HTTP 요청 객체를 얻고싶으면 `@Req` 데코레이터를 통해 접근할 수 있다.

```ts
    @Controller()
    export class SomeController {
    	@Get()
    	someContoller(@Req request: Request) {
    		// ...
    	}
    }
```

사용가능한 데코레이터들은 다음과 같다.

- `@Req` = `@Request`
- `@Res` = `@Response`
- `@Next`
- `@Session`
- `@Param(key?: string)`
- `@Body(key?: string)`
- `@Query(key?: string)`
- `@Header(name?: string)`

### WildCard Routing

패턴 기반 경로를 지원한다. 패턴은 정규표현식을 따른다.

```ts
    // use1s
    // use2s
    // users
    // ...
    @Get('use*s')
    myContoller() {
    	// ...
    }
```

### Route Parameter

파라미터를 얻고 싶다면 `@Param()` 데코레이터를 이용한다.

```ts
    @Get(':id')
    getUser(@Param() params) {
    	//	params.id	
    }
    ////////////////
    @Get(':id')
    getUser(@Param('id') id) {
    	// id값 바로 접근
    }
```

### POST

http post 방식을 사용한다면 페이로드를 `@Body()` 의 데코레이터를 이용해 body 에 접근가능하다.

## CURL 테스트

### GET
```
    curl http://localhost:3000
    curl http://localhost:3000/users
    curl http://localhost:3000/users/0
```

### POST

```
    curl -d '{"name":"heecheol","age":"25"}' http://localhost:3000
```
