struct Info {
    int mxpre = 0;
    int mxsuf = 0;
    int mx = 0;
    int mnpre = 0;
    int mnsuf = 0;
    int mn = 0;
    int sum = 0;
    static Info init(int x) {
    	int sum = x;
    	int mx = max(0ll, x);
    	int mn = min(0ll, x);
    	return {mx, mx, mx, mn, mn, mn, sum};
    }
};
 
Info operator+(Info a, Info b) {
    Info c;
    c.mxpre = std::max(a.mxpre, a.sum + b.mxpre);
    c.mnpre = std::min(a.mnpre, a.sum + b.mnpre);
    c.mxsuf = std::max(b.mxsuf, b.sum + a.mxsuf);
    c.mnsuf = std::min(b.mnsuf, b.sum + a.mnsuf);
    c.mx = std::max({a.mx, b.mx, a.mxsuf + b.mxpre});
    c.mn = std::min({a.mn, b.mn, a.mnsuf + b.mnpre});
    c.sum = a.sum + b.sum;
    return c;
}
 
Info rev(Info a) {
    std::swap(a.mxpre, a.mxsuf);
    std::swap(a.mnpre, a.mnsuf);
    return a;
}