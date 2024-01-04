package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"time"
)

var stdin = bufio.NewReader(os.Stdin)

func InputValue() (int, error) {
	var n int
	_, err := fmt.Scanln(&n)
	if err != nil {
		stdin.ReadString('\n')
	} // 에러 있으면 (즉, 이상한 거 입력하면) 입력 버퍼 지움
	return n, err
}

func main() {
	rand.Seed(time.Now().UnixNano()) // 랜덤 시드 설정

	answer := rand.Intn(100) // 0 ~ 99 랜덤 값 설정 (Intn(range))

	count := 0

	for {
		fmt.Println("숫자를 입력하세요.")
		n, err := InputValue()

		if err != nil {
			fmt.Println("숫자만 입력하세요.")
		} else {
			count += 1

			if n == answer {
				fmt.Println("정답입니다.")
				fmt.Println(answer)
				fmt.Println("시도 횟수 : ", count)
				break
			} else if n > answer {
				fmt.Println("정답보다 큽니다.")
			} else {
				fmt.Println("정답보다 작습니다.")
			}
		}
	}
}
