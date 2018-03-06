# [extract-text-webpack-plugin](https://github.com/webpack-contrib/extract-text-webpack-plugin)
이 플러그인은 텍스트를 파일로 추출하는 플러그인이다  
### 설치
```
$ npm install --save-dev extract-text-webpack-plugin
```
### 사용법

css파일을 별도로 뽑아보겠다

```javascript
// webpack.config.js
const ExtractTextPlugin = require('extract-text-webpack-plugin');
```
`webpack.config.js` 파일의 가장 상단에 require 해줌

```javascript
// webpack.config.js
const ExtractTextPlugin = require('extract-text-webpack-plugin');

module.exports = {
  module: {
    rules: [
      {
        test: /\.css$/,
        use: ExtractTextPlugin.extract({
          fallback: 'style-loader',
          use: 'css-loader'
        })
      }
    ]
  },
  plugins: [
    new ExtractTextPlugin({
      filename: 'common.css',
      disable: false
    })
  ]
};
```
#### `ExtractTextPlugin.extract({})` 구문


  `fallback` 프로퍼티는 해당 플러그인이 실패했을 때 대안으로 되는 로더입니다  
  `use` 프로퍼티는 `css-loader` 를 거쳐서 해당 플러그인으로 파일을 추출하겠다는 뜻이다.

#### `new ExtractTextPlugin({})` 구문
`filename` 프로퍼티는 추출될 파일의 이름을 명시한다.  
`disable` 프로퍼티는 해당 플러그인을 활성화/비활성화 이며, `Boolean`이다.

더 자세한 사항은 위의 링크를 타고 보면 된다.
