#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gray = 0;
            gray = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            gray = round(gray);
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float red = 0;
            float blue = 0;
            float green = 0;
            for (int row = -1; row < 2; row++)
            {
                for (int col = -1; col < 2; col++)
                {
                      if ((i + row >= 0) && (i + row < height) && (j + col >= 0) && (j + col < width))
                        {
                            red += copy[i + row][j + col].rgbtRed;
                            blue += copy[i + row][j + col].rgbtBlue;
                            green += copy[i + row][j + col].rgbtGreen;
                            count++;
                        }
                }
            }
            red /= count;
            green /= count;
            blue /= count;
            red = round(red);
            green = round(green);
            blue = round(blue);
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
 RGBTRIPLE copy[height][width];
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            copy[k][l] = image[k][l];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float redgx = 0;
            float bluegx = 0;
            float greengx = 0;
            float redgy = 0;
            float greengy = 0;
            float bluegy = 0;
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    if ((i + row >= 0) && (i + row < height) && (j + col >= 0) && (j + col < width))
                    {
                        if (col == 0)
                        {
                            redgy += (copy[i + row][j + col].rgbtRed * (row * 2));
                            bluegy += (copy[i + row][j + col].rgbtBlue * (row * 2));
                            greengy += (copy[i + row][j + col].rgbtGreen * (row * 2));
                        }
                        else
                        {
                            redgy += (copy[i + row][j + col].rgbtRed * row);
                            bluegy += (copy[i + row][j + col].rgbtBlue * row);
                            greengy += (copy[i + row][j + col].rgbtGreen * row);
                        }

                    }
                }
            }
            for (int row1 = -1; row1 <= 1; row1++)
            {
                for (int col1 = -1; col1 <= 1; col1++)
                {
                    if ((i + row1 >= 0) && (i + row1 < height) && (j + col1 >= 0) && (j + col1 < width))
                    {
                        if (row1 == 0)
                        {
                            redgx += (copy[i + row1][j + col1].rgbtRed * (col1 * 2));
                            bluegx += (copy[i + row1][j + col1].rgbtBlue * (col1 * 2));
                            greengx += (copy[i + row1][j + col1].rgbtGreen * (col1 * 2));
                        }
                        else
                        {
                            redgx += (copy[i + row1][j + col1].rgbtRed * col1);
                            bluegx += (copy[i + row1][j + col1].rgbtBlue * col1);
                            greengx += (copy[i + row1][j + col1].rgbtGreen * col1);
                        }

                    }
                }
            }
            float red = 0;
            float green = 0;
            float blue = 0;
            red = sqrt(pow(redgx, 2) + pow(redgy, 2));
            green = sqrt(pow(greengx, 2) + pow(greengy, 2));
            blue = sqrt(pow(bluegx, 2) + pow(bluegy, 2));
            red = round(red);
            green = round(green);
            blue = round(blue);
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}

