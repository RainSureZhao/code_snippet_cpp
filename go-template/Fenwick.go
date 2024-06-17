package template

import (
	"math/bits"
)

type Fenwick struct {
	n int
	a []int
}

func NewFenwick(n int) *Fenwick {
	fenwick := &Fenwick{
		n: n,
		a: make([]int, n+1),
	}
	return fenwick
}

func (f *Fenwick) Add(x int, v int) {
	for ; x <= f.n; x += x & -x {
		f.a[x] += v
	}
}

func (f *Fenwick) Sum(x int) int {
	sum := 0
	for ; x > 0; x -= x & -x {
		sum += f.a[x]
	}
	return sum
}

func (f *Fenwick) RangeSum(l, r int) int {
	return f.Sum(r) - f.Sum(l-1)
}

func (f *Fenwick) Kth(k int) int {
	x := 0
	p := 1 << bits.Len(uint(f.n))
	for p > 0 {
		if x+p <= f.n && k >= f.a[x+p] {
			x += p
			k -= f.a[x]
		}
		p >>= 1
	}
	return x + 1
}
