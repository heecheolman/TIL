# [vuejs-templates](https://github.com/vuejs-templates)
## Boilerplate 란?
boilerplate 는 반복되며 자주 쓰이는 것들에 대해 미리 개발환경설정을 구성해놓은 일종의 템플릿 개념이다.

front-end 개발을 하다보면 `babel`, `webpack` 등 많이 쓰이는 모듈들 또는 빌드 설정들, 폴더구조들을 반복적으로 설정하게되는데 이를 미리 만들어 놓는것이다.

이렇게 자동화를 해놓으면 갖다 쓰기만 하면돼서 개발환경구축에 시간과 비용을 단축시킬 수 있다.

```
$vue list
```
해당 명령어를 통해 공식적인 뷰 템플릿의 리스트들을 확인할 수 있다.

## vuejs-templates 종류

* ### [vue-webpack-boilerplate](https://github.com/vuejs-templates/webpack)
webpack + vue-loader 조합으로 hot-reload, lint-on-save, unit testing & css extraction 지원  
>*해당 보일러플레이트는 hot-reload, router, unit test, linting 등을 지원해  큰 프로젝트를 진행할 시에 적합하다.*

* ### [webpack-simple](https://github.com/vuejs-templates/webpack-simple)
빠르게 만들 수 있는 프로토타입, webpack + vue-loader 조합  
>*해당 보일러플레이트는 빠른 프로토타입을 만들고싶은경우 사용된다*


* ### [vue-browserify-boilerplate](https://github.com/vuejs-templates/browserify)
browserify + vueify 조합으로 hot-reload, linting & unit testing 지원  
#### [browserify란?](https://github.com/browserify/browserify#usage)
CommonJS 모듈을 위한 모듈번들러.
#### [vueify란?](https://github.com/vuejs/vueify)
browserify 변환을 위한 하나의 Vue 컴포넌트  
>*해당 보일러플레이트 hot-reload, router, unit test, linting 등을 지원해 큰 프로젝트를 진행할 시에 적합하다*

* ### [browserify-simple](https://github.com/vuejs-templates/browserify-simple)
빠르게 만들 수 있는 프로토타입, browserify + vueify 조합  
>*해당 보일러플레이트는 빠른 프로토타입을 만들고싶은경우 사용된다*

* ### [vue-pwa-boilerplate](https://github.com/vuejs-templates/pwa)
vue-webpack-boilerpate 기반 PWA 를 추가한 템플릿
#### [PWA란?](https://developers.google.com/web/progressive-web-apps/)
PWA(Progressive Web App) 이란 웹 사이트와 모바일 앱의 장점을 취하는 앱 생명주기 모델을 가지는 웹 어플리케이션.  
즉, 모바일 웹이지만 앱처럼 사용하는듯한 사용자 경험이다.
> *해당 보일러플레이트는 PWA 를 만들기 위해 사용*

* ### [vue-simple-boilerplate](https://github.com/vuejs-templates/simple)
Vue 를 알고싶은 초심자들을 위한 템플릿, 하나의 html 파일만 존재하 Vue 에대해 간단히 체험할 수 있다.
> *해당 보일러플레이트는 초심자들에게 체험하게끔 만든 템플릿*


## 참고문서
[자바스크립트 모듈, 모듈 포맷, 모듈 로더와 모듈 번들러에 대한 10분 입문서](https://github.com/codepink/codepink.github.com/wiki/%EC%9E%90%EB%B0%94%EC%8A%A4%ED%81%AC%EB%A6%BD%ED%8A%B8-%EB%AA%A8%EB%93%88,-%EB%AA%A8%EB%93%88-%ED%8F%AC%EB%A7%B7,-%EB%AA%A8%EB%93%88-%EB%A1%9C%EB%8D%94%EC%99%80-%EB%AA%A8%EB%93%88-%EB%B2%88%EB%93%A4%EB%9F%AC%EC%97%90-%EB%8C%80%ED%95%9C-10%EB%B6%84-%EC%9E%85%EB%AC%B8%EC%84%9C)  
[Vue-CLI 로 Vue.js 시작하기 (browserify / webpack) - 스키머(schemr)](https://medium.com/witinweb/vue-cli-%EB%A1%9C-vue-js-%EC%8B%9C%EC%9E%91%ED%95%98%EA%B8%B0-browserify-webpack-22582202cd52)  
[새로운 웹의 미래, 프로그레시브 웹 앱이란?](http://jhleed.tistory.com/76)
