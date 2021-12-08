/**
 * @file point.cpp
 * @author Yunfei Ma (ma110@mcmaster.ca)
 * @brief A program for pointer object cpp file
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <cstdarg>
#include <iostream>
#include <string>
#include "point.hpp"

//default constructor make all entries 0s (0,0,0)
template <uint32_t Dimension>
Point<Dimension>::Point()
{
    for (uint32_t i = 0; i < Dimension; i++)
    {
        this->entries[i] = 0;
    }
}

//constructor with input entries
template <uint32_t Dimension>
Point<Dimension>::Point(double arr[Dimension])
{
    for (uint32_t i = 0; i < Dimension; i++)
    {
        this->entries[i] = arr[i];
    }
}

//copy constructor
template <uint32_t Dimension>
Point<Dimension>::Point(const Point<Dimension> &another_point)
{
    for (unsigned i = 0; i < Dimension; i++)
    {
        this->entries[i] = another_point.entries[i];
    }
}

//constructor for the first 3 entry for only 3 dimensional tasks
template <uint32_t Dimension>
Point<Dimension>::Point(double x, double y, double z)
{
    this->entries[0] = x;
    this->entries[1] = y;
    this->entries[2] = z;
}

//assignment operator overload
template <uint32_t Dimension>
Point<Dimension> &Point<Dimension>::operator=(const Point<Dimension> &another_point)
{
    for (uint32_t i = 0; i < Dimension; i++)
    {
        this->entries[i] = another_point.entries[i];
    }
    return *this;
}

//operator for accessing a location at the point based on index without modifications
template <uint32_t Dimension>
double Point<Dimension>::operator[](uint32_t idx) const
{
    if (idx > Dimension)
    {
        cerr << "Points out of range with Dimension [" + to_string(Dimension) + "] and access index + [" + to_string(idx) + "]" << endl;
        exit(1);
    }
    else
    {
        return this->entries[idx];
    }
}

//operator for accessing a location at the point based on index (pass by reference)
template <uint32_t Dimension>
double &Point<Dimension>::operator[](uint32_t idx)
{
    if (idx > Dimension)
    {
        cerr << "Points out of range with Dimension [" + to_string(Dimension) + "] and access index + [" + to_string(idx) + "]" << endl;
        exit(1);
    }
    else
    {
        return this->entries[idx];
    }
}

//operator for checking if 2 points are the same
template <uint32_t Dimension>
bool Point<Dimension>::operator==(const Point<Dimension> another_point) const
{
    for (uint32_t i = 0; i < Dimension; i++)
    {
        if (this->entries[i] == another_point[i])
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

template <uint32_t Dimension>
bool Point<Dimension>::operator!=(const Point<Dimension> another_point) const
{
    return !(*this == another_point);
}

//Important: operator for comparison <: a point is less than another point when there is compairion with the fist different entry, this is very helpful for the task of finding the closest match picture.
template <uint32_t Dimension>
bool Point<Dimension>::operator<(const Point<Dimension> another_point) const
{
    for (uint32_t i = 0; i < Dimension; i++)
    {
        if (this->entries[i] != another_point[i])
        {
            return this->entries[i] < another_point[i];
        }
    }
    return false;
}

//operator overload
template <uint32_t Dimension>
bool Point<Dimension>::operator<=(const Point<Dimension> another_point) const
{
    return (*this < another_point) or (*this == another_point);
}

//operator overload
template <uint32_t Dimension>
bool Point<Dimension>::operator>(const Point<Dimension> another_point) const
{
    return !(*this < another_point);
}

//operator overload
template <uint32_t Dimension>
bool Point<Dimension>::operator>=(const Point<Dimension> another_point) const
{
    return !(*this < another_point) or (*this == another_point);
}

//function to print the point
template <uint32_t Dimension>
string Point<Dimension>::print_point()
{
    string output = "(";
    for (uint32_t i = 0; i < Dimension; i++)
    {
        output = output + to_string(this->entries[i]) + ',';
    }
    output = output.substr(0, output.length() - 1) + ")";
    return output;
}

//set function for modifying the point value
template <uint32_t Dimension>
void Point<Dimension>::set(uint32_t idx, double value)
{
    if (idx >= Dimension)
    {
        cerr << "Points out of range with Dimension [" + to_string(Dimension) + "] and access index + [" + to_string(idx) + "]" << endl;
        exit(1);
    }
    else
    {
        this->entries[idx] = value;
    }
}

//define the point dimension for 3d color space
template class Point<3>;