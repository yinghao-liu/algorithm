/*
 * Copyright (C) 2018 francis_hao <francis_hao@126.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "ring_buffer.h"
ring_buffer::ring_buffer(void)
{
	size = 0;
	buffer = NULL;
	read_index  = 0;
	write_index = 0;
}
int ring_buffer::init(size_t num)
{
	size = num;
	buffer = (char *)calloc(size, 1);
	if (NULL == buffer){
		perror("calloc");
		return -1;
	}
	return 0;
}
/**
	@param read_buff : data of length len will be copyed to this buff from ring buffer
	@param len : data length
	@return -1 : buffer is NULL or read_buff is NULL
			>=0: have read length 
*/
ssize_t ring_buffer::read(char *read_buff, size_t len)
{
	if (NULL == buffer || NULL == read_buff){
		return -1;
	}
	if (read_index == write_index){/*there is nothing to read*/
		return 0;
	}
	size_t avail=0;
	size_t read_len=0;
	size_t remain=0;
	if (read_index>write_index){
		avail = size - read_index + write_index;
		remain = size-read_index;//length before end from read_index
	}else{
		avail = write_index - read_index;
		remain = avail;
	}
	read_len = (avail > len) ? len : avail;

	if (read_len > remain){// only in one case that is 'read_index > write_index'
		memcpy(read_buff, &buffer[read_index], remain);
		memcpy(read_buff+remain, buffer, read_len-remain);
	}else{
		memcpy(read_buff, &buffer[read_index], read_len);
	}
	read_index = (read_index + read_len) % size;
	return read_len;
}
/**
	@param write_buff : buff of length len will be write to ring buffer
	@param len : data length
	@return 0 : write operation is success
			-1: error

*/
int ring_buffer::write(const char *write_buff, size_t len)
{
	if (NULL == buffer || NULL == write_buff){
		return -1;
	}
	if (read_index == (write_index + 1) % size){/*there is no space to write(only one left)*/
		return -1;
	}
	
	size_t avail=0;
	size_t write_len=0;
	size_t remain=0;
	if (write_index > read_index){
		avail = size - write_index + read_index - 1;
		remain = size - write_index;
	}else{
		avail = read_index - write_index - 1;
		remain = avail;
	}
	if (len > avail){
		return -1; // no enough space to write
	}
	write_len = (avail > len) ? len : avail;
	
	if (write_len > remain){// only in one case that is 'write_index > read_index'
		memcpy(&buffer[write_index], write_buff, remain);
		memcpy(buffer, write_buff+remain, write_len-remain);
	}else{
		memcpy(&buffer[write_index], write_buff, write_len);
	}
	write_index = (write_index+write_len) % size;
	return 0;
}

void ring_buffer::clear(void)
{
	read_index  = 0;
	write_index = 0;
}

void ring_buffer::destroy(void)
{
	//if (NULL != buffer){
		free(buffer);//If buffer is NULL, no operation is performed
	//}
}
ring_buffer::~ring_buffer(void)
{
	destroy();
}

