#include "raspCar.h"

/*
* Graduation Project
* Made by Nipa
* nipa0711@gmail.com
* http://www.nipa0711.net/2015/03/OpenCV-Graduation-project-autonomous-car.html
*/

int curStat;
int curSpeed;
int curOrder[10];

const int framePerSec = 24;
const int showSec = 1;

int frameCount=framePerSec * showSec;
int videoWidth;
int videoHeight;
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
Mat temp3[3];
Mat ROI_Black;

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

IplImage printImg;
CvFont* font;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;