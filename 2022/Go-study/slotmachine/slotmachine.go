package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"time"
)

// 초기값 1000원에서 1 ~ 5 랜덤값 중 맞추면 +500원 아니면 -100원 시키기
// 0원 이하, 5000원 이상이면 게임 종료

const (
	Balance = 1000 // 초기 값 1000원

	Earn = 500 // 맞추면 500원

	Lose = 100 // 틀리면 -100원

	Victory = 5000 // 승리 기준 5000원

	GameOver = 0 // 패배 기준 0원
)

var stdin = bufio.NewReader(os.Stdin)

func InputValue() (int, error) {
	var n int
	_, err := fmt.Scanln(&n)
	if err != nil {
		stdin.ReadString('\n')
	} // 잘못 입력하면 입력 버퍼 지우기
	return n, err
}

func main() {
	rand.Seed(time.Now().UnixNano()) // 랜덤 시드 현재 시각으로 설정
	// 임의로 시스템 시간 재설정하는 것 아니면 절대 같은 값 나올 수 없음

	balance := Balance

	for {
		fmt.Println("1 ~ 5 의 값을 입력하세요")
		n, err := InputValue()

		if (err != nil) || (n <= 0 || n >= 6) {
			fmt.Println("입력을 다시 하세요")
		} else {
			randomNumber := rand.Intn(5) + 1 // 1 ~ 5 랜덤값

			if n == randomNumber {
				fmt.Println("정답입니다.")
				balance += Earn
				fmt.Println("현재 잔액 : ", balance)
			} else {
				fmt.Println("틀렸습니다.")
				balance -= Lose
				fmt.Println("현재 잔액 : ", balance)
			}
		}

		if balance >= Victory {
			fmt.Println("승리하셨습니다!")
			fmt.Println("최종 잔액 : ", balance)
			break
		}

		if balance <= GameOver {
			fmt.Println("패배하셨습니다!")
			fmt.Println("최종 잔액 : ", balance)
			break
		}

	}
}
