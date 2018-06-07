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

void *pth_read(void *buff)
{
	static long i=0;
	//int res[100];
	char res[10]={0};
	//res = (char *)calloc(sizeof (char), 100);
	int ret;
	char str[512]={0};
	sleep(2);
	while (i < 400){// this number is calculated in pth_write (i * sizeof aa)
		ret = ((ring_buffer *)buff)->read(res, 5);
		if (ret > 0){
			sprintf(str, "read from ring_buffer" );	
			for (int j=0; j<ret; j++){
				sprintf(str+strlen(str), " %u", res[j]);	
			}
			printf("%s\n", str);

			usleep(10);// let pth_write work
			i+=ret;
		}else{
			//printf("no more data\n");
			usleep(3);
		}
	}	
}
void *pth_write(void *buff)
{
	static int i=0;
	static char aa[]={1,2,3,4};
	//aa = (char *)calloc(sizeof (char), 100);
	while (i < 100){
		if (-1 == ((ring_buffer *)buff)->write(aa, sizeof (aa))){
			//printf("ring buffer is full\n");
			usleep(2);
		}else{
			printf("write data to ring buffer \n");
			usleep(2);// let pth_read work
			i++;
		}
	}	
}
int main(void)
{
	pthread_t read_t;
	pthread_t write_t;
	
	
	auto data = new ring_buffer;
	data->init(12);

	pthread_create(&read_t, NULL, pth_read, data);
	pthread_create(&write_t, NULL, pth_write, data);

	pthread_join(read_t, NULL);
	pthread_join(write_t, NULL);
	return 0;
}
