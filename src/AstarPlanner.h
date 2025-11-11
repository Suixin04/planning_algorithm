#pragma once

#include "GridMap.h"
#include "PlannerBase.h"
#include <vector>

class AstarPlanner : public PlannerBase {
    public:
        AstarPlanner() {}

        virtual ~AstarPlanner() {}

        bool plan(const GridMap &map,
                  const Point2D &start,
                  const Point2D &goal,
                  std::vector<Point2D> &path) override;
};