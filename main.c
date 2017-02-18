/*
 * Copyright (C) 2017 francis_hao <francis_hao@126.com>
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TIMES 1000000
/*
 * next : next 
 * p	: patten string
 *
 *
 */
int get_next(char *p, char *next)
{
	if (NULL == p || NULL == next){
		return -1;
	}
	int tmp;
	int index;
	index = 1; // because we always set next[0] as zero
	tmp = next[0] = 0;
	while (p[index] != '\0'){
		if (p[index] == p[tmp]){
			tmp++;
		}else{ // not match,next time just give the value zero
			tmp = 0;
		}
		next[index] = tmp;
		index++;
	}
	return 0;//success
}
/*
 * s : source string
 * p : patten string
 *
 */
int kmp_match(char *s,char *p)
{
	char *next = NULL;
	size_t p_len;
	int s_index;
	int p_index;
	p_len = strlen(p);
	s_index = p_index = 0;
	if (NULL == (next=malloc(p_len))){
		return -1;
	} 
	if (0 != get_next(p, next)){
		return -1;
	}
	while (s[s_index] != '\0'){
		if (s[s_index] == p[p_index]){
			s_index++;
			p_index++;
			if (p_index == p_len){
				return (s_index - p_index);
			}
		}else{
			if (p_index == 0){
				s_index++;
				continue;
			}
			p_index = next[p_index]; // while s_index never retreat
		}
	}
	return -1;
}
/*
 *
 *
 *
 */
int match(char *s,char *p)
{	
	int index;
	int s_index;
	int p_index;
	index = s_index = p_index = 0;
	while (s[s_index] != '\0'){
		while(p[p_index] != '\0'){
			if (s[s_index] == p[p_index]){
				s_index++;
				p_index++;
			}else{
				index++;
				p_index = 0;
				s_index = index;
				break;
			}
		}
		if (s_index != index){
			return index;
		}
	}
	return -1;
}
void strstr_match(char *s, char *p)
{
	if (NULL == strstr(s,p)){
		printf("strstr not found\n");
	}
}
int waste_time(void)
{
	int a;
	a++;
	return a;
}
int main(int argc,char **argv)
{
	int tick=0;
	//char *source="abgabdfggdjsksjdhfklg";
	char *patten="abdfggdjsksjdhfklg";
	//char *source="edebcd";
	//char *patten="abcd";
	//char *patten_test="abcabcda";
	char *patten_test="abacabdaba";
	//char *source2="zzzzzzzzz";
	int next1[30]={0xff};
	int next2[30]={0xff};
	char *source="dfgdfdfkj;dkfjasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahsduchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqabdfggdjsksjdhfklg";
	#if 1
	for(tick=0; tick<TIMES; tick++){
	//for(tick=0; tick<1; tick++){
	//	printf("kmp_match %d\n",kmp_match(source,patten));
	//	printf("match %d\n",match(source,patten));
		
		kmp_match(source,patten);
		match(source,patten);
		strstr_match(source,patten);
		waste_time();
	}
	/*
	if (kmp_match(source,patten) >0 ){
		printf("kmp found str\n");
	}else{
		printf("kmp not found str\n");
	}*/
	#endif
	#if 0
	for(tick=0; tick<TIMES; tick++){
		strstr(source,patten);
	}
	if (NULL != strstr(source,patten)){
		printf("strstr found str\n");
	}else{
		printf("strstr not found str\n");
	}
	#endif







	return 0;
}
