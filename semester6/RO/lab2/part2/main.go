package main

import (
	"fmt"
)

func Ivanov(property []int, done chan int) {
	ch := make(chan int)
	go Petrov(ch, done)
	for i := 0; i < len(property); i++ {
		ch <- property[i]
	}
	close(ch)
}

func Petrov(input chan int, done chan int) {
	ch := make(chan int)
	go Necheporchuk(ch, done)

	for {
		val, opened := <-input
		if !opened {
			break
		}
		ch <- val
	}
	close(ch)
}

func Necheporchuk(input chan int, done chan int) {
	for {
		val, opened := <-input
		if !opened {
			break
		}
		fmt.Println(val)
	}
	close(done)
}

func main() {
	var done = make(chan int)
	var property []int = []int{1, 2, 30, 4, 5, 6, 7, 8, 9, 10}
	go Ivanov(property, done)
	for {
		_, open := <-done
		if !open {
			break
		}
	}
	// fmt.Println("x")
	// fmt.Println(<-input)
}
