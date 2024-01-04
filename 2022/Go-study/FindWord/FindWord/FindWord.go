package main

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
	"strings"
)

// 해당 라인 정보
type LineInfo struct {
	lineNo int
	line   string
}

// 파일 내 라인 정보
type FindInfo struct {
	filename string
	lines    []LineInfo
}

func main() {

	// 입력 예시 : ./FidnWord brother *.txt

	if len(os.Args) < 3 {
		fmt.Println("it needs more than 2 parameters : ex. FindWord word filePattern")
		return
	}

	word := os.Args[1]
	filePatterns := os.Args[2:]
	findInfos := []FindInfo{}

	// file에서 word 해당하는 정보 찾기
	for _, filePattern := range filePatterns {
		findInfos = append(findInfos, FindWordInAllFiles(word, filePattern)...)
	}

	// 해당 정보 내용 출력
	for _, findInfo := range findInfos {
		fmt.Println(findInfo.filename)
		fmt.Println("===============")

		for _, lineInfo := range findInfo.lines {
			fmt.Println("\t", lineInfo.lineNo, "\t", lineInfo.line)
		}
		fmt.Println("===============")
		fmt.Println()
	}
}

// filePattern 갖는 파일 찾기
func GetFileList(filePattern string) ([]string, error) {
	return filepath.Glob(filePattern)
}

// 모든 파일 내에서 word 갖는 문장 정보 찾기
func FindWordInAllFiles(word, filePattern string) []FindInfo {
	// {파일 이름, 라인 정보 슬라이스} 를 담을 정보 슬라이스 생성
	findInfos := []FindInfo{}

	filelist, err := GetFileList(filePattern)

	if err != nil {
		fmt.Println("file pattern error. ", "err : ", err, "filePattern : ", filePattern)
		return findInfos
	}

	// 각 file 별로 word 찾기
	for _, filename := range filelist {
		findInfos = append(findInfos, FindWordInFile(word, filename))
	}
	return findInfos
}

// 해당 파일에서 word 있는 문장 찾기
func FindWordInFile(word, filename string) FindInfo {
	// {파일 이름, 라인 정보 슬라이스} 생성
	findInfo := FindInfo{filename, []LineInfo{}}

	// 파일 오픈
	file, err := os.Open(filename)
	// 파일 유무 에러 체크
	if err != nil {
		fmt.Println("cannot find file : ", filename)
		return findInfo
	}

	// 함수 종료 직전 파일 닫기
	defer file.Close()

	lineNo := 1

	// 스캐너 생성
	scanner := bufio.NewScanner(file)

	// 스캐너로 한 줄 씩 읽기
	for scanner.Scan() {
		line := scanner.Text()

		// strings.Contains(line, word) : line에 word 유무 확인 (bool)
		// 있으면 그 줄 번호와 그 줄 통째로 넣기
		if strings.Contains(line, word) {
			findInfo.lines = append(findInfo.lines, LineInfo{lineNo, line})
		}
		lineNo += 1
	}

	return findInfo
}
