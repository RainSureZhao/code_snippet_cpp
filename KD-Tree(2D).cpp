struct Point {
    double x, y;

    Point(double x, double y) : x(x), y(y) {}
};

struct KDNode {
    Point point;
    int leftChild;
    int rightChild;

    KDNode(Point p) : point(p), leftChild(-1), rightChild(-1) {}
};

struct KDTree {
    vector<KDNode> nodes;
    int root;

    KDTree() : root(-1) {}

    // 递归构建KD树
    int buildTree(vector<Point>& points, int depth, int start, int end) {
        if (start > end) return -1;

        // 根据当前维度选择划分轴
        int axis = depth % 2;
        int mid = (start + end) / 2;

        // 根据划分轴排序点集
        if (axis == 0)
            nth_element(points.begin() + start, points.begin() + mid, points.begin() + end + 1,
                        [](const Point& a, const Point& b) { return a.x < b.x; });
        else
            nth_element(points.begin() + start, points.begin() + mid, points.begin() + end + 1,
                        [](const Point& a, const Point& b) { return a.y < b.y; });

        // 创建当前节点
        int currentNodeIndex = nodes.size();
        nodes.push_back(KDNode(points[mid]));

        // 递归构建左子树和右子树
        nodes[currentNodeIndex].leftChild = buildTree(points, depth + 1, start, mid - 1);
        nodes[currentNodeIndex].rightChild = buildTree(points, depth + 1, mid + 1, end);

        return currentNodeIndex;
    }

    // 构建KD树
    void build(vector<Point>& points) {
        root = buildTree(points, 0, 0, points.size() - 1);
    }

    // 递归插入节点
    int insertNode(int nodeIndex, Point& point, int depth) {
        if (nodeIndex == -1) {
            int newNodeIndex = nodes.size();
            nodes.push_back(KDNode(point));
            return newNodeIndex;
        }

        // 根据当前维度选择划分轴
        int axis = depth % 2;

        // 根据划分轴判断插入点的位置
        if (axis == 0) {
            if (point.x < nodes[nodeIndex].point.x)
                nodes[nodeIndex].leftChild = insertNode(nodes[nodeIndex].leftChild, point, depth + 1);
            else
                nodes[nodeIndex].rightChild = insertNode(nodes[nodeIndex].rightChild, point, depth + 1);
        } else {
            if (point.y < nodes[nodeIndex].point.y)
                nodes[nodeIndex].leftChild = insertNode(nodes[nodeIndex].leftChild, point, depth + 1);
            else
                nodes[nodeIndex].rightChild = insertNode(nodes[nodeIndex].rightChild, point, depth + 1);
        }

        return nodeIndex;
    }

    // 插入节点
    void insert(Point& point) {
        root = insertNode(root, point, 0);
    }

    // 递归进行区域查询
    void rangeSearch(int nodeIndex, const Point& minPt, const Point& maxPt, vector<Point>& result) {
        if (nodeIndex == -1) return;

        KDNode& node = nodes[nodeIndex];

        // 检查当前节点是否在查询区域内
        if (node.point.x >= minPt.x && node.point.x <= maxPt.x &&
            node.point.y >= minPt.y && node.point.y <= maxPt.y) {
            result.push_back(node.point);
        }

        // 根据当前维度选择划分轴
        int axis = nodeIndex % 2;

        // 判断是否需要在左子树和右子树中继续查询
        if (axis == 0) {
            if (minPt.x <= node.point.x)
                rangeSearch(node.leftChild, minPt, maxPt, result);
            if (maxPt.x >= node.point.x)
                rangeSearch(node.rightChild, minPt, maxPt, result);
        } else {
            if (minPt.y <= node.point.y)
                rangeSearch(node.leftChild, minPt, maxPt, result);
            if (maxPt.y >= node.point.y)
                rangeSearch(node.rightChild, minPt, maxPt, result);
        }
    }

    // 区域查询
    vector<Point> queryRange(const Point& minPt, const Point& maxPt) {
        vector<Point> result;
        rangeSearch(root, minPt, maxPt, result);
        return result;
    }
};
/**
 vector<Point> points = {Point(2, 3), Point(5, 4), Point(1, 2), Point(6, 5)};

KDTree kdTree;
kdTree.build(points);

**/