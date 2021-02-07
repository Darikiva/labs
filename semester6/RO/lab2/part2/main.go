package main

import (
	"fmt"
)

func Ivanov(value []int, input chan int) {
	chanel1 := make(chan int)
	go Petrov(chanel1, input)
	for i := 0; i < len(value); i++ {
		chanel1 <- value[i]
	}
	close(chanel1)
}

func Petrov(c chan int, input chan int) {
	chanel2 := make(chan int)
	go Necheporchuk(chanel2, input)

	for {
		x, wow := <-c
		if !wow {
			break
		}
		chanel2 <- x
	}
	close(chanel2)
}

func Necheporchuk(c chan int, input chan int) {
	for {
		x, wow := <-c
		if !wow {
			break
		}
		fmt.Println(x)
	}
	close(input)
}

func main() {
	var input = make(chan int)
	var arr []int = []int{1, 2, 30, 4, 5, 6, 7, 8, 9, 10}
	go Ivanov(arr, input)
	for {
		_, open := <-input
		if !open {
			break
		}
	}
	// fmt.Println("x")
	// fmt.Println(<-input)
}
