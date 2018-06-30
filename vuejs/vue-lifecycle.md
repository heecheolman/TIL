# Vue.js 라이프사이클 이해하기

Vue.js 의 라이프사이클은 크게 4가지로 나뉜다.

* Creation
* Mounting
* Updating
* Destruction

![이미지](https://kr.vuejs.org/images/lifecycle.png)

위의 그림은 Vue.js 의 라이프사이클 다이어그램이다.  
빨간색폰트가 컴포넌트에서 사용할 수 있는 함수들이다.

## Creation : 컴포넌트 초기화
컴포넌트들을 초기화하는 단계이며 서버렌더링에서 지원되는 단계이다.  
클라이언트나 서버 렌더 단에서 처리해야 일이 있으면 이 단계에서 진행한다.

아직 Component가 DOM 에 추가되기 전이므로 DOM에 접근할 수 없다.

#### new Vue()
Vue Instance 생성
#### Init(Events & Lifecycle)
Event 와 Lifecycle 초기화
#### *beforeCreate*
가장 처음으로 사용할 수 있는 함수
```javascript
export default {
  beforeCreate() {
    // data와 events가 세팅되지 않아 사용할 수 없음
  }
  // not es6
  beforeCreate: function(){

  }
}
```
#### Init(injections & reactivity)
주입하고 반응

#### *created*
Data, Events 가 주입되어 반응됨. Template 과 Virtual-DOM 은 아직 mount 및 rendering 되지 않은 상태
```javascript
export default {
  created() {

  }
  // not es6
  created: function() {

  }
}
```
----
## 렌더링
#### Has "el" option?
new Vue 작성시 instance 안에 el option으로 아이디나 클래스를 통해 element 를 가져왔으면 template이 존재하는지 검사.  
없다면, `vm.mount(el)` 을 통해 mount 시킴

> [vm.$mount([elementOrSelector])](https://kr.vuejs.org/v2/api/index.html#vm-mount)

#### Has "template" option?
template option 이 있으면 `render` 함수 내에 템플릿을 컴파일 :  [Vue.compile(template)](https://kr.vuejs.org/v2/api/index.html#Vue-compile)  
없다면, el 의 outerHTML 에 컴파일.

> [렌더 함수](https://kr.vuejs.org/v2/guide/render-function.html)

----

## Mounting : DOM 삽입
렌더링 직전에 Component 에 직접 접근 가능.  
**하지만 Component 초기에 세팅되어야 할 데이터는 created에서 처리하는것이 좋음**  
서버 사이드 렌더링시 호출되지 않음.

#### *beforeMount*
렌더링 전에 최초 1회 실행
```javascript
export default {
  beforeMount() {

  }
  // not es6
  beforeMount: function() {

  }
}
```

#### Create vm.$el and replace "el" with it
`vm.$el` 을 아까 컴파일한 대상으로 만들고, el을 교체.

#### *mounted*
렌더링 후 실행되는 함수.  
Component, Template, 렌더링된 DOM 에 접근가능.  
모든 Component 의 마운트된 상태를 보장하진 않음.  
`vm.$nextTick` 을 사용해 전체가 렌더링된 상태 보장 가능.
```javascript
export default {
  mounted() {
    this.$nextTick(function() {
      // 전체가 렌더링된 상태 보장
    })  
  }
}
```
>[vm.$nextTick([callback])](https://kr.vuejs.org/v2/api/index.html#vm-nextTick)

## Updating : Diff 및 재 렌더링
Component 에서 사용되는 반응형 속성들이 변경되거나 어떤 이유로 재 렌더링이 발생되면 실행.  
서버사이드 렌더링에서 호출되지 않음.

#### *beforeUpdate*
Component 의 데이터가 변하여 업데이트 사이클이 시작될때 실행 됨.  
바로 전의 데이터를 얻을 수 있으므로 많은 변경이 가능하나, 여기서의 변경은 적용되지않음.  
```javascript
export default {
  beforeUpdate() {
    this.$nextTick(function() {
      // 전체가 렌더링 된 상태 보장
    })
  }
}
```

#### *updated*
재 렌더링 후 실행되는 단계.  
DOM이 업데이트 완료된 이후 이므로 돔 종속적 연산 가능.  
`mounted` 와 마찬가지로 `vm.$nextTick` 을 이용해 렌더링 확정을 걸 수 있음.
```javascript
export default {
  updated() {
    this.$nextTick(function() {
      // 전체가 렌더링 된 상태 보장
    })
  }
}
```
## Destruction : 해체
서버사이드 렌더링시 호출되지 않음.
#### beforeDestroy
뷰 인스턴스 제거 직전에 호출됨.   
reactive subscription을 제거하고자 한다면 이 훅에 담으면 좋다.  

#### destroyed
이 훅은 해체 된 후에 호출됨.  
Vue 인스턴스의 모든 디렉티브가 바인딩 해제되고 모든 이벤트 리스너가 제거 및 모든 하위 vue 인스턴스도 삭제된다.
## 참고문서
[생명 주기 (Life Cycle) - Vallista](https://github.com/Vallista/TIL/blob/master/vuejs/life-cycle.md)  
[Vue.js 2.0 라이프사이클 이해하기 - Jeong Woo Ahn](https://medium.com/witinweb/vue-js-%EB%9D%BC%EC%9D%B4%ED%94%84%EC%82%AC%EC%9D%B4%ED%81%B4-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0-7780cdd97dd4)  
[Understanding Vue.js Lifecycle Hooks - Joshua Bemenderfer ](https://alligator.io/vuejs/component-lifecycle/)  
[Vue.js 공식문서 : 옵션/라이프사이클 훅](https://kr.vuejs.org/v2/api/index.html#%EC%98%B5%EC%85%98-%EB%9D%BC%EC%9D%B4%ED%94%84%EC%82%AC%EC%9D%B4%ED%81%B4-%ED%9B%85)
