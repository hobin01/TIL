package main

import (
	"fmt"

	"publicpkg/pkg"
	"publicpkg/pkg2"
	// go 1.16 버전부터는 모듈 아래에 있는 패키지는 $GOPATH/src/ 에 있는 것이 아닌
	// 해당 모듈 아래에 만들어야 함
	// 그리고 패키지 이름이랑 해당 디렉토리 이름 다르면 못 찾음 (주의!)
	// ex) publicpkg/pkg/pkgggg.go 의 패키지 이름이 pkg 여야 함
	// 디렉토리 이름이 publicpkg/pkg 말고 다른 거면 못 찾음
	// (해당 디렉토리 이름, 패키지 이름 동일하게, go 이름은 달라도 되지만 왠만하면 같게)
	////////////////
	// 추가 패키지에 init() 함수 있으면 import와 동시에 전역값 생성, init 실행
	// init()은 return, parameter 있으면 안 됨
	///////////////
	// 근데 vscode 왜 계속 $GOPATH 에 패키지 파일 넣어라는 거지
	// 1.16부터는 path에 일일이 안 넣고 모듈로 관리한다는데....
	// 에러를 자세히 보니 모듈 쓰고 있으면 해당 모듈 디렉토리에서 editor 열어라고 하는 군....
	// publicpkg 디렉토리에서 여니 에러가 안 나는군..... shit
	// 복수 모듈 관리할 때는 루트에도 모듈 필요하다.....
)

func main() {
	fmt.Println("package test")
	fmt.Println(pkg.PI)

	pkg.Public()

	var testStruct pkg.PublicStruct
	testStruct.PublicMethod()

	fmt.Println(pkg2.A)
	fmt.Println(pkg2.B)
}
