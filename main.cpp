/**
 * @file main.cpp
 * @author Yunfei Ma (ma110@mcmaster.ca)
 * @brief main program for generating the mosaic image information
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstdarg>
#include <map>
#include <filesystem>

//#include "point.hpp"
#include "sourceimage.hpp"
#include "tileimage.hpp"
#include "kdtree.hpp"

using namespace std;

/**
 * @brief The number of tile images for this program
 * 
 */
const uint64_t TILE_NUM = 54;

/**
 * @brief the canvas width for dividing the source image from input file is set to be 50x50
 * 
 */
const uint64_t CANVAS_WIDTH = 50;

/**
 * @brief function for checking if a charater is digit. Input a charater and output boolean for yes or no
 * 
 * @param chr input charactor value
 * @return true if the input can be modified to a digit
 * @return false if the input cannot be modified to a digit
 */
bool isDigit(const char &chr)
{
    if (chr >= '0' and chr <= '9')
    {
        return true;
    }
    return false;
}

/**
 * @brief check if the whole string contains only digits and maximum one decimal point, in other words, check it the string can be converted to a number. Input a string output a boolean for yes or no
 * 
 * @param word the input string 
 * @return true if the string can be converted to number
 * @return false if the string cannot be converted to number
 */
bool isNumber(const string &word)
{

    //flag for having decimal point
    bool decimal_point_flag = false;
    bool minus_sign_flag = false;

    //check for every char
    for (char const &c : word)
    {
        if (isDigit(c))
        {
            continue;
        }
        else
        {
            if (c == '.' and decimal_point_flag == false)
            {
                decimal_point_flag = true;
            }
            else if (c == '-' and minus_sign_flag == false)
            {
                minus_sign_flag = true;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief delete all files in a directory
 * 
 * @param dir_path the folder for the files to be deleted
 */
void delete_dir_content(const std::filesystem::path &dir_path)
{
    for (auto &path : std::filesystem::directory_iterator(dir_path))
    {
        std::filesystem::remove_all(path);
    }
}

/**
 * @brief fill up the tile image information by reading csv files from the input
 * 
 * @param filename_painting the input file location for painting/tile image csv file
 * @param filename_avg_color the input file location for painting LUV color space file
 * @param tiles the tile image object vectors to hold the values from the inputs
 */
void read_csv_tileimage(string filename_painting, string filename_avg_color, vector<TileImage> &tiles)
{
    //clear the content from the tileImages
    tiles.clear();

    //set the size for the tiles image based on the known number of tile images
    uint64_t tile_numbers = TILE_NUM;
    tiles.resize(tile_numbers);

    //create a pointer to the files
    ifstream fin;
    ifstream fin_avg_color;

    //line to hold the rows
    string line;
    string line_avg_color;

    //open the file
    fin.open(filename_painting);
    fin_avg_color.open(filename_avg_color);

    //check if the file is successfully open
    if (!fin.is_open())
    {
        cerr << "Error: Failed to open file : [" + filename_painting + "] " << endl;
        exit(1);
    }
    else if (!fin_avg_color.is_open())
    {
        cerr << "Error: Failed to open file : [" + filename_avg_color + "] " << endl;
    }
    else
    {
        //print the user-end info
        std::cout << "Successfully open the file [" + filename_painting + "]  and [" + filename_avg_color + "] for loading tile images information!" << endl;

        //define the number of rows
        uint32_t row = 0;

        //iterator throught the file by lines
        while (!fin.eof())
        {
            //read the line
            getline(fin, line);
            getline(fin_avg_color, line_avg_color);

            //std::cout << line << endl;

            //if it is the first row, skip because it is just the variable names
            if (row == 0)
            {
                row++;
                continue;
            }

            //initialize the column number
            uint32_t col = 0;
            uint32_t col_avg_color = 0;

            //split the string according to delimiter
            uint64_t start = 0;
            uint64_t end = line.find(',');
            uint64_t start_avg_color = 0;
            uint64_t end_avg_color = line_avg_color.find(',');

            //variables to hold the values for initializing the tileimage
            string name_of_tile = "";
            uint32_t price_of_tile = 0;
            double color_space_L = 0;
            double color_space_U = 0;
            double color_space_V = 0;

            //loop for the painting information file
            while (start < line.size())
            {
                //hold the entry in the string
                string entry = line.substr(start, end - start);

                //flag for "A,B" representation
                bool quotation_flag = false;

                //std::cout<< entry << endl;

                //check is the entry contains \" indicating the entries have ','
                if (entry.find('\"') != string::npos)
                {
                    // ignore the first \"
                    start = start + 1;
                    end = line.find('\"', start);
                    entry = line.substr(start, end - start);
                    quotation_flag = true;
                }

                //iterator through the csv to load the data
                //col == 0 -> name of the painting
                if (col == 0)
                {
                    if (entry == "" or entry == "NA")
                    {
                        cerr << "Error: Missing or invalid input from [" + filename_painting + "] at row [" + to_string(row) + "]  and column + [" + to_string(col) + "](painting name)";
                        exit(1);
                    }
                    else
                    {
                        //std::cout << "Name of art : " + entry << endl;
                        //set the name of the tileimage
                        name_of_tile = entry;
                    }
                }
                //col == 3 -> adjusted price for the painting
                else if (col == 3)
                {
                    if (!isNumber(entry))
                    {
                        cerr << "Error : invalid input from [" + filename_painting + "] at row [" + to_string(row) + "] and column + [" + to_string(col) + "](adjusted price)";
                        exit(1);
                    }
                    else
                    {
                        //std::cout << "adjusted: price: " + entry << endl;
                        price_of_tile = std::stoi(entry);
                    }
                }

                //modify the start and end for the next loop
                if (quotation_flag)
                {
                    start = end + 2;
                }
                else
                {
                    start = end + 1;
                }
                end = line.find(",", start);

                //check for if reach the end
                if (end == string::npos)
                {
                    end = line.size();
                }

                //add column number
                col++;
            }

            //loop for the LUV color space file
            while (start_avg_color < line_avg_color.size())
            {
                string entry_avg_color = line_avg_color.substr(start_avg_color, end_avg_color - start_avg_color);

                //std::cout << entry_avg_color << endl;

                //colorspace L
                if (col_avg_color == 0)
                {
                    if (!isNumber(entry_avg_color))
                    {
                        cerr << "Error : invalid input from [" + filename_avg_color + "] at row [" + to_string(row) + "] and column + [" + to_string(col_avg_color) + "](L)";
                        exit(1);
                    }
                    else
                    {
                        //hold the value for L
                        //std::cout << entry_avg_color << endl;
                        color_space_L = std::stod(entry_avg_color);
                    }
                }
                //colorspace U
                else if (col_avg_color == 1)
                {
                    if (!isNumber(entry_avg_color))
                    {
                        cerr << "Error : invalid input from [" + filename_avg_color + "] at row [" + to_string(row) + "] and column + [" + to_string(col_avg_color) + "](U)";
                        exit(1);
                    }
                    else
                    {
                        //hold the value for U
                        //std::cout << entry_avg_color << endl;
                        color_space_U = std::stod(entry_avg_color);
                    }
                }
                //colorspace V
                else if (col_avg_color == 2)
                {
                    if (!isNumber(entry_avg_color))
                    {
                        cerr << "Error : invalid input from [" + filename_avg_color + "] at row [" + to_string(row) + "] and column + [" + to_string(col_avg_color) + "](V)";
                        exit(1);
                    }
                    else
                    {
                        //hold the value for V
                        //std::cout << entry_avg_color << endl;
                        color_space_V = std::stod(entry_avg_color);
                    }
                }

                //change to the next entry
                start_avg_color = end_avg_color + 1;

                end_avg_color = line_avg_color.find(',', start_avg_color);

                if (end_avg_color == string::npos)
                {
                    end_avg_color = line_avg_color.size();
                }

                //add the col number
                col_avg_color++;
            }

            //initialize the color space point
            Point<3> color_space_tile(color_space_L, color_space_U, color_space_V);

            //initialize the TileImage
            TileImage tileimage(name_of_tile, price_of_tile, color_space_tile);

            //add the tileimage to the tiles vector
            tiles[row - 1] = tileimage;

            //add row number
            row++;

            //std::cout << to_string(row) << endl;
        }
    }

    std::cout << "Successfully loaded the tileimage information into the program. " << endl;
    //close the file
    fin.close();
}

/**
 * @brief Generate the mosaic csv file of all the source images from the tile images
 * 
 * @param source the source images for processing
 * @param tiles the tile images/paintings to generated the source image mosaics
 */
void generate_mosaic_csv(SourceImage &source, vector<TileImage> &tiles)
{
    //initialize the point vector to hold the color space with predefined length
    vector<Point<3>> all_tile_image_LUV_color_points(TILE_NUM);

    //map for one to one correspondence of color space to the pointer to the tileimages
    map<Point<3>, TileImage *> map_color_tileimage;

    //initialize the index to count the index in the tileimages when iterating
    uint32_t idx = 0;

    for (vector<TileImage>::iterator iter = tiles.begin(); iter != tiles.end(); iter++)
    {
        //Point to hold the tile color space
        Point<3> point_tile_color_space = iter->get_LUV_color();
        //put the tiles color space information in the predefined vector
        all_tile_image_LUV_color_points[idx] = point_tile_color_space;

        //add index by 1
        idx++;

        //create map link between the point and the tileimage
        map_color_tileimage[point_tile_color_space] = &*iter;
    }

    //create a kd-tree of the colors space of tileimage
    KDTree kdTree_avg_color(all_tile_image_LUV_color_points);

    //reset the value for source image
    source.reset_image_value();

    //get the name of the source image
    string name_of_image = source.get_image_name();

    //Open the file for writing the information for new mosaic
    ofstream output_file("outputImageCSV/" + name_of_image + ".csv");

    //iterator and find the best tile image for the whole mosaic
    for (uint32_t i = 0; i < CANVAS_WIDTH; i++)
    {
        //the line to hold the value for writing the output
        string line = "";
        for (uint32_t j = 0; j < CANVAS_WIDTH; j++)
        {
            //Hold the value for color in the specific region of the source image
            Point<3> source_region_color_space = source.get_tile_LUV_color(i, j);

            //Find the nearest neighbor points for the color space in the source region
            Point<3> best_tile_color_space = kdTree_avg_color.find_nearest_point(source_region_color_space);

            //get the tile image that is mapped to a specific region with a pointer
            TileImage *tile_image_best_mapped = map_color_tileimage[best_tile_color_space];

            //add the price value to the source image
            source.add_image_value(tile_image_best_mapped->get_price());

            //name of the tile image
            string name_tile = tile_image_best_mapped->get_name();

            //check if the name have ','
            if (name_tile.find(',') != string::npos)
            {
                line = line + "\"" + name_tile + "\",";
            }
            else
            {
                line = line + name_tile + ",";
            }
        }
        //delete the last comma
        line.pop_back();

        //check if the writing reaches last line
        if (i != CANVAS_WIDTH - 1)
        {
            line = line + "\n";
        }
        //write the line to the file
        output_file << line;
    }
    output_file.close();

    std::cout << "Successfully generate mosaic painting information for [" + name_of_image + "] in [outputImageCSV/" + name_of_image + ".csv]" << endl;
}

/**
 * @brief processing the generation of the mosaic from reading the user inputs
 * 
 */
void image_mosaics_processing_from_input()
{
    //read the tile image information from csv files
    vector<TileImage> tiles;
    read_csv_tileimage("paintings.csv", "paintings_avg_color.csv", tiles);
    //unknow length from the user, so use push_backs() for source image vector
    vector<SourceImage> sources;
    //read the source image information from input.txt
    ifstream fin;

    //line to hold the rows
    string line;
    fin.open("input.txt");

    //remove all other csv files created before
    if (!fin.is_open())
    {
        cerr << "Error: Failed to open file : [input.txt]." << endl;
        exit(1);
    }
    else
    {
        //delete all previous files in the outputImageCSV
        string path = "outputImageCSV/";
        delete_dir_content(path);
        //iterate through the names
        while (!fin.eof())
        {
            getline(fin, line);
            string file_colorspace_l = "sourceimage/" + line + "_l.csv";
            string file_colorspace_u = "sourceimage/" + line + "_u.csv";
            string file_colorspace_v = "sourceimage/" + line + "_v.csv";
            SourceImage image(line, file_colorspace_l, file_colorspace_u, file_colorspace_v);

            std::cout << "Successfully loading source image color space information for [" + line + "]" << endl;

            sources.push_back(image);

            //generate mosaic csv files
            generate_mosaic_csv(image, tiles);

            //Print the image information
            std::cout << "The market price of mosaic painting for [" + image.get_image_name() + "] is worth $" + to_string(image.get_image_value()) + "! WoW! \n"
                      << endl;
        }
    }

    std::cout << "\n"
              << endl;
    std::cout << "Successfully generated all output files in folder [outputImageCSV]. To visualize the mosaic images, please run [visualizing_output.rmd]. The output images will be generated in folder [outputImages]." << endl;
}

int main()
{
    //run the program
    image_mosaics_processing_from_input();

    /*********************************************Test cases**************************************************/
    //test file management
    //string path = "outputImageCSV/";
    //delete_dir_content(path);

    //test TileImage
    /**
    vector<TileImage> tiles;
    read_csv_tileimage("paintings/paintings.csv", "paintings/paintings_avg_color.csv", tiles);

    vector<Point<3>> all_points;
    for (TileImage &tileimage : tiles)
    {
        all_points.push_back(tileimage.get_LUV_color());
    }
    */

    //test KD tree
    //KDTree tile_average_color(all_points);

    //Point<3> a(0, 2, 1);
    //Point<3> b(1, 2, 3);
    //cout << to_string(a<b) << endl;
    //cout << a.print_point() << endl;
    //cout << "this program is on" << endl;
    //return 0;

    //test vectors
    /**
    vector<vector<Point<3>>> color_sub_spaces;
    color_sub_spaces.resize(30, vector<Point<3>>(30));
    for (int i = 0; i < 30; ++i)
    {
        for (int j = 0; j < 30; j++)
        {
            color_sub_spaces[i][j] = Point<3> (i,j,3);
        }
    }
    std::cout << color_sub_spaces[20][20].print_point() << endl;

    */

    //test SourceImage.cpp
    /**
    SourceImage Yunfei("Yunfei", "sourceimage/bmw_l.csv", "sourceimage/bmw_u.csv", "sourceimage/bmw_v.csv");
    std::cout << Yunfei.get_image_name() << endl;
    Yunfei.add_image_value(55005);
    Yunfei.add_image_value(2);
    std::cout << to_string(Yunfei.get_image_value()) << endl;
    
    std::cout << Yunfei.get_tile_LUV_color(1, 1).print_point() << endl;
    for (int i = 0; i < 10; i++)
    {
        std::cout << Yunfei.get_tile_LUV_color(i, 1).print_point() << endl;
    }
    */

    //test output
    /**
    vector<TileImage> tiles;
    read_csv_tileimage("paintings/paintings.csv", "paintings/paintings_avg_color.csv", tiles);

    SourceImage Yunfei("Barak Shoshany", "sourceimage/Barak Shoshany_l.csv", "sourceimage/Barak Shoshany_u.csv", "sourceimage/Barak Shoshany_v.csv");

    generate_mosaic_csv(Yunfei, tiles);

    cout << to_string(Yunfei.get_image_value()) << endl;
    */
    //test the kdtree
    /**
    Point<3> a(1, 2, 3);
    Point<3> b(3, 2, 1);
    vector<Point<3>> vec = {a,b};
    KDTree c(vec);
    Point<3> target(1, 3, 5);
    Point<3> currentBest1(1, 3, 2);
    Point<3> possibleBest1(2, 4, 4);
    Point<3> currentBest2(1, 3, 6);
    Point<3> possibleBest2(2, 4, 4);
    Point<3> currentBest3(0, 2, 4);
    Point<3> possibleBest3(2, 4, 6);
    cout << c.shouldReplace(target, currentBest1, possibleBest1) << endl; // should print true
    cout << c.shouldReplace(target, currentBest2, possibleBest2) << endl; // should print false
    cout << c.shouldReplace(target, currentBest3, possibleBest3) << endl; // based on operator<, this should be false!!!
    */
}