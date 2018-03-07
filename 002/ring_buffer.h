/* vim:set ft=cpp: */ 
/*
 * Copyright (C) 2018 francis_hao <francis_hao@126.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License for more
 * details.
 *
 */
#ifndef _RING_BUFFER_
#define _RING_BUFFER_

#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

namespace name_ring_buffer{

template <typename T>
class ring_buffer{
public:
	int init(size_t num);
	int read(T *read_buff);
	int write(const T *write_buff);
	void clear(void);
	void destroy(void);

private:
	size_t nmemb;
	size_t read_index;
	size_t write_index;
	T *buffer;
};

template <typename T>
int ring_buffer<T>::init(size_t num)
{
	nmemb = num;
	buffer = (T *)calloc(nmemb, sizeof (T));
	if (NULL == buffer){
		perror("calloc");
		return -1;
	}
	read_index  = 0;
	write_index = 0;
	return 0;
}
template <typename T>
int ring_buffer<T>::read(T *read_buff)
{
	if (read_index == write_index){/*there is nothing to read*/
		return -1;
	}
	memcpy(read_buff, &buffer[read_index], sizeof (T));
	read_index = (read_index + 1) % nmemb;
	return 0;
}

template <typename T>
int ring_buffer<T>::write(const T *write_buff)
{
	size_t next_write;
	next_write = (write_index + 1) % nmemb;
	if (read_index == next_write){/*there is no space to write(only one left)*/
		return -1;
	}
	memcpy(&buffer[write_index], write_buff, sizeof (T));
	write_index = next_write;
	return 0;
}

template <typename T>
void ring_buffer<T>::clear(void)
{
	read_index  = 0;
	write_index = 0;
}

template <typename T>
void ring_buffer<T>::destroy(void)
{
	if (NULL != buffer){
		free(buffer);
	}
}
}/*namespace ring_buffer*/
#endif /*_RING_BUFFER_*/
