/* vim:set ft=cpp: */ 
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
#ifndef _RING_BUFFER_
#define _RING_BUFFER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class ring_buffer{
public:
	ring_buffer(void);
	int init(size_t num);
	ssize_t read(char *read_buff, size_t len);
	int write(const char *write_buff, size_t len);
	void clear(void);
	void destroy(void);
	~ring_buffer(void);

private:
	size_t size;
	char *buffer;
	size_t read_index;
	size_t write_index;
};

#endif /*_RING_BUFFER_*/
