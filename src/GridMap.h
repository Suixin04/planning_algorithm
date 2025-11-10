#pragma once    // 防止头文件被重复包含

#include <vector>
#include <string>

struct Point2D {
    int x, y;
};

class GridMap {
    public:
        GridMap(int width, int height);

        bool loadFromFile(const std::string &filename);

        void setObstacle(int x, int y);

        bool isOccupied(int x, int y) const;

        int getWidth() const { return width_; }
        int getHeight() const { return height_; }

        const std::vector<std::vector<bool>> &getData() const { return data_; }

    private:
        int width_;
        int height_;
        std::vector<std::vector<bool>> data_;
};