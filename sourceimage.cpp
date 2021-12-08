/**
 * @file sourceimage.cpp
 * @author Yunfei Ma (ma110@mcmaster.ca)
 * @brief A program for source image object
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include "sourceimage.hpp"
#include "point.hpp"

const uint64_t CANVAS_WIDTH = 50;
SourceImage::SourceImage(string name, string filename_L, string filename_U, string filename_V)
{
    uint64_t size = CANVAS_WIDTH;
    this->name_of_the_image = name;
    this->total_value_of_the_image = 0;

    //set the size of the vector first
    this->color_sub_spaces.resize(size, vector<Point<3>>(size));
    //create a pointer to the file
    ifstream fin_L;
    ifstream fin_U;
    ifstream fin_V;

    //line to hold the row
    string line_L;
    string line_U;
    string line_V;

    //open the file
    fin_L.open(filename_L);
    fin_U.open(filename_U);
    fin_V.open(filename_V);

    if (!fin_L.is_open())
    {
        cerr << "Error: Failed to open file : [" + filename_L + "] in the construction of source image. Please check if the name [" + name + "] from user input file [input.txt] is correct or exist in the database in folder [sourceimages]" << endl;
        exit(1);
    }
    else if (!fin_U.is_open())
    {
        cerr << "Error: Failed to open file : [" + filename_U + "] in the construction of source image. Please check if the name [" + name + "] from user input file [input.txt] is correct or exist in the data base in folder [sourceimages]" << endl;
        exit(1);
    }
    else if (!fin_V.is_open())
    {
        cerr << "Error: Failed to open file : [" + filename_V + "] in the construction of source image. Please check if the name [" + name + "] from user input file [input.txt] is correct or exist in the data base in folder [sourceimages]" << endl;
        exit(1);
    }
    else
    {
        std::cout << "Successfully open source image color space files for [" + name + "]" << endl;

        //define the number of rows
        uint32_t row = 0;

        //iterator throught the file by lines
        while ((!fin_L.eof()) and (!fin_U.eof()) and (!fin_V.eof()))
        {
            //read the line
            getline(fin_L, line_L);
            getline(fin_U, line_U);
            getline(fin_V, line_V);

            //if it is the first row, skip because it is just the variable names
            if (row == 0)
            {
                row++;
                continue;
            }

            //initialize the column number
            uint32_t col = 0;

            //split the string according to delimiter
            uint64_t start_L = 0;
            uint64_t end_L = line_L.find(',');

            uint64_t start_U = 0;
            uint64_t end_U = line_U.find(',');

            uint64_t start_V = 0;
            uint64_t end_V = line_V.find(',');

            while (start_L < line_L.size())
            {
                //hold the entry in the string

                //cout << line_V.substr(start_V, end_V - start_V) << endl;
                double entry_L = std::stod(line_L.substr(start_L, end_L - start_L));
                double entry_U = std::stod(line_U.substr(start_U, end_U - start_U));
                double entry_V = std::stod(line_V.substr(start_V, end_V - start_V));

                color_sub_spaces[row - 1][col] = Point<3>(entry_L, entry_U, entry_V);

                //change to next entry
                start_L = end_L + 1;
                start_U = end_U + 1;
                start_V = end_V + 1;

                end_L = line_L.find(",", start_L);
                end_U = line_U.find(",", start_U);
                end_V = line_V.find(",", start_V);

                if (end_L == string::npos)
                {
                    end_L = line_L.size();
                    end_U = line_U.size();
                    end_V = line_V.size();
                }

                col++;
            }

            row++;
        }
    }

    //close the file
    fin_L.close();
    fin_U.close();
    fin_V.close();
}

uint32_t SourceImage::get_image_value()
{
    return this->total_value_of_the_image;
}

string SourceImage::get_image_name()
{
    return this->name_of_the_image;
}

Point<3> &SourceImage::get_tile_LUV_color(uint32_t row, uint32_t col)
{
    uint32_t size = CANVAS_WIDTH;
    if (row > size or col > size)
    {
        cerr << "Error, index row or col out of bound when accessing Source Image!" << endl;
        exit(1);
    }

    return color_sub_spaces[row][col];
}

void SourceImage::reset_image_value()
{
    this->total_value_of_the_image = 0;
}

void SourceImage::add_image_value(uint32_t price_of_painting)
{
    this->total_value_of_the_image += price_of_painting;
}