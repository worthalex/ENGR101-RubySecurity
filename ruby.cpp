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
// const int numRowSamples = (int)(numCols / pxBetweenSamples);
// const int numColSamples = (int)(numRows / pxBetweenSamples);

const int surrOffset = 60;



const double red = 1.7;

bool isRed(int row, int col)
{
    if ((double)get_pixel(row, col, 0) / (double)get_pixel(row, col, 3) > red) {
        return true;
    } else {return false;}
    
}

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
    
    struct pixel {int row; int col;};
    bool firstFrame = true;

    take_picture();
    convert_camera_to_screen();
    bool foundRuby = false;
    pixel ruby1;
    pixel ruby2;
    pixel ruby3;
    pixel ruby4;
    for (int row = 0; row < numRows; row += pxBetweenSamples)
    {
        for (int col = 0; col < numCols; col += pxBetweenSamples)
        {
            if (isRed(row, col))
            {
                std::cout << row << std::endl;
                std::cout << col << std::endl;
                pixel ruby1 = {row, col};
                pixel ruby2 = {row+pxBetweenSamples, col};
                pixel ruby3 = {row, col+pxBetweenSamples};
                pixel ruby4 = {row+pxBetweenSamples, col+pxBetweenSamples}; 
                set_pixel(row, col, 100, 255, 100);
                foundRuby = true;
                goto exit;
            }
        }
    }
    exit:
    update_screen();
    std::cout << ruby1.row << std::endl;
    if (!foundRuby)
    {
        std::cout << ("Error! Ruby not present at startup!") << std::endl;
        stoph();
        return 0;
    }
    if (ruby1.row < surrOffset + 10 || ruby1.row > numRows - (surrOffset+10) || ruby1.col < surrOffset + 10 || ruby1.col > numCols - (surrOffset+10))
    {
        std::cout << ("Error! Ruby too close to edge at startup!") << std::endl;
        stoph();
        return 0;
    }

    const int surrTop = ruby1.row - surrOffset;
    const int surrBottom = ruby1.row + surrOffset;
    const int surrLeft = ruby1.col - surrOffset;
    const int surrRight = ruby1.col + surrOffset;
    if (isRed(ruby1.row, surrLeft) ||
        isRed(ruby1.row, surrRight) ||
        isRed(surrTop, ruby1.col) ||
        isRed(surrBottom, ruby1.col) ||
        isRed(surrTop,surrRight) ||
        isRed(surrBottom,surrLeft) ||
        isRed(surrTop, surrLeft) ||
        isRed(surrBottom, surrRight))
    {
        std::cout << ("Error! Multiple rubies present at startup!") << std::endl;
        stoph();
        return 0;
    }
    std::cout << ("Ruby monitor started, ruby is present") << std::endl;



    while (true)
    {
        // std::cout << ("while") << std::endl;
        take_picture();
        convert_camera_to_screen();

        if (!isRed(ruby1.row, ruby1.col) ||
            !isRed(ruby1.row, ruby1.col) ||
            !isRed(ruby2.row, ruby2.col) ||
            !isRed(ruby3.row, ruby3.col) ||
            !isRed(ruby4.row, ruby4.col))
        {
            std::cout << ("ALERT!!! Ruby no longer detected; Ruby stolen!") << std::endl;
            stoph();
            return 0;
        }

        if (isRed(ruby1.row, surrLeft) ||
            isRed(ruby1.row, surrRight) ||
            isRed(surrTop, ruby1.col) ||
            isRed(surrBottom, ruby1.col) ||
            isRed(surrTop,surrRight) ||
            isRed(surrBottom,surrLeft) ||
            isRed(surrTop, surrLeft) ||
            isRed(surrBottom, surrRight))
        {
            std::cout << ("ALERT!!! Multiple rubies detected; Ruby stolen!") << std::endl;
            stoph();
            return 0;
        }
        // double rubyPixels[4] = {
        //     (double)get_pixel(centerRow, rubyLeft, 0) / (double)get_pixel(centerRow, rubyLeft, 3), // left
        //     (double)get_pixel(centerRow, rubyRight, 0) / (double)get_pixel(centerRow, rubyRight, 3), // right
        //     (double)get_pixel(rubyTop, centerCol, 0) / (double)get_pixel(rubyTop, centerCol, 3), // top
        //     (double)get_pixel(rubyBottom, centerCol, 0) / (double)get_pixel(rubyBottom, centerCol, 3), // bottom
        // }; int rubyPixelsSize = sizeof(rubyPixels) / sizeof(double);

        // std::cout << ("arr2") << std::endl;

        // set_pixel(centerRow, rubyLeft, 100, 255, 100);
        // set_pixel(centerRow, rubyRight, 100, 255, 100);
        // set_pixel(rubyTop, centerCol, 100, 255, 100);
        // set_pixel(rubyBottom, centerCol, 100, 255, 100);

        set_pixel(ruby1.row, ruby1.col, 100, 255, 100);
        set_pixel(ruby1.row, ruby1.col, 100, 255, 100);
        set_pixel(ruby2.row, ruby2.col, 100, 255, 100);
        set_pixel(ruby3.row, ruby3.col, 100, 255, 100);
        set_pixel(ruby4.row, ruby4.col, 100, 255, 100);
        
        set_pixel(ruby1.row, surrLeft, 0,0,0);
        set_pixel(ruby1.row, surrRight, 0,0,0);
        set_pixel(surrTop, ruby1.col, 0,0,0);
        set_pixel(surrBottom, ruby1.col, 0,0,0);
        set_pixel(surrTop, surrLeft, 0,0,0);
        set_pixel(surrTop, surrRight, 0,0,0);
        set_pixel(surrBottom, surrLeft, 0,0,0);
        set_pixel(surrBottom, surrRight, 0,0,0);
        update_screen();

            // std::cout << " " << std::endl;
            // std::cout << i << std::endl;
            // std::cout << pixels[i] << std::endl;
        // std::cout << relRed; std::cout << " +- "; std::cout << margin << std::endl;

        
    }
    
    close_screen_stream();
    return 0;
}
