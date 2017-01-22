/*
 * VideoStreamer.h
 *
 *  Created on: Jan 18, 2017
 *      Author: xonobo
 */

#ifndef VIDEOSTREAMER_H_
#define VIDEOSTREAMER_H_

#include <opencv2/opencv.hpp>
#include "SharedBuffer.h"

class VideoStreamer
{
public:
	VideoStreamer(cv::VideoWriter &writer, SharedBuffer &imgBuffer);
	VideoStreamer(cv::VideoCapture &cap, SharedBuffer &imgBuffer);
	virtual ~VideoStreamer();

	void play();
	void pause();

private:
	cv::VideoWriter *streamWriter;
	cv::VideoCapture *streamCap;
	SharedBuffer *imageBuffer;
	bool ioFlag; // true for reader - false for writer
	bool runFlag;
	void run();
};

#endif /* VIDEOSTREAMER_H_ */
