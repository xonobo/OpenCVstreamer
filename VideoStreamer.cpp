/*
 * VideoStreamer.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: xonobo
 */

#include "VideoStreamer.h"
#include <thread>
#include <chrono>

VideoStreamer::VideoStreamer()
{
	runFlag = false;
	ioFlag = false;
	streamCap = NULL;
	streamWriter = NULL;
	imageBuffer = NULL;
}

VideoStreamer::VideoStreamer(cv::VideoWriter *writer, SharedBuffer *imgBuffer)
{
	runFlag = false;
	ioFlag = false;
	streamCap = NULL;
	streamWriter = writer;
	imageBuffer = imgBuffer;
}

VideoStreamer::VideoStreamer(cv::VideoCapture *cap, SharedBuffer *imgBuffer)
{
	runFlag = false;
	ioFlag = false;
	streamWriter = NULL;
	streamCap = cap;
	imageBuffer = imgBuffer;
}

VideoStreamer::~VideoStreamer()
{
	runFlag = false;
}

void VideoStreamer::play()
{
	std::lock_guard<std::mutex> lockGuard(mtx);
	if (!runFlag)
	{
		runFlag = true;
		std::thread th(&VideoStreamer::run, this);
		th.join();
	}

}

void VideoStreamer::pause()
{
	std::lock_guard<std::mutex> lockGuard(mtx);
	runFlag = false;
}

void VideoStreamer::run()
{
	while ( runFlag )
	{
		if (streamWriter)
		{
			*streamWriter << imageBuffer->getBuffer();
		}

		if (streamCap)
		{
			*streamCap >> captureBuffer;
			imageBuffer->setBuffer( captureBuffer );
		}
	}
}
