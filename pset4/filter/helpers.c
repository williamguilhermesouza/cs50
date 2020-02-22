#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            int avg = round(sum / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Sepia Formula
    // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            for (int m = 0; m < 3; m++)
            {
                if (m == 0)
                {
                    if (sepiaRed > 255)
                    {
                        sepiaRed = 0xff;
                    }
                }
                if (m == 1)
                {
                    if (sepiaGreen > 255)
                    {
                        sepiaGreen = 0xff;
                    }
                }
                if (m == 2)
                {
                    if (sepiaBlue > 255)
                    {
                        sepiaBlue = 0xff;
                    }
                }
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < floor(width / 2); j++)
        {
            RGBTRIPLE aux = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = aux;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*copyimage)[width] = calloc(height, width * sizeof(RGBTRIPLE));


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    float sumRed = image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    float sumGreen = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    float sumBlue = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;

                    copyimage[i][j].rgbtRed = round(sumRed / 4);
                    copyimage[i][j].rgbtGreen = round(sumGreen / 4);
                    copyimage[i][j].rgbtBlue = round(sumBlue / 4);


                }
                else if (j == width - 1)
                {
                    float sumRed = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed;
                    float sumGreen = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen;
                    float sumBlue = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue;

                    copyimage[i][j].rgbtRed = round(sumRed / 4);
                    copyimage[i][j].rgbtGreen = round(sumGreen / 4);
                    copyimage[i][j].rgbtBlue = round(sumBlue / 4);
                }
                else
                {
                    float sumRed = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed;
                    float sumGreen = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen;
                    float sumBlue = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue;

                    copyimage[i][j].rgbtRed = round(sumRed / 6);
                    copyimage[i][j].rgbtGreen = round(sumGreen / 6);
                    copyimage[i][j].rgbtBlue = round(sumBlue / 6);
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    float sumRed = image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed;
                    float sumGreen = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
                    float sumBlue = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;

                    copyimage[i][j].rgbtRed = round(sumRed / 4);
                    copyimage[i][j].rgbtGreen = round(sumGreen / 4);
                    copyimage[i][j].rgbtBlue = round(sumBlue / 4);


                }
                else if (j == width - 1)
                {
                    float sumRed = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed;
                    float sumGreen = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen;
                    float sumBlue = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue;

                    copyimage[i][j].rgbtRed = round(sumRed / 4);
                    copyimage[i][j].rgbtGreen = round(sumGreen / 4);
                    copyimage[i][j].rgbtBlue = round(sumBlue / 4);
                }
                else
                {
                    float sumRed = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed;
                    float sumGreen = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen;
                    float sumBlue = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue;

                    copyimage[i][j].rgbtRed = round(sumRed / 6);
                    copyimage[i][j].rgbtGreen = round(sumGreen / 6);
                    copyimage[i][j].rgbtBlue = round(sumBlue / 6);
                }
            }
            else
            {
                if (j == 0)
                {
                    float sumRed = image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    float sumGreen = image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    float sumBlue = image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;

                    copyimage[i][j].rgbtRed = round(sumRed / 6);
                    copyimage[i][j].rgbtGreen = round(sumGreen / 6);
                    copyimage[i][j].rgbtBlue = round(sumBlue / 6);


                }
                else if (j == width - 1)
                {
                    float sumRed = image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed;
                    float sumGreen = image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen;
                    float sumBlue = image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue;

                    copyimage[i][j].rgbtRed = round(sumRed / 6);
                    copyimage[i][j].rgbtGreen = round(sumGreen / 6);
                    copyimage[i][j].rgbtBlue = round(sumBlue / 6);
                }
                else
                {
                    float sumRed = image[i][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    float sumGreen = image[i][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    float sumBlue = image[i][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;

                    copyimage[i][j].rgbtRed = round(sumRed / 9);
                    copyimage[i][j].rgbtGreen = round(sumGreen / 9);
                    copyimage[i][j].rgbtBlue = round(sumBlue / 9);
                }
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copyimage[i][j].rgbtRed;
            image[i][j].rgbtGreen = copyimage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copyimage[i][j].rgbtBlue;
        }
    }
    return;

}
