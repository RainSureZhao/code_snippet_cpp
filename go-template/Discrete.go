package template

import (
	"fmt"
	"sort"
)

func unique(nums []int) []int {
	if len(nums) == 0 {
		return nums
	}
	j := 0
	for i := 1; i < len(nums); i++ {
		if nums[j] != nums[i] {
			j++
			nums[j] = nums[i]
		}
	}
	return nums[:j+1]
}

func lowerBound(nums []int, x int) int {
	low, high := 0, len(nums)-1
	for low < high {
		mid := (low + high) >> 1
		if nums[mid] >= x {
			high = mid
		} else {
			low = mid + 1
		}
	}
	return low
}

func main() {
	n := 100
	nums := make([]int, n)
	sort.Ints(nums)
	nums = unique(nums)

	find := func(x int) int {
		return lowerBound(nums, x) + 1
	}
	fmt.Println(find(nums[0]))
}
