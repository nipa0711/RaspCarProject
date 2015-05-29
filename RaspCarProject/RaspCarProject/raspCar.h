#ifndef RASPCAR_H
#define RASPCAR_H

#pragma warning(disable:4996)

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
extern int totalVideoPixels;
extern int ingStat;
extern int speedSign;
extern int trafficSign;
extern int largest_area;
extern int largest_contour_index;
extern int largestIndex;
extern int largestContour;
extern int secondLargestIndex;
extern int secondLargestContour;

extern const int framePerSec; // fps 초당프레임
extern const int showSec; // 몇초간 보여줄지
extern const int LimitColsSize;
extern const int LimitRowsSize;

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

extern double hu[7];
extern double hu0;
extern double hu1;
extern double hu2;

extern Rect bounding_rect;

#endif