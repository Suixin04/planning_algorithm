#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "GridMap.h"

const int CELL_SIZE = 10;

cv::Point gridToPixel(const Point2D &point) {
    return cv::Point(point.x * CELL_SIZE, point.y * CELL_SIZE);
}

void drawMap(cv::Mat &canvas, const GridMap &map) {
    int w = map.getWidth();
    int h = map.getHeight();

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            cv::Point p1 = gridToPixel({x, y});
            cv::Point p2 = gridToPixel({x+1, y+1});

            cv::Scalar color = map.isOccupied(x, y) ? 
                                cv::Scalar(40, 40, 40) : 
                                cv::Scalar(255, 255, 255);

            cv::rectangle(canvas, p1, p2, color, -1);

            cv::rectangle(canvas, p1, p2, cv::Scalar(200, 200, 200), 1);
        }
    }
}

void drawPath(cv::Mat &canvas, const std::vector<Point2D> &path) {
    if (path.empty()) return;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        cv::Point p1 = gridToPixel(path[i]);
        cv::Point p2 = gridToPixel(path[i+1]);

        p1.x += CELL_SIZE / 2;
        p1.y += CELL_SIZE / 2;
        p2.x += CELL_SIZE / 2;
        p2.y += CELL_SIZE / 2;

        cv::line(canvas,  p1, p2,  cv::Scalar(0, 0, 255), 2);
    }
}

int main() {
    const int MAP_WIDTH = 50;
    const int MAP_HEIGHT = 40;
    GridMap map(MAP_WIDTH, MAP_HEIGHT);

    for (int i = 10; i < 40; ++i) map.setObstacle(i, 20);
    for (int i = 0; i < 30; ++i) map.setObstacle(30, i);

    // 用于测试，实际路径应为从起点到终点的有序点
    std::vector<Point2D> fake_path;
    fake_path.push_back({5, 5});
    fake_path.push_back({25, 5});
    fake_path.push_back({25, 25});
    fake_path.push_back({45, 35});

    int canvas_width = MAP_WIDTH * CELL_SIZE;
    int canvas_height = MAP_HEIGHT * CELL_SIZE;

    cv::Mat canvas = cv::Mat(canvas_height, canvas_width, CV_8UC3, cv::Scalar(220, 220, 220));

    drawMap(canvas, map);
    drawPath(canvas, fake_path);

    cv::rectangle(canvas, 
                gridToPixel(fake_path.front()), 
                gridToPixel(fake_path.front()) + cv::Point(CELL_SIZE, CELL_SIZE), 
                cv::Scalar(222, 124, 60), 
                -1);
    cv::rectangle(canvas, 
                gridToPixel(fake_path.back()), 
                gridToPixel(fake_path.back()) + cv::Point(CELL_SIZE, CELL_SIZE), 
                cv::Scalar(60, 222, 124), 
                -1);

    cv::imshow("路径可视化窗口", canvas);

    cv::waitKey(0);

    return 0;
}