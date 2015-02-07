/*
 Program: Point Image Processor
 For: CSC442, Spring 2015
 Professor: Dr. Weiss
 Authors: Joe Manke, Jonathan Tomes

 Description:
     Use qtimage lib to creat a GUI image manipulation program.
 Has the ability to perform several point process manipulations on images.


 */

#include "pa1.h"
#include <cmath>
#include <vector>

/*
 File: pa1.cpp
 Authors: Joe Manke, Jonathan Tomes

 Description:
     The main file and processes for the program. Handles logic behind the
     menu items.
 */

using namespace std;

bool BinaryThreshold(Image &image, int threshold);
bool Posterize(Image &image, int numLevels);
bool Contrast(Image &image, int iMin, int iMax);
bool Decolorize(Image &image, double percentRed, double percentGreen, double percentBlue);

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
bool PointProcesses::Menu_Color_Grayscale(Image &image)
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
bool PointProcesses::Menu_Color_Negate(Image &image)
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

/*
 Author: Joe Manke

 Adjusts an image's brightness by adding a value provided by the user to each
    pixel's RGB values.
 */
bool PointProcesses::Menu_Color_Brighten(Image &image)
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

/*
 Function: Menu_Color_DiscretePseudocolor
 Author: Jonathan Tomes
 Description:
     Uses a discrete scale to artificially color an image.
 in & out:
    image - the image being manipulated.
 */
bool PointProcesses::Menu_Color_DiscretePseudocolor(Image &image)
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
        for(unsigned int x = 0; x < image.Width(); x++)
        {
            unsigned char red = lut[image[y][x]][0];
            unsigned char green = lut[image[y][x]][1];
            unsigned char blue = lut[image[y][x]][2];

            image[y][x].SetRGB(red, green, blue);
        }
    }

    return true;
}

/*
 Function: Menu_Color_ContinuousPseudocolor
 Author: Jonathan Tomes
 Description:
     Colors an image using a continous coloring method.
     Blue starts high and ramps low
     Red is a triangle about the center
     and green starts low and ramps high.
 in & out:
     image - the image being manipulated.
*/
bool PointProcesses::Menu_Color_ContinuousPseudocolor(Image &image)
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
 Function: Menu_Color_Decolorize
 Authors: Jonathon Tomes, Joe Manke
 Description:
    Handles the menu logic for the Decolorize function.
    Retrieves the percentages of red, green and blue values
    to be removed from the image from the user.
 in & out:
    image - the image being manipulated.
 */
bool PointProcesses::Menu_Color_Decolorize(Image &image)
{
    double percentRed = 0, percentGreen = 0, percentBlue = 0;
    if(!Dialog("Decolorize")
        .Add(percentRed, "Percent of red to remove from image", 0, 1.00)
        .Add(percentGreen, "Percent of green to remove from image", 0, 1.00)
        .Add(percentBlue, "Percent of blue to remove from image", 0, 1.00)
        .Show())
        return false;

    return Decolorize(image, percentRed, percentGreen, percentBlue);
}

/*
 Function: Decolorize
 Authors: Jonathan Tomes, Joe Manke
 Description:
     Actual logic for decolorizing an image.
 in & out:
     image - the image being manipulated.
 in:
     percentRed - percentage of red to remove.
     percentGreen - percentage of green to remove.
     percentBlue - percentage of blue to remove.
 */
bool Decolorize(Image &image, double percentRed, double percentGreen, double percentBlue)
{
    for(uint y = 0; y < image.Height(); y++)
    {
        for(uint x = 0; x < image.Width(); x++)
        {
            Pixel pixel = image[y][x];

            uchar red = pixel.Red() * (1.0 - percentRed);
            uchar green = pixel.Green() * (1.0 - percentGreen);
            uchar blue = pixel.Blue() * (1.0 - percentBlue);

            image[y][x].SetRGB(red, green, blue);
        }
    }
    return true;
}

/*
 Function: Menu_Intensitiy_BinaryThreshold
 Author: Jonathan Tomes

 Description:
     Handles the menu for binary thresholding and passes
     it on to a method.

 in & out:
    image - the image to manipulate.
 */
bool PointProcesses::Menu_Intensity_BinaryThreshold(Image &image)
{
    int threshold = 0;
    if(!Dialog("Binary Threshold").Add(threshold,"Threshold Value", 0, 255).Show())
        return false;


    return BinaryThreshold(image, threshold);
}

