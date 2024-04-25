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
const int centerRow = 120;
const int centerCol = 160;

const int offset = 20;

const int top = centerRow - offset;
const int bot = centerRow + offset;
const int lft = centerCol - offset;
const int rgt = centerCol + offset;

const double relRed = 2.9;
const double margin = 0.4;

int main()
{
    int err = init(0);
    std::cout << "Error: " << err << std::endl;
    open_screen_stream();
    take_picture();

    // while (true)
    // {
    //     take_picture();
    //     std::cout << ((double)get_pixel(centerRow, centerCol, 0) / (double)get_pixel(centerRow, centerCol, 3)) << std::endl;
    //     sleep1(1000);
    //     convert_camera_to_screen();
    //     update_screen();
    // }
    double initRelRed = (double)get_pixel(centerRow, centerCol, 0) / (double)get_pixel(centerRow, centerCol, 3);
    if (initRelRed > relRed + margin || initRelRed < relRed - margin)
    {
        std::cout << "ALERT!!! Ruby missing at startup!" << std::endl;
        convert_camera_to_screen();
        update_screen();
        stoph();
        return 0;
    }
    // std::cout << ("arr1") << std::endl;
    
    while (true)
    {
        // std::cout << ("while") << std::endl;
        take_picture();
        convert_camera_to_screen();

        double pixels[4] = {
            (double)get_pixel(centerRow, lft, 0) / (double)get_pixel(centerRow, lft, 3) + 1, // left
            (double)get_pixel(centerRow, rgt, 0) / (double)get_pixel(centerRow, rgt, 3) + 1, // right
            (double)get_pixel(top, centerCol, 0) / (double)get_pixel(top, centerCol, 3) + 1, // top
            (double)get_pixel(bot, centerCol, 0) / (double)get_pixel(bot, centerCol, 3) + 1, // bottom
        };
        // std::cout << ("arr2") << std::endl;

        set_pixel(centerRow, lft, 100, 255, 100);
        set_pixel(centerRow, rgt, 100, 255, 100);
        set_pixel(top, centerCol, 100, 255, 100);
        set_pixel(bot, centerCol, 100, 255, 100);
        update_screen();

        for (int i = 0; i <= 3; i++)
        {
            // std::cout << " " << std::endl;
            // std::cout << i << std::endl;
            // std::cout << pixels[i] << std::endl;
            // std::cout << relRed; std::cout << " +- "; std::cout << margin << std::endl;
            if (pixels[i] > relRed + margin || pixels[i] < relRed - margin)
            {
                std::cout << ("ALERT!!! Ruby stolen!") << std::endl;
                stoph();
                return 0;
            }
        }
        
    }
    
    close_screen_stream();
    return 0;
}
