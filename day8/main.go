// AoC 2023 Day 8 Written in GO
package main

import (
	"fmt"
	"os"
	"strings"
)

var exampleInput = []string{
	"LLR",
	"",
	"AAA = (BBB, BBB)",
	"BBB = (AAA, ZZZ)",
	"ZZZ = (ZZZ, ZZZ)",
}

// Node ...
type Node struct {
	left string
	right string
}

const inputPath = "input.txt";

const doExample = false
func main() {
	fmt.Println("Welcome to Advent of Code - Day 8 in Go Language!")
	var lines []string
	if doExample {
		lines = exampleInput
	} else {
		input, err := os.ReadFile(inputPath);
		if err != nil {
			panic(err)
		}

		lines = strings.Split(string(input), "\n")
		lines = lines[:len(lines)-1]
	}

	instructions := lines[0]
	// fmt.Println(instructions)
	// firstName := strings.Trim(strings.Split(lines[2], "=")[0], " ")
	var m map[string]Node
	m = make(map[string]Node)
	for _, line := range lines[2:] {
		s := strings.Split(line, "=")
		name := strings.Trim(s[0], " ")
		s2 := strings.Split(s[1], ",")
		left := strings.Trim(s2[0], " ()")
		right := strings.Trim(s2[1], " ()")
		m[name] = Node{left, right}
		// fmt.Println(name, m[name].left, m[name].right)
	}
	// Map and Name created!

	// Character is either 76 aka L or 82 aka R
	curName := "AAA"
	curNode := m[curName]
	// fmt.Printf("Current Node: %s -> %s | %s\n", curName, curNode.left, curNode.right)
	steps := 0
	repeat: for {
		for i, c := range instructions {
			fmt.Printf("N: %s | I: %c | S: %d\n", curName, c, steps)
			if c == 'L' {
				curName = curNode.left
				node, ok := m[curNode.left]
				if ok { curNode = node } else { panic(ok) }
			} else if c == 'R' {
				curName = curNode.right
				node, ok := m[curNode.right]
				if ok { curNode = node } else { panic(ok) }
			} else {
				panic(curName)
			}
			if curName == "ZZZ" {
				steps += i+1
				break repeat;
			}
		}
		steps += len(instructions)
		//fmt.Scanln()
	}

	fmt.Printf("Steps necessary to find ZZZ: %d\n", steps)
	if doExample && steps != 6 { panic(steps) }
	return
}

