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

	// goroutine 써서 여러 파일 동시 처리 + 서브디렉토리에 있는 거까지 탐색
	// 입력 예시 : ./FidnWordWithSubDir brother *.txt

	if len(os.Args) < 3 {
		fmt.Println("it needs more than 2 parameters : ex. FindWordWithSubDir word filePattern")
		return
	}

	word := os.Args[1]
	filePattern := os.Args[2]

	cnt, ch := FindWordInAllFiles(word, filePattern)
	recvCnt := 0 // 파일 개수 확인용

	// 채널에 있는 정보들 출력 (각 파일로 부터 채널에 정보 넣음)
	for findInfo := range ch {
		fmt.Println(findInfo.filename)
		fmt.Println("===============")

		for _, lineInfo := range findInfo.lines {
			fmt.Println("\t", lineInfo.lineNo, "\t", lineInfo.line)
		}
		fmt.Println("===============")
		fmt.Println()

		recvCnt++

		if recvCnt == cnt {
			break
		}
	}
}

// filePattern 갖는 파일 찾기 (하위 폴더까지 모두 다)
func GetFileList(filePattern string) ([]string, error) {
	filelist := []string{}

	// filePattern과 일치하는 파일 : 현재 폴더와 하위 폴더 검색
	// filepath.Walk : "." : 현재 폴더, 첫 번째 파라미터 = 검색 루트
	err := filepath.Walk(".", func(path string, info os.FileInfo, err error) error {
		// 디렉토리 아닌 파일 (검색 대상)
		if !info.IsDir() {
			matched, _ := filepath.Match(filePattern, info.Name())
			if matched {
				filelist = append(filelist, path)
			}
		}
		return nil
	})

	if err != nil {
		return []string{}, err
	}
	return filelist, nil
}

// 모든 파일 내에서 word 갖는 문장 정보 찾기
func FindWordInAllFiles(word, filePattern string) (int, chan FindInfo) {
	// 파일 정보 가져오기
	filelist, err := GetFileList(filePattern)

	if err != nil {
		fmt.Println("cannot find file. err : ", err)
		return 0, nil
	}

	// 정보를 담을 채널 생성
	ch := make(chan FindInfo)
	cnt := len(filelist)
	// 고루틴으로 파일 정보 가져오기
	for _, filename := range filelist {
		go FindWordInFile(word, filename, ch)
	}
	return cnt, ch
}

// 해당 파일에서 word 있는 문장 찾기
func FindWordInFile(word, filename string, ch chan FindInfo) {
	findInfo := FindInfo{filename, []LineInfo{}}

	// 파일 오픈
	file, err := os.Open(filename)

	if err != nil {
		fmt.Println("cannot find file : ", filename)
		ch <- findInfo
		return
	}

	// 함수 종료 직전 파일 닫기
	defer file.Close()

	lineNo := 1

	// 스캐너로 파일 한 줄 씩 읽기
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		// 해당 줄에 word 포함 여부 확인
		if strings.Contains(line, word) {
			findInfo.lines = append(findInfo.lines, LineInfo{lineNo, line})
		}
		lineNo++
	}

	// 채널에 해당 파일에서 추출한 정보 넣기
	ch <- findInfo
}
