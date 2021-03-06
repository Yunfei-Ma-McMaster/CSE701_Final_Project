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
#include <vector>
#include "point.hpp"

template <uint32_t Dimension>
Point<Dimension>::Point()
{
    this->entries.resize(0);
    for (uint32_t i = 0; i < Dimension; i++)
    {
        this->entries.push_back(0.0);
    }
}

template <uint32_t Dimension>
Point<Dimension>::Point(vector<double> values)
{
    this->entries.resize(0);
    for (uint32_t i = 0; i < Dimension; i++)
    {
        this->entries.push_back(values[i]);
    }
}

template <uint32_t Dimension>
Point<Dimension>::Point(const Point<Dimension> &another_point)
{
    this->entries.resize(0);
    for (unsigned i = 0; i < Dimension; i++)
    {
        this->entries.push_back(another_point[i]);
    }
}

template <uint32_t Dimension>
Point<Dimension>::Point(double x, double y, double z)
{
    this->entries.resize(0);
    this->entries.push_back(x);
    this->entries.push_back(y);
    this->entries.push_back(z);
}

template <uint32_t Dimension>
Point<Dimension> &Point<Dimension>::operator=(const Point<Dimension> &another_point)
{
    this->entries.resize(0);
    for (uint32_t i = 0; i < Dimension; i++)
    {
        this->entries.push_back(another_point.entries[i]);
    }
    return *this;
}

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

template <uint32_t Dimension>
bool Point<Dimension>::operator<=(const Point<Dimension> another_point) const
{
    return (*this < another_point) or (*this == another_point);
}

template <uint32_t Dimension>
bool Point<Dimension>::operator>(const Point<Dimension> another_point) const
{
    return !(*this < another_point);
}

template <uint32_t Dimension>
bool Point<Dimension>::operator>=(const Point<Dimension> another_point) const
{
    return !(*this < another_point) or (*this == another_point);
}

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

// Define the point dimension for 3d color space
template class Point<3>;