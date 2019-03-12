## AppScript

구글은 G Suite 앱들을 사용하기 편하게 Google Apps Script 라는것을 제공하고있다. 그 중 Spreadsheet 과 gdrive 를 사용해보았다.

## 시작에 앞서
[Hugo](https://gohugo.io/) 에서 콘텐츠를 가져올 때 markdown 으로도 가져올 수 있다. 때문에, 구글 스프레드 시트에 작성되어있는 데이터를 각각의 markdown 으로 뽑아내는 것이다.

> hugo 에서는 json 으로도 콘텐츠를 가져올 수 있지만, 마크다운으로 뽑는 이유는 비 개발자가 콘텐츠를 작성해야하는 상황이기에 선택

### 기존에 시도했던 방식

1. 구글 스프레드시트에 작성된 파일을 별도의 엑셀 파일로 저장한다
2. 엑셀 파일을 내가 만든 node 프로그램에 돌린다.
3. parsing 되어 각각의 `.md` 파일들이 생성된다.

#### 문제점
여기서 문제가 몇가지 있는데 차례로 살펴보면 다음과 같다.

**1. 데이터 불일치**

별도의 엑셀파일을 저장하여 내가 만든 node 프로그램에 돌리게되면 바라보는 데이터가 한곳이 아니기에 일치하지 않을 수 있다.

**2. 비개발자가 사용하기에 어렵다**

비 개발자가 사용하기엔 무리가 있는 단계들이 존재한다. 예를들어 node 프로그램에 돌린다던지...

뭔가 새로운 방식이 필요하다.

## 새로운 방식

구글앱들은 AppScript 라는것이 존재한다. Spreadsheet 의 스크립트를 활용해 간단한 버튼으로 export 할 수 있다.

1. 데이터가 존재하는 스프레드시트에 앱 스크립트를 작성한다.
2. 앱 스크립트를 이용해 '변환하기' 버튼을 만들어 해당버튼을 클릭한다.
3. 변환되어 G Drive 에 저장된다.

비개발자가 사용하기에 어려웠던 기존방식이 앱 스크립트에 의해 UI 적으로 해결되었다. 그리고 export 된 마크다운들을 프로젝트에 넣는다. 데이터도 한곳을 바라보기에 데이터 불일치성에 대한 걱정도 한시름 놓았다.


#### 문제점

**markdown 으로 변환해 gdrive 에 넣는 속도가 너무 느렸다.**

많은 양의 데이터가 써지는데 상당히 느린 속도가 새로운 문제로 올라왔다. 때문에 한개의 JSON 파일에 데이터를 저장하기로 결정


#### 바뀐 로직

1. 데이터가 존재하는 스프레드 시트에 앱 스크립트를 작성한다.
2. 앱 스크립트를 이용해 JSON 파일을 gdrive에 저장한다.
3. 프로젝트 내에서 hugo 빌드 전에 gdrive 에 있는 JSON 파일을 가져와 콘텐츠 생성

JSON 파일을 가져와 프로젝트에서 돌리면 gdrive 에 써지는 속도보단 훨씬 빠를것으로 예상된다.


## AppScript 작성부

### 작성전 팁

* 최신 js 문법을 지원하지않기에 `let`, `const` 말고 `var` 을 사용한다. (어색)
* `console.log()` 대신 `Logger.log()` 를 이용한다. 그리고 탭의 `'보기 > 로그'` 를 눌러 확인한다.
* [AppScript API](https://developers.google.com/apps-script/reference/) 을 참고한다. (원하는 함수들이 거의 존재)

### 커스텀 메뉴 만들기

`onOpen` 메서드를 통해 스프레드시트에 들어오면 `saveAsJSON` 이라는 메서드가 등록된 `JSON 으로 저장` 버튼을 만들어준다.

```js
function onOpen() {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var markdownMenuEntires = [{ name: 'JSON 으로 저장', functionName: 'saveAsJSON' }];
  ss.addMenu('JSON으로 저장', markdownMenuEntires)
}
```

### saveAsJSON 함수

저장할 폴더를 생성한다. 만약, 존재하는경우 해당 폴더를 지우고 다시생성한다. 그리고 활성화된 스프레드 시트를 `extractExcelData()` 함수에 넣어 원하는 데이터를 뽑아낸다. 이후에 `createJSON()` 함수를 이용해 JSON 파일 생성

```js
function saveAsJSON() {
  var sheet = SpreadsheetApp.getActiveSheet();
  var folderIterator = DriveApp.getFoldersByName(FOLDER_NAME);

  // 폴더가 이미 존재하는 경우 지우고 다시 export
  if (folderIterator.hasNext()) {
    var oldFolder = folderIterator.next();
    DriveApp.removeFolder(oldFolder);
  }
  var folder = DriveApp.createFolder(FOLDER_NAME);
  var data = extractExcelData(sheet);
  createJSON(folder, data);
}
```


### extractExcelData 함수

뽑아낼 데이터의 첫번째 줄은 header 일 것이므로 header 만 따로 추출하고, 나머지는 bodys 에 넣어 return 시킨다.

```js
function extractExcelData(sheet) {
  var lastCol = sheet.getLastColumn();
  var lastRow = sheet.getLastRow();
  var headers = sheet.getRange(1, 1, 1, lastCol).getValues()[0];
  var bodys = sheet.getRange(2, 1, lastRow, lastCol).getValues();
  return {
    headers: headers,
    bodys: bodys,
  };
}
```

### createJSON 함수

MIME_TYPE 을 지정해주고, 뽑아내고싶은 json 의 `key: value` 를 `jsonDef` 에 지정해준다. 그리고 `folder.createFile()` 을 이용해 gdrive 에 저장!

> [앱 스크립트가 정해놓은 MimeType들](https://developers.google.com/apps-script/reference/base/mime-type) 중에 내가 원하는것이 없어 [MIME 타입의 전체목록 - MDN](https://developer.mozilla.org/ko/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Complete_list_of_MIME_types) 을 참고했다. `string` 으로 넣어도 될까? 해서 우선 넣어보고 `DriveApp.getFilesByType('application/json');` 을 해보니 잘 검색되어 이렇게 넣어줘도 된다는걸 알았다.

```js
function createJSON(folder, data) {
  var MIME_TYPE = 'application/json';
  var headers = data.headers;
  var bodys = data.bodys;
  var bodyLength = bodys.length - 1; // header 행을 뺏기에 - 1을 더 뺀다.
  var defaultWeight = 0;
  var container = [];

  for (var i = 0; i < bodyLength; i++) {
    var body = bodys[i];
    var jsonDef = {
      ...
    };
    container.push(jsonDef);
  }
  var json = JSON.stringify(container);
  folder.createFile(FILENAME, json, MIME_TYPE);
}
```

이렇게 하면 gdrive 에 파일이 생성된다. 만약 외부 프로젝트나 프로그램에서 사용하고 싶다면, Google API 를 이용하면된다. AppScript 를 활용해 비개발자와 개발자 사이의 협업이 좀 더 쉬워지겠다는 생각이 들었다.
