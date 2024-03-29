#pragma once
#include <qtimagelib.h>

/*
 File: pa1.h
 Authors: Joe Manke, Jonathan Tomes
 Description:
     The header file for programing assignment number 1.
     Contains the necessary information for Qt and qtimagelib
     to create the menu and interface for the program.
 */
class PointProcesses: public QObject
{
    Q_OBJECT;

  public slots:
    bool Menu_Color_Grayscale(Image &image);
    bool Menu_Color_Negate(Image &image);
    bool Menu_Color_Brighten(Image &image);
    bool Menu_Color_DiscretePseudocolor(Image &image);
    bool Menu_Color_ContinuousPseudocolor(Image &image);
    bool Menu_Color_Decolorize(Image &image);

    bool Menu_Intensity_BinaryThreshold(Image &image);
    bool Menu_Intensity_Contrast(Image &image);
    bool Menu_Intensity_AutomatedContrastStretch(Image &image);
    bool Menu_Intensity_ModifiedContrastStretch(Image &image);
    bool Menu_Intensity_Gamma(Image &image);
    bool Menu_Intensity_Compress(Image &image);
    bool Menu_Intensity_HistogramEqualization(Image &image);
    bool Menu_Intensity_HistogramEqualizationWithClipping(Image &image);
    bool Menu_Intensity_Posterize(Image &image);

    bool Menu_Other_DisplayHistogram(Image &image);
};
