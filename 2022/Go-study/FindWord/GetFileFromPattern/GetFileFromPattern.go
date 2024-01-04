package main

import (
	"fmt"
	"os"
	"path/filepath"
)

func main() {
	// 파라미터 체크
	if len(os.Args) < 3 {
		fmt.Println("it needs more than 2 parameters : ex. GetFileFromWord pattern filepattern")
		return
	}

	// 파라미터 가져오기
	pattern := os.Args[1]
	patterns := os.Args[2:]
	fmt.Println("word what to find : ", pattern)
	PrintAllFiles(patterns)
}

// filepath.Glob : pattern에 존재하는 file 이름 전부 가져옴
func GetFileList(pattern string) ([]string, error) {
	return filepath.Glob(pattern)
}

func PrintAllFiles(files []string) {
	for _, pattern := range files {
		// 파일 목록 가져오기
		filelist, err := GetFileList(pattern)

		// 경로 확인
		if err != nil {
			fmt.Println("file path error\n err : ", err, "path : ", pattern)
			return
		}

		fmt.Println("file list")
		for idx, name := range filelist {
			fmt.Println(idx, name)
		}
	}
}
