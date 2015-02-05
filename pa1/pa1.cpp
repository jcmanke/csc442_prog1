#include "pa1.h"
#include <cmath>
#include <vector>

using namespace std;

int main( int argc, char *argv[] )
{
    PointProcesses obj;
    ImageApp app( argc, argv );
    app.AddActions( &obj );
    return app.Start();
}

/*
 Author: Joe Manke

 Converts an image to grayscale.
 */
bool PointProcesses::Menu_Point_Grayscale(Image &image)
{
    for(unsigned int y = 0; y < image.Height(); y++)
    {
        for(unsigned int x = 0; x < image.Width(); x++)
        {
            Pixel pixel = image[y][x];
            int gray = 0.3 * pixel.Red() + 0.59 * pixel.Green() + 0.11 * pixel.Blue();
            image[y][x].SetGray(gray);
        }
    }
    return true;
}

/*
 Author: Joe Manke

 Negates an image.
 */
bool PointProcesses::Menu_Point_Negate(Image &image)
{
    for(uint y = 0; y < image.Height(); y++)
    {
        for(uint x = 0; x < image.Width(); x++)
        {
            Pixel pixel = image[y][x];

            uchar red = 255 - pixel.Red();
            uchar blue = 255 - pixel.Blue();
            uchar green = 255 - pixel.Green();

            image[y][x].SetRGB(red, green, blue);
        }
    }
    return true;
}

bool PointProcesses::Menu_Point_BinaryThreshold(Image &image)
{
    return true;
}

bool PointProcesses::Menu_Point_Posterize(Image &image)
{
    return true;
}

/*
 Author: Joe Manke

 Adjusts an image's brightness by adding a value provided by the user to each
    pixel's RGB values.
 */
