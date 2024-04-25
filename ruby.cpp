/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective.
 * Study the code so that you understand what the strategy is and how
 * it is implemented. Then design and implement a better startegy.
 *
 * */

#include <iostream>
#include "E101.h"
// const int pxBetweenSamples = 8;
// const int numRows = 240;
// const int numCols = 320;
// const int numRowSamples = (int)(numCols / pxBetweenSamples);
// const int numColSamples = (int)(numRows / pxBetweenSamples);
const int redThreshold = 2;
const int centerRow = 120;
const int centerCol = 160;

const int offset = 26;

const int top = centerRow - offset;
const int bot = centerRow + offset;
const int lft = centerCol - offset;
const int rgt = centerCol + offset;


bool check_if_different(double old, double nEw)
{
    // std::cout << ("call") << std::endl;
    if ((nEw + old)/ 2 > (old * 2) + redThreshold || (nEw + old)/ 2 > (old * 2) + redThreshold)
    {
        // std::cout << ("gorg") << std::endl;
        return true;
    }
    return false;
}

int main()
{
    int err = init(0);
    std::cout << "Error: " << err << std::endl;
    open_screen_stream();
    take_picture();
    std::cout << (double)get_pixel(centerRow, lft, 0) / (double)get_pixel(centerRow, lft, 3) + 1 << std::endl;
    double old[4] = {
        (double)get_pixel(centerRow, lft, 0) / (double)get_pixel(centerRow, lft, 3) + 1, // left
        (double)get_pixel(centerRow, rgt, 0) / (double)get_pixel(centerRow, rgt, 3) + 1, // right
        (double)get_pixel(top, centerCol, 0) / (double)get_pixel(top, centerCol, 3) + 1, // top
        (double)get_pixel(bot, centerCol, 0) / (double)get_pixel(bot, centerCol, 3) + 1, // bottom
    };
    // std::cout << ("arr1") << std::endl;
    
    while (true)
    {
        // std::cout << ("while") << std::endl;
        take_picture();
        set_pixel(centerRow, lft, 100, 255, 100);
        set_pixel(centerRow, rgt, 100, 255, 100);
        set_pixel(top, centerCol, 100, 255, 100);
        set_pixel(bot, centerCol, 100, 255, 100);
        convert_camera_to_screen();
        update_screen();

        double nEw[4] = {
            (double)get_pixel(centerRow, lft, 0) / (double)get_pixel(centerRow, lft, 3) + 1, // left
            (double)get_pixel(centerRow, rgt, 0) / (double)get_pixel(centerRow, rgt, 3) + 1, // right
            (double)get_pixel(top, centerCol, 0) / (double)get_pixel(top, centerCol, 3) + 1, // top
            (double)get_pixel(bot, centerCol, 0) / (double)get_pixel(bot, centerCol, 3) + 1, // bottom
        };
        // std::cout << ("arr2") << std::endl;
        for (int i = 0; i <= 3; i++)
        {
            if (check_if_different(old[i], nEw[i]))
            {
                std::cout << ("ruby stolen") << std::endl;
                stoph();
            }
        }
        
    }
    
    close_screen_stream();
    return 0;
}
