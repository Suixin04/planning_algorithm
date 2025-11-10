#include "GridMap.h"
#include <opencv2/opencv.hpp>

GridMap::GridMap(int width, int height) : width_(width), height_(height) {
    data_.resize(height, std::vector<bool>(width, false));
}

void GridMap::setObstacle(int x, int y) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        data_[y][x] = true;
    }
}

bool GridMap::isOccupied(int x, int y) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return true;
    }
    return data_[y][x];
}

bool GridMap::loadFromFile(const std::string &filename) {
    cv::Mat img = cv::imread(filename, cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        return false;
    }

    width_ = img.cols;
    height_ = img.rows;
    data_.resize(height_, std::vector<bool>(width_, false));

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (img.at<uchar>(y, x) < 128) {
                data_[y][x] = true;
            }
        }
    }

    return true;
}