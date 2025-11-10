#include "GridMap.h"
#include "BFSPlanner.h"
#include <queue>
#include <vector>
#include <iostream>

bool BFSPlanner::plan(const GridMap &map,
          const Point2D &start,
          const Point2D &goal,
          std::vector<Point2D> &path) {
    
    path.clear();

    std::vector<std::vector<bool>> isVisited(map.getHeight(), std::vector<bool>(map.getWidth(), false));
    std::vector<std::vector<Point2D>> parent(map.getHeight(), std::vector<Point2D>(map.getWidth(), {-1, -1}));

    int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };

    std::queue<Point2D> q;
    q.push(start);
    
    do {
        if (q.empty()) return false;

        Point2D current = q.front();
        q.pop();
        isVisited[current.y][current.x] = true;

        for (int i = 0; i < 8; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (!map.isOccupied(nx, ny) && !isVisited[ny][nx]) {
                isVisited[ny][nx] = true;
                parent[ny][nx] = current;
                q.push({nx, ny});
            }
        }

    } while(q.front().x != goal.x || q.front().y != goal.y);
    
    Point2D p = goal;
    do {
        path.push_back(p);
        p = parent[p.y][p.x];
    } while(p.x != start.x || p.y != start.y);

    std::reverse(path.begin(), path.end());

    return true;
}