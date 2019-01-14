<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular HTTP 통신
대부분의 웹 애플리케이션에서 HTTP 통신은 필수입니다. HttpClient 클래스를 통해 HTTP 요청 API와 인터셉터를 제공합니다. 이 섹션에서는 http 통신에 대해서 다뤄보겠습니다.

## 📝 목차
* [HttpClient 살펴보기](#httpclient-살펴보기)
  * [HttpClientModule](#httpclientmodule)
* [HTTP 요청](#http-요청)
  * [GET](#get)
    * [Response 타입 체크](#response-타입-체크)
    * [HttpParams](#httpparams)
    * [HttpHeaders](#httpheaders)
    * [HttpResponse](#httpresponse)
    * [에러 핸들링](#에러-핸들링)
  * [POST](#post)
  * [PUT](#put)
  * [PATCH](#patch)
    * [PUT과 PATCH 차이](#put과-patch-차이)
  * [DELETE](#delete)
* [HTTP 중복 요청 방지](#http-중복-요청-방지)
* [인터셉터](#인터셉터)

## HttpClient 살펴보기
Angular 4.3 버전 이후부터는 `@angular/common/http` 패키지의 HttpClient 클래스로 사용합니다. HttpClient 클래스는 `@Injectable()` 데코레이터로 주입 가능한 클래스입니다. 그리고 HttpClient 의 메서드는 '옵저버블'을 반환합니다. 이를 통해 RxJS의 옵저버블 객체를 기반으로 작성했다는것을 알 수 있습니다.

#### HttpClientModule
HttpClient 를 사용하기 위해서는 HttpClientModule 을 임포트 해야합니다.
```ts
// app.module.ts
import { HttpClientModule } from '@angular/common/http';

@NgModule({
  ...
  imports: [
    ...
    HttpClientModule, // 추가
  ],
  ...
})
```

## HTTP 요청
### GET
GET 요청은 모든 리소스 또는 특정 리소스를 조회할 때 사용합니다. 서버의 응답은 옵저버블로 반환됩니다.
```ts
get(url: string, options: {...}): Observable<any>
```

#### Response 타입 체크
`HttpClient.get` 메서드는 기본 응답 데이터 타입을 Object 로 해석합니다. 때문에 `HttpClient.get<Type>()` 처럼 응답 데이터 타입을 알리려면 제네릭을 사용해 설정해줍니다.
```ts
http.get<Type>('something url')
  .subscribe(() => {...});
```
#### responseType
HttpClient 는 `responseType`을 설정하지 않으면 기본적으로 JSON 데이터를 반환합니다. JSON 데이터가 아닌 데이터를 요청할 때는 `responseType` 옵션을 사용합니다.

```ts
http.get('url', { responseType: 'text' })
  .subscribe((data) => { ... });
```

#### HttpParams
GET 요청은 쿼리 파라미터를 같이 전달할 수 있습니다. 쿼리는 어떤 데이터를 조회할지 조회 대상을 특정하기 위해 사용합니다.  
쿼리 파라미터를 안전하게 이스케이프 처리하기 위해 [엔코드](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/encodeURI) 해야 한다면 HttpParams 를 사용합니다. HttpParams 는 변경 불가능한(이뮤터블)한 객체를 생성하기 때문에 객체의 프로퍼티값을 직접 변경할 수 없습니다. 또한, `set` 메서드는 항상 새로운 `HttpParams`를 반환하므로 **반드시 체이닝 하여 사용합니다.**

```ts
const params = new HttpParams()
  .set('id', '1')
  .set('name', 'heecheol'); // 체이닝
```

#### HttpHeaders
Content-type, Accept, 인증 토큰 등을 HTTP 요청 헤더에 추가할 필요가 있을 시 HttpHeaders 클래스를 이용합니다.

```ts
const headers = new HttpHeaders()
  .set('Content-type', 'application/json')
  .set('Authorization', 'my-auth-token');

// 동일
const headers = new HttpHeaders({
  'Content-Type': 'application/json',
  'Authorization': 'my-auth-token',
});


// 사용법
http.get<Type>(url, { headers })
  .subscribe((data) => {...});
```

#### HttpResponse
특정 헤더 정보나 상태 코드(status code) 를 확인하려면 전체 응답을 받아야하는데 이 때 observe 옵션을 사용합니다.

```ts
http.get<Type>(url, { observe: 'respose' })
  .pipe(
    tap(res => console.log(res)),
    tap(res => console.log(res.header)),
    tap(res => console.log(res.status)),
  )
  .subscribe(data => this.data = data.body);
```

#### 에러 핸들링
HttpClient 는 에러가 발생하면 `subscribe`의 두번째 콜백함수를 호출합니다.  
HttpErrorResponse 타입의 err 파라미터는 에러에 관련된 정보들을 담고있어 핸들링하기 좋습니다.

```ts
import { throwError } from 'rxjs';

private handleError(error: HttpErrorResponse) {
  if(error.error instanceof ErrorEvent) {
    // 클라이언트 에러
  } else {
    // 백엔드 에러
  }
  // throwError 오퍼레이터는 옵저버에게 데이터 방출을 중지하고
  // 즉시 에러 노티피케이션을 방출하는 옵저버블을 생성합니다.
  return throwError();
}
```

사용예는 다음과 같습니다.
```ts
// mycomponent.component.ts
...
http.get<Type>(url)
  .pipe(
    catchError(this.handleError) // 에러핸들링 콜백함수 전달
  )
  .subscribe(...)
```

### POST
POST 요청은 서버에 데이터를 보내 **리소스를 생성할 때 사용합니다.** 그렇기 때문에 생성할 리소스(페이로드)를 보냅니다.

```ts
post(url: string, body: any | null, options: {...}): Observable<any>
```

실사용 예
```ts
// myservice.service.ts
writePost(id: number, contents: string) {
    const newPost = { id, contents };
    return this.http.post<Post>(this.url, newPost)
      .pipe(catchError(PostService.postServiceErrorHandle));
}
```
위의 예시코드를 보면 인자로 `id` 와 `contents`를 받고 생성할 리소스(페이로드)를 만들어줍니다. 그러면 `newPost`는 페이로드가 되었습니다. `http.post` 요청시 페이로드를 두번째 인자로 넣는것을 확인할 수 있고 추가적으로 에러핸들링을 넣어줬습니다.

### PUT
PUT 요청은 리소스를 업데이트(갱신) 때 사용합니다.
```ts
put(url: string, body: any | null, options: { ... })
```

실사용 예
```ts
// myservice.service.ts
editPost(id: number, contents: string) {
    const updatedPost = { id, contents };
    const url = `${ this.url }/${ id }`;
    return this.http.put<Post>(url, updatedPost)
      .pipe(catchError(PostService.postServiceErrorHandle));
}
```

### PATCH
PATCH 요청은 리소스의 일부를 업데이트할 때 사용하고 동일하게 페이로드를 같이 보냅니다.
```ts
patch(url: string, body: any | null, options: {...}): Observable<any>
```

실사용 예
```ts
// myservice.service.ts
editPost(id: number, contents: string) {
    const updatedPost = { id, contents };
    const url = `${ this.url }/${ id }`;
    return this.http.patch<Post>(url, updatedPost)
      .pipe(catchError(PostService.postServiceErrorHandle));
}
```

#### PUT과 PATCH 차이
PUT 과 PATCH 의 공통점은 리소스를 업데이트한다는데 있습니다. 차이점을 알아보면

**PUT** 은 전체 엔티티를 전달하여 업데이트하는것이고,  
**PATCH** 는 엔티티중 변경하고자하는 속성만 전달해주면 됩니다.

### DELETE
DELETE 요청은 리소스를 삭제할 때 사용합니다. 페이로드는 필요 없지만 특정 대상을 삭제하고 싶을 때는 REST API 에 첨부하여 서버에 알립니다.

```ts
delete(url: string, options: {...}): Observable<any>
```

실사용 예는 다음과 같습니다.
```ts
deletePost(id: number) {
    const url = `${ this.url }/${ id }`;
    return this.http.delete(url)
      .pipe(catchError(PostService.postServiceErrorHandle));
}
```
페이로드는 필요 없지만 특정 id값만 리소스를 삭제하고 싶을 때 `url`에 실어서 보냈습니다.

## HTTP 중복 요청 방지
HttpClient 는 옵저버블을 반환하는데 구독되기 전까지는 실행되지 않습니다. `subscribe` 메서드가 두번 호출되면(두번 구독하면) 중복 요청이 발생되게 되는데, RxJS 의 **[`shareReplay`](http://reactivex.io/documentation/operators/replay.html) 오퍼레이터** 를 통해 해결할 수 있습니다.

```ts
http.get<Type>(url)
  .pipe(
    tap(() => console.log('HTTP REQUEST')),
    shareReplay(),
  );
```
이제 구독을 여러번 하여도 HTTP 요청은 한번만 전송됩니다.

## 인터셉터
HttpClient 는 미들웨어 로직을 파이프라인에 삽입할 수 있는 인터셉터(HttpInterceptor) 를 도입했습니다. 인터셉터를 사용하면 HTTP 요청 전후에 특정 기능을 실행해야할 때 유용합니다.

HttpInterceptor 는 인터페이스로 `implements` 한 후 다음 인터페이스를 구현해야합니다.
```ts
interface HttpInterceptor {
  intercept(req: HttpRequest<any>, next: HttpHandler): Observable<HttpEvent<any>>;
}
```


```ts
// myservice.service.ts
import { HttpInterceptor } from '@angular/core';

@Injectable()
export class MyService implements HttpInterceptor {
  intercept(req: HttpRequest<any>, next: HttpHandler): Observable<HttpEvent<any>> {
    // 처리
  }
}
```
**req: HttpRequest<any>** : 첫번째 인자인 req 는 이뮤터블 객체이기 때문에 변경할 수 없습니다. 때문에 `req.clone()` 을 통해 복사하여 사용합니다.  
**next: HttpHandler** : 두번째 인자인 next 는 인터셉터를 체이닝할 때 사용하는데 다음 인터셉터가 존재하면 다음 인터셉터에게 전달하고 그렇지 않으면 최종 HttpHandler 인 HttpBackEnd가 되어 요청을 전송하고 옵저버블을 반환합니다.


인터셉터를 HTTP 요청에 적용을 하려면 모듈의 프로바이더에 `HTTP_INTERCEPTOR` 프로바이더를 추가합니다.

```ts
// app.module.ts
import { HTTP_INTERCEPTOR } from '@angular/common/http';

@NgModule({
  ...
  providers: [{
    provide: HTTP_INTERCEPTOR,
    useClass: MyInterceptor,
    multi: true,
  }]
})
```
이렇게 작성을 하면 HTTP 요청이 MyInterceptor 의 `intercept()` 를 거치게 됩니다.

> multi 속성이 true 일 경우 동일 토큰에 대하여 거쳐지는 프로바이더를 확장합니다. - [참고문서](https://blog.thoughtram.io/angular2/2015/11/23/multi-providers-in-angular-2.html)

## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
