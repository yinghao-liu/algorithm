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
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "ring_buffer.h"

using namespace std;
using namespace name_ring_buffer;

void *pth_read(void *buff)
{
	static long a=0;
	int res;
	while (a < 100){
		if (0 == ((ring_buffer<int> *)buff)->read(&res)){
			printf("read from ring_buffer %u\n", res);
			usleep(2);// let pth_write work
			a++;
		}else{
			//printf("no more data\n");
			//sleep(3);
		}
	}	
}
void *pth_write(void *buff)
{
	static int i=0;
	while (i < 100){
		if (0 != ((ring_buffer<int> *)buff)->write(&i)){
			//printf("ring buffer is full\n");
			//sleep(3);
		}else{
			printf("write data to ring buffer %u\n",i);
			usleep(3);// let pth_read work
			i++;
		}
	}	
}
int main(void)
{
	pthread_t read_t;
	pthread_t write_t;

	ring_buffer<int> data;
	data.init(10);
	pthread_create(&read_t, NULL, pth_read, &data);
	pthread_create(&write_t, NULL, pth_write, &data);

	pthread_join(read_t, NULL);
	pthread_join(write_t, NULL);
	return 0;
}
