/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective.
 * Study the code so that you understand what the strategy is and how
 * it is implemented. Then design and implement a better startegy.
 *
 * */

#include <iostream>
#include "E101.h"
const int pxBetweenSamples = 8;
const int numRows = 240;
const int numCols = 320;
const int numRowSamples = (int)(numCols / pxBetweenSamples);
const int numColSamples = (int)(numRows / pxBetweenSamples);
const int redThreshold = 40;

bool check_if_different(double old, double nEw)
{
    if ((nEw + old)/ 2 > (old * 2) + redThreshold || (nEw + old)/ 2 > (old * 2) + redThreshold)
    {
        return true;
    }
    return false;
}

int main()
{
    int err = init(0);
    std::cout << "Error: " << err << std::endl;
    open_screen_stream();
    
    double old[4] = {
        get_pixel(120, 140, 0) / get_pixel(120, 140, 3), // left
        get_pixel(120, 180, 0) / get_pixel(120, 180, 3), // right
        get_pixel(100, 160, 0) / get_pixel(100, 160, 3), // top
        get_pixel(140, 160, 0) / get_pixel(140, 160, 3), // bottom
    };
    
    while (true)
    {
        take_picture();
        double nEw[4] = {
            get_pixel(120, 140, 0) / get_pixel(120, 140, 3), // left
            get_pixel(120, 180, 0) / get_pixel(120, 180, 3), // right
            get_pixel(100, 160, 0) / get_pixel(100, 160, 3), // top
            get_pixel(140, 160, 0) / get_pixel(140, 160, 3), // bottom
        };

        for (int i = 0; i <= 3; i++)
        {
            if (check_if_different(old[i], nEw[i]))
            {
                std::cout << ("ruby stolen") << std::endl;
                stoph();
            }
        }
        
    }

    update_screen();
    close_screen_stream();
    return 0;
}
