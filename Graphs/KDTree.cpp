#include "KDTree.h"

#include <algorithm>
#include <cmath>
#include <cassert>
#include <iostream>

namespace graph {
template <int D>
KDTree<D>::KDTree() {}

template <int D>
KDTree<D>::KDTree(const std::vector<geometry::Point3D>& points) {
    for (const auto& p : points) {
        points_.push_back(p);
    }
}

template <int D>
void KDTree<D>::AddPoint(const geometry::Point3D& point) {
    points_.push_back(point);
}

template <int D>
KDNode* KDTree<D>::BalanceTree() {
    if (points_.empty()) {
        return nullptr;
    }

    // Reserve space for the tree nodes
    nodes_.reserve(points_.size());
    
    std::function<KDNode*(size_t,size_t,int)> build_tree = [&](size_t begin, size_t end, int axis = 0) -> KDNode* {
        if (begin >= end) {
            // invalid search range
            return nullptr;
        }
        auto comp = [&](geometry::Point3D a, geometry::Point3D b) { 
            return a[axis] < b[axis]; 
        };

        size_t n = begin + (end - begin) / 2;
        std::nth_element(points_.begin() + begin, points_.begin() + n, points_.begin() + end, comp);
        axis = (axis + 1) % D;

        auto node_ptr = AddNode(points_[n]);
        node_ptr->left = build_tree(begin, n, axis);
        node_ptr->right = build_tree(n+1, end, axis);
        std::cout << "Created node " << node_ptr->point << " @ " << node_ptr
                  << " w/ left ptr @ " << node_ptr->left 
                  << " and right ptr @ " << node_ptr->right << std::endl; 
        return node_ptr;
    };

    return build_tree(0, points_.size(), 0);
}

template <int D>
KDNode* KDTree<D>::AddNode(const geometry::Point3D& point) {
    nodes_.push_back(KDNode{point, nullptr, nullptr});
    return &nodes_.back();
}

template <int D>
void KDTree<D>::RemovePoint(const geometry::Point3D& point) {}

template <int D>
geometry::Point3D KDTree<D>::FindNearestNeighbor(const KDNode* root, const geometry::Point3D& point) {
    printf("Search for node (%f,%f,%f)\n", point.x, point.y, point.z);
    const KDNode* ptr = root;
    const KDNode* last_valid_ptr = nullptr;
    int axis = 0;
    constexpr double threshold = 0.01;
    while (ptr) {
        const double dist = (ptr->point - point).norm2();
        std::cout << "Compare against point " << ptr->point << " distance: " << dist << std::endl;
        if (dist < threshold) {
            printf("Found close point ...\n");
            return ptr->point;
        }
        double df = 0.;
        if (axis == 0) {
            df = ptr->point.x - point.x;
        } else if (axis == 1) {
            df = ptr->point.y - point.y;
        } else {
            df = ptr->point.z - point.z;
        }
        axis = (axis + 1) % D;
        last_valid_ptr = ptr;
        ptr = (df > 0) ? ptr->left : ptr->right;
    }   
    return last_valid_ptr->point;
}
}

// Note: compiler needs to have access to entire template definition, not just the signature.
// template class graph::KDTree<2>;
template class graph::KDTree<3>;
