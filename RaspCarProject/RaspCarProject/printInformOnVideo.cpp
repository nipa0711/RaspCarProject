#include "raspCar.h"

/*
* Graduation Project
* Made by Nipa
* nipa0711@gmail.com
* http://www.nipa0711.net/2015/03/OpenCV-Graduation-project-autonomous-car.html
*/

Mat printInformOnVideo(Mat res)
{
	printImg = res;

	if (frameCount > 0 && ROI.cols > 130)
	{
		switch (curStat)
		{
		case LEFT:
			cvPutText(&printImg, "Turn Left", cvPoint(videoWidth / 3, videoHeight - 50), font, CV_RGB(255, 0, 0));
			res = cvarrToMat(&printImg);
			frameCount--;
			break;
		case RIGHT:
			cvPutText(&printImg, "Turn Right", cvPoint(videoWidth / 3, videoHeight - 50), font, CV_RGB(255, 0, 0));
			res = cvarrToMat(&printImg);
			frameCount--;
			break;
		case UTURN:
			cvPutText(&printImg, "U-Turn", cvPoint(videoWidth / 3, videoHeight - 50), font, CV_RGB(255, 0, 0));
			res = cvarrToMat(&printImg);
			frameCount--;
			break;
		case FORWARD:
			cvPutText(&printImg, "FORWARD", cvPoint(videoWidth / 3, videoHeight - 50), font, CV_RGB(255, 0, 0));
			res = cvarrToMat(&printImg);
			frameCount--;
			break;
		case  limit30:
			cvPutText(&printImg, "Speed limit 30km/h", cvPoint(videoWidth / 3, videoHeight - 50), font, CV_RGB(255, 0, 0));
			res = cvarrToMat(&printImg);
			frameCount--;
			break;
		case  limit40:
			cvPutText(&printImg, "Speed limit 40km/h", cvPoint(videoWidth / 3, videoHeight - 50), font, CV_RGB(255, 0, 0));
			res = cvarrToMat(&printImg);
			frameCount--;
			break;
		case  limit50:
			cvPutText(&printImg, "Speed limit 50km/h", cvPoint(videoWidth / 3, videoHeight - 50), font, CV_RGB(255, 0, 0));
			res = cvarrToMat(&printImg);
			frameCount--;
			break;
		}
	}
	return res;
}