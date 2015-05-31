#include "raspCar.h"

/*
* Graduation Project
* Made by Nipa
* nipa0711@gmail.com
* http://www.nipa0711.net/2015/03/OpenCV-Graduation-project-autonomous-car.html
*/

int main()
{
	// Run on the Windows
	VideoCapture capture;
	//capture.open(0); //capture the video from webcam
	capture.open("res/test11.mp4"); // playing video
	//capture.open("http://192.168.0.36:8080/video?x.mjpeg"); // IP camera

	if (!capture.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	// Run on the Raspberry Pi
	/*raspicam::RaspiCam_Cv Camera;
	Camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	Camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	if (!Camera.open())
	{
	cout << "camera open failed" << endl;
	return -1;
	}*/


	//clock_t start_time, end_time;
	font = new CvFont; // using font
	cvInitFont(font, CV_FONT_VECTOR0, 1.5f, 1.5f, 0, 2);

	Mat frame;

	for (int i = 0; i < 10; i++)
	{
		curOrder[i] = 0;
	}

	while (true)
	{
		//start_time = clock();

		// Run on the Raspberry Pi
		/*Camera.grab();
		Camera.retrieve(frame);*/

		// Run on the Windows
		capture >> frame;

		if (frame.empty())
		{
			printf("frame empty error\n");
			return -1;
		}

		videoWidth = frame.cols; 
		videoHeight = frame.rows; 		

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

		if (waitKey(25) == 27) //wait for 'esc' key press for 25ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}

		//end_time = clock();
		//cout << ((double)(end_time - start_time)) / CLOCKS_PER_SEC << endl;
	}
	return 0;
}