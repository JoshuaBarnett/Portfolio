#include <stdio.h>
#include <math.h>
#define  PICSIZE 256
#define  MAXMASK 100

         int    pic[PICSIZE][PICSIZE];
         double outputX[PICSIZE][PICSIZE];
         double outputY[PICSIZE][PICSIZE];
         double maskX[MAXMASK][MAXMASK];
         double maskY[MAXMASK][MAXMASK];
         double mag[PICSIZE][PICSIZE];
         double peaks[PICSIZE][PICSIZE];
         int histo[PICSIZE];
	 double final[PICSIZE][PICSIZE];

main(argc,argv)
int argc;
char **argv;
{
        int     i, j, p, q, mr, centx, centy, picPercent, HI, LO, moved, sum;
        double  sum1, sum2, sig, maxival, percent, dir;
        FILE    *fo1, *fo2, *fo3, *fp1, *fopen();
        sig = 3;
        printf("Enter sigma:\n");
        scanf("%lf",&sig);
        printf("Enter percent:\n");
        scanf("%lf",&percent);

        fp1=fopen("garb34.pgm","rb");

	fo1=fopen("CannyMagGrad.pgm","wb");
	fo2=fopen("CannyPeaks.pgm","wb");
	fo3=fopen("CannyFinal.pgm","wb");


          /*change files to .pgm files*/
	fprintf(fo1, "P5\n256 256\n255\n");
	fprintf(fo2, "P5\n256 256\n255\n");
	fprintf(fo3, "P5\n256 256\n255\n");


        mr = (int)(sig * 3);
        centx = (MAXMASK / 2);
        centy = (MAXMASK / 2);
    char tempC;
    int tempI;

    fscanf(fp1,"%c %c %c %d %d %c %d %c",&tempC,&tempC,&tempC,&tempI,&tempI,&tempC,&tempI,&tempC); //discard pgm header
        for (i=0;i<256;i++)
        { for (j=0;j<256;j++)
                {
                  pic[i][j]  =  getc (fp1);
                  pic[i][j]  &= 0377;
                }
        }

        for (p=-mr;p<=mr;p++) //Gaussian Blur
        {  for (q=-mr;q<=mr;q++)
           {
             maskX[p+centy][q+centx] = ((-1*q) * (exp((-1*(q*q + p*p))/(2 * sig * sig))));
             maskY[p+centy][q+centy] = ((-1*p) * (exp((-1*(q*q + p*p))/(2 * sig * sig))));
           }
        }

        for (i=mr;i<=255-mr;i++) //Get Magnitude of Gradients
        { for (j=mr;j<=255-mr;j++)
          {
             sum1 = 0;
             sum2 = 0;
             for (p=-mr;p<=mr;p++)
             {
                for (q=-mr;q<=mr;q++)
                {
                   sum1 += pic[i+p][j+q] * maskX[p+centy][q+centx];
                   sum2 += pic[i+p][j+q] * maskY[p+centy][q+centx];
                }
             }
             outputX[i][j] = sum1;
             outputY[i][j] = sum2; 
          }
        }

	maxival = 0;
	for (i=mr;i<=255-mr;i++)
        { for (j=mr;j<=255-mr;j++) //Finish the magnitude of gradients by combining horizontal and vertical
          {
             mag[i][j]=sqrt((double)((outputX[i][j]*outputX[i][j]) + (outputY[i][j]*outputY[i][j])));
             if (mag[i][j] > maxival)
                maxival = mag[i][j];
           }
        }


        for (i = mr; i <= 255 - mr; i++) //Find the Peaks
        {
        	for (j = mr; j <= 255 - mr; j++)
        	{   if (outputX[i][j]==0.0) outputX[i][j]=0.00001;
        		dir = outputY[i][j]/ outputX[i][j];

        		if ((dir >= -0.414) && (dir < 0.414))
        		{
        			if ((mag[i][j] > mag[i][j+1]) && (mag[i][j] > mag[i][j-1]))
        				peaks[i][j] = 255;
        		}

        		else if ((dir >= 0.414) && (dir < 2.414))
        		{
        			if ((mag[i][j] > mag[i+1][j+1]) && (mag[i][j] > mag[i-1][j-1]))
        				peaks[i][j] = 255;
        		}

        		else if ((dir < -0.414) && (dir >= -2.414))
        		{
        			if ((mag[i][j] > mag[i+1][j-1]) && (mag[i][j] > mag[i-1][j+1]))
        				peaks[i][j] = 255;
        		}

        		else
        		{
        			if ((mag[i][j] > mag[i+1][j]) && (mag[i][j] > mag[i-1][j]))
        				peaks[i][j] = 255;
        		}
        	}
        }

        for (i=0;i<256;i++) //Print file outputs for the Magnitude Gradients as well as the Peaks
        { for (j=0;j<256;j++)
          {
             mag[i][j] = ((mag[i][j] / maxival) * 255);
             fprintf(fo1, "%c", (char)((int)(mag[i][j])));
             fprintf(fo2, "%c", (char)((int)(peaks[i][j])));
          }
        }


       	for (i = 0; i < 256; i++) //Create a histogram of magnitudes
       	{
       		histo[i] = 0;
       	}

        for (i = mr; i < 256 - mr; i++)
        {
        	for (j= mr; j < 256 - mr; j++)
        	{
        		histo[(int)mag[i][j]]++;
        	}
        }


        picPercent = (int) (percent * 256 *256);

        sum = 0;

        for (i = 255; i >= 0; i--) //Find all parts of histogram that surpass the first threshold
        {
        	sum += histo[i];
        	if (sum >= picPercent)
        	{
        		HI = i;
        		break;
        	}
        }

        LO = .35 * HI; //low threshold is 35% of the high threshold


        printf("HIGH = %d\nLOW = %d\n\n", HI, LO);


        for (i = mr; i <= 255 - mr; i++) //mark those which hit the high threshold, discard all of those lower than low threshold
        {
        	for (j = mr; j <= 255 - mr; j++)
        	{
        		if (peaks[i][j] == 255)
        		{
        			if (mag[i][j] > HI)
        			{
        				final[i][j] = 255;
        				peaks[i][j] = 0;
        			}

        			else if (mag[i][j] < LO)
        			{
        				peaks[i][j] = 0;
        			}
        		}
        	}
	}

	moved = 1;
	while (moved) //pick up those who are above the low threshold and attached to portions which hit the high threshold
	{
		moved = 0;
		for (i = mr; i <= 255 - mr; i++)
		{
			for (j = mr; j <= 255 - mr; j++)
			{
				if (peaks[i][j] == 255)
				{
					for (p = -1; p <= 1; p++)
					{
						for (q = -1; q <= 1; q++)
						{
							if (final[i + p][j + q] == 255)
							{
								final[i][j] = 255;
								peaks[i][j] = 0;
								moved = 1;
							}
						}
					}
				}
			}
		}
	}

	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++) //output the final Canny Edge Detection
		{
			fprintf(fo3, "%c", (char)((int)(final[i][j])));
		}
	}

}