/*
 Function: BinaryThreshold
 Author: Jonathan Tomes

 Description:
     Actual logic for the binary threshold manipulation.
     Sets the intensity for values below a threshold to zero
     and at the threshold and above to 255;
 in & out:
     image - the image to manipulate
 in:
     threshold - the cutoff intensity level
 */
bool BinaryThreshold(Image &image, int threshold)
{
    uchar lut[256];

    for(int i = 0; i<threshold; i++)
    {
        lut[i] = 0;
    }

    for(int i = threshold; i < 256; i++)
    {
        lut[i] = 255;
    }

    for(uint y =0; y < image.Height(); y++)
    {
        for(uint x = 0; x < image.Width(); x++)
        {
            image[y][x] = lut[image[y][x]];
        }
    }
    return true;
}

/*
 Function: Menu_Intensity_Contrast
 Author: Jonathan Tomes
 Description:
     Handles the menu operation for contrasting an image
     getting the min and max values from the user
     and sending it along to be processed.
  in & out:
    image - the image to manipulate
 */
bool PointProcesses::Menu_Intensity_Contrast(Image &image)
{
    int iMin = 0;
    int iMax = 255;
    if(!Dialog("Contrast")
        .Add(iMin, "Minium intensity", 0, 128)
        .Add(iMax,"Maxium Intensity", 128, 255).Show())
        return false;
    return Contrast(image, iMin, iMax);
}

/*
 Function: Contrast
 Author: Jonathan Tomes
 Description:
     A method to modify the contrast of an image
     by doing a contrast by the given iMin and iMax.
 in & out:
     image - the image being manipulated.
 */
bool Contrast(Image &image, int iMin, int iMax)
{
    double scale = 255.0/(iMax - iMin);
    uchar lut[256];

    for(int i = 0; i < 256; i++)
    {
        int intensity = scale *(i - iMin);
        if(intensity < 0)
        {
            intensity = 0;
        }
        if(intensity > 255)
        {
            intensity = 255;
        }
        lut[i] = intensity;
    }

    for(uint y = 0; y < image.Height(); y++)
    {
        for(uint x = 0; x < image.Width(); x++)
        {
            image[y][x] = lut[image[y][x].Intensity()];
        }
    }

    return true;
}

/*
 Author: Joe Manke

 Performs an automated contrast stretch by scaling each pixel's intensity value
    to relative to the minimum and maximum intensities of the entire image.
 */
bool PointProcesses::Menu_Intensity_AutomatedContrastStretch(Image &image)
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

/*
 Function: Menu_Intensity_ModifiedContrastStretch
 Author: Jonathan Tomes
 Description:
     Handles the menu for the modified contrast stretch.
 in & out:
    image - the image being manipulated.
 */
