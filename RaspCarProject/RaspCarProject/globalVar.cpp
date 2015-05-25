#include "raspCar.h"

int curStat;
int curSpeed;
int curOrder[10];
const int framePerSec = 24;
const int showSec = 1;
int frameCount=framePerSec * showSec;
int videoWidth;
int videoHeight;
int ingStat = FORWARD;
int largestIndex;
int largestContour;
int secondLargestIndex;
int secondLargestContour;
Mat show;
Mat cropedImage;
Mat channel[3];
Mat temp;
Mat temp2;
Mat drawing;
Mat ROI;
Mat showFrontNumber;
double hu[7];
double hu0;
double hu1;
double hu2;
Rect bounding_rect;