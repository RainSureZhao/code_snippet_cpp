auto f([&](int x) {
	return;
});

// 整数三分

// 求凸函数的极大值
while(l < r) {
	int lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
	if(check(lmid) >= check(rmid)) l = lmid + 1;
	else r = rmid - 1;
}
return max(f(l), f(r));


// 防止意外情况, 可以写成while(r - l > 5); 然后for(int i = l; i <= r; i ++) res = max(res, f(i));



// 求凹函数的极小值

while(l < r) {
	int lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
	if(check(lmid) <= check(rmid)) r = rmid - 1;
	else l = lmid + 1;
}
return min(f(l), f(r));


// 浮点数三分

// 凸函数极大值
const double eps = 1e-8;
while(r - l > eps) {
	double lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
	if(check(lmid) >= check(rmid)) l = lmid;
	else r = rmid;
}

// 凹函数极小值
while(r - l > eps) {
	double lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
	if(check(lmid) <= check(rmid)) r = rmid;
	else l = lmid;
}