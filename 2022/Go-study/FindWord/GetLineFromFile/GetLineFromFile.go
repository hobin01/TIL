package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	//PrintFile("test.txt")
	PrintFile("hamlet.txt")
}

func PrintFile(filename string) {
	// 파일 열기
	file, err := os.Open(filename)

	if err != nil {
		fmt.Println("cannot find file : ", filename)
		return
	}

	// 함수 종료 직전에 오픈한 파일 닫기
	defer file.Close()

	// 스캐너로 한 줄 씩 읽기
	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		fmt.Println(scanner.Text())
	}

}
