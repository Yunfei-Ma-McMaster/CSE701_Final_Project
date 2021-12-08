/**
 * @file tileimage.cpp
 * @author Yunfei Ma (ma110@mcmaster.ca)
 * @brief A program of tile image object cpp file
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "tileimage.hpp"
#include "point.hpp"

TileImage::TileImage()
{
    this->name_of_painting = "";
    this->price_of_the_painting = 0;
    this->average_color_of_the_painting = Point<3>(0, 0, 0);
}

TileImage::TileImage(string name, uint32_t price, const Point<3> &color_space)
{
    this->name_of_painting = name;
    this->price_of_the_painting = price;
    this->average_color_of_the_painting = color_space;
}

string TileImage::get_name()
{
    return this->name_of_painting;
}

uint32_t TileImage::get_price()
{
    return this->price_of_the_painting;
}

Point<3> &TileImage::get_LUV_color()
{
    return average_color_of_the_painting;
}

void TileImage::set_name(string name)
{
    this->name_of_painting = name;
}

void TileImage::set_price(uint32_t price)
{
    this->price_of_the_painting = price;
}

void TileImage::set_LUV_color(const Point<3> &point)
{
    //add exception later
    this->average_color_of_the_painting = point;
}