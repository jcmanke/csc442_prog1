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

bool PointProcesses::Menu_Point_DiscretePseudocolor(Image &image)
{
    return true;
}

bool PointProcesses::Menu_Point_ContinuousPseudocolor(Image &image)
{
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
