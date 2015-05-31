#ifndef RASPCAR_H
#define RASPCAR_H

#pragma warning(disable:4996)

/*
* Graduation Project
* Made by Nipa
* nipa0711@gmail.com
* http://www.nipa0711.net/2015/03/OpenCV-Graduation-project-autonomous-car.html
*/

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <time.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/photo/photo.hpp"
//#include "raspicam_cv.h" // Run on the Raspberry Pi

using namespace cv;
using namespace std;

#define FORWARD 1000
#define LEFT 1001
#define RIGHT 1002
#define UTURN 1003
#define limit30 1030
#define limit40 1040
#define limit50 1050

Mat SpeedSign(Mat res, Mat yuv);
Mat DirectionSign(Mat res, Mat yuv);
Mat printInformOnVideo(Mat res);

extern int curStat;
extern int curSpeed;
extern int curOrder[10];
extern int frameCount;
extern int videoWidth;
extern int videoHeight;
extern int ingStat;
extern int speedSign;
extern int trafficSign;
extern int largest_area;
extern int largest_contour_index;
extern int largestIndex;
extern int largestContour;
extern int secondLargestIndex;
extern int secondLargestContour;

extern const int framePerSec;
extern const int showSec;

extern Mat show;
extern Mat cropedImage;
extern Mat channel[3];
extern Mat temp;
extern Mat temp2;
extern Mat drawing;
extern Mat ROI;
extern Mat showFrontNumber;
extern Mat yuv;
extern Mat frontNumber;
extern Mat temp3[3];
extern Mat ROI_Black;

extern double hu[7];
extern double hu0;
extern double hu1;
extern double hu2;

extern Rect bounding_rect;
extern IplImage printImg;
extern CvFont* font;
extern vector<vector<Point> > contours;
extern vector<Vec4i> hierarchy;

#endif