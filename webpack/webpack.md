# Webpack
[Webpack](https://webpack.js.org/concepts/) 은 `Module Bundler` 이다.  

## Module ?
모듈은 구현 세부사항을 캡슐화하고 공개 API를 노출해 다른 코드에서 쉽게 로드하고 사용할 수 있도록 재사용 가능한 코드조각이다.
## Bundler ?
`Bundle` : 소프트웨어 및 일부 하드웨어와 함께 작동하는데 필요한 모든것을 포함하는 패키지.  
`Bundler` 란 필요한 의존성에 대해 정확히 추적해 해당하는 의존성들을 그룹핑 해주는 도구이다.

* 모듈번들러는 빌드타임에 실행되며 번들파일을 생성한다 (예: bundle.js)  
* 생성된 번들파일을 브라우저에서 로드한다.

## 웹팩(Webpack) 의 장점
* 모듈 번들러의 기능을 커스터마이징해서 사용 가능
* third-party library에 대해 모듈로 통합하는 기능 제공


## webpack config
`webpack.config.js` 파일을 통해 webpack을 설정할 수 있다.
작업하려는 프로젝트의 가장 상위 폴더에 `webpack.config.js` 파일을 생성한다.

* Entry
* Output
* Module
* Plugins

### entry
`entry` 프로퍼티는 번들링하고싶은 파일들을 선언해주는 역할이며  
`key : value` 방식으로 선언할 경우 `key`값이 파일 이름이 되고, `value` 값이 번들링하고싶은 파일이 된다.
```javascript
// webpack.config.js
module.exports = {
  entry: {
        bundle: './src/index.js'
    }
}
```

### output
`output` 프로퍼티는 번들링되고 만들어지느 파일에 대한 정보를 명시해준다  
`output.filename` 프로퍼티는 번들링된 파일의 이름을 명시해준다  
`output.path` 프로퍼티는 먼들링된 파일의 위치를 명시해준다
```javascript
module.exports = {
  // entry: './src/index.js' 라고해도 무방
  // ./ 의미 : 현재폴더
  entry: {
        bundle: './src/index.js'
    },
    output: {
      // entry에 bundle 프로퍼티를통해 이름을 명시했어도
      // filename: 'bundlebundle.js' 라고 명시하면
      // bundlebundle.js 라는 파일로 생성됨
        filename: '[name].js',
        path: path.resolve(__dirname, 'build')
        // __dirname : 현재실행중인 자바스크립트가 있는 폴더
    }
}
```

### module
`module` 프로퍼티는 프로젝트 내의 여러 유형의 모듈들을 처리할 방법을 결정  
`module.rules` : 모듈이 생성 될 때 요청과 일치하는 규칙 의 배열
`module.rules.test` : loader를 적용시킬 파일들을 정규식으로 명시  
`module.rules.loader` : 사용할 loader 명시  
>사용할 loader가 많을 경우엔 Rule.use:[ { loader }] 로 사용가능
Rule.loaders 는 Rule.use로 사용
Rule.loader: ['loader'] 처럼 배열로도 사용가능

`module.rules.exclude` : loader가 실행될 때 배제시킬 파일들을 명시  
`module.rules.query` : loader는 `query`를 통해 매개변수 전달가능

```javascript
module.exports = {
  entry: {
        bundle: './src/index.js'
    },
    output: {
        filename: '[name].js',
        path: path.resolve(__dirname, 'build')
    },
    module: {
        rules: [
            {
                test: /\.js$/,
                loader: 'babel-loader',
                query: {
                    presets: ['es2015']
                }
            },
            {
                test: /\.css$/,
                /*
                loader: ['style-loader', 'css-loader'] 동일표현

                use: [{   동일표현
                     loader: 'style-loader'
                },{
                     loader: 'css-loader'
                }]
                */
                loaders: [{ // 동일표현
                    loader: 'style-loader'
                },{
                    loader: 'css-loader'
                }]
            }
        ]
    },
}
```
로더는 여러 로더를 전달하여 연결될 수 있는데 오른쪽에서 왼쪽으로 적용된다는점이 주의사항이다. 위의 코드에서는  
첫번째로 적용되는것이 `css-loader`  
두번째로 적용되는것이 `style-loader`

> `css-loader` 로 css파일들을 읽은 뒤 `style-loader`를 통해 css파일들을 style 태그로 만들어 head 태그 안에 넣어준다.


### webpack-dev-server
임시 개발서버를 띄워 코드를 수정할 때마다 reloading 되는 툴을 제공한다.  
2.11.0 버전기준으로 한다
```
$ npm install -g webpack-dev-server@2.11.0
```
```
$ npm install --save-dev webpack-dev-server@2.11.0
```

설치가 됐다면 `webpack.config.js` 파일 내에
```javascript
module.exports = {
  {...}, // 생략
  devServer:{
          contentBase: path.join(__dirname, 'build'),
          compress: true
      }  
}
```
`contentBase` 속성에는 콘텐츠를 제공할 파일을 서버에 알려주는 역할이다  
필자는 build 폴더 내에 index.html이 존재하므로 `build` 폴더를 명시했다
`compress` 속성은 코드들을 압축해서 뿌려주는것같다. 자세한 내용은 [Webpack dev server](https://webpack.js.org/configuration/dev-server/) 참고

이후에 커맨드라인에
```
$ webpack-dev-server
```
를 입력한다면 컴파일 성공이 뜬다. 이후에 웹 브라우저의 주소에 `localhost:8080` 을 입력하면  
index.html이 보여진다.  
또한 css, javascript, html 등을 변경을하면 변경된 파일로 reloading해서 보여준다. 개발시에 상당히 편리하다.

webpack-dev-server@2.11.0?
sudo npm install --save-dev webpack@2.11.0
컨트롤 씨 누르면 dev-server 종료



## 참고문서
[http://haviyj.tistory.com/17](http://haviyj.tistory.com/17)
[https://goo.gl/jW4JaJ](https://goo.gl/jW4JaJ)  
[https://hjlog.me/post/118](https://hjlog.me/post/118)  
[https://webpack.js.org/concepts/](https://webpack.js.org/concepts/)
