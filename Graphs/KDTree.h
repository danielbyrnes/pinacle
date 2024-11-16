#pragma once

#include <span>
#include <vector>
#include "../Geometry/Point3D.h"

// Note: only D = 3 supported at the moment. Need to generalize to higher dimensions
namespace graph {

// Data required for each node in KDTree
struct KDNode {
    geometry::Point3D point;
    KDNode* left;
    KDNode* right;
};

template <int D = 3>
class KDTree {
    public:
        // Default constructor
        KDTree();
        // Instantiate KDTree with all the points up front
        KDTree(const std::vector<geometry::Point3D>& points);

        void AddPoint(const geometry::Point3D& point);

        // Balances the KDTree from the existing points and returns root
        KDNode* BalanceTree();

        void RemovePoint(const geometry::Point3D& point);

        geometry::Point3D FindNearestNeighbor(const KDNode* root, const geometry::Point3D& point);
    private:
        KDNode* AddNode(const geometry::Point3D& point);

        std::vector<geometry::Point3D> points_;
        std::vector<KDNode> nodes_;
};
}