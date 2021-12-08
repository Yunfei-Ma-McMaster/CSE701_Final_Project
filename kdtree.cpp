/**
 * @file kdtree.cpp
 * @author Yunfei Ma (you@domain.com)
 * @brief A program for Kd-tree object cpp file
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <utility>
#include <algorithm>
#include <iostream>
#include "kdtree.hpp"

using namespace std;

bool KDTree::dimension_comparison(const Point<3> &first_point, const Point<3> &second_point, uint32_t dimension) const
{
    //check for valid dimensions
    if (dimension >= 3)
    {
        cerr << "Error: out of bounds dimension access with dimension 3 and access number : [" + to_string(dimension) + "]" << endl;
        exit(1);
    }
    // same on this dimension, use the point comparision operator overload
    if (first_point[dimension] == second_point[dimension])
    {
        return first_point < second_point;
    }
    else
    {
        return (first_point[dimension] < second_point[dimension]);
    }
}

bool KDTree::check_for_new_points_switch(const Point<3> &goal_point, const Point<3> &current_best_point, const Point<3> &potential_point) const
{

    //squared distance for comparing similarity of color
    double current_distance_squared = 0;
    double potential_distance_squared = 0;

    // Add up squares of differences for each dimension
    for (uint32_t i = 0; i < 3; i++)
    {
        current_distance_squared += ((goal_point[i] - current_best_point[i]) * (goal_point[i] - current_best_point[i]));
        potential_distance_squared += ((goal_point[i] - potential_point[i]) * (goal_point[i] - potential_point[i]));
    }

    //if the same distance squared, compare the points based on operator overload
    if (current_distance_squared == potential_distance_squared)
    {
        return potential_point < current_best_point;
    }

    return potential_distance_squared < current_distance_squared;
}

uint32_t KDTree::quick_select_helper(vector<Point<3>> &all_color_space_points, uint32_t dimension, uint32_t left, uint32_t right, uint32_t index_pivot_point)
{
    //hold the pivot point value
    Point<3> pivot_point_value = all_color_space_points[index_pivot_point];

    //swap pivot value and end of list
    Point<3> temp = all_color_space_points[index_pivot_point];
    all_color_space_points[index_pivot_point] = all_color_space_points[right];
    all_color_space_points[right] = temp;

    //index for store the value
    uint32_t new_index_value = left;

    //select points less than the pivot values
    for (uint32_t i = left; i < right; i++)
    {
        if (dimension_comparison(all_color_space_points[i], pivot_point_value, dimension))
        {
            //swap the values
            temp = all_color_space_points[new_index_value];
            all_color_space_points[new_index_value] = all_color_space_points[i];
            all_color_space_points[i] = temp;
            new_index_value++;
        }
    }

    //last iteration
    temp = all_color_space_points[new_index_value];
    all_color_space_points[new_index_value] = all_color_space_points[right];
    all_color_space_points[right] = temp;

    return new_index_value;
}

Point<3> &KDTree::quick_select(vector<Point<3>> &all_color_space_points, uint32_t dimension, uint32_t left, uint32_t right, uint32_t k)
{
    //check if the algorithm start with the optimal left equals right
    if (left == right)
    {
        return all_color_space_points[left];
    }

    //index for holding the pivot
    uint32_t index_pivot_point = k;

    //calling the helper function for the new index based on partitioning
    index_pivot_point = quick_select_helper(all_color_space_points, dimension, left, right, index_pivot_point);

    //recursion based on the conditions until the whole points are sorted
    if (k == index_pivot_point)
    {
        return all_color_space_points[k];
    }
    //recursion on the left
    else if (k < index_pivot_point)
    {
        return quick_select(all_color_space_points, dimension, left, index_pivot_point - 1, k);
    }
    //recursion on the right
    else
    {
        return quick_select(all_color_space_points, dimension, index_pivot_point + 1, right, k);
    }
}

KDTree::KDTreeNode *KDTree::Constructor_Helper(vector<Point<3>> &color_space_points, uint32_t dimension, uint32_t left, uint32_t right)
{
    //check for the input value is valid for constructor
    if (color_space_points.empty() or right >= color_space_points.size() or left >= color_space_points.size())
    {
        return nullptr;
    }
    // Check if parameters are in bounds
    if (left > right)
    {
        return nullptr;
    }

    //set median to be the pivot index
    uint32_t median_idx = (left + right) / 2;

    //create new subroot based on the sorted color space points
    KDTreeNode *subroot = new KDTreeNode(quick_select(color_space_points, dimension % 3, left, right, median_idx));

    //add the size of the tree
    size += 1;

    //change to a new dimension
    dimension++;

    //recursion construction on both sides of the tree roots
    subroot->left = Constructor_Helper(color_space_points, dimension, left, median_idx - 1);
    subroot->right = Constructor_Helper(color_space_points, dimension, median_idx + 1, right);

    return subroot;
}

KDTree::KDTree(const vector<Point<3>> &new_color_points)
{
    size = 0;

    //new vector to hold a copy of the new color points
    vector<Point<3>> points_holder;

    //copy all the color points
    points_holder.assign(new_color_points.begin(), new_color_points.end());

    //constructor a new kd-tree using the helper constructor
    root = Constructor_Helper(points_holder, 0, 0, (uint32_t)(points_holder.size() - 1));
}

KDTree::KDTree(const KDTree &another_tree)
{
    copy(this->root, another_tree.root);
    size = another_tree.size;
}

const KDTree &KDTree::operator=(const KDTree &another_tree)
{

    deconstruct_kd_helper(root);
    copy(this->root, another_tree.root);
    size = another_tree.size;
    return *this;
}

KDTree::~KDTree()
{
    deconstruct_kd_helper(root);
}

Point<3> KDTree::find_nearest_point(const Point<3> &new_point) const
{
    //call the helper function
    return find_nearest_point_helper(root, new_point, 0);
}

Point<3> KDTree::find_nearest_point_helper(KDTreeNode *subroot, const Point<3> &new_point, uint32_t dimension) const
{
    //points to hold the current best color space point
    Point<3> current_best_point = subroot->point;

    //flag true on right false on left
    bool flag_side = true;

    // Check bounds for end of the tree
    if (subroot->left == nullptr && subroot->right == nullptr)
    {
        return subroot->point;
    }

    // check the travesal on the left subtree
    if (dimension_comparison(new_point, subroot->point, dimension))
    {
        // if left subtree is empty tree, traverse on the right
        if (subroot->left == nullptr)
        {
            current_best_point = find_nearest_point_helper(subroot->right, new_point, (dimension + 1) % 3);
        }
        // left side
        else
        {
            current_best_point = find_nearest_point_helper(subroot->left, new_point, (dimension + 1) % 3);
        }
        // Set left flag to true for right
        flag_side = true;
    }
    // if right subtree is empty tree, traverse on the left
    else
    {
        // if right subtree is empty tree, traverse on the left
        if (subroot->right == nullptr)
        {
            current_best_point = find_nearest_point_helper(subroot->left, new_point, (dimension + 1) % 3);
        }
        else
        {
            current_best_point = find_nearest_point_helper(subroot->right, new_point, (dimension + 1) % 3);
        }
        flag_side = false;
    }

    // check to change to the current best point
    if (check_for_new_points_switch(new_point, current_best_point, subroot->point))
    {
        current_best_point = subroot->point;
    }

    // Calculate square radius of closest point
    double square_of_radius = 0;
    for (uint32_t i = 0; i < 3; i++)
    {
        square_of_radius += (new_point[i] - current_best_point[i]) * (new_point[i] - current_best_point[i]);
    }

    // Calculate the split of the new point
    double split_distance = subroot->point[dimension] - new_point[dimension];
    split_distance = split_distance * split_distance;

    // Check if we need to traverse the other subtree
    if (split_distance <= square_of_radius)
    {
        KDTreeNode *subroot_testing;
        if (flag_side)
        {
            subroot_testing = subroot->right;
        }
        else
        {
            subroot_testing = subroot->left;
        }

        //if there is more subtrees, recursion
        if (subroot_testing != nullptr)
        {
            Point<3> anther_best_point = find_nearest_point_helper(subroot_testing, new_point, (dimension + 1) % 3);

            // Replace current best point
            if (check_for_new_points_switch(new_point, current_best_point, anther_best_point))
            {
                current_best_point = anther_best_point;
            }
        }
    }

    return current_best_point;
}

// Helper function for destructor and = operator

void KDTree::deconstruct_kd_helper(KDTreeNode *subroot)
{
    if (subroot == nullptr)
        return;
    if (subroot->left != nullptr)
        deconstruct_kd_helper(subroot->left);
    if (subroot->right != nullptr)
        deconstruct_kd_helper(subroot->right);
    delete subroot;
    subroot = nullptr;
}

// Helper function for copy constructor and = operator

void KDTree::copy(KDTreeNode *subroot, KDTreeNode *another_subroot)
{
    //set a new root
    subroot = new KDTreeNode();
    //copy the color info for this node
    subroot->point = another_subroot->point;

    //copy the subtree info
    copy(subroot->left, another_subroot->left);
    copy(subroot->right, another_subroot->right);
}