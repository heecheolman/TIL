<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cf/Angular_full_color_logo.svg/250px-Angular_full_color_logo.svg.png" style="width: 100px; height: 100px;">
</div>

# Angular 폼과 유효성 검증
웹 애플리케이션에서 폼은 사용자의 입력을 받는 인터페이스 입니다. HTML 표준 입력폼을 사용해도되지만 단점과 한계(submit 누르면 페이지전환, 세밀한 유효성검사의 어려움 등)가 있습니다. 그리고 Angular 폼을 사용하여도 애플리케이션이 복잡해지면 테스트도 힘들어집니다.

여기서는 앞서 말한 폼들과는 다른 '템플릿 기반 폼'과 '리액티브 폼'에 대해 다뤄보겠습니다.

## 📝 목차
* [템플릿 기반 폼](#템플릿-기반-폼)
  * [NgForm 디렉티브](#ngform-디렉티브)
    * [novalidate](#novalidate)
    * [ngNoForm](#ngnoform)
    * [내부에서 벌어지는 일](#내부에서-벌어지는-일)
  * [NgModel 디렉티브](#ngmodel-디렉티브)
  * [NgModelGroup 디렉티브](#ngmodelgroup-디렉티브)
  * [NgModel과 양방향 바인딩](#ngmodel과-양방향-바인딩)
  * [템플릿 기반 폼 유효성 검증](#템플릿-기반-폼-유효성-검증)
* 리액티브 폼

## 템플릿 기반 폼
템플릿 기반 폼은 컴포넌트 템플릿에서 '디렉티브'를 사용하여 폼을 구성하는 방식으로 필드의 형식, 유효성 검증 규칙 모두 템플릿에서 정의합니다. 사용 범위는 비교적 간단한 폼에 사용합니다.

### NgForm 디렉티브
#### novalidate
```HTML
<form novalidate></form>
```
novalidate 어트리뷰트를 추가하면 HTML표준 폼의 유효성 검증기능을 비활성화 합니다.

#### ngNoForm
```HTML
<form ngNoForm></form>
```
폼 요소에 자동으로 적용되는 NgForm 디렉티브의 적용을 취소하려면 ngNoForm 을 추가합니다.


ngForm 디렉티브가 적용된 템플릿 기반 폼은 `submit`을 할 시 `submit` 이벤트를 인터셉트하여 폼 데이터를 서버로 전송하고 페이지를 전환하는 기본 동작을 막습니다.

즉, `submit`이벤트를 대신하여 NgForm 디렉티브가 방출하는 ngSubmit 을 사용합니다.

```HTML
<form (ngSumbit)="onNgSumbit()" novalidate></form>
```

템플릿 기반 폼에도 템플릿 참조 변수를 사용할 수 있는데 참조변수에 ngForm 을 할당하여 네이티브 DOM 이 아닌 NgForm 인스턴스를 가리키도록 합니다.
```HTML
<form #f="ngForm" (ngSubmit)="onNgSubmit(f)" novalidate></form>
```

#### 내부에서 벌어지는 일
NgForm 인스턴스는 NgForm 디렉티브가 생성하는 인스턴스로서 폼 전체를 관리합니다.
```
NgForm 인스턴스 생성
-> 자신이 적용된 폼 요소의 값 또는 유효성 검증 상태를 추적할 수 있는 기능을 제공하는 FormGroup 인스턴스 생성
-> NgForm 인스턴스의 프로퍼티로 추가
-> FormGroup 이 프로퍼티로 추가된 NgForm 인스턴스를 참조변수가 가리킴
만약 -> 폼 요소의 자식 폼 컨트롤 요소 중 NgModel 디렉티브가 적용된것이 있다면
    -> FormControl 인스턴스를 생성하고 FormGroup 인스턴스의 프로퍼티로 추가
```
즉, 폼 유효성 검사를 할 때 FormControl 인스턴스 중 하나라도 유효하지 않다면 FormGroup 상태는 invalid 상태가 됩니다.

### NgModel 디렉티브
ngModel 디렉티브를 사용하면 자신이 적용된 폼 컨트롤 요소의 값이나 유효성 검증 상태의 추적기능을 제공하는 FormControl이 생성됩니다. 그리고 템플릿 기반 폼의 기본단위입니다.

ngForm 을 가리키는 템플릿 참조변수의 `value` 프로퍼티를 통해 ngModel로 생성된 FormControl 인스턴스의 값들을 조회할 수 있습니다.
```html
<form #userForm="ngForm" (ngSubmit)="onNgSubmit(userForm)" novalidate>
  <input type="text" name="userid" placeholder="userid" ngModel>
  <input type="password" name="password" placeholder="password" ngModel>
  <button>submit</button>
</form>
```
```ts
...
onNgSubmit(userForm: NgForm) {
  console.log(userForm.value);
  // { id: 'foo', password: 'bar'}
}
```

FormControl 의 key 는 name 어트리뷰트 값이므로 **반드시 name 어트리뷰트를 지정해야합니다.**

FormControl 에도 템플릿 참조변수를 사용할 수 있습니다.
```html
<input type="text" name="userid" ngModel #userid>
<input type="text" name="userid" ngModel #userid="ngModel">
```
위와 같은 경우는 `#userid` 가 네이티브DOM 을 가리키지만 **아래와 같은 경우는 NgModel 인스턴스를 가리킵니다.**
```html
<input type="text" name="userid" ngModel #userid="ngModel">
{{ userid.value }}
{{ userid.valid }}
```
`value` 에는 값, `valid`에는 해당 폼이 유효한지의 여부를 알려줍니다.

### NgModelGroup 디렉티브
NgModelGroup 디렉티브는 NgForm 과 유사하게 FormGroup 인스턴스를 생성하고 NgModelGroup 디렉티브가 적용된 폼 그룹 요소의 자식 요소 중에서 NgModel 디렉티브가 적용된 요소를 탐색해 FormGroup 인스턴스에 추가합니다.

다시말해 NgModelGroup 으로 폼컨트롤이 그룹화 된다고 생각하면 될 것 같습니다.

```html
<form #userForm="ngForm" (ngSubmit)="onNgSubmit(userForm.value)" novalidate>
  <input type="text" name="userid" placeholder="userid" ngModel>
  <div ngModelGroup="password">
    <input type="password" name="password1" placeholder="password" ngModel>
    <input type="password" name="password2" placeholder="confirm password" ngModel>
  </div>
  <button type="submit">확인</button>
</form>
```
```ts
...
onNgSubmit(user) {
  console.log(user);
  /*
  { userid: '',
    password: {
      password1: '',
      password2: '',
    }
  }
  */

  if (user.password.password1 !== user.password.password2) {
    console.log('패스워드가 일치하지 않습니다.');
  }
}
```

### NgModel과 양방향 바인딩
**양방향 데이터 바인딩** : 뷰와 컴포넌트 클래스의 상태 변화를 상호 반영하는 것

앵귤러는 양방향 바인딩을 지원하지 않습니다. 양방향 바인딩은 프로퍼티바인딩 + 이벤트 바인딩의 축약형 표현일 뿐입니다.
```html
<input type="text" [(ngModel)]="name">
<input type="text" [ngModel]="name" (ngModelChange)="name=$event">
```
`[ngModel]`프로퍼티 바인딩은 컴포넌트 프로퍼티 `name`의 상태 변화를 받아서 업데이트시키고,  
`(ngModelChange)` 이벤트 바인딩은 상태 변화 이벤트를 방출해 `name`의 상태를 업데이트 합니다.

### 템플릿 기반 폼 유효성 검증
NgForm, NgModel, NgModelGroup 디렉티브를 폼 컨트롤에 적용하면 FormGroup 또는 FormControl 인스턴스를 생성하는데 이 둘은 유효성 검증 기능을 제공합니다.

FormGroup과 FormControl 은 [AbstractControl](https://angular.io/api/forms/AbstractControl)을 상속한 클래스입니다.

```ts
abstract class AbstractControl {
  constructor(validator: ValidatorFn, asyncValidator: AsyncValidatorFn)
  // ... 생략
  valid: boolean
  invalid: boolean
  errors: ValidationErrors | null
  pristine: boolean
  dirty: boolean
  touched: boolean
  untouched: boolean
}
```
위는 AbstractControl 추상클래스의 일부를 나타낸 것인데 추려낸 프로퍼티들은 '유효성 검증 상태 프로퍼티'입니다.  
차례로 살펴보자면 다음과 같습니다.

* **errors**: 유효성 검증에 실패한 경우, ValidationErrors 타입의 에러 객체 반환. 성공한 경우 null 반환
* **valid**: 유효성 검증에 성공한 상태일 경우 true
* **invalid**: 유효성 검증에 실패한 상태일 경우 true
* **pristine**: 값을 한 번도 입력하지 않은 상태이면 true
* **dirty**: 값을 한 번 이상 입력한 상태이면 true
* **touched**: focus in 이 한 번 이상 발생한 상태이면 true
* **untouched**: focus in 이 이 한 번도 발생하지 않은 상태이면 true

간단한 예제
```html
<input type="text"
  name="title"
  ngModel
  #title="ngModel"
  pattern="[a-zA-Z0-9]{4,10}"
  required>

<em *ngIf="title.errors?.required && title.touched">title을 입력하시오</em>
<em *ngIf="title.errors?.pattern && title.touched">title은 영문 또는 숫자로 4자리 이상 10이하로 입력</em>

<p>errors: {{ title.errors | json }}</p>
<p>invalid: {{ title.invalid }}</p>
<p>dirty: {{ title.dirty }}</p>
<p>touched: {{ title.touched }}</p>
<p>pristine: {{ title.pristine }}</p>
```

## 리액티브 폼

## 참고문서
* [Angular Essentials - 이웅모](https://book.naver.com/bookdb/book_detail.nhn?bid=13761643)
