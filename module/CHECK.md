# 헷갈림 정리
헷갈릴 수 있는 개념들을 정리해 놓은 글


* [entry는 Array? Object?](#a)

* [Loaders 와 Plugin의 차이](#b)  

* [query 와 options 뭘 써야하지?](#c)

* [loaders 와 rules 중 뭘 써야하지?](#d)  

* [use 를 써야하나 loader를 써야하나?](#e)  

* [__dirname 과 . 의 차이가 무엇인가?](#f)

------
## <a name="a"> entry는 Array? Object?</a>

`entry` 프로퍼티에는 Array 를 써야하나요 Object를 써야하나요?

#### Array 를 쓰는 경우
서로 의존성 없는 여러파일을 사용한다면 Array형식으로 사용한다
```javascript
module.exports = {
  entry: ['./js/index.js', './js/foo.js'],
  output: {
    path: path.resolve(__dirname, 'build'),
    filename: 'bundle.js'
  }
}
```
build 디렉토리가 없으면 생성되며 이 디렉토리에 `bundle.js` 라는 파일이 생성된다. `bundle.js` 파일은 `index.js` 와 `foo.js`의 내용을 담고있다.

#### Object 를 쓰는 경우
Object 형식으로 작성하게 되면 `bundle` 파일이 각각 나오게 되며, 필요한 `html` 파일에 사용 가능하다
```javascript
module.exports = {
  entry: {
    bundle: './js/index.js',
    foo: './js/foo.js'
  },
  output: {
    path: path.resolve(__dirname, 'build'),
    filename: '[name].js'
  }
}
```
`filename` 에 `[name].js` 이렇게 [name] 으로 해놓으면  
output 되는 파일 이름이 `entry` 프로퍼티에서 설정한 각각의 `key` 값의 이름으로 등록이 된다
```
bundle.js
foo.js
```
--------------------------------

## <a name="b"> Loaders 와 Plugin 차이 </a>
Loaders 는 번들이 생성되는 동안이나 생성되기 전에 개별 파일 수준에서 작업이되는 것이고  
Plugin 은 번들이 생성 된 후에 작동한다

--------------------------------

## <a name="c"> query 와 options 뭘 써야하지? </a>
다음과 같은 코드가 있다
```javascript
{
  test: /\.js$/,
  loader: 'babel-loader',
  query: {
    presets: ["env"]
  }
}
```
`query` 는 이제 `options` 로 대체된다.  
하지만 `query`도 쓸 수 있다. 하지만 Webpack Doc 대로 `options` 를 쓰자

위의 코드는 다음과 같이 변경 될 수 있다
```javascript
{
  test: /\.js$/,
  loader: 'babel-loader',
  options: {
    presets: ["env"]
  }
}
```

[자세한 사항](https://webpack.js.org/configuration/module/#rule-options-rule-query)

---------------------------
## <a name="d"> loaders 와 rules 중 뭘 써야하지? </a>
`loaders` 는 이제 `rules` 로 바뀌었다. 기능이 좀 더 추가되었다.
 `loaders` 는 여전히 유효하지만 `rules` 를 추천한다
``` javascript
// 생략
module: {
  rules: [
    ... 생략
  ]
}
```
``` javascript
// 생략
module: {
  loaders: [
    ... 생략
  ]
}
```
위의 두 코드는 동일하게 작동한다

 [자세한 사항](https://webpack.js.org/guides/migrating/#what-are-options-)

------------------------------------------

## <a name="e"> use 를 써야하나 loader를 써야하나? </a>

`loader` 에 옵션을 전달하는 방법은 `query` 나 `options` 를 통해 전달할 수 있는데  
만약 이러한 옵션이 없다면 `use`,  옵션이 있다면 `loader` 를 사용하자!

다음 예를 살펴보자
```javascript
// 생략
module: {
  rules: [
    {
      test: /\.js$/,
      loader: 'babel-loader',
      options: {
        presets: ["env"]
      }
    },
    {
      test: /\.css$/,
      use: ['style-loader', 'css-loader']
    } // options 가 필요하지않으므로 use 를 써도됨
  ]
}
```
----------------------------------------
## <a name="f">__dirname 과 . 의 차이가 무엇인가?</a>
`__dirname` 은 항상 현재 실행중인 스크립트가 있는 폴더  
`.` 은 작업디렉토리

예를들어 파일구조가 다음과 같다
```
main
   /dir1
      /dir2
          foo.js
```

```javascript
//foo.js
const path = require('path');
console.log(". = %s", path.resolve("."));
console.log("__dirname = %s", path.resolve(__dirname));
```  
여기서 터미널로 작업을 해보자  
현재 디렉토리가 main 디렉토리라고 가정하자
```
터미널

$ cd dir1
$ cd dir2
$ node foo.js

----------------

설명
dir1 디렉토리로 이동 ->  
dir2 디렉토리로 이동 ->  
foo.js 실행
```

실행결과는 다음과 같다
```
./ = main/dir1/dir2
__dirname = main/dir1/dir2
```
`.` : 작업디렉토리는 dir2 이고   
`__dirname` : 현재 실행중인 스크립트가 있는 디렉토리는 dir2  


그렇다면 더 확실하게 이해해보자
다시 main 디렉토리에서 시작한다
```
터미널

$ cd dir1
$ node dir2/foo.js

----------------

설명
dir1 디렉토리로 이동
dir2 의 foo.js 실행
```
실행결과는 다음과 같다
```
./ = main/dir1
__dirname = main/dir1/dir2
```
`.` : 작업디렉토리는 dir1 이고   
`__dirname` : 현재 실행중인 스크립트가 있는 디렉토리는 dir2  

이제 이해가 되었을 것이다

[stackoverflow를 발번역함](https://stackoverflow.com/questions/8131344/what-is-the-difference-between-dirname-and-in-node-js)

----------------------------------------
### 참고문서
 [https://goo.gl/vfmqzj](https://goo.gl/vfmqzj)
