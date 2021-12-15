#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/**
 * @brief Function for checking if a charater is digit. Input a charater and output boolean for yes or no
 * 
 * @param chr input charactor value
 * @return true If the input can be modified to a digit
 * @return false If the input cannot be modified to a digit
 */
bool isDigit(const char &chr);

/**
 * @brief check If the whole string contains only digits and maximum one decimal point, in other words, check it the string can be converted to a number. Input a string output a boolean for yes or no
 * 
 * @param word the input string 
 * @return true If the string can be converted to number
 * @return false If the string cannot be converted to number
 */
bool isNumber(const string &word);