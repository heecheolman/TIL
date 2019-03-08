# git 자주쓰는 명령어 모음

`[]`로 감싸져있는 부분은 그대로 입력하는 부분입니다.

예를들어, `git config --global user.name [값] 은 git config --global user.name heecheol` 로 대체됩니다.
## 설정관련

#### git config --list
설정목록에 대한 리스트들을 보여준다.

#### git config --global user.name [값]
전역으로 사용자의 이름을 설정합니다.

#### git config --global user.email [값]
전역으로 사용자의 이메일을 설정합니다.


## 커밋관련

#### git add [파일명]
해당 파일에 대한 변경이력을 stage 에 올립니다.

#### git add .
git 이 추적하는 수정되고 새로 생성된 모든 파일들을 stage 에 올립니다.

#### git commit
stage 에 올라간 파일들에 대한 변경이력을 남깁니다. 커밋 메세지는 vim 에디터로 작성됩니다.

#### git commit -m ["메세지"]
stage 에 올라간 파일들에 대한 변경이력을 남깁니다. 커밋 메세지는 `""`안에 넣어줍니다.

#### git commit --amend
최근 커밋을 수정합니다.

#### git cherry-pick [커밋명:해쉬값]
특정 커밋을 선택하여 합치기

#### git rebase -i HEAD~[숫자]
현재 HEAD 를 기준으로 수정하고싶은 커밋많큼 [숫자]를 적어줍니다.
> 커밋을 자주하고 squash 로 합치는것이 유용

## 브랜치 관련

#### git branch
로컬 브랜치 목록 보기

#### git branch -r
리모트의 브랜치 목록 보기

#### git branch -a
로컬 + 리모트를 합친 모든 브랜치 목록 보기

#### git branch [브랜치이름]
현재 HEAD 위치에 브랜치 생성

#### git checkout [브랜치이름]
다른 브랜치로 checkout

#### git checkout -b [브랜치이름]
현재 HEAD 위치에 새로운 브랜치를 생성하고 checkout

#### git branch [새로운 브랜치] [브랜치를 생성할 위치]
다른지점에 새로운 브랜치 생성

#### git branch -D [삭제할 브랜치명]
브랜치 삭제



## 저장소 관련

#### git init
저장소 초기화

#### git clone [저장소 URL]
저장소 복제

#### git remote add [저장소 별칭] [저장소 URL]
저장소 URL 을 저장소 별칭으로 대체
> git remote add origin 'url' 은 url 을 origin 으로 등

#### git fetch
리모트 저장소에있는 변경이력들을 가져옴

#### git pull
리모트 저장소에 있는 변경이력들을 가져오고 merge 함

#### git push [저장소 별칭] [브랜치]
해당 브랜치를 리모트 저장소에 푸시

#### git stash
현재 변경사항들을 임시 저장

#### git stash pop
임시 저장된 변경사항들을 가져와 적용시키고 임시저장된 stash 삭제

#### git stash apply
임시 저장된 변경사항들을 가져와 적용시킴. pop과는 다르게 삭제되지는 않음

#### git stash clear
stash 들 모두 삭제

### git merge [브랜치 이름]
해당 브랜치와 현재 브랜치 merge
