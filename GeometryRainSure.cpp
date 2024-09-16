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
	Point() = default;
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

	bool operator==(const Point& rhs) const {
		return sgn(x - rhs.x) == 0 and sgn(y - rhs.y) == 0;
	}
	bool operator<(const Point& rhs) const { // 先按照x排序，再按照y排序
		return sgn(x - rhs.x) < 0 or (sgn(x - rhs.x) == 0 and sgn(y - rhs.y) < 0);
	}
};

double distance(const Point& A, const Point& B) {
	return hypot(A.x - B.x, A.y - B.y);
}

long long distance2(const Point& a, const Point& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
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
Vector rotate(const Vector& a, double rad) {
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
		if(sgn(angle - pi / 2) == 0) p2 = p1 + Point(0, 1);
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
	return sgn(cross(p - v.p1, v.p2 - v.p1)) == 0 and sgn(dot(p - v.p1, p - v.p2)) <= 0;
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

// 点和三角形的位置关系，判断点p和三角形abc的位置关系，1: 内部; 2: 外部; 3: 边界上; 4: 顶点上
int point_triangle_relation(const Point& p, const Point& a, const Point& b, const Point& c) {
	int right = 0, left = 0;
	std::vector<Point> v {a, b, c};
	for(int i = 0; i < 3; i ++) {
		int relation = cross(p - v[i], p - v[(i + 1) % 3]);
		if(relation > 0) right ++;
		else if(relation < 0) left ++;
	}
	if(right == 3 or left == 3) return 1;
	else if(right > 0 and left > 0) return 2;
	else if(right + left == 1) return 4;
	return 3;
}


// 判断点是否在多边形内部—— 0: 点在多边形外部，1: 点在多边形内部; 2: 点在多边形的边上; 3: 点在多边形的顶点上
int point_in_polygon(const Point& p, const std::vector<Point>& points) {
	int n = points.size();
	for(int i = 0; i < n; i ++) {
		if(points[i] == p) return 3;
	}
	for(int i = 0; i < n; i ++) {
		auto segment = Segment(points[i], points[(i + 1) % n]);
		if(point_on_segment(p, segment)) {
			return 2;
		}
	}
	int num = 0;
	for(int i = 0; i < n; i ++) {
		int j = (i + 1) % n;
		int c = sgn(cross(p - points[j], points[i] - points[j]));
		int u = sgn(points[i].y - p.y);
		int v = sgn(points[j].y - p.y);
		if(c > 0 and u < 0 and v >= 0) num ++;
		if(c < 0 and u >= 0 and v < 0) num --;
	}
	return num != 0;
}

// 求多边形的面积
double polygon_area(const std::vector<Point>& points) {
	double res = 0;
	int n = points.size();
	for(int i = 0; i < n; i ++) {
		res += cross(points[i], points[(i + 1) % n]);
	}
	return res / 2;
}

// 求多边形的重心，将多边形进行三角剖分，求出每个三角形的重心，三角形的重心是顶点坐标的平均值，然后对每个三角形的有向面积加权平均
Point polygon_center(const std::vector<Point>& points) {
	int n = points.size();
	Point res(0, 0);
	if(polygon_area(points) == 0) return res;
	for(int i = 0; i < n; i ++) {
		res = res + (points[i] + points[(i + 1) % n]) * cross(points[i], points[(i + 1) % n]);
	}
	return res / polygon_area(points) / 6;
}

// 二维凸包
std::vector<Point> convex_hull(const std::vector<Point>& points) {
	auto ps = points;
	ps.erase(std::unique(begin(ps), end(ps)), end(ps));
	sort(begin(ps), end(ps));
	std::vector<Point> res;
	int n = ps.size();
	// 求下凸包，如果是右拐弯的，说明这个点不在凸包上
	for(int i = 0; i < n; i ++) {
		while(res.size() >= 2 and sgn(cross(res.back() - res[res.size() - 2], ps[i] - res.back())) <= 0) {
			res.pop_back();
		}
		res.push_back(ps[i]);
	}
	int sz = res.size();
	// 求上凸包
	for(int i = n - 2; i >= 0; i --) {
		while(static_cast<int>(res.size()) > sz and sgn(cross(res.back() - res[res.size() - 2], ps[i] - res.back())) <= 0) {
			res.pop_back();
		}
		res.push_back(ps[i]);
	}
	if(n > 1) res.pop_back();
	return res;
}

// 平面最近点对，输入数据要求已经排好序——先对x排序，再对y排序
double closest_pair(const vector<Point>& points, int l, int r) {
	double dis = inf;
	if(l == r) return dis;
	if(l + 1 == r) return distance(points[l], points[r]);
	int mid = (l + r) >> 1;
	double d1 = closest_pair(points, l, mid);
	double d2 = closest_pair(points, mid + 1, r);
	dis = min(d1, d2);
	std::vector<Point> tmp;
	for(int i = l; i <= r; i ++) {
		if(fabs(points[mid].x - points[i].x) <= dis) {
			tmp.push_back(points[i]);
		}
	}
	sort(begin(tmp), end(tmp), [](Point &a, Point &b) {
		return sgn(a.y - b.y) < 0;
	});
	for(int i = 0; i < tmp.size(); i ++) {
		for(int j = i + 1; j < tmp.size(); j ++) {
			if(tmp[j].y - tmp[i].y >= dis) break;
			dis = min(dis, distance(tmp[i], tmp[j]));
		}
	}
	return dis;
}

// 旋转卡壳，需要在凸包的基础上进行，传入的点的数据一般是一个凸包，求平面上距离最远的点的距离的平方
long long rotating_calipers(const std::vector<Point>& points) {
	int n = points.size();
	if(n <= 1) return 0;
	if(n <= 2) return distance2(points[0], points[1]);
	long long maxDistSq = 0;
	for(int i = 0, j = 2; i < n; i ++) {
		auto p1 = points[i], p2 = points[(i + 1) % n];
		while(sgn(cross(p2 - p1, points[j] - p1) - cross(p2 - p1, points[(j + 1) % n] - p1)) < 0) {
			j = (j + 1) % n;
		}
		maxDistSq = max({maxDistSq, distance2(p1, points[j]), distance2(p2, points[j])});
	}
	return maxDistSq;
}

// 半平面交，半平面可以用一个有向直线来定义，多个半平面的交集可以构成一个凸多边形
struct HalfPlane {
	Point p; // 直线上的一个点
	Vector v; // 方向向量，它的左边是半平面
	double ang; // 极角，

	HalfPlane() = default;
	HalfPlane(const Point& p, const Vector& v) : p(p), v(v) {
		ang = atan2(v.y, v.x);
	}
	bool operator<(const HalfPlane& rhs) { // 用于极角排序
		return ang < rhs.ang;
	}
};

// 判断点p在半平面的左边
bool OnLeft(const HalfPlane& plane, const Point& p) {
	return sgn(cross(plane.v, p - plane.p)) > 0;
}

// 求两个半平面的交点
Point CrossPoint(const HalfPlane& plane, const HalfPlane& b) {
	Vector u = a.p - b.p;
	double t = cross(b.v, u) / cross(a.v, b.v);
	return a.p + a.v * t;
}

std::vector<Point> HPI(std::vector<HalfPlane> planes) {
	int n = planes.size();
	std::sort(begin(planes), end(planes));
	int first = 0, second = 0;
	std::vector<Point> p(n);
	std::vector<HalfPlane> q(n);
	q[0] = planes[0];
	for(int i = 1; i < n; i ++) {
		// 删除尾部的半平面
		while(first < last and !OnLeft(planes[i], p[last - 1])) last --;
		// 删除首部的半平面
		while(first < last and !OnLeft(planes[i], p[first])) first ++;
		q[++ last] = planes[i];
		// 极角相同的两个半平面，保留左边
		if(fabs(cross(q[last].v, q[last - 1].v)) < eps) {
			last --;
			if(OnLeft(q[last], planes[i].p)) q[last] = planes[i];
		}
		// 计算队列尾部半平面交点
		if(first < last) p[last - 1] = CrossPoint(q[last - 1], q[last]);
	}
	// 删除队列尾部的无用半平面
	while(first < last and !OnLeft(q[first], p[last - 1])) last --;
	if(last - first <= 1) return ans;
	p[last] = CrossPoint(q[last], q[first]);
	for(int i = first; i <= last; i ++) ans.push_back(p[i]);
	return ans;
}

// 圆
struct Circle {
	Point c; // 圆心
	double r; // 半径
	Circle() = default;
	Circle(const Point& c, double r) : c(c), r(r) {}
	Circle(double x, double y, double _r) {
		c = Point(x, y);
		r = _r;
	}
};

// 点和圆的位置关系
int point_circle_relation(const Point& p, const Circle& c) {
	double dst = distance(p, C.c);
	if(sgn(dst - C.r) < 0) return 0; // 0: 点在圆内
	if(sgn(dst - C.r) == 0) return 1; // 1: 点在圆上
	return 2; // 2: 点在圆外
}

// 直线和圆的位置关系
int line_circle_relation(const Line& v, const Circle& c) {
	double dst = dis_point_line(C.c, v);
	if(sgn(dst - C.r) < 0) return 0; // 0: 直线和圆相交
	if(sgn(dst - C.r) == 0) return 1; // 1: 直线和圆相切
	return 2; // 2： 直线在圆外
}

// 线段和圆的位置关系
int segment_circle_relation(const Segment& v, const Circle& c) {
	double dst = dis_point_segment(c.c, v);
	if(sgn(dst - c.r) < 0) return 0; // 0: 线段在圆内
	if(sgn(dst - c.r) == 0) return 1; // 1: 线段与圆相切
	return 2; // 2: 线段在圆外
}

// 直线和圆的交点
std::vector<Point> line_cross_circle(const Line& v, const Circle& c) {
	std::vector<Point> res;
	if(line_circle_relation(v, c) == 2) return res; // 无交点
	auto q = point_line_proj(c.c, v); // 圆心在直线上的投影点
	double d = dis_point_line(c.c, v); // 圆心到直线的距离
	double k = sqrt(c.r * c.r - d * d);
	if(sgn(k) == 0) { // 相切的时候就一个交点
		res.push_back(q);
		return res;
	}
	Vector n = (v.p2 - v.p1) / len(v.p2 - v.p1);
	res.push_back(q + n * k);
	res.push_back(q - n * k);
	return res;
}

// 求三角形的abc的外接圆的圆心
Point circle_center(const Point& a, const Point& b, const Point& c) {
	double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2;
	double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2;
	return {a.x + (c1 * b2 - c2 * b1) / d, a.y + (a1 * c2 - a2 * c1) / 2};
}

// 最小圆覆盖
Circle min_cover_circle(std::vector<Point>& p) {
	std::random_shuffle(begin(p), end(p));
	assert(!p.empty());
	Point c = p[0];
	double r = 0;
	for(int i = 1; i < n; i ++) {
		if(sgn(distance(p[i], c) - r) > 0) {
			c = p[i];
			r = 0;
		}
		for(int j = 0; j < i; j ++) {
			if(sgn(distance(p[j], c) - r) > 0) {
				c.x = (p[i].x + p[j].x) / 2;
				c.y = (p[i].y + p[j].y) / 2;
				r = distance(p[j], c);
				for(int k = 0; k < j; k ++) {
					if(sgn(distance(p[k], c) - r) > 0) {
						c = circle_center(p[i], p[j], p[k]);
						r = distance(p[i], c);
					}
				}
			}
		}
	}
	return c;
}