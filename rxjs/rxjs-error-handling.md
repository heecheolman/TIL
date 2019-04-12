# Error Handling

에러 핸들링을 사용해 에러 발생 시 에러를 정상적으로 처리해주는 연산자들

## 목록
* [catchError](#catcherror) ⭐️
* [retry][#retry]
* [retryWhen](#retryWhen)

## catchError ⭐️

옵저버블의 에러를 잡아 처리해주는 연산자입니다.

```ts
// 에러 방출
const source = Rx.Observable.throw('This is an error!');
// catch 로 에러 잡기, 여기서는 of 연산자로 메세지를 던
const example = source.catch(val => Rx.Observable.of(`I caught: ${val}`));
//output: 'I caught: This is an error'
const subscribe = example.subscribe(val => console.log(val));
```


## retry

## retryWhen
