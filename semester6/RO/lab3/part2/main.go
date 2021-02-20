package main

import (
	"fmt"
	"sync"
	"time"
)

func Barber(visitors chan int, done chan int) {
	for {
		fmt.Println("Barber sleep")
		time.Sleep(time.Second)
		ind := <-visitors
		fmt.Println("Barber get up")
		time.Sleep(time.Second)
		done <- ind
		fmt.Println("Barber finish work")
	}
}

func Visitor(visitors chan int, done chan int, wg *sync.WaitGroup, id int) {
	visitors <- id
	<-done
	wg.Done()
}

func main() {
	var visitors = make(chan int)
	var done = make(chan int)

	var wg sync.WaitGroup
	wg.Add(3)

	go Barber(visitors, done)
	go Visitor(visitors, done, &wg, 1)
	go Visitor(visitors, done, &wg, 2)
	go Visitor(visitors, done, &wg, 3)

	wg.Wait()
}