bool PointProcesses::Menu_Point_Brightness(Image &image)
{
    int brighten = 20;

    if(getParams(brighten))
    {
        for(uint y = 0; y < image.Height(); y++)
        {
            for(uint x = 0; x < image.Width(); x++)
            {
                Pixel pixel = image[y][x];

                uchar red = qMin(pixel.Red() + brighten, 255);
                uchar green = qMin(pixel.Green() + brighten, 255);
                uchar blue = qMin(pixel.Blue() + brighten, 255);

                image[y][x].SetRGB(red, green, blue);
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool PointProcesses::Menu_Point_Contrast(Image &image)
{
    return true;
}

/*
 Author: Joe Manke

 Adjusts the image's intensity to by exponentiating each pixel's intensity
    by a gamma value provided by the user.
 */
bool PointProcesses::Menu_Point_Gamma(Image &image)
{
    double gamma = 0.5;

    if(getParams(gamma))
    {
        for(uint y = 0; y < image.Height(); y++)
        {
            for(uint x = 0; x < image.Width(); x++)
            {
                int intensity = pow(image[y][x].Intensity(), gamma);
                image[y][x].SetIntensity(intensity);
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}
/*
 Author: Jonathan Tomes

     Adjusts the images intensity by a simple log function down into a meaningful range.
 */
bool PointProcesses::Menu_Point_Compress(Image &image)
{
    int LUT[256];

    for(int i = 0; i < 256; i++)
    {
        LUT[i] = log(i+1.0) * (255/log(256.0)) + 0.5;
        if(LUT[i] > 255)
            LUT[i] = 255;
        if(LUT[i] < 0)
            LUT[i] = 0;
    }

    for(unsigned int y = 0; y < image.Height(); y++)
    {
        for(unsigned int x = 0; x < image.Width(); x++)
        {
            image[y][x] = LUT[image[y][x]];
        }
    }
    return true;
}
/*
 Author: Jonathan Tomes
     Useses a discrete scale to artificially color an image.
 */
bool PointProcesses::Menu_Point_DiscretePseudocolor(Image &image)
{
    int lut[256][3];
    int i = 0;
    for(; i < 32; i++)
    {
        lut[i][0]= 0;
        lut[i][1]= 0;
        lut[i][2]= 0;
    }

    for(; i< 64; i++)
    {
        lut[i][0]=0;
        lut[i][1]=0;
        lut[i][2]=255;
    }

    for(; i < 96; i++)
    {
        lut[i][0]= 128;
        lut[i][1]= 0;
        lut[i][2]= 128;
    }

    for(; i < 128; i++)
    {
        lut[i][0] = 255;
        lut[i][1] = 0;
        lut[i][2] = 0;
    }

    for(; i < 160; i++)
    {
        lut[i][0] = 0;
        lut[i][1] = 128;
        lut[i][2] = 128;
    }

    for(; i < 192; i++)
    {
        lut[i][0] = 0;
        lut[i][1] = 255;
        lut[i][2] = 0;
    }

    for(; i < 224; i++)
    {
        lut[i][0] = 255;
        lut[i][1] = 255;
        lut[i][2] = 0;
    }

    for(; i < 256; i++)
    {
        lut[i][0] = 255;
        lut[i][1] = 255;
        lut[i][2] = 255;
    }

    for(unsigned int y = 0; y < image.Height(); y++)
    {
        for(unsigned int x = 0; x < image.Height(); x++)
        {
            unsigned char red = lut[image[y][x]][0];
            unsigned char green = lut[image[y][x]][1];
            unsigned char blue = lut[image[y][x]][2];

            image[y][x].SetRGB(red, green, blue);
        }
    }

    return true;
}

bool PointProcesses::Menu_Point_ContinuousPseudocolor(Image &image)
{
    int lutR[256];
    int lutG[256];
    int lutB[256];

    lutR[0] = 0;
    lutG[0] = 0;
    lutB[0] = 0;



    // set the remaining blue value
    int blue = 255;
    for(int i = 1; i < 126; i++)
    {
        lutB[i] = blue;
        blue -= 2;
        if(blue < 0)
        {
            blue = 0;
        }
    }
    for(int i = 126; i < 255; i++)
    {
        lutB[i] = 0;
    }

    // Set up the Reds
    int red = 1;
    for(int i = 0; i < 128; i++)
    {
        lutR[i] = red;
        red += 2;
        if(red > 255)
        {
            red = 255;
        }
    }

    red = 255;
    for(int i = 128; i < 255; i++)
    {
        lutR[i] = 255;
        red -= 2;
        if(red < 0)
        {
            red = 0;
        }
    }

    // set the Greens
    for(int i =1; i < 130; i++)
    {
        lutG[i] = 0;
    }
    int green = 0;
    for(int i = 130; i < 255; i++)
    {
        lutG[i] = green;
        green += 2;
        if(green > 255)
        {
            green = 255;
        }
    }

    // Make the highest value white
    lutR[255] = 255;
    lutG[255] = 255;
    lutB[255] = 255;

    for(uint y = 0; y < image.Height(); y++)
    {
        for(uint x = 0; x < image.Width(); x++)
        {
            int intensity = image[y][x].Intensity();

            uchar red = lutR[intensity];
            uchar green = lutG[intensity];
            uchar blue = lutB[intensity];

            image[y][x].SetRGB(red, green, blue);
        }
    }
    return true;
}

/*
 Author: Joe Manke

 Displays a histogram using the QtImageLib function.
 */
bool PointProcesses::Menu_Point_DisplayHistogram(Image &image)
{
    displayHistogram(image);
    return true;
}

/*
 Author: Joe Manke

 Performs an automated contrast stretch by scaling each pixel's intensity value
    to relative to the minimum and maximum intensities of the entire image.
 */
bool PointProcesses::Menu_Point_AutomatedContrastStretch(Image &image)
{
    vector<uint> histogram = image.Histogram();

    uint min = 0, max = 0;

    //find minimum intensity
    int i = 0;
    while(histogram[i] == 0 && i < 256) i++;
    min = i;

    //find maximum intensity
    i = 255;
    while(histogram[i] == 0 && i >= 0) i--;
    max = i;

    double scale = 255.0 / (max - min);

    for(uint y = 0; y < image.Height(); y++)
    {
        for(uint x = 0; x < image.Width(); x++)
        {
            int intensity = image[y][x].Intensity();
            intensity = scale * (intensity - min);
            image[y][x].SetIntensity(intensity);
        }
    }

    return true;
}

bool PointProcesses::Menu_Point_ModifiedContrastStretch(Image &image)
{
    return true;
}

bool PointProcesses::Menu_Point_HistogramEqualization(Image &image)
{
    return true;
}

bool PointProcesses::Menu_Point_HistogramEqualizationWithClipping(Image &image)
{
    return true;
}

bool PointProcesses::Menu_Point_TodoPickAnotherOne(Image &image)
{
    return true;
}
