package main

import "fmt"

func permutations(nums []int) [][]int {
	var results [][]int
	used := make([]bool, len(nums))
	var path []int
	var build func()
	build = func() {
		if len(path) == len(nums) {
			results = append(results, append([]int(nil), path...))
			return
		}
		for index, value := range nums {
			if used[index] {
				continue
			}
			used[index] = true
			path = append(path, value)
			build()
			path = path[:len(path)-1]
			used[index] = false
		}
	}
	build()
	return results
}

func subsets(nums []int) [][]int {
	var results [][]int
	var path []int
	var build func(start int)
	build = func(start int) {
		results = append(results, append([]int(nil), path...))
		for index := start; index < len(nums); index++ {
			path = append(path, nums[index])
			build(index + 1)
			path = path[:len(path)-1]
		}
	}
	build(0)
	return results
}

func abs(value int) int {
	if value < 0 {
		return -value
	}
	return value
}

func isSafe(row, column int, placed []int) bool {
	for previousRow, previousColumn := range placed {
		if previousColumn == column || abs(row-previousRow) == abs(column-previousColumn) {
			return false
		}
	}
	return true
}

func placeQueens(n int, placed []int) int {
	row := len(placed)
	if row == n {
		return 1
	}
	total := 0
	for column := 0; column < n; column++ {
		if isSafe(row, column, placed) {
			placed = append(placed, column)
			total += placeQueens(n, placed)
			placed = placed[:len(placed)-1]
		}
	}
	return total
}

func nQueensCount(n int) int {
	return placeQueens(n, nil)
}

func main() {
	perms := permutations([]int{1, 2, 3})
	if len(perms) != 6 || fmt.Sprint(perms[0]) != "[1 2 3]" || fmt.Sprint(perms[5]) != "[3 2 1]" {
		panic("permutations")
	}
	if len(subsets([]int{1, 2, 3})) != 8 {
		panic("subsets")
	}
	if nQueensCount(4) != 2 || nQueensCount(8) != 92 {
		panic("nQueensCount")
	}
	fmt.Println("go: all checks passed")
}
