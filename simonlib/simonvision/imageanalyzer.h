#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H
#include "simonvision_export.h"
#include <cv.h>
#include <highgui.h>
#include<QObject>
class SIMONVISION_EXPORT ImageAnalyzer : public QObject
{

public:
    ImageAnalyzer(QObject* parent = 0);
    ~ImageAnalyzer();
    virtual void analyze(IplImage* currentImage)=0;

};

#endif // IMAGEANALYZER_H
