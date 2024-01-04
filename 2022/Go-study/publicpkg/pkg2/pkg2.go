package pkg2

import "fmt"

var A = 10
var B = 20

func init() {
	fmt.Println("Init!!!!")
	fmt.Println(A)
	B += 30
	fmt.Println(B)
}
