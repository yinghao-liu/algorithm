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
typedef int (*P_RB_TYPE)[100];

void *pth_read(void *buff)
{
	static long a=0;
	//int res[100];
	int *res;
	res = (int *)calloc(sizeof (int), 100);
	while (a < 100){
		if (0 == ((ring_buffer<int[100]> *)buff)->read((P_RB_TYPE)res)){
			printf("read from ring_buffer %u\n", res[20]);
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
	static int i[100]={0};
	static int *aa = NULL;
	aa = (int *)calloc(sizeof (int), 100);
	aa[20]=0;
	while (aa[20] < 100){
		if (0 != ((ring_buffer<int[100]> *)buff)->write((P_RB_TYPE)aa)){
			//printf("ring buffer is full\n");
			//sleep(3);
		}else{
			printf("write data to ring buffer %u\n",aa[20]);
			usleep(3);// let pth_read work
			aa[20]++;
		}
	}	
}
int main(void)
{
	pthread_t read_t;
	pthread_t write_t;
	
	
	auto data = new ring_buffer<int[100]>;
	data->init(10);

	pthread_create(&read_t, NULL, pth_read, data);
	pthread_create(&write_t, NULL, pth_write, data);

	pthread_join(read_t, NULL);
	pthread_join(write_t, NULL);
	return 0;
}
