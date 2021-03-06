#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *img = &image[i][j];
            if (img->rgbtBlue == img->rgbtGreen && img->rgbtGreen == img->rgbtRed)
            {
                continue;
            }
            int sum = img->rgbtBlue + img->rgbtGreen + img->rgbtRed;
            float res = (float) sum / 3.0;
            int ress = (int) roundf(res);
            img->rgbtBlue = ress;
            img->rgbtGreen = ress;
            img->rgbtRed = ress;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *img = &image[i][j];
            float oBlue = (float) img->rgbtBlue;
            float oGreen = (float) img->rgbtGreen;
            float oRed = (float) img->rgbtRed;

            int nBlue = (int) roundf(0.272 * oRed + 0.534 * oGreen + 0.131 * oBlue);
            if (nBlue > 255)
            {
                nBlue = 255;
            }
            img->rgbtBlue = nBlue;
            int nGreen = (int) roundf(0.349 * oRed + 0.686 * oGreen + 0.168 * oBlue);
            if (nGreen > 255)
            {
                nGreen = 255;
            }
            img->rgbtGreen = nGreen;
            int nRed = (int) roundf(0.393 * oRed + .769 * oGreen + 0.189 * oBlue);
            if (nRed > 255)
            {
                nRed = 255;
            }
            img->rgbtRed = nRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // itself
            int aBlue = image[i][j].rgbtBlue;
            int aRed = image[i][j].rgbtRed;
            int aGreen = image[i][j].rgbtGreen;
            int c = 1;

            if (i != 0)
            {
                // top
                aBlue += image[i - 1][j].rgbtBlue;
                aRed += image[i - 1][j].rgbtRed;
                aGreen += image[i - 1][j].rgbtGreen;
                c++;


                // top-right
                if (j != width - 1)
                {
                    aBlue += image[i - 1][j + 1].rgbtBlue;
                    aRed += image[i - 1][j + 1].rgbtRed;
                    aGreen += image[i - 1][j + 1].rgbtGreen;
                    c++;
                }

                // top-left
                if (j != 0)
                {
                    aBlue += image[i - 1][j - 1].rgbtBlue;
                    aRed += image[i - 1][j - 1].rgbtRed;
                    aGreen += image[i - 1][j - 1].rgbtGreen;
                    c++;
                }
            }

            // right
            if (j != width - 1)
            {
                aBlue += image[i][j + 1].rgbtBlue;
                aRed += image[i][j + 1].rgbtRed;
                aGreen += image[i][j + 1].rgbtGreen;
                c++;
            }

            // left
            if (j != 0)
            {
                aBlue += image[i][j - 1].rgbtBlue;
                aRed += image[i][j - 1].rgbtRed;
                aGreen += image[i][j - 1].rgbtGreen;
                c++;
            }

            if (i != height - 1)
            {
                // bottom
                aBlue += image[i + 1][j].rgbtBlue;
                aRed += image[i + 1][j].rgbtRed;
                aGreen += image[i + 1][j].rgbtGreen;
                c++;

                // bottom-right
                if (j != width - 1)
                {
                    aBlue += image[i + 1][j + 1].rgbtBlue;
                    aRed += image[i + 1][j + 1].rgbtRed;
                    aGreen += image[i + 1][j + 1].rgbtGreen;
                    c++;
                }
                // botoom-left
                if (j != 0)
                {
                    aBlue += image[i + 1][j - 1].rgbtBlue;
                    aRed += image[i + 1][j - 1].rgbtRed;
                    aGreen += image[i + 1][j - 1].rgbtGreen;
                    c++;
                }
            }

            RGBTRIPLE *img = &image[i][j];

            newImage[i][j].rgbtBlue = (int) roundf((float) aBlue / (float) c);
            newImage[i][j].rgbtRed = (int) roundf((float)aRed / (float) c);
            newImage[i][j].rgbtGreen = (int) roundf((float) aGreen / (float) c);
        }
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            image[i][j] = newImage[i][j];
        }
    }
}
