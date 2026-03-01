// Author: Marko Solajic

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            float average =
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;

            // Update pixel values
            image[i][j].rgbtRed = (int) round(average);
            image[i][j].rgbtGreen = (int) round(average);
            image[i][j].rgbtBlue = (int) round(average);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Go over each pixel, checking 3x3 box
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum_red = 0;
            float sum_green = 0;
            float sum_blue = 0;
            int pixels = 0;

            for (int ni = -1; ni <= 1; ni++)
            {
                for (int nj = -1; nj <= 1; nj++)
                {
                    if (j + nj < 0 || j + nj >= width || i + ni < 0 || i + ni >= height)
                    {
                        continue;
                    }
                    else
                    {
                        sum_red += copy[i + ni][j + nj].rgbtRed;
                        sum_green += copy[i + ni][j + nj].rgbtGreen;
                        sum_blue += copy[i + ni][j + nj].rgbtBlue;
                        pixels++;
                    }
                }
            }
            // calculate average value for each color, setting this value to new image's pixels
            float average_red = sum_red / pixels;
            float average_green = sum_green / pixels;
            float average_blue = sum_blue / pixels;

            image[i][j].rgbtRed = (int) round(average_red);
            image[i][j].rgbtGreen = (int) round(average_green);
            image[i][j].rgbtBlue = (int) round(average_blue);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Sobel operator (gx and gy kernels)
    int gx[3][3] = {{-1.0, 0.0, 1.0}, {-2.0, 0.0, 2.0}, {-1.0, 0.0, 1.0}};

    int gy[3][3] = {{-1.0, -2.0, -1.0}, {0.0, 0.0, 0.0}, {1.0, 2.0, 1.0}};

    // Iterate through each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx_red = 0;
            int gy_red = 0;
            int gx_green = 0;
            int gy_green = 0;
            int gx_blue = 0;
            int gy_blue = 0;

            // For each of the colors go through the 3x3 box, if the pixel is past the edge set the
            // color values to 0
            for (int ni = -1; ni <= 1; ni++)
            {
                for (int nj = -1; nj <= 1; nj++)
                {
                    if (j + nj < 0 || j + nj >= width || i + ni < 0 || i + ni >= height)
                    {
                        continue;
                    }
                    else
                    {
                        // Get a value of Gx and Gy for each color
                        gx_red += copy[i + ni][j + nj].rgbtRed * gx[ni + 1][nj + 1];
                        gy_red += copy[i + ni][j + nj].rgbtRed * gy[ni + 1][nj + 1];
                        gx_green += copy[i + ni][j + nj].rgbtGreen * gx[ni + 1][nj + 1];
                        gy_green += copy[i + ni][j + nj].rgbtGreen * gy[ni + 1][nj + 1];
                        gx_blue += copy[i + ni][j + nj].rgbtBlue * gx[ni + 1][nj + 1];
                        gy_blue += copy[i + ni][j + nj].rgbtBlue * gy[ni + 1][nj + 1];
                    }
                }
            }

            // Get final color value for each color using square root Gx^2 + Gy^2, round each value
            // to nearest int
            int red_final = (int) round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            int green_final = (int) round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            int blue_final = (int) round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));

            // If it exceeds 255, set it to 255
            if (red_final > 255)
            {
                red_final = 255;
            }
            if (green_final > 255)
            {
                green_final = 255;
            }
            if (blue_final > 255)
            {
                blue_final = 255;
            }

            // Set this value to each color of the pixel
            image[i][j].rgbtRed = red_final;
            image[i][j].rgbtGreen = green_final;
            image[i][j].rgbtBlue = blue_final;
        }
    }
    return;
}