bool PointProcesses::Menu_Intensity_ModifiedContrastStretch(Image &image)
{
    double iMin = 0;
    double iMax = 0;
    if(!Dialog("Modified Contrast Stretch")
        .Add(iMin, "Left Ignore", 0, 1.0)
        .Add(iMax,"Right Ignore", 0, 1.0).Show())
        return false;

    vector<uint> histogram = image.Histogram();

    uint min = 0, max = 0;
    uint numLeftIgnore = iMin* (image.Width()*image.Height());
    uint numRightIgnore = iMax*(image.Width()*image.Height());

    //find minimum intensity
    int i = 0;
    uint sum = 0;
    while(sum < numLeftIgnore && i < 256)
    {
        sum += histogram[i];
        i++;
    }
    min = i;

    //find maximum intensity
    i = 255;
    sum = 0;
    while(sum< numRightIgnore && i >= 0)
    {
        sum += histogram[i];
        i--;
    }
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

/*
 Author: Joe Manke

 Adjusts the image's intensity to by exponentiating each pixel's intensity
    by a gamma value provided by the user.
 */
bool PointProcesses::Menu_Intensity_Gamma(Image &image)
{
    double gamma = 0.5;

    if(getParams(gamma))
    {
        for(uint y = 0; y < image.Height(); y++)
        {
            for(uint x = 0; x < image.Width(); x++)
            {
                int intensity = pow(image[y][x].Intensity() / 255.0, gamma) * 255;
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
 Function: Menu_Intensity_Compress
 Author: Jonathan Tomes
 Description:
     Adjusts the images intensity by a simple log function down into a meaningful range.
 in & out:
    image - the image to manipulate
 */
bool PointProcesses::Menu_Intensity_Compress(Image &image)
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
 Function: Menu_Intensity_HistogramEqualization
 Author: Jonathan Tomes
 Description:
    Performs a historgram equalization on an image.
 in & out:
    image - the image being manipulated.
 */
bool PointProcesses::Menu_Intensity_HistogramEqualization(Image &image)
{
    vector<uint> histogram = image.Histogram();
    uint CDF[256];
    uint lut[256];
    uint totalPixels = image.Height() * image.Width();
    CDF[0] = histogram[0];
    for(int i = 1; i < 256; i++)
    {
        CDF[i] = CDF[i-1] + histogram[i];
    }

    for(int i = 0; i < 256; i++)
    {
        lut[i] = CDF[i] * (255.0/totalPixels);
        if(lut[i] > 255)
        {
            lut[i] = 255;
        }
        if(lut[i] < 0)
        {
            lut[i] = 0;
        }
    }

    for(uint y = 0; y < image.Height(); y++)
    {
        for(uint x = 0; x < image.Width(); x++)
        {
            image[y][x] = lut[image[y][x]];
        }
    }

    return true;
}

/*
 Function: Menu_Intensity_HistogramEqualizationWithClipping
 Author: Jonathan Tomes
 Description:
     Performs a historgram equalization on an image. Includes clipping off of
     a number of pixels
 in & out:
    image - the image being manipulated.
 */
bool PointProcesses::Menu_Intensity_HistogramEqualizationWithClipping(Image &image)
{
    double clipPercent = 0;
    if(!Dialog("Equalize with Clipping")
        .Add(clipPercent,"Clip Ammount", 0, 1.0)
        .Show())
        return false;


    vector<uint> histogram = image.Histogram();
    uint CDF[256];
    uint lut[256];
    uint totalPixels = image.Height() * image.Width();
    double clipAmmount = clipPercent * totalPixels;
    uint newTotal = 0;
    for(int i = 0; i < 256; i++)
    {
        if(histogram[i] > clipAmmount)
        {
            histogram[i]= clipAmmount;
        }
        newTotal += histogram[i];
    }
    CDF[0] = histogram[0];
    for(int i = 1; i < 256; i++)
    {

        CDF[i] = CDF[i-1] + histogram[i];
    }

    for(int i = 0; i < 256; i++)
    {
        lut[i] = CDF[i] * (255.0/newTotal);
        if(lut[i] > 255)
        {
            lut[i] = 255;
        }
        if(lut[i] < 0)
        {
            lut[i] = 0;
        }
    }

    for(uint y = 0; y < image.Height(); y++)
    {
        for(uint x = 0; x < image.Width(); x++)
        {
            image[y][x] = lut[image[y][x]];
        }
    }

    return true;
}

/*
 Function:Menu_Other-Posterize
 Author: Jonathan Tomes
 Description:
     Handles the menu for posterize, passing the number of levels
     to the posterize function.
 in & out:
     image - the image to manipulate.
 */
bool PointProcesses::Menu_Intensity_Posterize(Image &image)
{
    int numLevels = 2;
    if(!Dialog("Posterize")
        .Add(numLevels, "Number of Levels", 2, 32).Show())
        return false;

    return Posterize(image, numLevels);
}

/*
 Function: Posterize
 Author: Jonathan Tomes
 Description:
     Handels the actual posterizing of an image.
 in & out:
     image - the image to manipulate
 */
bool Posterize(Image &image, int numLevels)
{
    int numberPerLevel = 256.0/numLevels;

    int scale = 0;
    uchar lut[256];
    int count = 0;

    // initialize lut to 255.

    for(int i = 0; i < 256; i++)
    {
        lut[i] = 255;
    }

    for(int i = 0; i < numLevels; i++)
    {
        for(int j = 0; j < numberPerLevel; j++)
        {
            lut[count] = scale;
            count++;
        }
        scale += numberPerLevel;
    }

    for(uint y = 0; y < image.Height(); y++)
    {
        for(uint x = 0; x < image.Width(); x++)
        {
            image[y][x] = lut[image[y][x]];
        }
    }
    return true;
}

/*
 Author: Joe Manke

 Displays a histogram using the QtImageLib function.
 */
bool PointProcesses::Menu_Other_DisplayHistogram(Image &image)
{
    displayHistogram(image);
    return true;
}
