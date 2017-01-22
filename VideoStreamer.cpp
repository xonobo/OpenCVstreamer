/*
 * VideoStreamer.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: xonobo
 */

#include "VideoStreamer.h"

VideoStreamer::VideoStreamer()
{
	streamCap = NULL;
	streamWriter = NULL;
	imageBuffer = NULL;
}

VideoStreamer::VideoStreamer(cv::VideoWriter *writer, SharedBuffer *imgBuffer)
{
	streamCap = NULL;
	streamWriter = writer;
	imageBuffer = imgBuffer;
}

VideoStreamer::VideoStreamer(cv::VideoCapture *cap, SharedBuffer *imgBuffer)
{
	streamWriter = NULL;
	streamCap = cap;
	imageBuffer = imgBuffer;
}

VideoStreamer::~VideoStreamer()
{
}


void VideoStreamer::play()
{
	std::lock_guard<std::mutex> lockGuard(mtx);
	runFlag = true;
}

void VideoStreamer::pause()
{
	std::lock_guard<std::mutex> lockGuard(mtx);
	runFlag = false;
}

bool VideoStreamer::getRunFlag()
{
	std::lock_guard<std::mutex> lockGuard(mtx);
	return runFlag;
}

void VideoStreamer::run()
{
	while ( getRunFlag() )
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
