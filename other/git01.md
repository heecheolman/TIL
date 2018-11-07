# Git 기초 첫번째

## 목차
* Git의 특징
* Git 기본 사용법
* 수정하고 저장소에 저장하기
  * 수정하고 저장소에 저장하기
  * 파일의 상태 확인하기
  * 파일을 새로 추적하기
  * Modified 상태의 파일을 Stage 하기
  * 파일 무시하기
  * Staged 와 Unstaged 상태의 변경내용을 보기
  * 변경사항 커밋하기
  * Staging Area 생략하기
  * 파일을 삭제하기
  * 파일 이름 변경하기
* 마치며


---

## Git 의 특징
#### 1. 스냅샷
* Git의 데이터는 파일시스템의 스냅이며 크기가 아주 작다.
* Git은 커밋하거나 프로젝트의 상태를 저장할 때마다 파일이 존재하는 그 순간을 중요하게 여긴다.
* Git은 성능을 위해서 파일을 저장하지 않는다. 단지, 이전 상태의 파일에 대한 링크만 저장한다.


![이미지](https://git-scm.com/figures/18333fig0105-tn.png)

#### 2. 로컬실행
* Git은 네트워크의 속도에 영향을 받지않는다.
* 비행기나 기차 등에서 작업하고 네트워크에 접속하고 있지않아도 커밋할 수 있다.

#### 3. Git의 무결성
* Git은 모든 데이터를 저장하기 전에 체크섬(해시)를 구하고 그 체크섬으로 데이터를 관리
* 체크섬은 Git 에서 사용하는 가장 기본적인(Atomic) 데이터 단위이자 기본 철학.
* `SHA-1` 해시를 이용해 체크섬을 만든다.

```
SHA-1 해시는 이렇게 생겼다

24b9da6552252987aa493b52f8696cd6d3b00373
```

#### 4. Git 은 데이터를 추가할 뿐
* Git 은 뭘 하던 데이터를 추가함
* 되돌리거나 데이터를 삭제할 방법이 없다. (삭제한 파일은 삭제한 파일대로 커밋)

#### 5. 세 가지 상태
* Git은 파일을 `Committed`, `Modified`, `Staged` 상태로 관리
  * `Committed` : 데이터가 로컬 데이터베이스에 안전하게 저장됨
  * `Modified` : 수정한 파일을 아직 로컬 데이터베이스에 커밋 하지 않음
  * `Staged` : 현재 수정한 파일을 곧 커밋할 것이라고 표시한 상태 (중간단계: staging area)

* Git 디렉토리에 있는 파일들은 `Committed` 상태.

![이미지](https://git-scm.com/figures/18333fig0106-tn.png)

---

## Git 기본 사용법

### Git 저장소 만들기
Git 저장소를 만드는 방법은 두가지다.

1. 기존 프로젝트를 Git 저장소로 만들기
2. 다른 서버에 있는 저장소를 Clone 하기

#### 기존 프로젝트를 Git 저장소로 만들기
기존 프로젝트를 Git 으로 관리하고 싶을 때, 프로젝트 디렉토리로 이동한다. 그 다음,
```
$ git init
```
위의 명령어를 통해 `.git` 이라는 하위 디렉토리를 만드는데 `.git` 디렉토리 안에는 저장소에 필요한 파일들이 존재하게 된다.

```
$ git add filename
$ git commit -m "commit text"
```
`filename` 을 입력시에는 확장자명까지 입력한다. 이렇게 위의 명령어들을 통해 Git 저장소를 만들고 파일이 관리되게 하였다.

#### 다른 서버에 있는 저장소를 Clone 하기
다른 프로젝트에 참여하거나 Git 저장소를 복사하고싶을 때 `git clone` 명령어를 사용한다.

```
$ git clone url
```
위의 명령어를 통해 저장소가 복제되는데, 히스토리를 포함한 모든 데이터를 복사한다.


---
## 수정하고 저장소에 저장하기

### 수정하고 저장소에 저장하기
이 섹션의 목적은 파일의 상태들을 살펴보고, 파일을 다루는 법에 대해 배우는데 있다.  
다음 이미지는 워킹 디렉토리의 모든 파일에 대한 상태들을 나타낸 그림이다.
> 워킹디렉토리(Working Directory)   
`$ git init` 의 명령어를 이용해 Git 저장소를 갖게된 폴더

![이미지](https://git-scm.com/figures/18333fig0201-tn.png)

파일은 다음과 같이 나눌 수 있다.

* `Untracked (관리대상 아님)`

* `Tracked (관리대상)` :  이미 스냅샷에 포함돼 있던 파일
  * `Unmodified (수정하지 않음)`

  * `Modified (수정함)`

  * `Staged (커밋하면 저장소에 기록되는 상태)`

기본 로직은 다음과 같다.
```
git 저장소를 만든 상태라고 가정한다.
README.md 파일을 추가한다고 가정한다.

1. README.md 파일을 생성한다.
  1-1. git은 README.md 를 Untracked(추적하지않은 상태) 로 본다.

2. git add README.md
  2-1. git 이 README.md 파일을 관리할 수 있게 해준다.

3. README.md 파일은 Unmodified 상태가 되었다.

4. README.md 파일을 수정했다.
  4-1. README.md 는 Modified 상태가 된다.

5. README.md 를 다시 add 하여 stage 시킨다.

6. README.md 를 커밋하여 다시 Unmodified 상태가 되었다.

```

#### 파일의 상태 확인하기
```
$ git status
```
위의 명령어를 통해서 워킹디렉토리에 대한 파일들의 상태를 확인할 수 있다.

#### 파일을 새로 추적하기
```
$ git add (files)
```
위의 명령어를 통해서 git이 파일을 새로 추적하게 만들어준다. `(files)` 는 파일 또는 디렉토리 경로명을 argument 로 받는다.

#### Modified 상태의 파일을 Stage 하기
바로 전에 썻던 명령어를 통해 수정된 파일을 다시 staged 올릴 수 있다.
```
$ git add (files)
```

중요한 개념을 짚고 넘어가보자.

```
가정 : README.md 이 존재하고 이미 Tracked 상태

1. README.md 를 수정함 ----- modified 상태로 변경됨

2. git add README.md ----- staged 에 README.md 파일이 올라감 (a : README.md)

3. README.md 파일을  수정할 일이 생겨서 수정함 ---- modified (b: README.md)

4. "커밋을 해버린다면? a 가 올라갈까 b가 올라갈까?"
```
위의 경우대로 커밋을 하면 add 를 한 시점의 파일이 올라가게된다. 즉, a의 시점인 README.md 파일이 올라가게 된다.  
수정을 한 파일을 다시 staged 로 올리려면 `$ git add (files)` 를 통해 staged 상태로 올려야한다.

다음의 과정이 추가되어야한다.

```
5. git add README.md
```

위의 과정을 비로소 거친 후에야 최종 수정된 README.md 파일이 commit 되게 되는것이다.

#### 파일 무시하기
git 에 추적당하기 싫은 파일이 있을 경우는 `.gitignore` 라는 파일을 통해 추적을 못하게 만들 수 있다.

```
$ touch .gitignore
```
위의 명령어를 통해 `.gitignore` 파일을 만들 수 있고, 파일 내부에는 다음과같이 무시하고싶은 파일을 등록할 수 있다.
```
.a
```
확장자가 `.a` 인 파일들은 git 이 추적하지 못하게 하였다.

`.gitignore` 에 아래와 같은 패턴을 입력함으로써 제어할 수 있다.

```
# a comment - 이 줄은 무시한다.
# 확장자가 .a인 파일 무시
*.a
# 윗 줄에서 확장자가 .a인 파일은 무시하게 했지만 lib.a는 무시하지 않는다.
!lib.a
# 루트 디렉토리에 있는 TODO파일은 무시하고 subdir/TODO처럼 하위디렉토리에 있는 파일은 무시하지 않는다.
/TODO
# build/ 디렉토리에 있는 모든 파일은 무시한다.
build/
# `doc/notes.txt`같은 파일은 무시하고 doc/server/arch.txt같은 파일은 무시하지 않는다.
doc/*.txt
# `doc` 디렉토리 아래의 모든 .txt 파일을 무시한다.
doc/**/*.txt
```

#### Staged 와 Unstaged 상태의 변경내용을 보기
`$ git status` 명령어를 통해 상태를 알아볼 수 있었는데 `$ git diff` 라는 명령어를 쓰면 어떤 라인을 추가했고 삭제햇는지 볼 수 있다.
```
$ git diff
```

#### 변경사항 커밋하기
수정한 파일에 대하여 커밋을 한다. 여기서 주의해야할 점은 `$ git add` 명령어로 Staged 상태에 들어가지 않은 파일을 커밋되지 않는다.
```
$ git commit
```
위의 명령어를 실행하게되면 **변경사항에 대한 메세지** 를 남길수 있는데, `-m` 옵션을 통해 메세지를 인라인으로 넣을 수 있다. 예를들어,
```
$ git commit -m "something message"
```
이렇게 쓰면 편집기를 키지 않고 바로 추가 시킬 수 있다!
> 커밋할 땐 항상 신중히 해야한다. 그리고 커밋 메세지도 의미있게 붙일것!!!


#### Staging Area 생략하기
```
$ git commit -a -m "something message"
```
위의 `-a` 옵션을 통해 Tracked 상태인 파일을 자동으로 Staging Area 에 넣고 커밋한다.
#### 파일을 삭제하기
```
$ git rm
```
위의 명령으로 Tracked 상태의 파일을 삭제한다. 커밋까지 마쳐야 비로소 삭제가 된다. **유의할점은 진짜 파일도 삭제된다.**  

**만약 git 없이 그냥 파일을 삭제하면?**  
만약 그럴경우에 `$ git status` 명령어를 입력하면 `Changes not staged for commit` 그러니까 Unstaged 상태에 속해진다.

실제로 파일은 제거가 되었지만 git은 삭제된사항이 Staged 상태에 있지 않으니 여기서 커밋을 해도 삭제된 이력은 추가되지않는다.  
즉, git은 파일을 가지고 있다 이말이다.
```
1. git 명령어 없이 파일을 삭제함
  1-1. git add 를 통해 삭제한 파일에 대한 변경이력을 add 명령어를 통해 Staged 상태에 올리던가
  1-2. git rm 을 통해 Staged 상태에 올리던가
```

제거하려면 그냥 `$ git rm` 을 쓰자!

**이미 Staged 에 있는 파일인데 삭제하고싶어요!!**

  이미 Staged 상태에 올라간 파일은 `-f` 옵션을 추가해 강제로 삭제해야한다. 이유는 실수로 데이터가 삭제되는것을 막기 위한 안전장치라고 한다.  
만약 하위 폴더들도 포함된 상위폴더라면 `-r` 옵션을 추가해 하위 폴더들 까지도 삭제시킨다.

> forced (강제) -f  
recursive (순환) -r

```
Example

$ git rm -rf anyDirectory
```

**Staged 에 파일을 잘못 올렸어요!!! git에서만 삭제하려면 어떻게하죠?**
```
$ git rm --cached filename
```
`--cached` 옵션을 사용해 git 이 추적하지 않게 만든다.

#### 파일 이름 변경하기
```
$ git mv file_from file_to
```
git 은 파일이름이 변경되었다는것을 명시적으로 관리하지 않는다.  
하지만, 위의 명령어를 실행하고 `$ git status` 명령어를 입력하면 이미 git 은 파일 변경에 대한 사실을 알고있다.

그 이유는 위의 명령어는 다음을 묵어서 쓴것과 같다.

```
$ mv file_from file_to   --- (1)
$ git rm file_from       --- (2)
$ git add file_to        --- (3)

(1) --- file_from 에서 file_to 로 이름변경
(2) --- 기존의 파일을 git 이 추적하지않음 (삭제)
(3) --- 변경후의 파일이름을 add 한다.
```



## 마치며
* git 에서 File 에 대한 LifeCycle 을 이해했다!
* git 의 기본 명령어들에 대해 어떻게 동작하는지 알아보았다!
