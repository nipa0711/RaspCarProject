#include "raspCar.h"

int main() //int argc, char** argv
{
	//clock_t start_time, end_time;
	VideoCapture capture;
	//capture.open(0); //capture the video from webcam
	capture.open("res/test11.mp4");
	//capture.open("http://192.168.0.36:8080/video?x.mjpeg");

	if (!capture.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	Mat frame;

	for (int i = 0; i < 10; i++)
	{
		curOrder[i] = 0;
	}

	videoWidth = 854; // frame.cols
	videoHeight = 480; // frame.rows
	totalVideoPixels = videoWidth * videoHeight;

	while (true)
	{
		//start_time = clock();
		capture >> frame;

		if (frame.empty())
		{
			printf("frame empty error\n");
			return -1;
		}

		cvtColor(frame, yuv, CV_RGB2YUV);
		split(yuv, channel);
		threshold(channel[1], channel[1], 140, 255, CV_THRESH_TOZERO);
		threshold(channel[2], channel[2], 140, 255, CV_THRESH_TOZERO);

		speedSign = 0;
		trafficSign = 0;

		speedSign = countNonZero(channel[2]);
		trafficSign = countNonZero(channel[1]);

		if (speedSign > trafficSign)
		{
			SpeedSign(frame, yuv);
		}
		else if (speedSign < trafficSign)
		{
			DirectionSign(frame, yuv);
		}

		imshow("final", frame);


		if (waitKey(25) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}

		//end_time = clock();

		//cout << ((double)(end_time - start_time)) / CLOCKS_PER_SEC << endl;
	}
	return 0;
}