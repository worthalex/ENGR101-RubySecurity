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
const int numRowSamples = (int)(numRows / pxBetweenSamples);
const int numColSamples = (int)(numCols / pxBetweenSamples);
const int redThreshold = 300;
const int rubyPxSize = 10;
const int marginOfError = 6;
const int bufferSize = 4;

const char PositiveColour[3] = {255, 255, 0};   // yellow, shows up well on red
const char NegativeColour[3] = {0, 128, 255}; // cyan, shows up well on black and white and gray and easily differentiable from yellow

struct pixel
{
    int x;
    int y;
    int r;
    int g;
    int b;
    int v;
    bool isRed;
};

int setPx(pixel targetPixel)
{
    if (targetPixel.isRed)
    {
        set_pixel(targetPixel.y, targetPixel.x, PositiveColour[0], PositiveColour[1], PositiveColour[2]);

        set_pixel(targetPixel.y+1, targetPixel.x, PositiveColour[0], PositiveColour[1], PositiveColour[2]);
        set_pixel(targetPixel.y+2, targetPixel.x, PositiveColour[0], PositiveColour[1], PositiveColour[2]);
        set_pixel(targetPixel.y-1, targetPixel.x, PositiveColour[0], PositiveColour[1], PositiveColour[2]);
        set_pixel(targetPixel.y-2, targetPixel.x, PositiveColour[0], PositiveColour[1], PositiveColour[2]);

        set_pixel(targetPixel.y, targetPixel.x+1, PositiveColour[0], PositiveColour[1], PositiveColour[2]);
        set_pixel(targetPixel.y, targetPixel.x+2, PositiveColour[0], PositiveColour[1], PositiveColour[2]);
        set_pixel(targetPixel.y, targetPixel.x-1, PositiveColour[0], PositiveColour[1], PositiveColour[2]);
        set_pixel(targetPixel.y, targetPixel.x-2, PositiveColour[0], PositiveColour[1], PositiveColour[2]);
        
    }
    else
    {
        set_pixel(targetPixel.y, targetPixel.x, NegativeColour[0], NegativeColour[1], NegativeColour[2]);

        //set_pixel(targetPixel.y+1, targetPixel.x, NegativeColour[0], NegativeColour[1], NegativeColour[2]); // No crosshairs for negative pixels
        //set_pixel(targetPixel.y+2, targetPixel.x, NegativeColour[0], NegativeColour[1], NegativeColour[2]); // to make it more easily differentiable
        //set_pixel(targetPixel.y-1, targetPixel.x, NegativeColour[0], NegativeColour[1], NegativeColour[2]);
        //set_pixel(targetPixel.y-2, targetPixel.x, NegativeColour[0], NegativeColour[1], NegativeColour[2]);

        //set_pixel(targetPixel.y, targetPixel.x+1, NegativeColour[0], NegativeColour[1], NegativeColour[2]);
        //set_pixel(targetPixel.y, targetPixel.x+2, NegativeColour[0], NegativeColour[1], NegativeColour[2]);
        //set_pixel(targetPixel.y, targetPixel.x-1, NegativeColour[0], NegativeColour[1], NegativeColour[2]);
        //set_pixel(targetPixel.y, targetPixel.x-2, NegativeColour[0], NegativeColour[1], NegativeColour[2]);
    }
}

int main()
{
    int err = init(0);
    std::cout << "Error: " << err << std::endl;

    open_screen_stream();
    
    int buffer[bufferSize]; 
    while (true)
    {
        take_picture();
        convert_camera_to_screen();
        int numRedPx = 0;
        for (int row = 0; row < numRows; row += pxBetweenSamples)
        {
            for (int col = 0; col < numCols; col += pxBetweenSamples)
            {
                pixel sample = {col, row, get_pixel(sample.y, sample.x, 0),
                get_pixel(sample.y, sample.x, 1),get_pixel(sample.y, sample.x, 2),get_pixel(sample.y, sample.x, 3),
                (sample.r > (sample.g + sample.b + redThreshold )/ 3) ? true : false};
                if (sample.isRed) {numRedPx++;}
                setPx(sample);
            }
        }
        buffer[0] = numRedPx;
        for (int i = 1; i < bufferSize; i++)
        {
            buffer[i] = buffer[i-1];
        }
        int framesNotEnoughRed = 0;
        for (int i : buffer)
        {
            if (i < rubyPxSize + marginOfError)
            {
                framesNotEnoughRed++;
            }
        }
        switch (framesNotEnoughRed)
        {
            case 0:
                break;
            case 1:
                std::cout << "Not enough red for one (1) frame(s)" << std::endl;
            case 2:
                std::cout << "Not enough red for two (2) frame(s)" << std::endl;
            case 3:
                std::cout << "Not enough red for three (3) frame(s)" << std::endl;
            case bufferSize:
                std::cout << "Not enough red for four (4) frame(s)" << std::endl;
                std::cout << "CODE RED, RUBY STOLEN!!!! AAAAAAAAAAAAA" << std::endl;
        }
        update_screen();
        sleep1(10);
    }

    // while (true)
    // {
    //     take_picture();

    //     for (int i; i < numColSamples; i++)
    //     {
    //         for (int j; j < numRowSamples; j++)
    //         {
    //             int pixelRed = get_pixel(i * pxBetweenSamples, j * pxBetweenSamples, 0) - '0'; // subtract '0' to turn chars into ints for some reason
    //             setPx(pixelRed, redThreshold, i * pxBetweenSamples, j * pxBetweenSamples);
    //         }
    //         int pixelRed = get_pixel(i * pxBetweenSamples, columns, 0) - '0'; // check px on very edge for redundancy
    //         setPx(pixelRed, redThreshold, i * pxBetweenSamples, columns);
    //     }
    //     for (int j; j < numRowSamples; j++)
    //     {
    //         int pixelRed = get_pixel(rows, j * pxBetweenSamples, 0) - '0'; // check px on very corner for redundancy
    //         setPx(pixelRed, redThreshold, rows, j * pxBetweenSamples);
    //     }
    //     int pixelRed = get_pixel(rows, columns, 0) - '0'; // check px on very corner for redundancy
    //     setPx(pixelRed, redThreshold, rows, columns);

    //     convert_camera_to_screen();
    //     update_screen();
    // }

    close_screen_stream();
    return 0;
}
