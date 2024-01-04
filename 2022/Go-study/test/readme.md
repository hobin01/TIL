go lang 빌드 시 주의 점



프로젝트에 필요한 모듈이 필요하다

(go 파일마다 필요한 것이 아닌 프로젝트 별로 필요)

=> cd <모듈 만들 위치>

=> go mod init <모듈 이름>

=> cd <go 파일 위치>

=> go build

=> exe 실행



모듈 안 만들거나 build 안 하고 go run test.go 해도 해당 go 파일 실행은 가능 (파이썬처럼) 

