/*
 * VideoStreamer.h
 *
 *  Created on: Jan 18, 2017
 *      Author: xonobo
 */

#ifndef VIDEOSTREAMER_H_
#define VIDEOSTREAMER_H_

#include <atomic>
#include <opencv2/opencv.hpp>
#include "SharedBuffer.h"

class VideoStreamer
{
public:
	VideoStreamer();
	VideoStreamer(cv::VideoWriter *writer, SharedBuffer *imgBuffer);
	VideoStreamer(cv::VideoCapture *cap, SharedBuffer *imgBuffer);
	virtual ~VideoStreamer();

	void play();
	void pause();

private:
	cv::VideoWriter *streamWriter;
	cv::VideoCapture *streamCap;
	SharedBuffer *imageBuffer;
	cv::Mat captureBuffer;
	bool ioFlag; // true for reader - false for writer
	std::atomic<bool> runFlag;
	std::mutex mtx;

	void run();
};

#endif /* VIDEOSTREAMER_H_ */
