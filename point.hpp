/**
 * @file point.hpp
 * @author Yunfei Ma (ma110@mcmaster.ca)
 * @brief Define the class Point with k dimensions
 * @version 
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <cstdarg>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/**
 * @brief Point Class
 * 
 * @tparam Dimension The dimension of the space 
 */
template <uint32_t Dimension>
class Point
{
public:
    /**
     * @brief Construct a new Point object (default constructor)
     * 
     */
    Point();

    /**
     * @brief Construct a new Point object 
     * 
     * @param values the array of values for the point
     */
    Point(vector<double> values);

    Point(const Point &another_point);

    /**
     * @brief Construct a new Point object (for first 3 dimensions)
     * 
     * 
     * @param x 
     * @param y 
     * @param z 
     */
    explicit Point(double x, double y, double z);

    /**
     * @brief = operator overload for point class
     * 
     * @param another_point another point for assignment
     * @return Point& 
     */
    Point &operator=(const Point &another_point);

    /**
     * @brief == operator overload for point class
     * 
     * @param another_point another point for comparison
     * @return true 
     * @return false 
     */
    bool operator==(const Point<Dimension> another_point) const;

    /**
     * @brief != operator overload for point class
     * 
     * @param another_point another point for comparison
     * @return A boolean value indicating whether the current Point if equal to another point  
     */
    bool operator!=(const Point<Dimension> another_point) const;

    /**
     * @brief < operator overload for point class
     * 
     * @param another_point another point for comparison
     * @return A boolean value indicating whether the current Point if not equal to another point 
     */
    bool operator<(const Point<Dimension> another_point) const;

    /**
     * @brief <= operator overload for point class
     * 
     * @param another_point another point for comparison
     * @return A boolean value indicating whether the current Point if less than another point 
     */
    bool operator<=(const Point<Dimension> another_point) const;

    /**
     * @brief > operator overload for point class
     * 
     * @param another_point another point for comparison
     * @return A boolean value indicating whether the current Point if less than or equal to another point 
     */
    bool operator>(const Point<Dimension> another_point) const;

    /**
     * @brief >= operator overload for point class
     * 
     * @param another_point another point for comparison
     * @return A boolean value indicating whether the current Point if great than or equal to another point 
     * 
     */
    bool operator>=(const Point<Dimension> another_point) const;

    /**
     * @brief [] operator overload to get the value at specific dimension
     * 
     * @param idx 
     * @return The value of the dimension
     */
    double operator[](uint32_t idx) const;

    /**
     * @brief [] operator overload get the value for non-const version, it can be used to modify the points
     * 
     * @param idx 
     * @return Reference to the value of the Point at a dimension
     */
    double &operator[](uint32_t idx);

    /**
     * @brief set the value of the point to a value
     * 
     * @param idx the index of the point dimension
     * @param value the value to set at this dimension
     */
    void set(uint32_t idx, double value);

    /**
     * @brief Generate the string format output for the point 
     * 
     * @return the string of format of the point
     */
    string print_point();

private:
    /**
     * @brief The value entries for all the dimensions for the point
     * 
     */
    vector<double> entries;
};
