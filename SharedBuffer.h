/*
 * SharedBuffer.h
 *
 *  Created on: Jan 18, 2017
 *      Author: xonobo
 */

#ifndef SHAREDBUFFER_H_
#define SHAREDBUFFER_H_

#include <mutex>
#include <opencv2/opencv.hpp>

class SharedBuffer
{
public:
	SharedBuffer();
	virtual ~SharedBuffer();

	void setBuffer(const cv::Mat &mat);
	cv::Mat getBuffer();
	bool isUpdated();

private:
	cv::Mat buffer;
	std::mutex mtx;
	bool rwFlag; // write sets to true - read sets to false
};

#endif /* SHAREDBUFFER_H_ */
