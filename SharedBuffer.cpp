/*
 * SharedBuffer.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: xonobo
 */

#include "SharedBuffer.h"


SharedBuffer::SharedBuffer()
{
	buffer = cv::Mat();
	rwFlag = false;
}

SharedBuffer::~SharedBuffer()
{
}

void SharedBuffer::setBuffer(const cv::Mat &mat)
{
	std::lock_guard<std::mutex> lockGuard(mtx);

	if (mat.rows == buffer.rows && mat.cols == buffer.cols && mat.type() == buffer.type() )
		mat.copyTo( buffer );
	else
		buffer = mat.clone();

	rwFlag = true;
}

cv::Mat SharedBuffer::getBuffer()
{
	std::lock_guard<std::mutex> lockGuard(mtx);

	rwFlag = false;

	return buffer.clone();
}

bool SharedBuffer::isUpdated()
{
	std::lock_guard<std::mutex> lockGuard(mtx);

	return rwFlag;
}
