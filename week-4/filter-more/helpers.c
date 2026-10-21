#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int average = round((red + green + blue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE support;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            support = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = support;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            copy[i][j] = image[i][j];

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                    if (i + di >= 0 && i + di < height && j + dj >= 0 && j + dj < width)
                    {
                        sumRed += copy[i + di][j + dj].rgbtRed;
                        sumGreen += copy[i + di][j + dj].rgbtGreen;
                        sumBlue += copy[i + di][j + dj].rgbtBlue;
                        count++;
                    }
            image[i][j].rgbtRed = round((float) sumRed / count);
            image[i][j].rgbtGreen = round((float) sumGreen / count);
            image[i][j].rgbtBlue = round((float) sumBlue / count);
        }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            copy[i][j] = image[i][j];

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            int sumRedX = 0, sumGreenX = 0, sumBlueX = 0;
            int sumRedY = 0, sumGreenY = 0, sumBlueY = 0;

            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    int red = 0, green = 0, blue = 0;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        red = copy[ni][nj].rgbtRed;
                        green = copy[ni][nj].rgbtGreen;
                        blue = copy[ni][nj].rgbtBlue;
                    }

                    sumRedX += red * gx[di + 1][dj + 1];
                    sumGreenX += green * gx[di + 1][dj + 1];
                    sumBlueX += blue * gx[di + 1][dj + 1];

                    sumRedY += red * gy[di + 1][dj + 1];
                    sumGreenY += green * gy[di + 1][dj + 1];
                    sumBlueY += blue * gy[di + 1][dj + 1];
                }

            int red = round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY));
            int green = round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY));
            int blue = round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY));

            if (red > 255)
                red = 255;
            if (green > 255)
                green = 255;
            if (blue > 255)
                blue = 255;

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
}
