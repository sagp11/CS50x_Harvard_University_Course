#include<stdio.h>
#include<math.h>
#include "helpers.h"

RGBTRIPLE sepia_calc(RGBTRIPLE values);
RGBTRIPLE blur_filter(RGBTRIPLE values, int i, int j);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //printf("H: %i, W: %i\n", height, width);
    BYTE x = image[1][1].rgbtRed;
    //printf("PIX: %u\n", x);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            //printf("%u ", avg);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
        //printf("\n");
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE sepia_value = sepia_calc(image[i][j]);
            image[i][j].rgbtBlue = sepia_value.rgbtBlue;
            image[i][j].rgbtGreen = sepia_value.rgbtGreen;
            image[i][j].rgbtRed = sepia_value.rgbtRed;
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
            RGBTRIPLE temp;
            temp.rgbtBlue = image[i][j].rgbtBlue;
            temp.rgbtGreen = image[i][j].rgbtGreen;
            temp.rgbtRed = image[i][j].rgbtRed;

            int reverse_width_index = width - 1 - j;
            image[i][j].rgbtBlue = image[i][reverse_width_index].rgbtBlue;
            image[i][j].rgbtGreen = image[i][reverse_width_index].rgbtGreen;
            image[i][j].rgbtRed = image[i][reverse_width_index].rgbtRed;

            image[i][reverse_width_index].rgbtBlue = temp.rgbtBlue;
            image[i][reverse_width_index].rgbtGreen = temp.rgbtGreen;
            image[i][reverse_width_index].rgbtRed = temp.rgbtRed;
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
    //printf("H: %i, W: %i\n", height, width);


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float total_pixels = 0;
            float red = 0, green = 0, blue = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k > height - 1)
                    {
                        continue;
                    }
                    if (j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }
                    //printf("T: %f\n", blue);
                    blue += copy[i + k][j + l].rgbtBlue;
                    green += copy[i + k][j + l].rgbtGreen;
                    red += copy[i + k][j + l].rgbtRed;
                    total_pixels++;
                    //printf("T: %f, C: %u\n", blue, copy[i + k][j + l].rgbtBlue);
                }
            }
            //printf("%f \n", total_pixels);
            // printf("%u\n", temp.rgbtRed);
            image[i][j].rgbtBlue = round(blue / total_pixels);
            image[i][j].rgbtGreen = round(green / total_pixels);
            image[i][j].rgbtRed = round(red / total_pixels);
            // printf("%u\n", image[i][j].rgbtRed);
        }
    }
    return;
}

RGBTRIPLE sepia_calc(RGBTRIPLE values)
{
    BYTE sepiaRed = round(fmin(.393 * values.rgbtRed + .769 * values.rgbtGreen + .189 * values.rgbtBlue, 255));
    BYTE sepiaGreen = round(fmin(.349 * values.rgbtRed + .686 * values.rgbtGreen + .168 * values.rgbtBlue, 255));
    BYTE sepiaBlue = round(fmin(.272 * values.rgbtRed + .534 * values.rgbtGreen + .131 * values.rgbtBlue, 255));

    values.rgbtRed = sepiaRed;
    values.rgbtBlue = sepiaBlue;
    values.rgbtGreen = sepiaGreen;

    //printf("R: %u, G: %u, B: %u\n", values.rgbtRed, values.rgbtGreen, values.rgbtBlue);

    return values;
}

