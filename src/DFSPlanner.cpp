#include "GridMap.h"
#include "DFSPlanner.h"
#include <queue>
#include <vector>
#include <iostream>

bool visit_callback(const GridMap &map, Point2D curr, int *dx, int *dy, int dir,
                    std::vector<std::vector<bool>> &isVisited,
                    std::vector<std::vector<Point2D>> &parent,
                    Point2D goal) {
    if (curr.x == goal.x && curr.y == goal.y) {
        return true;
    }
    
    if (dir >= 8) {
        return false;
    }
    
    int nx = curr.x + dx[dir];
    int ny = curr.y + dy[dir];
    
    if (!map.isOccupied(nx, ny) && !isVisited[ny][nx]) {
        isVisited[ny][nx] = true;
        parent[ny][nx] = curr;
        
        if (visit_callback(map, {nx, ny}, dx, dy, 0, isVisited, parent, goal)) {
            return true;
        }
    }
    
    return visit_callback(map, curr, dx, dy, dir + 1, isVisited, parent, goal);
}

bool DFSPlanner::plan(const GridMap &map,
          const Point2D &start,
          const Point2D &goal,
          std::vector<Point2D> &path) {
    
    path.clear();

    std::vector<std::vector<bool>> isVisited(map.getHeight(), std::vector<bool>(map.getWidth(), false));
    std::vector<std::vector<Point2D>> parent(map.getHeight(), std::vector<Point2D>(map.getWidth(), {-1, -1}));

    int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };

    isVisited[start.y][start.x] = true;
    bool founded = visit_callback(map, start, dx, dy, 0, isVisited, parent, goal);
    
    if (!founded) {
        return false;
    }
    
    Point2D p = goal;
    do {
        path.push_back(p);
        p = parent[p.y][p.x];
    } while(p.x != start.x || p.y != start.y);

    std::reverse(path.begin(), path.end());

    return founded;
}