#include "helpers.h"
#include <math.h>
float avgred(int i, int j ,int height, int width, RGBTRIPLE image[height][width]);
float avgblue (int i, int j ,int height, int width, RGBTRIPLE image[height][width]);
float avggreen (int i, int j ,int height, int width, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0 ;
            BYTE average = round(avg);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
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
            float sepiared =  (.393 * image[i][j].rgbtRed + .189 * image[i][j].rgbtBlue + .769 * image[i][j].rgbtGreen);
            float sepiablue =  (.272 * image[i][j].rgbtRed + .131 * image[i][j].rgbtBlue + .534 * image[i][j].rgbtGreen);
            float sepiagreen =  (.349 * image[i][j].rgbtRed + .168 * image[i][j].rgbtBlue + .686 * image[i][j].rgbtGreen);
            
            if(sepiared > 255)
            {
                sepiared = 255;
            }
            else if (sepiared < 0)
            {
                sepiared = 0;
            }
            if(sepiablue > 255)
            {
                sepiablue = 255;
            }
             else if (sepiablue < 0)
            {
                sepiablue = 0;
            }
            if(sepiagreen > 255)
            {
                sepiagreen = 255;
            }
             else if (sepiagreen < 0)
            {
                sepiagreen = 0;
            }
            
            image[i][j].rgbtBlue = round (sepiablue);
            image[i][j].rgbtGreen =round (sepiagreen);
            image[i][j].rgbtRed = round (sepiared);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    
    int k;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp [i][j] = image [i][j];
        }
    }
      for (int i = 0; i < height; i++)
    {
         k = width - 1;
        for (int j = 0; j < width; j++)
        {
            image [i][j] = tmp [i][k];
            k--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp [height][width];
     for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp [i][j] = image [i][j];
        }
    }
    
     for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = avgred(i,j,height,width,tmp);
            float blue = avgblue(i,j,height,width,tmp);
            float green = avggreen(i,j,height,width,tmp);
            image[i][j].rgbtRed = round(red);
            image[i][j].rgbtBlue = round(blue);
            image[i][j].rgbtGreen = round(green);
        }
    }
    return;
}
float avgred(int i, int j ,int height, int width, RGBTRIPLE image[height][width])
{
    float sum=0, avg;
    int k, l, m, n, counter = 0;;
    if ((i - 1) < 0)
    {
        k = i;
    }
    else
    {
        k = i-1;
    }
    if ((i + 1) == height)
    {
        l = i;
    }
     else
    {
        l = i+1;
    }
    if ((j - 1) < 0)
    {
        m = j;
    }
     else
    {
        m = j-1;
    }
    if ((j + 1) == width)
    {
        n = j;
    } else
    {
        n = j+1;
    }
    for (int y = k ; y <= l; y++)
    {
        for (int z =m; z <= n; z++)
        {
            sum += image[y][z].rgbtRed;
            counter ++;
        }
        
    }
    avg = sum/counter;
    return avg;
}
float avgblue (int i, int j ,int height, int width, RGBTRIPLE image[height][width])
{
    float sum=0, avg;
    int k, l, m, n, counter = 0;;
    if ((i - 1) < 0)
    {
        k = i;
    }
    else
    {
        k = i-1;
    }
    if ((i + 1) == height)
    {
        l = i;
    }
     else
    {
        l = i+1;
    }
    if ((j - 1) < 0)
    {
        m = j;
    }
     else
    {
        m = j-1;
    }
    if ((j + 1) == width)
    {
        n = j;
    } else
    {
        n = j+1;
    }
    for (int y = k ; y <= l; y++)
    {
        for (int z =m; z <= n; z++)
        {
            sum += image[y][z].rgbtBlue;
            counter ++;
        }
    }
     avg = sum/counter;
    return avg;
}
float avggreen (int i, int j ,int height, int width, RGBTRIPLE image[height][width])
{
    float sum=0, avg;
    int k, l, m, n, counter = 0;;
    if ((i - 1) < 0)
    {
        k = i;
    }
    else
    {
        k = i-1;
    }
    if ((i + 1) == height)
    {
        l = i;
    }
     else
    {
        l = i+1;
    }
    if ((j - 1) < 0)
    {
        m = j;
    }
     else
    {
        m = j-1;
    }
    if ((j + 1) == width)
    {
        n = j;
    } else
    {
        n = j+1;
    }
    for (int y = k ; y <= l; y++)
    {
        for (int z =m; z <= n; z++)
        {
            sum += image[y][z].rgbtGreen;
            counter ++;
        }
    }
     avg = sum/counter;
    return avg;
}

