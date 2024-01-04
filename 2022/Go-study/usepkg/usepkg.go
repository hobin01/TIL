package main

import (
	"fmt" // 표준 패키지

	"GO-STUDY/usepkg/custompkg" // 모듈 내 패키지

	"github.com/guptarohit/asciigraph"
	"github.com/tuckersGo/musthaveGo/ch16/expkg" // 외부 패키지
)

func main() {
	custompkg.CustomPrint()

	expkg.PrintSample()

	data := []float64{3, 4, 5, 6, 9, 7, 5, 8, 5, 10, 2, 7, 2, 5, 6}
	graph := asciigraph.Plot(data)
	fmt.Println(graph)

}
