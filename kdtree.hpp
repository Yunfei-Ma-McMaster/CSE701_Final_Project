/**
 * @file kdtree.hpp
 * @author Yunfei Ma (ma110@mcmaster.ca)
 * @brief A program for Kd-tree object, header file
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <vector>
#include "point.hpp"

using namespace std;

class KDTree
{
private:
    /**
     * @brief KD Tree Node stucture for a KD tree
     * 
     */
    struct KDTreeNode
    {
        Point<3> point;
        KDTreeNode *left, *right;

        /**
         * @brief Construct a new KDTreeNode structure (default constructor)
         * 
         */
        KDTreeNode() : point(), left(nullptr), right(nullptr) {}

        /**
         * @brief Construct a new KDTreeNode structure
         * 
         * @param point 3 dimensional color space point
         */
        KDTreeNode(const Point<3> &point) : point(point), left(nullptr), right(nullptr) {}
    };

    /**
     * @brief Root node of the tree
     * 
     */
    KDTreeNode *root = nullptr;

    /**
     * @brief Size of the tree (number of KD tree nodes)
     * 
     */
    uint64_t size;

    /**
     * @brief Helper function for constructing KD tree 
     * 
     * @param color_space_points The input 3d color space base on LUV standards
     * @param dimension the current dimension in the color space
     * @param left left child recursively assigned based on the right index is set left median
     * @param right right child recursively assigned based on the left index is set right median
     * @return KDTreeNode* Pointer to the KDtree node of root of the next iteration
     */
    KDTreeNode *Constructor_Helper(vector<Point<3>> &color_space_points, uint32_t dimension, uint32_t left, uint32_t right);

    /**
     * @brief Helper function of finding the nearest point based on Euclidean distance
     * 
     * @param subroot the subroot of the KD tree
     * @param new_point the new point to check for nearest point
     * @param dimension the current dimension of the color space for investigation
     * @return Point<3> Return the current best point, whether it is the new point or the original best point
     */
    Point<3> find_nearest_point_helper(KDTreeNode *subroot, const Point<3> &new_point, uint32_t dimension) const;

    /**
     * @brief Helper function for quick select algorithm
     * 
     * @param all_color_space_points A vector of points in color space for the algorithm 
     * @param dimension the current dimension of color space
     * @param left left part index
     * @param right right part index
     * @param index_pivot_point index of the pivot point
     * @return uint32_t Index of the kth smallest element based on quick sort
     */
    uint32_t quick_select_helper(vector<Point<3>> &all_color_space_points, uint32_t dimension, uint32_t left, uint32_t right, uint32_t index_pivot_point);

    /**
     * @brief Quick select algorithm for the k-th smallest element
     * 
     * @param all_color_space_points  A vector of points in color space for the algorithm 
     * @param dimension the current dimension of the color space point
     * @param left left part index
     * @param right right part index
     * @param k k for k-th smallest element
     * @return Point<3>& The k-smallest point based on the algorithm in the input color space points
     */
    Point<3> &quick_select(vector<Point<3>> &all_color_space_points, uint32_t dimension, uint32_t left, uint32_t right, uint32_t k);

public:
    /**
     * @brief Compare the points value in the designated dimension, when tie, uses the point comparison operator overload to compare the points instead
     * 
     * @param first_point the first point for comparison
     * @param second_point the second point for comparison
     * @param dimension the dimesion for comparison
     * @return true First point at the dimesion is larger
     * @return false First point at the dimesion is smaller
     */
    bool dimension_comparison(const Point<3> &first_point, const Point<3> &second_point, uint32_t dimension) const;

    /**
     * @brief Checking for new point in the color space if it can be switched with current best color space
     * 
     * @param goal_point the input color space for reference from source image
     * @param current_best_point the current best color space from tile image
     * @param potential_point potential best point from the tile image
     * @return true If the points can be switched to potential point
     * @return false If keep the current best point
     */
    bool check_for_new_points_switch(const Point<3> &goal_point, const Point<3> &current_best_point, const Point<3> &potential_point) const;

    /**
     * @brief Construct a new KDTree object
     * 
     * @param new_color_points The color space points input for constructing the tree
     */
    KDTree(const vector<Point<3>> &new_color_points);

    /**
     * @brief Copy Constructor: Construct a new KDTree object
     * 
     * @param another_tree a reference to anthoer kd tree
     */
    KDTree(const KDTree &another_tree);

    /**
     * @brief Operator overload for = to assign the kd tree and to another
     * 
     * @param another_tree a reference to another kd tree
     * @return KDTree const& 
     */

    /**
     * @brief Destroy the KDTree object
     * 
     */
    ~KDTree();

    /**
     * @brief Destructor helper function: recursively delete the kd tree nodes
     * 
     * @param subroot the node input where all the leaves including the subroot will be destroyed
     */
    void deconstruct_kd_helper(KDTreeNode *subroot);

    /**
     * @brief Recursively copy construct a kd tree
     * 
     * @param subroot subroot of a kd tree for construction
     * @param another_subroot subroot of the tree to be copied
     */
    void copy(KDTreeNode *subroot, KDTreeNode *another_subroot);

    /**
     * @brief Operator overload to assign kd tree
     * 
     * @param another_tree the kd tree to be assigned to
     * @return KDTree const& the assigned kd tree to the left hand side
     */
    KDTree const &operator=(const KDTree &another_tree);

    /**
     * @brief Find the closet color space point for new point (from source image)
     * 
     * @param new_point the new point for investigation
     * @return Point<3> The nearest color space point for this new point from input
     */
    Point<3> find_nearest_point(const Point<3> &new_point) const;
};