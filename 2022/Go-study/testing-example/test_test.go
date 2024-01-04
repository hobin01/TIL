package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestSquare1(t *testing.T) {
	result := square(9)
	if result != 81 {
		t.Errorf("square 9 is 81 but %d\n", result)
	}
}

func TestSquare2(t *testing.T) {
	result := square(3)
	if result != 9 {
		t.Errorf("square 3 is 9 but %d\n", result)
	}
}

func TestSquare3(t *testing.T) {
	assert := assert.New(t)
	assert.Equal(81, square(9), "square 9 is 81")
}

func TestSquare4(t *testing.T) {
	assert := assert.New(t)
	assert.Equal(9, square(3), "square 3 is 9")
}

func BenchmarkSquare5(b *testing.B) {
	for i := 0; i < b.N; i++ {
		square(i)
	}
}
