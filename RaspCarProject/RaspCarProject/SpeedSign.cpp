#include "raspCar.h"

Mat SpeedSign(Mat res, Mat yuv)
{
	try
	{
		vector<vector<Point> > contours;
		largest_area = 0;

		split(yuv, channel);
		threshold(channel[2], channel[2], 140, 255, CV_THRESH_TOZERO);

		vector<Vec4i> hierarchy;

		largest_contour_index = 0;

		findContours(channel[2], contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		// iterate through each contour.
		for (int i = 0; i < contours.size(); i++)
		{
			//  Find the area of contour
			double a = contourArea(contours[i], false);
			if (a > largest_area){
				largest_area = a;
				// Store the index of largest contour
				largest_contour_index = i;
				// Find the bounding rectangle for biggest contour
				bounding_rect = boundingRect(contours[i]);
				ROI = res(bounding_rect);
			}
		}

		Scalar color(255, 255, 255);  // color of the contour in the
		//Draw the contour and rectangle
		drawContours(yuv, contours, largest_contour_index, color, CV_FILLED, 8, hierarchy);

		rectangle(res, bounding_rect, Scalar(0, 255, 0), 2, 8, 0); // error

		Mat temp3[3];
		Mat ROI_Black;

		cvtColor(ROI, ROI_Black, CV_RGB2HLS);

		split(ROI_Black, temp3);

		threshold(temp3[1], temp3[1], 50, 255, CV_THRESH_BINARY_INV);
		//Canny(temp[1], temp[1], 50, 150, 3);	

		erode(temp3[1], temp3[1], Mat(Size(3, 3), CV_8UC1));
		erode(temp3[1], temp3[1], Mat(Size(3, 3), CV_8UC1));
		erode(temp3[1], temp3[1], Mat(Size(3, 3), CV_8UC1));

		dilate(temp3[1], temp3[1], Mat(Size(3, 3), CV_8UC1));
		dilate(temp3[1], temp3[1], Mat(Size(3, 3), CV_8UC1));
		dilate(temp3[1], temp3[1], Mat(Size(3, 3), CV_8UC1));

		frontNumber;
		temp3[1].copyTo(frontNumber);

		vector<vector<Point> > contours_poly(contours.size());
		vector<Rect> boundRect(contours.size());

		//adaptiveThreshold(temp[2], temp[2], 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 3, 5);
		findContours(temp3[1], contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		largestIndex = 0;
		largestContour = 0;
		secondLargestIndex = 0;
		secondLargestContour = 0;

		for (int i = 0; i < contours.size(); i++)
		{
			if (contours[i].size() > largestContour){
				secondLargestContour = largestContour;
				secondLargestIndex = largestIndex;
				largestContour = contours[i].size();
				largestIndex = i;
			}
			else if (contours[i].size() > secondLargestContour){
				secondLargestContour = contours[i].size();
				secondLargestIndex = i;
			}
		}
		drawing = Mat::zeros(ROI.size(), CV_8U);

		// From the example you posted, you already know how to compute the contours
		// so let's take just the first one and compute the moments

		drawContours(drawing, contours, largestIndex, color, CV_FILLED, 8);
		drawContours(drawing, contours, secondLargestIndex, color, CV_FILLED, 8);

		findContours(drawing, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		for (int i = 0; i < contours.size(); i++)
		{
			approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
			boundRect[i] = boundingRect(Mat(contours_poly[i]));
			rectangle(ROI, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 0, 0), 2, 8, 0);
		}

		frontNumber(Rect(0, 0, frontNumber.cols / 2, frontNumber.rows)).copyTo(cropedImage);
		drawContours(cropedImage, contours, -1, color, CV_FILLED, 8); // Assertion Failed Error largestIndex
		findContours(cropedImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		for (int i = 0; i < contours.size(); i++)
		{
			approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
			boundRect[i] = boundingRect(Mat(contours_poly[i]));
		}

		for (int i = 0; i < contours.size(); i++)
		{
			showFrontNumber = frontNumber(boundRect[i]);
		}

		if ((contours.size()>0) && (ROI.rows > LimitRowsSize || ROI.cols > LimitColsSize))
		{
			Moments mom = moments(contours[0]);
			HuMoments(mom, hu);

			hu0 = hu[0] * 1000;
			hu1 = hu[1] * 1000;
			hu2 = hu[2] * 1000;
			
			/*printf("hu 0번 값 : %lf\n", hu0);
			printf("hu 1번 값 : %lf\n", hu1);
			printf("hu 2번 값 : %lf\n", hu2);*/

			if ((hu0 >= 600 && hu0 < 670) && (hu1 >= 150 && hu1 < 200) && (hu2>20 && hu2 < 30))
			{
				curOrder[5] = 0;
				curOrder[6] = 0;

				if (curStat != limit30 && ROI.cols > 150)
				{
					frameCount = framePerSec * showSec;
					printf("Speed limit 30km/h sign detected\n");
					curStat = limit30;
				}
				if (ROI.cols > 50 && curOrder[4] != limit30)
				{
					printf("Mindstorm will drive 30km/h.\n");
					curOrder[4] = limit30;
				}
			}
			else if ((hu0 >= 200 && hu0 < 250) && (hu1 >= 5 && hu1 < 9))
			{
				curOrder[4] = 0;
				curOrder[6] = 0;
				if (curStat != limit40 && ROI.cols < 150)
				{
					frameCount = framePerSec * showSec;
					printf("Speed limit 40km/h sign detected\n");
					curStat = limit40;
				}
				if (ROI.cols > 50 && curOrder[5] != limit40)
				{
					printf("Mindstorm will drive 40km/h.\n");
					curOrder[5] = limit40;
				}
			}
			else if ((hu0 >= 450 && hu0 < 590) && (hu1 >= 60 && hu1<79) && (hu2>1.5 && hu2 < 8))
			{
				curOrder[4] = 0;
				curOrder[5] = 0;

				if (curStat != limit50 && ROI.cols < 150)
				{
					frameCount = framePerSec * showSec;
					printf("Speed limit 50km/h sign detected\n");
					curStat = limit50;
				}
				if (ROI.cols > 50 && curOrder[6] != limit50)
				{
					printf("Mindstorm will drive 50km/h.\n");
					curOrder[6] = limit50;
				}
			}
		}
		res = printInformOnVideo(res);
	}
	catch (Exception e)
	{
		printf("error\n");
	}
	return res;
}
