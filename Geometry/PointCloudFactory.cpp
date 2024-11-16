#include "PointCloudFactory.h"

namespace geometry {
PointCloudFactory::PointCloudFactory(size_t num_points, double min_boundary, double max_boundary) : 
    gen_(123), dist_(min_boundary, max_boundary), num_points_(num_points) {}

PointCloud PointCloudFactory::GeneratePointCloud() {
    PointCloud pc;
    pc.reserve(num_points_);
    for (size_t i = 0; i < num_points_; ++i) {
        pc.emplace_back(dist_(gen_),dist_(gen_),dist_(gen_));
    }
    return pc;
}
}