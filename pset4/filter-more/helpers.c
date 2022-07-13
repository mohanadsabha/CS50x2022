#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // convert pixels to float
            float Blue = image[i][j].rgbtBlue;
            float Red = image[i][j].rgbtRed;
            float Green = image[i][j].rgbtGreen;

            //find avg value :
            int avg = round((Blue + Red + Green) / 3);
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = avg;
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
            // reflect the pixels (array)
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    // creat a copy of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed, totalGreen, totalBlue;
            totalRed = totalGreen = totalBlue = 0;
            float counter = 0.00;

            //get neighbering pixels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int CurrentX = i + x;
                    int CurrentY = j + y;

                    // check if the pixel is inside the border of the pic
                    if (CurrentX < 0 || CurrentX > (height - 1) || CurrentY < 0 || CurrentY > (width - 1))
                    {
                        continue;
                    }

                    //get img value
                    totalRed += image[CurrentX][CurrentY].rgbtRed;
                    totalBlue += image[CurrentX][CurrentY].rgbtBlue;
                    totalGreen += image[CurrentX][CurrentY].rgbtGreen;
                    counter++;
                }
            }
            // Calcalute avg of near pixels
            temp[i][j].rgbtBlue = round(totalBlue / counter);
            temp[i][j].rgbtRed = round(totalRed / counter);
            temp[i][j].rgbtGreen = round(totalGreen / counter);
        }
    }
    // copy new img into original img ;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // loop throw each row and columen
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redX = 0;
            int greenX = 0;
            int blueX = 0;
            int redY = 0;
            int greenY = 0;
            int blueY = 0;

            // loop throw each pixle for neighbering pixles
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    // check for vaild pixels
                    if (i - 1 + x < 0 || i - 1 + x > height - 1 || j - 1 + y < 0 || j - 1 + y > width - 1)
                    {
                        continue;
                    }

                    // Calculate Gx for each color
                    redX += (image[i - 1 + x][j - 1 + y].rgbtRed * Gx[x][y]);
                    blueX += (image[i - 1 + x][j - 1 + y].rgbtBlue * Gx[x][y]);
                    greenX += (image[i - 1 + x][j - 1 + y].rgbtGreen * Gx[x][y]);

                    // Calculate Gy for rach color
                    redY += (image[i - 1 + x][j - 1 + y].rgbtRed * Gy[x][y]);
                    blueY += (image[i - 1 + x][j - 1 + y].rgbtBlue * Gy[x][y]);
                    greenY += (image[i - 1 + x][j - 1 + y].rgbtGreen * Gy[x][y]);
                }
            }
            // Calculate sqrt for Gx and Gy
            int red = round(sqrt((redX * redX) + (redY * redY)));
            int blue = round(sqrt((blueX * blueX) + (blueY * blueY)));
            int green = round(sqrt((greenX * greenX) + (greenY * greenY)));

            // Cap value 255 if its esceeds
            if (red > 255)
            {
                red = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            // copy values into temp img
            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtBlue = blue;
            temp[i][j].rgbtGreen = green;
        }
    }
    // copy new pixles in temp to original pic
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}
