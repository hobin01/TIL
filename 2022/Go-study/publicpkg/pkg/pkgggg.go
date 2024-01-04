package pkg

import "fmt"

const (
	PI = 3.14   // 공개 상수
	pi = 3.1415 // 비공개 상수
)

// 패키지 외부 공개 : 대문자로, 비공개 : 소문자로 시작

func Public() {
	myConst := 100
	fmt.Println("myConst : ", myConst)
}

func private() {
	fmt.Println("private function")
}

type PublicStruct struct {
	Name string // 공개 필드
	age  int    // 비공개 필드
}

type PrivcateStruct struct {
	name string
	age  int
} // 비공개 구조체

func (st PublicStruct) PublicMethod() {
	st.Name = "struct name!!!!"
	st.age = 123

	fmt.Println(st.Name)
	fmt.Println(st.age)
} // 공개 메서드

func (st PublicStruct) privateMethod() {
	st.Name = "private name!!!!"
	st.age = 123456

	fmt.Println(st.Name)
	fmt.Println(st.age)
} // 비공개 메서드
