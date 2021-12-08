/**
 * @file tileimage.hpp
 * @author Yunfei Ma (ma110@mcmaster.ca)
 * @brief A program for tile image object header file
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <string>
#include "point.hpp"

using namespace std;

class TileImage
{
private:
    /**
     * @brief the name of the painting for tile image
     * 
     */
    string name_of_painting;

    /**
     * @brief the price of the painting tile image
     * 
     */
    uint32_t price_of_the_painting;

    /**
     * @brief the average color of the painting in LUV color space
     * 
     */
    Point<3> average_color_of_the_painting;

public:
    /**
     * @brief Construct a new Tile Image object
     * 
     */
    TileImage();

    /**
     * @brief Construct a new Tile Image object
     * 
     * @param name the name of the painting
     * @param price the price of the painting
     * @param color_space the color space of the painting
     */
    TileImage(string name, uint32_t price, const Point<3> &color_space);

    /**
     * @brief Get the name of the tile image 
     * 
     * @return string the name of the painting
     */
    string get_name();

    /**
     * @brief Get the price of the tile image
     * 
     * @return uint32_t the price of the tile image
     */
    uint32_t get_price();

    /**
     * @brief Get the LUV color space of the tile image
     * 
     * @return Point<3>& the LUV color space of the average color of the painting
     */
    Point<3> &get_LUV_color();

    /**
     * @brief Set the name of the tile image
     * 
     * @param name the name to be changed to
     */
    void set_name(string name);

    /**
     * @brief Set the price of the tile image
     * 
     * @param price the price of the tile image
     */
    void set_price(uint32_t price);

    /**
     * @brief Set the LUV color space of the tile image
     * 
     * @param point the LUV color space point
     */
    void set_LUV_color(const Point<3> &point);
};