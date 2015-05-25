#include "raspCar.h"

Mat DirectionSign(Mat res, Mat yuv)
{
	try
	{
		res.copyTo(show);

		split(yuv, channel);
		yuv.release();

		threshold(channel[1], channel[1], 140, 255, CV_THRESH_TOZERO);

		erode(channel[1], channel[1], Mat(Size(3, 3), CV_8UC1));
		erode(channel[1], channel[1], Mat(Size(3, 3), CV_8UC1));

		dilate(channel[1], channel[1], Mat(Size(3, 3), CV_8UC1));
		dilate(channel[1], channel[1], Mat(Size(3, 3), CV_8UC1));


		int largest_area = 0;
		vector<vector<Point> > contours;

		vector<Vec4i> hierarchy;

		channel[1].copyTo(temp2);

		int largest_contour_index = 0;
		findContours(channel[1], contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		for (int i = 0; i < 3; i++)
		{
			channel[i].release();
		}


		// iterate through each contour.
		for (int i = 0; i < contours.size(); i++)
		{
			//  Find the area of contour
			double a = contourArea(contours[i], false);
			if (a > largest_area)
			{
				largest_area = a;
				// Store the index of largest contour
				largest_contour_index = i;
				// Find the bounding rectangle for biggest contour
				bounding_rect = boundingRect(contours[i]);
				ROI = res(bounding_rect);
				temp = temp2(bounding_rect);
			}
		}

		temp2.release();

		Scalar color(255, 255, 255);  // color of the contour in the
		//Draw the contour and rectangle
		drawContours(show, contours, largest_contour_index, color, CV_FILLED, 8, hierarchy);
		show.release();

		rectangle(res, bounding_rect, Scalar(0, 255, 0), 2, 8, 0);

		threshold(temp, temp, 128, 200, CV_THRESH_TOZERO);

		erode(temp, temp, Mat(Size(3, 3), CV_8UC1));
		erode(temp, temp, Mat(Size(3, 3), CV_8UC1));
		erode(temp, temp, Mat(Size(3, 3), CV_8UC1));

		dilate(temp, temp, Mat(Size(3, 3), CV_8UC1));
		dilate(temp, temp, Mat(Size(3, 3), CV_8UC1));
		dilate(temp, temp, Mat(Size(3, 3), CV_8UC1));

		findContours(temp, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
		temp.release();

		vector<vector<Point> > contours_poly(contours.size());
		vector<Rect> boundRect(contours.size());

		largestIndex = 0;
		largestContour = 0;
		secondLargestIndex = 0;
		secondLargestContour = 0;
		for (int i = 0; i < contours.size(); i++)
		{
			if (contours[i].size() > largestContour)
			{
				secondLargestContour = largestContour;
				secondLargestIndex = largestIndex;
				largestContour = contours[i].size();
				largestIndex = i;
			}
			else if (contours[i].size() > secondLargestContour)
			{
				secondLargestContour = contours[i].size();
				secondLargestIndex = i;
			}
		}

		drawing = Mat::zeros(ROI.size(), CV_8UC1);

		// From the example you posted, you already know how to compute the contours
		// so let's take just the first one and compute the moments

		drawContours(drawing, contours, secondLargestIndex, color, CV_FILLED, 8);

		drawing(Rect(0, 0, drawing.cols / 2, drawing.rows)).copyTo(cropedImage);

		findContours(cropedImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		//imshow("crop", cropedImage);
		cropedImage.release();

		Moments mom = moments(contours[0]);

		HuMoments(mom, hu);

		hu0 = hu[0] * 1000;
		hu1 = hu[1] * 1000;
		hu2 = hu[2] * 1000;

		/*printf("hu 0번 값 : %lf\n", hu0);
		printf("hu 1번 값 : %lf\n", hu1);
		printf("hu 2번 값 : %lf\n", hu2);*/

		if ((hu0 >= 350 && hu0 < 375) && (hu1 >= 80 && hu1 < 100) && (hu2 >= 1 && hu2 < 5))
		{
			curOrder[1] = 0;
			curOrder[2] = 0;
			curOrder[3] = 0;
			if (curStat != RIGHT && ROI.cols > 150)
			{
				frameCount = framePerSec * showSec;
				printf("Trun Right.\n");
				//printf("우회전 하십시오.\n");
				curStat = RIGHT;
			}
			if (ROI.cols > 200 && curOrder[0] != RIGHT)
			{
				printf("Mindstorm will turn right.\n");
				//printf("마인드 스톰에 우회전 명령을 지시하였습니다.\n");
				curOrder[0] = RIGHT;
			}
		}
		else if ((hu0 >= 900 && hu0 < 1100) && (hu1 >= 850 && hu1 < 1200) && (hu2 >= 60 && hu2 < 90))
		{
			curOrder[0] = 0;
			curOrder[2] = 0;
			curOrder[3] = 0;
			if (curStat != FORWARD && ROI.cols < 150)
			{
				frameCount = framePerSec * showSec;
				printf("Move Forward.\n");
				//printf("직진 하십시오.\n");
				curStat = FORWARD;
			}
			if (ROI.cols > 200 && curOrder[1] != FORWARD)
			{
				printf("Mindstorm will forward.\n");
				//printf("마인드 스톰에 직진 명령을 지시하였습니다.\n");
				curOrder[1] = FORWARD;
			}
		}
		else if ((hu0 >= 160 && hu0 < 180) && (hu1 >= 0 && hu1 < 1) && (hu2 >= 0.5 && hu2 < 3))
		{
			curOrder[0] = 0;
			curOrder[1] = 0;
			curOrder[3] = 0;
			if (curStat != LEFT && ROI.cols > 100)
			{
				frameCount = framePerSec * showSec;
				printf("Trun Left.\n");
				//printf("좌회전 하십시오.\n");
				curStat = LEFT;
			}
			if (ROI.cols > 50 && curOrder[2] != LEFT)
			{
				printf("Mindstorm will turn left.\n");
				//printf("마인드 스톰에 좌회전 명령을 지시하였습니다.\n");
				curOrder[2] = LEFT;
			}
		}
		else if ((hu0 >= 500 && hu0 < 650) && (hu1 >= 200 && hu1 < 350) && (hu2 >= 9 && hu2 < 22))
		{
			curOrder[0] = 0;
			curOrder[1] = 0;
			curOrder[2] = 0;
			if (curStat != UTURN && ROI.cols > 100)
			{
				frameCount = framePerSec * showSec;
				printf("U-turn.\n");
				//printf("유턴 하십시오.\n");
				curStat = UTURN;
			}
			if (ROI.cols > 200 && curOrder[3] != UTURN)
			{
				printf("Mindstorm will U-turn.\n");
				//printf("마인드 스톰에 좌회전 명령을 지시하였습니다.\n");
				curOrder[3] = UTURN;
			}
		}

		res = printInformOnVideo(res);

		ROI.release();

		return res;
	}
	catch (Exception e)
	{
		printf("error\n");
	}
}
