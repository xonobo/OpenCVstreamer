/*
 * main.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: xonobo
 */
#include <iostream>
#include <stdio.h>
#include <thread>
#include <opencv2/opencv.hpp>

#include "SharedBuffer.h"

using namespace std;
using namespace cv;

SharedBuffer sbImage;

void streamOut(VideoWriter &writer, SharedBuffer &imageBuffer)
{

}

void streamIn(VideoCapture &cap, SharedBuffer &imageBuffer)
{

}

int main(int argc, char* argv[])
{
	cout << "Streamer starts \n";

	VideoCapture cap;
	cap.open("rtsp://rtsp-v3-spbtv.elt.spbtv.com/spbtv_v3_1/53_110.sdp");
	int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);
	double fps = cap.get(CAP_PROP_FPS);


	width = 640;
	height = 480;

	VideoWriter writer;
	writer.open("appsrc ! videoconvert ! x264enc ! rtph264pay config-interval=10 pt=96 ! udpsink host=127.0.0.1 port=5000", 0, fps, Size(width, height), true);

	Mat capFrame;
	Mat frame;
	size_t counter = 0;
	while (true)
	{
		cap >> capFrame;

		frame = Mat(height, width, CV_8UC3, Scalar(0,0,0));
		resize(capFrame, frame, Size(width, height));

		putText(frame, to_string(counter), Point(20,60), CV_FONT_HERSHEY_PLAIN, 3, Scalar(0,255,128), 2);

		imshow("cap", capFrame);
		imshow("wrt", frame);
		cvWaitKey(5);

		writer << frame;
		cout << counter << "\n";

		counter++;
	}

	return 0;
}


