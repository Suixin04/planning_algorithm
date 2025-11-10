#pragma once

#include "GridMap.h"
#include "PlannerBase.h"
#include <vector>

class DFSPlanner : public PlannerBase {
    public:
        DFSPlanner() {}

        virtual ~DFSPlanner() {}

        bool plan(const GridMap &map,
                  const Point2D &start,
                  const Point2D &goal,
                  std::vector<Point2D> &path) override;
};