#include <iostream>
#include <string>
#include <vector>

#include"number.hpp"

using namespace std;

bool isDigit(const char &chr)
{
    if (chr >= '0' and chr <= '9')
    {
        return true;
    }
    return false;
}

bool isNumber(const string &word)
{

    // Flag for having decimal point
    bool decimal_point_flag = false;
    bool minus_sign_flag = false;
    
    // Flag for exponent regarding tiny numbers
    bool tiny_number_flag = false;

    // Check for every char
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
            else if (c == 'e' and tiny_number_flag == false)
            {
                tiny_number_flag = true;
                minus_sign_flag = false;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}