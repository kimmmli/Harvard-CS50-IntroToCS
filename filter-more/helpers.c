#include "helpers.h"
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include<stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height;i++)
    {
        for (int j=0; j<width;j++)
        {
            int temgray=(image[i][j].rgbtRed+image[i][j].rgbtGreen+image[i][j].rgbtBlue)/3;
            image[i][j].rgbtRed=temgray;
            image[i][j].rgbtGreen=temgray;
            image[i][j].rgbtBlue=temgray;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if ((width%2)==0){
        for (int i=0; i<height;i++)
        {
            for (int j=0; j<width/2;j++)
            {
                RGBTRIPLE tem=image[i][j];
                image[i][j]=image[i][width-1-j];
                image[i][width-1-j]=tem;
                }
            }
    }
    else if ((width%2)!=0){
        for (int i=0; i<height;i++)
        {
            for (int j=0; j<(width/2)+1;j++)
            {
                RGBTRIPLE tem=image[i][j];
                image[i][j]=image[i][width-1-j];
                image[i][width-1-j]=tem;
                }
            }
    }
    return;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE ori[height][width];
    for (int i=0; i<height;i++)
    {
        for (int j=0; j<width;j++)
        {
            ori[i][j]=image[i][j];
        }
    }



    for (int i=0; i<height;i++)
    {
        for (int j=0; j<width;j++)
        {
            if (i==0)
            {
                if (j==0)
                {
                    image[i][j].rgbtRed=(ori[i+1][j].rgbtRed+ori[i][j+1].rgbtRed+ori[i][j].rgbtRed)/3;
                    image[i][j].rgbtGreen=(ori[i+1][j].rgbtGreen+ori[i][j+1].rgbtGreen+ori[i][j].rgbtGreen)/3;
                    image[i][j].rgbtBlue=(ori[i+1][j].rgbtBlue+ori[i][j+1].rgbtBlue+ori[i][j].rgbtBlue)/3;

                }
                else if (j==(width-1))
                {
                    image[i][j].rgbtRed=(ori[i-1][j].rgbtRed+ori[i][j+1].rgbtRed+ori[i][j].rgbtRed)/3;
                    image[i][j].rgbtGreen=(ori[i-1][j].rgbtGreen+ori[i][j+1].rgbtGreen+ori[i][j].rgbtGreen)/3;
                    image[i][j].rgbtBlue=(ori[i-1][j].rgbtBlue+ori[i][j+1].rgbtBlue+ori[i][j].rgbtBlue)/3;

                }
                else
                {
                    image[i][j].rgbtRed=(ori[i-1][j].rgbtRed+ori[i][j+1].rgbtRed+ori[i+1][j].rgbtRed+ori[i][j].rgbtRed)/4;
                    image[i][j].rgbtGreen=(ori[i-1][j].rgbtGreen+ori[i][j+1].rgbtGreen+ori[i+1][j].rgbtGreen+ori[i][j].rgbtGreen)/4;
                    image[i][j].rgbtBlue=(ori[i-1][j].rgbtBlue+ori[i][j+1].rgbtBlue+ori[i+1][j].rgbtBlue+ori[i][j].rgbtBlue)/4;

                }

            }
            else if (i==(height-1))
            {
                if (j==0)
                {
                    image[i][j].rgbtRed=(ori[i][j-1].rgbtRed+ori[i+1][j].rgbtRed+ori[i][j].rgbtRed)/3;
                    image[i][j].rgbtBlue=(ori[i][j-1].rgbtBlue+ori[i+1][j].rgbtBlue+ori[i][j].rgbtBlue)/3;
                    image[i][j].rgbtGreen=(ori[i][j-1].rgbtGreen+ori[i+1][j].rgbtGreen+ori[i][j].rgbtGreen)/3;

                }
                else if (j==(width-1))
                {
                    image[i][j].rgbtRed=(ori[i-1][j].rgbtRed+ori[i][j-1].rgbtRed+ori[i][j].rgbtRed)/3;
                    image[i][j].rgbtGreen=(ori[i-1][j].rgbtGreen+ori[i][j-1].rgbtGreen+ori[i][j].rgbtGreen)/3;
                    image[i][j].rgbtBlue=(ori[i-1][j].rgbtBlue+ori[i][j-1].rgbtBlue+ori[i][j].rgbtBlue)/3;

                }
                else
                {
                    image[i][j].rgbtRed=(ori[i-1][j].rgbtRed+ori[i][j-1].rgbtRed+ori[i+1][j].rgbtRed+ori[i][j].rgbtRed)/4;
                    image[i][j].rgbtGreen=(ori[i-1][j].rgbtGreen+ori[i][j-1].rgbtGreen+ori[i+1][j].rgbtGreen+ori[i][j].rgbtGreen)/4;
                    image[i][j].rgbtBlue=(ori[i-1][j].rgbtBlue+ori[i][j-1].rgbtBlue+ori[i+1][j].rgbtBlue+ori[i][j].rgbtBlue)/4;


                }

            }
            else
            {
                if (j==0)
                {
                    image[i][j].rgbtRed=(ori[i][j+1].rgbtRed+ori[i][j-1].rgbtRed+ori[i+1][j].rgbtRed+ori[i][j].rgbtRed)/4;
                    image[i][j].rgbtGreen=(ori[i][j+1].rgbtGreen+ori[i][j-1].rgbtGreen+ori[i+1][j].rgbtGreen+ori[i][j].rgbtGreen)/4;
                    image[i][j].rgbtBlue=(ori[i][j+1].rgbtBlue+ori[i][j-1].rgbtBlue+ori[i+1][j].rgbtBlue+ori[i][j].rgbtBlue)/4;

                }
                else if (j==width-1)
                {
                    image[i][j].rgbtRed=(ori[i][j+1].rgbtRed+ori[i][j-1].rgbtRed+ori[i-1][j].rgbtRed+ori[i][j].rgbtRed)/4;
                    image[i][j].rgbtGreen=(ori[i][j+1].rgbtGreen+ori[i][j-1].rgbtGreen+ori[i-1][j].rgbtGreen+ori[i][j].rgbtGreen)/4;
                    image[i][j].rgbtBlue=(ori[i][j+1].rgbtBlue+ori[i][j-1].rgbtBlue+ori[i-1][j].rgbtBlue+ori[i][j].rgbtBlue)/4;

                }
                else
                {
                    image[i][j].rgbtRed=(ori[i][j+1].rgbtRed+ori[i][j-1].rgbtRed+ori[i-1][j].rgbtRed+ori[i+1][j].rgbtRed+ori[i][j].rgbtRed)/5;
                    image[i][j].rgbtGreen=(ori[i][j+1].rgbtGreen+ori[i][j-1].rgbtGreen+ori[i-1][j].rgbtGreen+ori[i+1][j].rgbtGreen+ori[i][j].rgbtGreen)/5;
                    image[i][j].rgbtBlue=(ori[i][j+1].rgbtBlue+ori[i][j-1].rgbtBlue+ori[i-1][j].rgbtBlue+ori[i+1][j].rgbtBlue+ori[i][j].rgbtBlue)/5;

                }
            }

        }

    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int leri[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}};
    int updo[3][3]={{-1,-2,-1},{0,0,0},{1,2,1}};

    RGBTRIPLE ori[height+2][width+2];
    for (int i=0; i<width+2;i++)
    {
        ori[0][i].rgbtRed=0;
        ori[0][i].rgbtGreen=0;
        ori[0][i].rgbtBlue=0;
        ori[height+1][i].rgbtRed=0;
        ori[height+1][i].rgbtGreen=0;
        ori[height+1][i].rgbtBlue=0;
    }
    for (int j=1; j<height+2;j++)
    {
        ori[j][0].rgbtRed=0;
        ori[j][0].rgbtGreen=0;
        ori[j][0].rgbtBlue=0;
        ori[j][width+1].rgbtRed=0;
        ori[j][width+1].rgbtGreen=0;
        ori[j][width+1].rgbtBlue=0;
    }
    for (int i=1;i<height+1;i++)
    {
        for (int j=1;j<width+1;j++)
        {
            ori[i][j]=image[i-1][j-1];

        }
    }

    for (int i=1; i<height+1;i++)
    {
        for (int j=1; j<width+1;j++)
        {

            int leriRed=ori[i-1][j-1].rgbtRed*leri[0][0]+ori[i-1][j].rgbtRed*leri[0][1]+ori[i-1][j+1].rgbtRed*leri[0][2]+ori[i][j-1].rgbtRed*leri[1][0]+ori[i][j].rgbtRed*leri[1][1]+ori[i][j+1].rgbtRed*leri[1][2]+ori[i+1][j-1].rgbtRed*leri[2][0]+ori[i+1][j].rgbtRed*leri[2][1]+ori[i+1][j+1].rgbtRed*leri[2][2];

            int leriGreen=ori[i-1][j-1].rgbtGreen*leri[0][0]+ori[i-1][j].rgbtGreen*leri[0][1]+ori[i-1][j+1].rgbtGreen*leri[0][2]+ori[i][j-1].rgbtGreen*leri[1][0]+ori[i][j].rgbtGreen*leri[1][1]+ori[i][j+1].rgbtGreen*leri[1][2]+ori[i+1][j-1].rgbtGreen*leri[2][0]+ori[i+1][j].rgbtGreen*leri[2][1]+ori[i+1][j+1].rgbtGreen*leri[2][2];

            int leriBlue=ori[i-1][j-1].rgbtBlue*leri[0][0]+ori[i-1][j].rgbtBlue*leri[0][1]+ori[i-1][j+1].rgbtBlue*leri[0][2]+ori[i][j-1].rgbtBlue*leri[1][0]+ori[i][j].rgbtBlue*leri[1][1]+ori[i][j+1].rgbtBlue*leri[1][2]+ori[i+1][j-1].rgbtBlue*leri[2][0]+ori[i+1][j].rgbtBlue*leri[2][1]+ori[i+1][j+1].rgbtBlue*leri[2][2];
            int updoRed=ori[i-1][j-1].rgbtRed*updo[0][0]+ori[i-1][j].rgbtRed*updo[0][1]+ori[i-1][j+1].rgbtRed*updo[0][2]+ori[i][j-1].rgbtRed*updo[1][0]+ori[i][j].rgbtRed*updo[1][1]+ori[i][j+1].rgbtRed*updo[1][2]+ori[i+1][j-1].rgbtRed*updo[2][0]+ori[i+1][j].rgbtRed*updo[2][1]+ori[i+1][j+1].rgbtRed*updo[2][2];

            int updoGreen=ori[i-1][j-1].rgbtGreen*updo[0][0]+ori[i-1][j].rgbtGreen*updo[0][1]+ori[i-1][j+1].rgbtGreen*updo[0][2]+ori[i][j-1].rgbtGreen*updo[1][0]+ori[i][j].rgbtGreen*updo[1][1]+ori[i][j+1].rgbtGreen*updo[1][2]+ori[i+1][j-1].rgbtGreen*updo[2][0]+ori[i+1][j].rgbtGreen*updo[2][1]+ori[i+1][j+1].rgbtGreen*updo[2][2];
            int updoBlue=ori[i-1][j-1].rgbtBlue*updo[0][0]+ori[i-1][j].rgbtBlue*updo[0][1]+ori[i-1][j+1].rgbtBlue*updo[0][2]+ori[i][j-1].rgbtBlue*updo[1][0]+ori[i][j].rgbtBlue*updo[1][1]+ori[i][j+1].rgbtBlue*updo[1][2]+ori[i+1][j-1].rgbtBlue*updo[2][0]+ori[i+1][j].rgbtBlue*updo[2][1]+ori[i+1][j+1].rgbtBlue*updo[2][2];

            if (round(sqrt(pow(leriRed,2)+pow(updoRed,2)))>=255)
            {
                image[i-1][j-1].rgbtRed=255;
            }
            else
            {
                image[i-1][j-1].rgbtRed=round(sqrt(pow(leriRed,2)+pow(updoRed,2)));
            }
            

            if (round(sqrt(pow(leriGreen,2)+pow(updoGreen,2)))>=255)
            {
                image[i-1][j-1].rgbtGreen=255;
            }
            else
            {
                image[i-1][j-1].rgbtGreen=round(sqrt(pow(leriGreen,2)+pow(updoGreen,2)));
            }

            if (round(sqrt(pow(leriBlue,2)+pow(updoBlue,2)))>=255)
            {
                image[i-1][j-1].rgbtBlue=255;
            }
            else
            {
                image[i-1][j-1].rgbtBlue=round(sqrt(pow(leriBlue,2)+pow(updoBlue,2)));
            }


        }
    }





    return;
}
