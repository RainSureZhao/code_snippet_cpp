// RainSure的计算几何竞赛库

const double pi = acos(-1.0);
const double eps = 1e-8;
const double inf = 1e18 + 10;

int sgn(double x) {
	if(fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}

int dcmp(double x, double y) {
	if(fabs(x - y) < eps) return 0;
	return x < y ? -1 : 1;
}


struct Point {
	double x, y;
	Point(double x, double y) : x(x), y(y) {}
	
	Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}

	Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}

	Point operator*(double k) const {
		return Point(x * k, y * k);
	}

	Point operator/(double k) const {
		return Point(x / k, y / k);
	}

	bool operator=(const Point& rhs) const {
		return sgn(x - rhs.x) == 0 and sgn(y - rhs.y) == 0;
	}
};

double distance(const Point& A, const Point& B) {
	return hypot(A.x - B.x, A.y - B.y);
}


// 向量
using Vector = Point;

// dot 点乘
double dot(const Vector& a, const Vector& b) {
	return a.x * b.x + a.y * b.y;
}

// len 求向量的长度
double len(const Vector& a) {
	return sqrt(dot(a, a));
}

// len2 长度的平方
double len2(const Vector& a) {
	return dot(a, a);
}

// angle 求向量A和向量B的夹角
double angle(const Vector& a, const Vector& b) {
	return acos(dot(a, b) / len(a) / len(b));
}

// cross 向量的叉乘
double cross(const Vector& a, const Vector& b) {
	return a.x * b.y - b.x * a.y;
}

// area2 计算向量ab, 向量ac构成的平行四边形的面积
double area2(const Point& a, const Point& b, const Point& c) {
	return cross(b - a, c - a);
}

// rotate 向量a绕原点逆时针旋转rad角度，单位是弧度
Vector rotate(const Vector& a, doubla rad) {
	return {a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad)};
}

// normal 求向量a的单位法向量，先逆时针旋转90度，再取单位值
Vector normal(const Vector& a) {
	return {-a.y / len(a), a.x / len(a)};
}

// parallel 判断两个向量是否平行
bool parallel(const Vector& a, const Vector& b) {
	return sgn(cross(a, b)) == 0;
}


// 直线类
struct Line {
	Point p1, p2; // 直线上的两个点
	Line() = default;
	Line(const Point& p1, const Point& p2) : p1(p1), p2(p2) {}
	Line(const Point& p, double angle) {
		// 根据一个点和一个角度来定义直线, 0 <= angle < pi
		p1 = p;
		if(sgn(angle - pi / 2) == 0) p2 = (p1 + Point(0, 1));
		else p2 = p1 + Point(1, tan(angle));
	}
	Line(double a, double b, double c) {
		// ax + by + c = 0
		if(sgn(a) == 0) {
			p1 = Point(0, -c / b);
			p2 = Point(1, -c / b);
		}
		else if(sgn(b) == 0) {
			p1 = Point(-c / a, 0);
			p2 = Point(-c / a, 1);
		}
		else {
			p1 = Point(0, -c / b);
			p2 = Point(1, (-c - a) / b);
		}
	}
};

using Segment = Line;

// 点和直线的位置关系
int point_line_relation(const Point& p, const Line& v) {
	int c = sgn(cross(p - v.p1, v.p2 - v.p1));
	if(c < 0) return 1; // 1: p在v的左侧
	if(c > 0) return 2; // 2: p在v的右侧
	return 0; 			// 0: p在v上 
}

// 点和线段的位置关系
bool point_on_segment(const Point& p, const Segment& v) {
	// 0: 点p不在线段上，1: 点p在线段上
	return sgn(cross(p - v.p1, v.p2 - v.p1)) == 0 and sgn(dot(p - v.p1, p1.p - v.p2)) <= 0;
}

// 点到直线的距离
double dis_point_line(const Point& p, const Line& v) {
	return fabs(cross(p - v.p1, v.p2 - v.p1)) / distance(v.p1, v.p2);
}

// 点在直线上的投影
Point point_line_proj(const Point& p, const Line& v) {
	double k = dot(v.p2 - v.p1, p - v.p1) / len2(v.p2 - v.p1);
	return v.p1 + (v.p2 - v.p1) * k;
}

// 点关于直线的对称点
Point point_line_symmetry(const Point& p, const Line& v) {
	Point q = point_line_proj(p, v);
	return {2 * q.x - p.x, 2 * q.y - p.y};
}

// 点到线段的距离
double dis_point_segment(const Point& p, const Segment& v) {
	if(sgn(dot(p - v.p1, v.p2 - v.p1)) < 0 or sgn(dot(p - v.p2, v.p1 - v.p2)) < 0) {
		return min(distance(p, v.p1), distance(p, v.p2));
	}
	return dis_point_line(p, v); // 点的投影在线段上
}

// 两条直线的位置关系
int line_relation(const Line& v1, const Line& v2) {
	if(sgn(cross(v1.p2 - v1.p1, v2.p2 - v2.p1)) == 0) {
		if(point_line_relation(v1.p1, v2) == 0) return 1; // 1: 重合
		return 0;										  // 0: 平行
	}
	return 2;											  // 2: 相交
}

// 两条直线的交点，利用叉积
Point line_intersection(const Point& a, const Point& b, const Point& c, const Point& d) { // 线段1: ab, 线段2: cd
	double s1 = cross(b - a, c - a);
	double s2 = cross(b - a, d - a);
	return Point(c.x * s2 - d.x * s1, c.y * s2 - d.y * s1) / (s2 - s1);
}

// 两条线段是否相交
bool cross_segment(const Point& a, const Point& b, const Point& c, const Point& d) { // 线段1: ab, 线段2: cd
	double c1 = cross(b - a, c - a), c2 = cross(b - a, d - a);
	double d1 = cross(d - c, a - c), d2 = cross(d - c, b - c);
	return sgn(c1) * sgn(c2) < 0 and sgn(d1) * sgn(d2) < 0;
}

// 两条线段的交点
Point segment_intersetion(const Point& a, const Point& b, const Point& c, const Point& d) {
	if(cross_segment(a, b, c, d)) return line_intersection(a, b, c, d);
	return Point(-inf, -inf); // 不相交
}