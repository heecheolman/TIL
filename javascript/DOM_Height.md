# DOM Height

## [DOM Element](https://www.w3schools.com/jsref/dom_obj_all.asp)

### [clientHeight](https://www.w3schools.com/jsref/prop_element_clientheight.asp)
```javascript
element.clientHeight
```
요소의 보여지는(viewable) 높이의 픽셀을 return
padding 포함
border, scrollbar, margin 미포함

### [offsetHeight](https://www.w3schools.com/jsref/prop_element_offsetheight.asp)
```javascript
element.offsetHeight
```
요소의 보여지는(viewable) 높이의 픽셀을 return
padding, border, scrollbar 포함
margin 미포함

### [scrollHeight](https://www.w3schools.com/jsref/prop_element_scrollheight.asp)
```javascript
element.scrollHeight
```
요소의 전체높이를 픽셀단위로 return
padding 포함
border, scrollbar, margin 미포함

### [scrollTop](https://www.w3schools.com/jsref/prop_element_scrolltop.asp)
```javascript
element.scrollTop
```
요소의 내용을 세로로 스크롤하는 픽셀 수 return
또는, 설정

## [DOM Window](https://www.w3schools.com/jsref/obj_window.asp)

## [innerHeight](https://www.w3schools.com/jsref/prop_win_innerheight.asp)
```javascript
window.innerHeight
```
window content 내부 영역의 height 값 return
```javascript
// cross-browser solution
let h = window.innerHeight
|| document.documentElement.clientHeight
|| document.body.clientHeight;
```
## [pageYOffset](https://www.w3schools.com/jsref/prop_win_pagexoffset.asp)
```javascript
window.pageYOffset
```
window 의 위쪽 모서리에서 세로로 스크롤된 픽셀을 return

```javascript
// cross-browser solution
let h = (window.pageYOffset !== undefined) ? window.pageYOffset : (document.documentElement || document.body.parentNode || document.body).scrollTop;
```
## [scrollY](https://www.w3schools.com/jsref/obj_window.asp)
```javascript
window.scrollY;
```
window.pageYOffset 의 별칭
