#pragma once

#include <random>
#include "Point3D.h"

namespace geometry {
using PointCloud = std::vector<Point3D>;
class PointCloudFactory {
    public:
        /// @brief  Constructor
        PointCloudFactory(size_t num_points, double min_boundary, double max_boundary);

        /// @brief Generates a random point cloud
        PointCloud GeneratePointCloud();

        /// @brief Loads a point cloud from file
        /// @param filepath Filepath to load from
        // TODO: Implement this
        PointCloud LoadPointCloudFromFile(std::string filepath) = delete;        
    private:
        std::mt19937 gen_;
        std::uniform_real_distribution<> dist_;
        size_t num_points_;
};
}