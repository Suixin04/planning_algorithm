#pragma once

#include "GridMap.h"
#include "PlannerBase.h"
#include <vector>

class DijkstraPlanner : public PlannerBase {
    public:
        DijkstraPlanner() {}

        virtual ~DijkstraPlanner() {}

        bool plan(const GridMap &map,
                  const Point2D &start,
                  const Point2D &goal,
                  std::vector<Point2D> &path) override;
};