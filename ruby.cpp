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

const int offset = 5;
const int surrOffset = 60;

const int rubyTop = centerRow - offset;
const int rubyBottom = centerRow + offset;
const int rubyLeft = centerCol - offset;
const int rubyRight = centerCol + offset;

const int surrTop = centerRow - surrOffset;
const int surrBottom = centerRow + surrOffset;
const int surrLeft = centerCol - surrOffset;
const int surrRight = centerCol + surrOffset;

const double red = 1.7;

int main()
{
    int err = init(0);
    std::cout << "Error: " << err << std::endl;
    open_screen_stream();

    // while (true)
    // {
    //     take_picture();
    //     std::cout << ((double)get_pixel(centerRow, centerCol, 0) / (double)get_pixel(centerRow, centerCol, 3)) << std::endl;
    //     sleep1(1000);
    //     convert_camera_to_screen();
    //     update_screen();
    // }
    // double initRelRed = (double)get_pixel(centerRow, centerCol, 0) / (double)get_pixel(centerRow, centerCol, 3);
    // if (initRelRed > relRed + margin || initRelRed < relRed - margin)
    // {
    //     std::cout << "ALERT!!! Ruby missing at startup!" << std::endl;
    //     set_pixel(centerRow, lft, 100, 255, 100);
    //     set_pixel(centerRow, rgt, 100, 255, 100);
    //     set_pixel(top, centerCol, 100, 255, 100);
    //     set_pixel(bot, centerCol, 100, 255, 100);
    //     convert_camera_to_screen();
    //     update_screen();
    //     stoph();
    //     return 0;
    // }
    // // std::cout << ("arr1") << std::endl;
    
    bool firstFrame = true;
    while (true)
    {
        // std::cout << ("while") << std::endl;
        take_picture();
        convert_camera_to_screen();

        double rubyPixels[4] = {
            (double)get_pixel(centerRow, rubyLeft, 0) / (double)get_pixel(centerRow, rubyLeft, 3), // left
            (double)get_pixel(centerRow, rubyRight, 0) / (double)get_pixel(centerRow, rubyRight, 3), // right
            (double)get_pixel(rubyTop, centerCol, 0) / (double)get_pixel(rubyTop, centerCol, 3), // top
            (double)get_pixel(rubyBottom, centerCol, 0) / (double)get_pixel(rubyBottom, centerCol, 3), // bottom
        }; int rubyPixelsSize = sizeof(rubyPixels) / sizeof(double);

        double surrPixels[8] = {
            (double)get_pixel(centerRow, surrLeft, 0) / (double)get_pixel(centerRow, surrLeft, 3), // left
            (double)get_pixel(centerRow, surrRight, 0) / (double)get_pixel(centerRow, surrRight, 3), // right
            (double)get_pixel(surrTop, centerCol, 0) / (double)get_pixel(surrTop, centerCol, 3), // top
            (double)get_pixel(surrBottom, centerCol, 0) / (double)get_pixel(surrBottom, centerCol, 3), // bottom
            (double)get_pixel(surrTop, surrRight, 0) / (double)get_pixel(surrTop, surrRight, 3), // top right
            (double)get_pixel(surrBottom, surrLeft, 0) / (double)get_pixel(surrBottom, surrLeft, 3), // bottom left
            (double)get_pixel(surrTop, surrLeft, 0) / (double)get_pixel(surrTop, surrLeft, 3), // top left
            (double)get_pixel(surrBottom, surrRight, 0) / (double)get_pixel(surrBottom, surrRight, 3), // bottom right
        }; int surrPixelsSize = sizeof(rubyPixels) / sizeof(double);
        // std::cout << ("arr2") << std::endl;

        set_pixel(centerRow, rubyLeft, 100, 255, 100);
        set_pixel(centerRow, rubyRight, 100, 255, 100);
        set_pixel(rubyTop, centerCol, 100, 255, 100);
        set_pixel(rubyBottom, centerCol, 100, 255, 100);

        set_pixel(centerRow, surrLeft, 0,0,0);
        set_pixel(centerRow, surrRight, 0,0,0);
        set_pixel(surrTop, centerCol, 0,0,0);
        set_pixel(surrBottom, centerCol, 0,0,0);
        set_pixel(surrTop, surrLeft, 0,0,0);
        set_pixel(surrTop, surrRight, 0,0,0);
        set_pixel(surrBottom, surrLeft, 0,0,0);
        set_pixel(surrBottom, surrRight, 0,0,0);
        update_screen();

        for (int i = 0; i < rubyPixelsSize; i++)
        {
            // std::cout << " " << std::endl;
            // std::cout << i << std::endl;
            // std::cout << pixels[i] << std::endl;
            // std::cout << relRed; std::cout << " +- "; std::cout << margin << std::endl;
            if (rubyPixels[i] < red)
            {
                if (!firstFrame)
                {
                    std::cout << ("ALERT!!! Ruby no longer detected; Ruby stolen!") << std::endl;

                } else 
                {
                    std::cout << ("Error! Ruby not present at startup!") << std::endl;
                }
                stoph();
                return 0;
            }
        }
        for (int i = 0; i < surrPixelsSize; i++)
        {
            if (surrPixels[i] > red)
            {
                if (!firstFrame)
                {
                    std::cout << ("ALERT!!! Multiple rubies detected; Ruby stolen!") << std::endl;
                } else
                {
                    std::cout << ("Error! Multiple rubies present at startup!") << std::endl;
                }
                stoph();
                return 0;

            }
        } 

        if (firstFrame)
        {
            std::cout << ("Ruby monitor started, ruby is present") << std::endl;
            firstFrame = false;
        }
        
    }
    
    close_screen_stream();
    return 0;
}
