#include "raspCar.h"

int curStat;
int curSpeed;
int curOrder[10];

const int framePerSec = 24;
const int showSec = 1;
const int LimitColsSize = 100;
const int LimitRowsSize = 100;

int frameCount=framePerSec * showSec;
int videoWidth;
int videoHeight;
int totalVideoPixels;
int ingStat = FORWARD;

Mat show;
Mat cropedImage;
Mat channel[3];
Mat temp;
Mat temp2;
Mat drawing;
Mat ROI;
Mat showFrontNumber;
Mat yuv;
Mat frontNumber;

double hu[7];
double hu0;
double hu1;
double hu2;
Rect bounding_rect;

int speedSign;
int trafficSign;
int largest_area;
int largest_contour_index;
int largestIndex;
int largestContour;
int secondLargestIndex;
int secondLargestContour;