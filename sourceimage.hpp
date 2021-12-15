/**
 * @file sourceimage.hpp
 * @author Yunfei Ma (ma110@mcmaster.ca)
 * @brief  A program for source image object header file
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <string>
#include <vector>
#include "point.hpp"

using namespace std;

class SourceImage
{
private:
    /**
     * @brief The name of the source image
     * 
     */
    string name_of_the_image;

    /**
     * @brief The total value of the source image based on the construction from paintings
     * 
     */
    uint32_t total_value_of_the_image;

    /**
     * @brief The color spaces of the cutting the source image to small squares
     * 
     */
    vector<vector<Point<3>>> color_sub_spaces;

public:
    /**
     * @brief Construct a new Source Image object from LUV color space files
     * 
     * @param name the name of the painting
     * @param filename_L the file location for 3d color space information L 
     * @param filename_U the file location for 3d color space information U 
     * @param filename_V the file location for 3d color space information V 
     */
    SourceImage(string name, string filename_L, string filename_U, string filename_V);

    /**
     * @brief Get the image value of the source image
     * 
     * @return uint32_t the market value of the image calculated from the sum of all paintings to generate the mosaic image
     */
    uint32_t get_image_value();

    /**
     * @brief Get the image name 
     * 
     * @return string The name of the image
     */
    string get_image_name();

    /**
     * @brief Get the tile LUV color object
     * 
     * @param row the row of the source image color space location
     * @param col the column of the source image color space location
     * @return Point<3>& The color space of the tile space for the source image
     */
    Point<3> &get_tile_LUV_color(uint32_t row, uint32_t col);

    /**
     * @brief Reset the image market price to 0
     * 
     */
    void reset_image_value();

    /**
     * @brief Add the market value to the source image based on the price of the painting from the tileimage
     * 
     * @param price_of_painting 
     */
    void add_image_value(uint32_t price_of_painting);
};