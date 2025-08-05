#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <set>
using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

// 计算曼哈顿距离
int manhattanDistance(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// 获取连接两点的路径上的所有点
set<Point> getPath(const Point& a, const Point& b) {
    set<Point> path;
    int x1 = a.x, y1 = a.y;
    int x2 = b.x, y2 = b.y;
    
    // 先水平移动，再垂直移动
    int x = x1, y = y1;
    while (x != x2) {
        path.insert(Point(x, y));
        x += (x2 > x1) ? 1 : -1;
    }
    while (y != y2) {
        path.insert(Point(x, y));
        y += (y2 > y1) ? 1 : -1;
    }
    path.insert(Point(x2, y2));
    
    return path;
}

// 计算连接三个点的最小代价
int minCostToConnect(Point A, Point B, Point C) {
    int minCost = INT_MAX;
    
    // 方案1: A-B-C
    set<Point> path1 = getPath(A, B);
    set<Point> path2 = getPath(B, C);
    set<Point> totalPath1;
    totalPath1.insert(path1.begin(), path1.end());
    totalPath1.insert(path2.begin(), path2.end());
    minCost = min(minCost, (int)totalPath1.size());
    
    // 方案2: A-C-B
    path1 = getPath(A, C);
    path2 = getPath(C, B);
    set<Point> totalPath2;
    totalPath2.insert(path1.begin(), path1.end());
    totalPath2.insert(path2.begin(), path2.end());
    minCost = min(minCost, (int)totalPath2.size());
    
    // 方案3: B-A-C
    path1 = getPath(B, A);
    path2 = getPath(A, C);
    set<Point> totalPath3;
    totalPath3.insert(path1.begin(), path1.end());
    totalPath3.insert(path2.begin(), path2.end());
    minCost = min(minCost, (int)totalPath3.size());
    
    // 方案4: 通过斯坦纳点
    int minX = min({A.x, B.x, C.x});
    int maxX = max({A.x, B.x, C.x});
    int minY = min({A.y, B.y, C.y});
    int maxY = max({A.y, B.y, C.y});
    
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            Point steiner(x, y);
            
            set<Point> pathAS = getPath(A, steiner);
            set<Point> pathBS = getPath(B, steiner);
            set<Point> pathCS = getPath(C, steiner);
            
            set<Point> totalPath;
            totalPath.insert(pathAS.begin(), pathAS.end());
            totalPath.insert(pathBS.begin(), pathBS.end());
            totalPath.insert(pathCS.begin(), pathCS.end());
            
            minCost = min(minCost, (int)totalPath.size());
        }
    }
    
    return minCost;
}

int main() {
    Point A, B, C;
    cin >> A.x >> A.y;
    cin >> B.x >> B.y;
    cin >> C.x >> C.y;
    
    int result = minCostToConnect(A, B, C);
    cout << result << endl;
    
    return 0;
}