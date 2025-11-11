#include "GridMap.h"
#include "DijkstraPlanner.h"
#include <queue>
#include <vector>
#include <iostream>

bool DijkstraPlanner::plan(const GridMap &map,
          const Point2D &start,
          const Point2D &goal,
          std::vector<Point2D> &path) {
    path.clear();

    const int width = map.getWidth();
    const int height = map.getHeight();

    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::vector<std::vector<Point2D>> parent(height, std::vector<Point2D>(width, {-1, -1}));
    std::vector<std::vector<double>> dist(height, std::vector<double>(width, INF));

    int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
    // double cost[8] = {1, 3.414, 1, 3.414, 1, 3.414, 1, 3.414};  // 故意设计斜线具有较大代价，算法应该只走上下左右。
    double cost[8] = {1, 1.414, 1, 1.414, 1, 1.414, 1, 1.414};

    std::priority_queue<Point2D> q;
    Point2D s = start;
    s.f = 0;
    dist[s.y][s.x] = 0;
    q.push(s);

    bool found = false;

    while (!q.empty()) {
        Point2D current = q.top();
        q.pop();

        if (visited[current.y][current.x]) {
            continue;
        }
        visited[current.y][current.x] = true;

        if (current.x == goal.x && current.y == goal.y) {
            found = true;
            break;
        }

        for (int i = 0; i < 8; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (map.isOccupied(nx, ny) || visited[ny][nx]) {
                continue;
            }

            double newCost = dist[current.y][current.x] + cost[i];
            if (newCost < dist[ny][nx]) {
                dist[ny][nx] = newCost;
                parent[ny][nx] = current;
                Point2D np{nx, ny};
                np.f = newCost;
                q.push(np);
            }
        }
    }

    if (!found) {
        return false;
    }

    std::vector<Point2D> rev;
    Point2D p = {goal.x, goal.y};
    // while (!(p.x == start.x && p.y == start.y)) {
    //     rev.push_back(p);
    //     p = parent[p.y][p.x];
    // }
    // rev.push_back(start);

    do {
        rev.push_back(p);
        p = parent[p.y][p.x];
    } while (!(p.x == start.x && p.y == start.y));

    std::reverse(rev.begin(), rev.end());
    path.swap(rev);

    return true;
}