#include "../Geometry/PointCloudFactory.h"
#include "../Graphs/KDTree.h"

#include <iostream>
#include <cassert>

int main() {
    std::cout << "Point Cloud Processing ... " << std::endl;
    constexpr size_t num_points = 100;
    geometry::PointCloudFactory factory(num_points, 0., 100.);
    auto pc = factory.GeneratePointCloud();
    // Build the KDTree
    graph::KDTree<3> kdtree{};
    for (const auto& point : pc) {
        std::cout << "Point cloud point: " << point << std::endl;
        kdtree.AddPoint(point);
    }
   auto root = kdtree.BalanceTree();

    // Select random point to search for
    std::srand(std::time(0));
    size_t random_point = std::rand() % num_points;
    auto query_point = pc[random_point];
    // query_point.x -= 0.003;
    // query_point.y += 0.1;
    // query_point.z -= 0.1;
    auto point = kdtree.FindNearestNeighbor(root, query_point);
    printf("Found point (%f,%f,%f) close to query (%f,%f,%f)\n", point.x, point.y, point.z, query_point.x, query_point.y, query_point.z);
    assert((point - query_point).norm2() < 0.5);
    return 0;  
}