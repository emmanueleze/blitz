#ifndef BLITZ_ENGINE_INCLUDE_ENGINE_CV_DETECT_H
#define BLITZ_ENGINE_INCLUDE_ENGINE_CV_DETECT_H

#include "engine.h"

#include "opencv4/opencv2/objdetect.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/videoio.hpp"




static void help(const char** argv);

void detectAndDraw(cv::Mat& img, cv::CascadeClassifier& cascade,
    cv::CascadeClassifier& nestedCascade,
    double scale, bool tryflip);









#endif    