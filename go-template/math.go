package template

func main() {
	gcd := func(a, b int) int {
		for a != 0 {
			a, b = b%a, a
		}
		return b
	}
	lcm := func(a, b int) int {
		return a * b / gcd(a, b)
	}
}
