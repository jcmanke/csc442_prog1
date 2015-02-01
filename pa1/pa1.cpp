#include "pa1.h"

// main function will always follow this format
int main( int argc, char *argv[] )
{
    PointProcesses obj;
    ImageApp app( argc, argv );
    app.AddActions( &obj );
    return app.Start();
}

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

bool PointProcesses::Menu_Point_Negate(Image &image)
{
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

bool PointProcesses::Menu_Point_Brightness(Image &image)
{
    return true;
}

bool PointProcesses::Menu_Point_Contrast(Image &image)
{
    return true;
}

bool PointProcesses::Menu_Point_Gamma(Image &image)
{
    return true;
}

bool PointProcesses::Menu_Point_Compress(Image &image)
{
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

bool PointProcesses::Menu_Point_DisplayHistogram(Image &image)
{
    return true;
}

bool PointProcesses::Menu_Point_AutomatedContrastStretch(Image &image)
{
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
