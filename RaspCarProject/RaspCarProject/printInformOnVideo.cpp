#include "raspCar.h"

Mat printInformOnVideo(Mat res)
{
	IplImage printImg = res;

	CvFont* font = new CvFont;
	cvInitFont(font, CV_FONT_VECTOR0, 1.5f, 1.5f, 0, 2);

	//printf("%d\n", frameCount);

	if (frameCount>0 && ROI.cols>130) 
	{
		switch (curStat)
		{
		case LEFT:
			cvPutText(&printImg, "Turn Left", cvPoint(videoWidth / 3, videoHeight - 50), font, CV_RGB(255, 0, 0));
			res = cvarrToMat(&printImg);
			frameCount--;
			break;
		case RIGHT:
			if (ROI.cols>200)
			{
				cvPutText(&printImg, "Turn Right", cvPoint(videoWidth / 3, videoHeight - 50), font, CV_RGB(255, 0, 0));
				res = cvarrToMat(&printImg);
				frameCount--;
			}
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