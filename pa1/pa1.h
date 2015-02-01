#pragma once
#include <qtimagelib.h>

class PointProcesses: public QObject
{
    Q_OBJECT;

  public slots:
    bool Menu_Point_Grayscale(Image &image);
    bool Menu_Point_Negate(Image &image);
    bool Menu_Point_BinaryThreshold(Image &image);
    bool Menu_Point_Posterize(Image &image);
    bool Menu_Point_Brightness(Image &image);
    bool Menu_Point_Contrast(Image &image);
    bool Menu_Point_Gamma(Image &image);
    bool Menu_Point_Compress(Image &image);
    bool Menu_Point_DiscretePseudocolor(Image &image);
    bool Menu_Point_ContinuousPseudocolor(Image &image);
    bool Menu_Point_DisplayHistogram(Image &image);
    bool Menu_Point_AutomatedContrastStretch(Image &image);
    bool Menu_Point_ModifiedContrastStretch(Image &image);
    bool Menu_Point_HistogramEqualization(Image &image);
    bool Menu_Point_HistogramEqualizationWithClipping(Image &image);
    bool Menu_Point_TodoPickAnotherOne(Image &image);
};
