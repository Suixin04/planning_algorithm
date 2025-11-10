#pragma once

#include "GridMap.h"
#include <vector>

class PlannerBase {
    public:
        virtual ~PlannerBase() {}

        virtual bool plan(const GridMap &map,
                          const Point2D &start,
                          const Point2D &goal,
                          std::vector<Point2D> &path) = 0;
};