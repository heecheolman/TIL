# [css-loader](https://github.com/webpack-contrib/css-loader)
webpack에서 `.css` 파일을 읽어들이기위해 사용하는 로더

### 설치
```
$ npm install --save-dev css-loader
```

# [style-loader](https://github.com/webpack-contrib/style-loader)
`<style>` 태그를 삽입하여 CSS에 DOM을 추가

### 설치
```
$ npm install --save-dev style-loader
```

### 사용법

`style-loader` 와 `css-loader` 를 결합해서 쓰는것이 보통이다


* 번들링할 `.js` 파일의 상단에 css 파일을 `import`

```JavaScript
 import '/* 경로 */'
```
* `webpack.config.js` 파일에서 설정

```JavaScript
module.exports = {
  module: {
    rules: [
      {...}, // 생략
      {
        test: /\.css$/,
        use: ['style-loader', 'css-loader']
      }
    ]
  }
}
```
* `webpack --config webpack.config.js` 명령어를 통해 빌드

### 짚고 넘어가기
여러 loader 를 위와 같이 중복해서 쓰면 오른쪽의 loader 부터 읽게된다.  
이러한 것을 ChainingLoaders 라고 한다.  

1. Webpack은 모듈안에 의존적인 css 파일을 검색

2. 찾으면 `css-loader` 실행

3. `css-loader` 는 모든 css와 그 css 내부의 import한 다른 css 파일을 `json` 파일로 로드하고 `style-loader`에 넘겨준다

4. `style-loader` 는 `json`을 가져와서 `<style>` 태그를 추가하고 `index.html` 파일 안에 tag를 삽입한다


### 참고문서
##### import 관련
 [https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Statements/import](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Statements/import)  
##### CommonJS 관련
 [http://d2.naver.com/helloworld/12864](http://d2.naver.com/helloworld/12864)  
 ##### 헷갈리는부분
 [https://goo.gl/zSx6Hy](https://goo.gl/zSx6Hy)
