기본적인 패키지 추가

1. 메인 모듈이 있는 디렉토리(GO-STUDY/usepkg)를 만들고 go 모듈 만든다

go mod init GO-STUDY/usepkg

2. usepkg 디렉토리 아래에 usepkg 패키지 내부에서 불러올 custompkg 패키지를 만든다

mkdir custompkg <br>
touch custompkg.go # windows : New-item custompkg.go

3. custompkg.go 의 패키지 이름을 custompkg 라 하자

4. 메인 패키지 파일인 usepkg.go 에 GO-STUDY/usepkg/custompkg 를 import 한다 <br>
(같은 go 모듈 아래에 있는 패키지는 해당 go 모듈 아래에 위치하도록 해야 제대로 import 됨) <br>

형식 : "main-module"/"sub-package"

5. github 외부 패키지 import : "github.com/github-package" 형식으로 import 한다 <br>
(보통 외부 패키지 쓰게 만든 것들은 해당 module 이름 위 형식)

6. go mod tidy  <br>
=> 해당 외부 패키지 필요한 것 다운로드 및 정보를 go.mod에 저장 및 go.sum 파일 생성 <br>
(직접 만들어도 될 듯)

7. 해당 import한 패키지 내부의 xxx.go 에서 구현된 함수, 전역값 등을 사용한다. 

8. main.go 작성 <br>
=> go build <br>
=> main.exe 실행 (windows) or go run main.go 로 결과 확인 등등 