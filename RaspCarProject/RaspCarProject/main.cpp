#include "raspCar.h"

int main() //int argc, char** argv
{
	//clock_t start_time, end_time;
	VideoCapture capture;
	//capture.open(0); //capture the video from webcam
	capture.open("res/test11.mp4");

	if (!capture.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	//VideoCapture capture(cap);
	
	for (int i = 0; i < 10; i++)
	{
		curOrder[i] = 0;
	}
	
	while (true)
	{
		//start_time = clock();
		capture >> frame;
		videoWidth = frame.cols;
		videoHeight = frame.rows;

		if (!frame.empty())
		{
			frame.copyTo(yuv);

			if (yuv.empty())
			{
				printf("yuv error\n");
				return -1;
			}

			cvtColor(yuv, yuv, CV_RGB2YUV);
			split(yuv, channel);
			threshold(channel[1], channel[1], 140, 255, CV_THRESH_TOZERO);
			threshold(channel[2], channel[2], 150, 255, CV_THRESH_TOZERO);

			int speedSign = 0;
			int trafficSign = 0;

			speedSign = countNonZero(channel[2]);
			trafficSign = countNonZero(channel[1]);

			for (int i = 0; i < 3; i++)
			{
				channel[i].release();
			}


			if (speedSign > trafficSign)
			{
				SpeedSign(frame, yuv);
			}
			else if (speedSign < trafficSign)
			{
				DirectionSign(frame, yuv);
			}

			imshow("final", frame);

			yuv.release();
			frame.release();

			if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			{
				cout << "esc key is pressed by user" << endl;
				break;
			}
		}
		//end_time = clock();

		//cout << ((double)(end_time - start_time))/CLOCKS_PER_SEC << endl;
	}
	return 0;
}