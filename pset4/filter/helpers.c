#include <stdio.h>
#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through every row (for)
    // loop through every pixel in that row (second for)
    // calculate the average for each pixel

    int rgbGray;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // find pixel's colour average
            rgbGray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0000000000);

            image[i][j].rgbtBlue = rgbGray;
            image[i][j].rgbtGreen = rgbGray;
            image[i][j].rgbtRed = rgbGray;
        }
    }

    return;
}

// takes in the pointers of the two pizels that need to be swapped to reflect the image
void swap_pixels(BYTE* p1, BYTE* p2)
{
    BYTE tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap_pixels(&image[i][j].rgbtBlue, &image[i][(width - 1) - j].rgbtBlue);
            swap_pixels(&image[i][j].rgbtGreen, &image[i][(width - 1) - j].rgbtGreen);
            swap_pixels(&image[i][j].rgbtRed, &image[i][(width - 1) - j].rgbtRed);
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE imgcpy[height][width];

    // populate the image copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imgcpy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            imgcpy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imgcpy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    // loop through the original image and blur 'em

    float avgBlue;
    float avgGreen;
    float avgRed;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // edge cases:
            // top left, top right, bottom left, bottom right
            // side left, side right

            // top left:
            // i, j = 0
            // refer to:
            // imgcpy[i][j+1] + imgcpy[i+1][j] + imgcpy[i+1][j+1]

            if ((i == 0) && (j == 0))
            {
                // find average of neighbouring pixels
                // find the average of the relative blue, green, red values
                // then assign the values of image[i][j] its average calculated above  

                avgBlue = (imgcpy[i][j].rgbtBlue + imgcpy[i][j + 1].rgbtBlue + imgcpy[i + 1][j].rgbtBlue + imgcpy[i + 1][j + 1].rgbtBlue) / 4.00000000;
                avgGreen = (imgcpy[i][j].rgbtGreen + imgcpy[i][j + 1].rgbtGreen + imgcpy[i + 1][j].rgbtGreen + imgcpy[i + 1][j + 1].rgbtGreen) /4.00000000;
                avgRed = (imgcpy[i][j].rgbtRed + imgcpy[i][j + 1].rgbtRed + imgcpy[i + 1][j].rgbtRed + imgcpy[i + 1][j + 1].rgbtRed) / 4.00000000;

                // set the average colour to the image[i][j]
                image[i][j].rgbtBlue = round(avgBlue);
                image[i][j].rgbtGreen = round(avgGreen);
                image[i][j].rgbtRed = round(avgRed);
            }

            // top right:
            // i = 0, j = width - 1
            // refer to:
            // imgcpy[i][j-1] + imgcpy[i+1][j-1] + imgcpy[i+1][j]

            else if ((i == 0) && (j == width - 1))
            {
                avgBlue = (imgcpy[i][j].rgbtBlue + imgcpy[i][j - 1].rgbtBlue + imgcpy[i + 1][j - 1].rgbtBlue + imgcpy[i + 1][j].rgbtBlue) / 4.00000000;
                avgGreen = (imgcpy[i][j].rgbtGreen + imgcpy[i][j - 1].rgbtGreen + imgcpy[i + 1][j - 1].rgbtGreen + imgcpy[i + 1][j].rgbtGreen) / 4.00000000;
                avgRed = (imgcpy[i][j].rgbtRed + imgcpy[i][j - 1].rgbtRed + imgcpy[i + 1][j - 1].rgbtRed + imgcpy[i + 1][j].rgbtRed) / 4.00000000;

                image[i][j].rgbtBlue = round(avgBlue);
                image[i][j].rgbtGreen = round(avgGreen);
                image[i][j].rgbtRed = round(avgRed);
            }

            // bottom left
            // i = height - 1, j = 0
            // refer to:
            // imgcpy[i-1][j] + imgcpy[i-1][j+1] + imgcpy[i][j+1]

            else if ((i == height - 1) && (j == 0))
            {
                avgBlue = (imgcpy[i][j].rgbtBlue + imgcpy[i - 1][j].rgbtBlue + imgcpy[i - 1][j + 1].rgbtBlue + imgcpy[i][j + 1].rgbtBlue) / 4.00000000;
                avgGreen = (imgcpy[i][j].rgbtGreen + imgcpy[i - 1][j].rgbtGreen + imgcpy[i - 1][j + 1].rgbtGreen + imgcpy[i][j + 1].rgbtGreen) / 4.00000000;
                avgRed = (imgcpy[i][j].rgbtRed + imgcpy[i - 1][j].rgbtRed + imgcpy[i - 1][j + 1].rgbtRed + imgcpy[i][j + 1].rgbtRed) / 4.00000000;

                image[i][j].rgbtBlue = round(avgBlue);
                image[i][j].rgbtGreen = round(avgGreen);
                image[i][j].rgbtRed = round(avgRed);
            }

            // bottom right
            // i = height - 1, j = width - 1
            // refer to:
            // imgcpy[i-1][j] + imgcpy[i-1][j-1] + imgcpy[i][j-1]

            else if ((i == height - 1) && (j == width -1))
            {
                avgBlue = (imgcpy[i][j].rgbtBlue + imgcpy[i - 1][j].rgbtBlue + imgcpy[i - 1][j - 1].rgbtBlue + imgcpy[i][j - 1].rgbtBlue) / 4.00000000;
                avgGreen = (imgcpy[i][j].rgbtGreen + imgcpy[i - 1][j].rgbtGreen + imgcpy[i - 1][j - 1].rgbtGreen + imgcpy[i][j - 1].rgbtGreen) / 4.00000000;
                avgRed = (imgcpy[i][j].rgbtRed + imgcpy[i - 1][j].rgbtRed + imgcpy[i - 1][j - 1].rgbtRed + imgcpy[i][j - 1].rgbtRed) / 4.00000000;

                image[i][j].rgbtBlue = round(avgBlue);
                image[i][j].rgbtGreen = round(avgGreen);
                image[i][j].rgbtRed = round(avgRed);
            }

            // side left
            // j = 0
            // refer to:
            // imgcpy[i-1][j] + imgcpy[i-1][j+1] + imgcpy[i][j+1] + imgcpy[i+1][j+1] + imgcpy[i+1][j]

            else if (j == 0)
            {
                avgBlue = (imgcpy[i][j].rgbtBlue + imgcpy[i - 1][j].rgbtBlue + imgcpy[i - 1][j + 1].rgbtBlue + imgcpy[i][j + 1].rgbtBlue + imgcpy[i + 1][j + 1].rgbtBlue + imgcpy[i + 1][j].rgbtBlue) / 6.00000000;
                avgGreen = (imgcpy[i][j].rgbtGreen + imgcpy[i - 1][j].rgbtGreen + imgcpy[i - 1][j + 1].rgbtGreen + imgcpy[i][j + 1].rgbtGreen + imgcpy[i + 1][j + 1].rgbtGreen + imgcpy[i + 1][j].rgbtGreen) / 6.00000000;
                avgRed = (imgcpy[i][j].rgbtRed + imgcpy[i - 1][j].rgbtRed + imgcpy[i - 1][j + 1].rgbtRed + imgcpy[i][j + 1].rgbtRed + imgcpy[i + 1][j + 1].rgbtRed + imgcpy[i + 1][j].rgbtRed) / 6.00000000;

                image[i][j].rgbtBlue = round(avgBlue);
                image[i][j].rgbtGreen = round(avgGreen);
                image[i][j].rgbtRed = round(avgRed);
            }

            // side right
            // j = width - 1
            // refer to:
            // imgcpy[i-1][j] + imgcpy[i-1][j-1] + imgcpy[i][j-1] + imgcpy[i+1][j-1] + imgcpy[i+1][j]

            else if (j == width - 1)
            {
                avgBlue = (imgcpy[i][j].rgbtBlue + imgcpy[i - 1][j].rgbtBlue + imgcpy[i - 1][j - 1].rgbtBlue + imgcpy[i][j - 1].rgbtBlue + imgcpy[i + 1][j - 1].rgbtBlue + imgcpy[i + 1][j].rgbtBlue) / 6.00000000;
                avgGreen = (imgcpy[i][j].rgbtGreen + imgcpy[i - 1][j].rgbtGreen + imgcpy[i - 1][j - 1].rgbtGreen + imgcpy[i][j - 1].rgbtGreen + imgcpy[i + 1][j - 1].rgbtGreen + imgcpy[i + 1][j].rgbtGreen) / 6.00000000;
                avgRed = (imgcpy[i][j].rgbtRed + imgcpy[i - 1][j].rgbtRed + imgcpy[i - 1][j - 1].rgbtRed + imgcpy[i][j - 1].rgbtRed + imgcpy[i + 1][j - 1].rgbtRed + imgcpy[i + 1][j].rgbtRed) / 6.00000000;

                image[i][j].rgbtBlue = round(avgBlue);
                image[i][j].rgbtGreen = round(avgGreen);
                image[i][j].rgbtRed = round(avgRed);
            }

            // top
            // i = 0,
            // imgcpy[i][j-1] + imgcpy[i][j+1] + imgcpy[i+1][j-1] + imgcpy[i+1][j] + imgcpy[i+1][j+1]

            else if (i == 0)
            {
                avgBlue = (imgcpy[i][j].rgbtBlue + imgcpy[i][j - 1].rgbtBlue + imgcpy[i][j + 1].rgbtBlue + imgcpy[i + 1][j - 1].rgbtBlue + imgcpy[i + 1][j].rgbtBlue + imgcpy[i + 1][j + 1].rgbtBlue) / 6.00000000;
                avgGreen = (imgcpy[i][j].rgbtGreen + imgcpy[i][j - 1].rgbtGreen + imgcpy[i][j + 1].rgbtGreen + imgcpy[i + 1][j - 1].rgbtGreen + imgcpy[i + 1][j].rgbtGreen + imgcpy[i + 1][j + 1].rgbtGreen) / 6.00000000;
                avgRed = (imgcpy[i][j].rgbtRed + imgcpy[i][j - 1].rgbtRed + imgcpy[i][j + 1].rgbtRed + imgcpy[i + 1][j - 1].rgbtRed + imgcpy[i + 1][j].rgbtRed + imgcpy[i + 1][j + 1].rgbtRed) / 6.00000000;

                image[i][j].rgbtBlue = round(avgBlue);
                image[i][j].rgbtGreen = round(avgGreen);
                image[i][j].rgbtRed = round(avgRed);
            }



            // bottom
            // i = height - 1
            // imgcpy[i][j-1] + imgcpy[i-1][j-1] + imgcpy[i-1][j] + imgcpy[i-1][j+1] + imgcpy[i][j+1]

            else if (i == height - 1)
            {
                avgBlue = (imgcpy[i][j].rgbtBlue + imgcpy[i][j - 1].rgbtBlue + imgcpy[i - 1][j - 1].rgbtBlue + imgcpy[i - 1][j].rgbtBlue + imgcpy[i - 1][j + 1].rgbtBlue + imgcpy[i][j + 1].rgbtBlue) / 6.00000000;
                avgGreen = (imgcpy[i][j].rgbtGreen + imgcpy[i][j - 1].rgbtGreen + imgcpy[i - 1][j - 1].rgbtGreen + imgcpy[i - 1][j].rgbtGreen + imgcpy[i - 1][j + 1].rgbtGreen + imgcpy[i][j + 1].rgbtGreen) / 6.00000000;
                avgRed = (imgcpy[i][j].rgbtRed + imgcpy[i][j - 1].rgbtRed + imgcpy[i - 1][j - 1].rgbtRed + imgcpy[i - 1][j].rgbtRed + imgcpy[i - 1][j + 1].rgbtRed + imgcpy[i][j + 1].rgbtRed) / 6.00000000;

                image[i][j].rgbtBlue = round(avgBlue);
                image[i][j].rgbtGreen = round(avgGreen);
                image[i][j].rgbtRed = round(avgRed);
            }


            // if all above cases return false, then the current pixel is surrounded by 8 pixels
            // imgcpy[i-1][j-1] + imgcpy[i-1][j] + imgcpy[i-1][j+1] + imgcpy[i][j-1] + imgcpy[i][j+1] + imgcpy[i+1][j-1] + imgcpy[i+1][j] + imgcpy[i+1][j+1]
            else
            {
                avgBlue = (imgcpy[i][j].rgbtBlue + imgcpy[i - 1][j - 1].rgbtBlue + imgcpy[i - 1][j].rgbtBlue + imgcpy[i - 1][j + 1].rgbtBlue + imgcpy[i][j - 1].rgbtBlue + imgcpy[i][j + 1].rgbtBlue + imgcpy[i + 1][j - 1].rgbtBlue + imgcpy[i + 1][j].rgbtBlue + imgcpy[i + 1][j + 1].rgbtBlue) / 9.00000000;
                avgGreen = (imgcpy[i][j].rgbtGreen + imgcpy[i - 1][j - 1].rgbtGreen + imgcpy[i - 1][j].rgbtGreen + imgcpy[i - 1][j + 1].rgbtGreen + imgcpy[i][j - 1].rgbtGreen + imgcpy[i][j + 1].rgbtGreen + imgcpy[i + 1][j - 1].rgbtGreen + imgcpy[i + 1][j].rgbtGreen + imgcpy[i + 1][j + 1].rgbtGreen) / 9.00000000;
                avgRed = (imgcpy[i][j].rgbtRed + imgcpy[i - 1][j - 1].rgbtRed + imgcpy[i - 1][j].rgbtRed + imgcpy[i - 1][j + 1].rgbtRed + imgcpy[i][j - 1].rgbtRed + imgcpy[i][j + 1].rgbtRed + imgcpy[i + 1][j - 1].rgbtRed + imgcpy[i + 1][j].rgbtRed + imgcpy[i + 1][j + 1].rgbtRed) / 9.00000000;

                image[i][j].rgbtBlue = round(avgBlue);
                image[i][j].rgbtGreen = round(avgGreen);
                image[i][j].rgbtRed = round(avgRed);
            }
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE imgcpy[height][width];

    // populate the image copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imgcpy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            imgcpy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imgcpy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    // loop through the image copy
    // calculate Gx for each pixel
    // save the value for each colour channel into GxBlue, GxGreen, GxRed
    // similarly, calculate Gy for each pixel (GyBlue, GyGreen, GyRed)
    // magnitude: sqrt(Gx_bgr^2 + Gx_bgr^2)

    int GxBlue, GxGreen, GxRed;
    int GyBlue, GyGreen, GyRed;
    double magB, magG, magR;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // first: edge cases

            // top left, top right, top edge
            // bottom right, bottom left, bottom edge
            // side left, side right

            // top left:
            if ((i == 0) && (j == 0))
            {
                // Gx
                GxBlue = (2 * imgcpy[i][j + 1].rgbtBlue) + (1 * imgcpy[i + 1][j + 1].rgbtBlue);
                GxGreen = (2 * imgcpy[i][j + 1].rgbtGreen) + (1 * imgcpy[i + 1][j + 1].rgbtGreen);
                GxRed = (2 * imgcpy[i][j + 1].rgbtRed) + (1 * imgcpy[i + 1][j + 1].rgbtRed);

                // Gy
                GyBlue = (2 * imgcpy[i + 1][j].rgbtBlue) + (1 * imgcpy[i + 1][j + 1].rgbtBlue);
                GyGreen = (2 * imgcpy[i + 1][j].rgbtGreen) + (1 * imgcpy[i + 1][j + 1].rgbtGreen);
                GyRed = (2 * imgcpy[i + 1][j].rgbtRed) + (1 * imgcpy[i + 1][j + 1].rgbtRed);

                // magnitude
                magB = sqrt((pow(GxBlue, 2)) + (pow(GyBlue, 2)));
                magG = sqrt((pow(GxGreen, 2)) + (pow(GyGreen, 2)));
                magR = sqrt((pow(GxRed, 2)) + (pow(GyRed, 2)));

                if (magB > 255) 
                { 
                    image[i][j].rgbtBlue = 255; 
                }
                else 
                { 
                    image[i][j].rgbtBlue = round(magB); 
                }

                if (magG > 255) 
                { 
                    image[i][j].rgbtGreen = 255; 
                }
                else 
                { 
                    image[i][j].rgbtGreen = round(magG); 
                }

                if (magR > 255) 
                {
                    image[i][j].rgbtRed = 255;
                }
                else 
                {
                    image[i][j].rgbtRed = round(magR);
                }
            }


            // top right
            else if ((i == 0) && (j == width - 1))
            {
                // Gx
                GxBlue = (-2 * imgcpy[i][j - 1].rgbtBlue) + (-1 * imgcpy[i + 1][j - 1].rgbtBlue);
                GxGreen = (-2 * imgcpy[i][j - 1].rgbtGreen) + (-1 * imgcpy[i + 1][j - 1].rgbtGreen);
                GxRed = (-2 * imgcpy[i][j - 1].rgbtRed) + (-1 * imgcpy[i + 1][j - 1].rgbtRed);

                // Gy
                GyBlue = (1 * imgcpy[i + 1][j - 1].rgbtBlue) + (2 * imgcpy[i + 1][j].rgbtBlue);
                GyGreen = (1 * imgcpy[i + 1][j - 1].rgbtGreen) + (2 * imgcpy[i + 1][j].rgbtGreen);
                GyRed = (1 * imgcpy[i + 1][j - 1].rgbtRed) + (2 * imgcpy[i + 1][j].rgbtRed);

                // magnitude
                magB = sqrt((pow(GxBlue, 2)) + (pow(GyBlue, 2)));
                magG = sqrt((pow(GxGreen, 2)) + (pow(GyGreen, 2)));
                magR = sqrt((pow(GxRed, 2)) + (pow(GyRed, 2)));

                if (magB > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(magB);
                }

                if (magG > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(magG);
                }

                if (magR > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(magR);
                }
            }

            // bottom left
            else if ((i == height - 1) && (j == 0))
            {
                // Gx
                GxBlue = (1 * imgcpy[i - 1][j + 1].rgbtBlue) + (2 * imgcpy[i][j + 1].rgbtBlue);
                GxGreen = (1 * imgcpy[i - 1][j + 1].rgbtGreen) + (2 * imgcpy[i][j + 1].rgbtGreen);
                GxRed = (1 * imgcpy[i - 1][j + 1].rgbtRed) + (2 * imgcpy[i][j + 1].rgbtRed);

                // Gy
                GyBlue = (-2 * imgcpy[i - 1][j].rgbtBlue) + (-1 * imgcpy[i - 1][j + 1].rgbtBlue);
                GyGreen = (-2 * imgcpy[i - 1][j].rgbtGreen) + (-1 * imgcpy[i - 1][j + 1].rgbtGreen);
                GyRed = (-2 * imgcpy[i - 1][j].rgbtRed) + (-1 * imgcpy[i - 1][j + 1].rgbtRed);

                // magnitude
                magB = sqrt((pow(GxBlue, 2)) + (pow(GyBlue, 2)));
                magG = sqrt((pow(GxGreen, 2)) + (pow(GyGreen, 2)));
                magR = sqrt((pow(GxRed, 2)) + (pow(GyRed, 2)));

                if (magB > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(magB);
                }

                if (magG > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(magG);
                }

                if (magR > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(magR);
                }
            }
            
            // bottom right
            else if ((i == height - 1) && (j == width - 1))
            {
                // Gx
                GxBlue = (-1 * imgcpy[i - 1][j - 1].rgbtBlue) + (-2 * imgcpy[i][j - 1].rgbtBlue);
                GxGreen = (-1 * imgcpy[i - 1][j - 1].rgbtGreen) + (-2 * imgcpy[i][j - 1].rgbtGreen);
                GxRed = (-1 * imgcpy[i - 1][j - 1].rgbtRed) + (-2 * imgcpy[i][j - 1].rgbtRed);

                // Gy
                GyBlue = (-1 * imgcpy[i - 1][j - 1].rgbtBlue) + (-2 * imgcpy[i - 1][j].rgbtBlue);
                GyGreen = (-1 * imgcpy[i - 1][j - 1].rgbtGreen) + (-2 * imgcpy[i - 1][j].rgbtGreen);
                GyRed = (-1 * imgcpy[i - 1][j - 1].rgbtRed) + (-2 * imgcpy[i - 1][j].rgbtRed);

                // magnitude
                magB = sqrt((pow(GxBlue, 2)) + (pow(GyBlue, 2)));
                magG = sqrt((pow(GxGreen, 2)) + (pow(GyGreen, 2)));
                magR = sqrt((pow(GxRed, 2)) + (pow(GyRed, 2)));

                if (magB > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(magB);
                }

                if (magG > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(magG);
                }

                if (magR > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(magR);
                }
            }

            // side left 
            else if (j == 0)
            {
                // Gx
                GxBlue = (1 * imgcpy[i + 1][j + 1].rgbtBlue) + (2 * imgcpy[i][j + 1].rgbtBlue) + (1 * imgcpy[i - 1][j + 1].rgbtBlue);
                GxGreen = (1 * imgcpy[i + 1][j + 1].rgbtGreen) + (2 * imgcpy[i][j + 1].rgbtGreen) + (1 * imgcpy[i - 1][j + 1].rgbtGreen);
                GxRed = (1 * imgcpy[i + 1][j + 1].rgbtRed) + (2 * imgcpy[i][j + 1].rgbtRed) + (1 * imgcpy[i - 1][j + 1].rgbtRed);

                // Gy
                GyBlue = (-2 * imgcpy[i + 1][j].rgbtBlue) + (-1 * imgcpy[i + 1][j + 1].rgbtBlue) + (2 * imgcpy[i - 1][j].rgbtBlue) + (1 * imgcpy[i - 1][j + 1].rgbtBlue);
                GyGreen = (-2 * imgcpy[i + 1][j].rgbtGreen) + (-1 * imgcpy[i + 1][j + 1].rgbtGreen) + (2 * imgcpy[i - 1][j].rgbtGreen) + (1 * imgcpy[i - 1][j + 1].rgbtGreen);
                GyRed = (-2 * imgcpy[i + 1][j].rgbtRed) + (-1 * imgcpy[i + 1][j + 1].rgbtRed) + (2 * imgcpy[i - 1][j].rgbtRed) + (1 * imgcpy[i - 1][j + 1].rgbtRed);

                // magnitude
                magB = sqrt((pow(GxBlue, 2)) + (pow(GyBlue, 2)));
                magG = sqrt((pow(GxGreen, 2)) + (pow(GyGreen, 2)));
                magR = sqrt((pow(GxRed, 2)) + (pow(GyRed, 2)));

                if (magB > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(magB);
                }

                if (magG > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(magG);
                }

                if (magR > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(magR);
                }
            }

            // side right
            else if (j == width - 1)
            {
                // Gx
                GxBlue = (-1 * imgcpy[i - 1][j - 1].rgbtBlue) + (-2 * imgcpy[i][j - 1].rgbtBlue) + (-1 * imgcpy[i + 1][j - 1].rgbtBlue);
                GxGreen = (-1 * imgcpy[i - 1][j - 1].rgbtGreen) + (-2 * imgcpy[i][j - 1].rgbtGreen) + (-1 * imgcpy[i + 1][j - 1].rgbtGreen);
                GxRed = (-1 * imgcpy[i - 1][j - 1].rgbtRed) + (-2 * imgcpy[i][j - 1].rgbtRed) + (-1 * imgcpy[i + 1][j - 1].rgbtRed);

                // Gy
                GyBlue = (-1 * imgcpy[i - 1][j - 1].rgbtBlue) + (-2 * imgcpy[i - 1][j].rgbtBlue) + (1 * imgcpy[i + 1][j - 1].rgbtBlue) + (2 * imgcpy[i + 1][j].rgbtBlue);
                GyGreen = (-1 * imgcpy[i - 1][j - 1].rgbtGreen) + (-2 * imgcpy[i - 1][j].rgbtGreen) + (1 * imgcpy[i + 1][j - 1].rgbtGreen) + (2 * imgcpy[i + 1][j].rgbtGreen);
                GyRed = (-1 * imgcpy[i - 1][j - 1].rgbtRed) + (-2 * imgcpy[i - 1][j].rgbtRed) + (1 * imgcpy[i + 1][j - 1].rgbtRed) + (2 * imgcpy[i + 1][j].rgbtRed);

                // magnitude
                magB = sqrt((pow(GxBlue, 2)) + (pow(GyBlue, 2)));
                magG = sqrt((pow(GxGreen, 2)) + (pow(GyGreen, 2)));
                magR = sqrt((pow(GxRed, 2)) + (pow(GyRed, 2)));

                if (magB > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(magB);
                }

                if (magG > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(magG);
                }

                if (magR > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(magR);
                }
            }

            // top
            else if (i == 0)
            {
                // Gx
                GxBlue = (-2 * imgcpy[i][j - 1].rgbtBlue) + (2 * imgcpy[i][j + 1].rgbtBlue) + (-1 * imgcpy[i + 1][j - 1].rgbtBlue) + (1 * imgcpy[i + 1][j + 1].rgbtBlue);
                GxGreen = (-2 * imgcpy[i][j - 1].rgbtGreen) + (2 * imgcpy[i][j + 1].rgbtGreen) + (-1 * imgcpy[i + 1][j - 1].rgbtGreen) + (1 * imgcpy[i + 1][j + 1].rgbtGreen);
                GxRed = (-2 * imgcpy[i][j - 1].rgbtRed) + (2 * imgcpy[i][j + 1].rgbtRed) + (-1 * imgcpy[i + 1][j - 1].rgbtRed) + (1 * imgcpy[i + 1][j + 1].rgbtRed);

                // Gy
                GyBlue = (1 * imgcpy[i + 1][j - 1].rgbtBlue) + (2 * imgcpy[i + 1][j].rgbtBlue) + (1 * imgcpy[i + 1][j + 1].rgbtBlue);
                GyGreen = (1 * imgcpy[i + 1][j - 1].rgbtGreen) + (2 * imgcpy[i + 1][j].rgbtGreen) + (1 * imgcpy[i + 1][j + 1].rgbtGreen);
                GyRed = (1 * imgcpy[i + 1][j - 1].rgbtRed) + (2 * imgcpy[i + 1][j].rgbtRed) + (1 * imgcpy[i + 1][j + 1].rgbtRed);

                // magnitude
                magB = sqrt((pow(GxBlue, 2)) + (pow(GyBlue, 2)));
                magG = sqrt((pow(GxGreen, 2)) + (pow(GyGreen, 2)));
                magR = sqrt((pow(GxRed, 2)) + (pow(GyRed, 2)));

                if (magB > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(magB);
                }

                if (magG > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(magG);
                }

                if (magR > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(magR);
                }
            }

            // bottom 
            else if (i == height - 1)
            {
                // Gx
                GxBlue = (-1 * imgcpy[i - 1][j - 1].rgbtBlue) + (1 * imgcpy[i - 1][j + 1].rgbtBlue) + (-2 * imgcpy[i][j - 1].rgbtBlue) + (2 * imgcpy[i][j + 1].rgbtBlue);
                GxGreen = (-1 * imgcpy[i - 1][j - 1].rgbtGreen) + (1 * imgcpy[i - 1][j + 1].rgbtGreen) + (-2 * imgcpy[i][j - 1].rgbtGreen) + (2 * imgcpy[i][j + 1].rgbtGreen);
                GxRed = (-1 * imgcpy[i - 1][j - 1].rgbtRed) + (1 * imgcpy[i - 1][j + 1].rgbtRed) + (-2 * imgcpy[i][j - 1].rgbtRed) + (2 * imgcpy[i][j + 1].rgbtRed);

                // Gy
                GyBlue = (-1 * imgcpy[i - 1][j - 1].rgbtBlue) + (-2 * imgcpy[i - 1][j].rgbtBlue) + (-1 * imgcpy[i - 1][j + 1].rgbtBlue);
                GyGreen = (-1 * imgcpy[i - 1][j - 1].rgbtGreen) + (-2 * imgcpy[i - 1][j].rgbtGreen) + (-1 * imgcpy[i - 1][j + 1].rgbtGreen);
                GyRed = (-1 * imgcpy[i - 1][j - 1].rgbtRed) + (-2 * imgcpy[i - 1][j].rgbtRed) + (-1 * imgcpy[i - 1][j + 1].rgbtRed);

                // magnitude
                magB = sqrt((pow(GxBlue, 2)) + (pow(GyBlue, 2)));
                magG = sqrt((pow(GxGreen, 2)) + (pow(GyGreen, 2)));
                magR = sqrt((pow(GxRed, 2)) + (pow(GyRed, 2)));

                if (magB > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(magB);
                }

                if (magG > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(magG);
                }

                if (magR > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(magR);
                }
            }

            // no edge
            else 
            {
                // Gx
                GxBlue = (-1 * imgcpy[i - 1][j - 1].rgbtBlue) + (1 * imgcpy[i - 1][j + 1].rgbtBlue) + (-2 * imgcpy[i][j - 1].rgbtBlue) + (2 * imgcpy[i][j + 1].rgbtBlue) + (-1 * imgcpy[i + 1][j - 1].rgbtBlue) + (1 * imgcpy[i + 1][j + 1].rgbtBlue);
                GxGreen = (-1 * imgcpy[i - 1][j - 1].rgbtGreen) + (1 * imgcpy[i - 1][j + 1].rgbtGreen) + (-2 * imgcpy[i][j - 1].rgbtGreen) + (2 * imgcpy[i][j + 1].rgbtGreen) + (-1 * imgcpy[i + 1][j - 1].rgbtGreen) + (1 * imgcpy[i + 1][j + 1].rgbtGreen);
                GxRed = (-1 * imgcpy[i - 1][j - 1].rgbtRed) + (1 * imgcpy[i - 1][j + 1].rgbtRed) + (-2 * imgcpy[i][j - 1].rgbtRed) + (2 * imgcpy[i][j + 1].rgbtRed) + (-1 * imgcpy[i + 1][j - 1].rgbtRed) + (1 * imgcpy[i + 1][j + 1].rgbtRed);

                // Gy
                GyBlue = (-1 * imgcpy[i - 1][j - 1].rgbtBlue) + (-2 * imgcpy[i - 1][j].rgbtBlue) + (-1 * imgcpy[i - 1][j + 1].rgbtBlue) + (1 * imgcpy[i + 1][j - 1].rgbtBlue) + (2 * imgcpy[i + 1][j].rgbtBlue) + (1 * imgcpy[i + 1][j + 1].rgbtBlue);
                GyGreen = (-1 * imgcpy[i - 1][j - 1].rgbtGreen) + (-2 * imgcpy[i - 1][j].rgbtGreen) + (-1 * imgcpy[i - 1][j + 1].rgbtGreen) + (1 * imgcpy[i + 1][j - 1].rgbtGreen) + (2 * imgcpy[i + 1][j].rgbtGreen) + (1 * imgcpy[i + 1][j + 1].rgbtGreen);
                GyRed = (-1 * imgcpy[i - 1][j - 1].rgbtRed) + (-2 * imgcpy[i - 1][j].rgbtRed) + (-1 * imgcpy[i - 1][j + 1].rgbtRed) + (1 * imgcpy[i + 1][j - 1].rgbtRed) + (2 * imgcpy[i + 1][j].rgbtRed) + (1 * imgcpy[i + 1][j + 1].rgbtRed);

                // magnitude
                magB = sqrt((pow(GxBlue, 2)) + (pow(GyBlue, 2)));
                magG = sqrt((pow(GxGreen, 2)) + (pow(GyGreen, 2)));
                magR = sqrt((pow(GxRed, 2)) + (pow(GyRed, 2)));

                if (magB > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(magB);
                }

                if (magG > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(magG);
                }

                if (magR > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(magR);
                }
            }
            

        }
    }

    return;
}
