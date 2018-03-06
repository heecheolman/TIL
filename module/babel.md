# [Babel](https://babeljs.io/)

Babel 은 es6/es7 으로 작성된 코드를 es5 코드로 transpiling 하기 위한 도구이며 transpiler 이다.  
작은 모듈들로 구성되어있으며, Babel은 다양한 모듈을 담는 일종의 상자역할을 함

### 왜 쓰는가 ?
아직까지 최신 문법을 지원하지 않는 브라우저가 있기에 호환을 위해 씀
## [babel-loader](https://github.com/babel/babel-loader)
webpack이 모듈을 번들링할 때 바벨을 사용하기 위한 로더  
```
$ npm install --save-dev babel-loader
```
## [babel-preset-env](https://babeljs.io/docs/plugins/preset-env/)
`babel-preset-env` 모듈은 설정된 환경에 적합한 플러그인을 자동으로 설정해줌
```
$ npm install --save-dev babel-preset-env
```
```javascript
query: {
  presets: ["env"]
}
// or
options: {
  presets: ["env"]
}
```
> qeury 프로퍼티는 webpack1 이고 webpack2로 넘어가면서 options로 바뀌었다고 한다. *options 권장*  
또한  query나 options가 필요없는 로더는 use 사용, 필요한 로더는 loaders 사용

## [babel-polyfill](https://babeljs.io/docs/usage/polyfill/)
es6를 지원하지않는 웹브라우저를 위해 지원해주는 모듈
```
$ npm install --save-dev babel-polyfill
```

### 참고문서
[http://poiemaweb.com/es6-babel#1-babel-cli-%EC%84%A4%EC%B9%98](http://poiemaweb.com/es6-babel#1-babel-cli-%EC%84%A4%EC%B9%98)  
[https://jaeyeophan.github.io/2017/05/16/Everything-about-babel/](https://jaeyeophan.github.io/2017/05/16/Everything-about-babel/)  
[http://blog.jeonghwan.net/js/2017/05/15/webpack.html](http://blog.jeonghwan.net/js/2017/05/15/webpack.html)  
[https://babeljs.io/env/](https://babeljs.io/env/)  
[http://haviyj.tistory.com/17](http://haviyj.tistory.com/17)
