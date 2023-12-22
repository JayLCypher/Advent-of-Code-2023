// AoC 2023 Day 8 Written in GO
package main

import (
	"fmt"
	"os"
	"strings"
)

var exampleInput1 = []string{
	"LLR",
	"",
	"AAA = (BBB, BBB)",
	"BBB = (AAA, ZZZ)",
	"ZZZ = (ZZZ, ZZZ)",
}

var exampleInput2 = []string{
	"LR",
	"",
	"11A = (11B, XXX)",
	"11B = (XXX, 11Z)",
	"11Z = (11B, XXX)",
	"22A = (22B, XXX)",
	"22B = (22C, 22C)",
	"22C = (22Z, 22Z)",
	"22Z = (22B, 22B)",
	"XXX = (XXX, XXX)",
}

// Node ...
type Node struct {
	left string
	right string
}

func part1(m map[string]Node, instructions string) int {
	// Character is either 76 aka L or 82 aka R
	curName := "AAA"
	curNode := m[curName]
	// fmt.Printf("Current Node: %s -> %s | %s\n", curName, curNode.left, curNode.right)
	steps := 0
	repeat: for {
		for i, c := range instructions {
			fmt.Printf("S: %d | I: %c | N: %s\n", steps + i, c, curName)
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
	return steps
}

func part2(m map[string]Node, instructions string, keys []string) int {
	// Keys linear order: [RMA NXA GDA PLA QLA AAA]
	fmt.Println(keys)

	// Character is either 76 aka L or 82 aka R
	var nodes []Node
	for _, k := range keys {
		nodes = append(nodes, m[k])
	}
	// fmt.Printf("Current Node: %s -> %s | %s\n", curName, curNode.left, curNode.right)
	steps := 0
	// max_steps := 277*1
	iter := 1
	repeat: for {
		fmt.Printf("Iteration: %d\n", iter)
		inner: for i, c := range instructions {
			fmt.Printf("S: %d | I: %c | N: ", steps + i, c)
			// Update all nodes
			for j, n := range nodes {
				fmt.Printf("%s ", keys[j])
				if c == 'L' {
					keys[j] = n.left
				} else if c == 'R' {
					keys[j] = n.right
				} else {
					panic(n)
				}
				node, ok := m[keys[j]]
				if ok { nodes[j] = node } else { panic(ok) }
			}
			fmt.Println()
			// Check if we've hit exit condition
			for l, k := range keys {
				if k[2] != 'Z' {
					continue inner
				}
				fmt.Printf("\t%d ", l)
			}
			steps += i+1
			fmt.Println(keys)
			break repeat;
		}
		steps += len(instructions)
		iter++
		// fmt.Scanln()
	}
	return steps
}

func part2_2(m map[string]Node, instructions string, keys []string) int {
	// Keys linear order: [RMA NXA GDA PLA QLA AAA]
	fmt.Println(keys)

	var stepCollect []int
	// Character is either 76 aka L or 82 aka R
	var k string
	var n Node
	// fmt.Printf("Current Node: %s -> %s | %s\n", curName, curNode.left, curNode.right)
	steps := 0
	for i := range keys {
		k = keys[i]
		n = m[k]
		repeat: for {
			for j, c := range instructions {
				fmt.Printf("S: %d | I: %c | N: %s\n", steps + j, c, k)
				if c == 'L' {
					k = n.left
					node, ok := m[k]
					if ok { n = node } else { panic(ok) }
				} else if c == 'R' {
					k = n.right
					node, ok := m[k]
					if ok { n = node } else { panic(ok) }
				} else {
					panic(k)
				}
				if k[2] == 'Z' {
					steps += j+1
					stepCollect = append(stepCollect, steps)
					steps = 0
					break repeat;
				}
			}
			steps += len(instructions)
			//fmt.Scanln()
		}
		keys[i] = k
	}
	fmt.Println(keys)
	fmt.Println(stepCollect)
	var ret uint64
	ret = uint64(stepCollect[0])
	// The answer was per key how many collection of (steps / length of instructions) which were repetitions.
	// Don't try to brute force this shit.
	for i := range stepCollect[1:]  {
		ret *= uint64(stepCollect[i+1] / len(instructions))
	}
	fmt.Println(ret)
	return int(ret)
}

const inputPath = "input.txt"
const doPart1 = false
const doPart2 = true

const doExample = false
func main() {
	fmt.Println("Welcome to Advent of Code - Day 8 in Go Language!")
	if !(doPart1 != doPart2) {
		panic("Please pick one part and at most one part.")
	}
	var lines []string
	if doExample && doPart1 {
		lines = exampleInput1
	} else if doExample && doPart2 {
		lines = exampleInput2
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
	var keys []string
	var m map[string]Node
	m = make(map[string]Node)
	for _, line := range lines[2:] {
		s := strings.Split(line, "=")
		name := strings.Trim(s[0], " ")
		if name[2] == 'A' { keys = append(keys, name)}
		s2 := strings.Split(s[1], ",")
		left := strings.Trim(s2[0], " ()")
		right := strings.Trim(s2[1], " ()")
		m[name] = Node{left, right}
		// fmt.Println(name, m[name].left, m[name].right)
	}
	// Map and Name created!

	steps := 0
	if doPart1 {
		steps = part1(m, instructions)
	} else if doPart2 {
		steps = part2_2(m, instructions, keys)
	} else {
		panic("Please choose part 1 or part 2!")
	}

	fmt.Printf("Steps necessary to find ZZZ: %d\n", steps)
	if doExample && steps != 6 { panic(steps) }
	return
}

