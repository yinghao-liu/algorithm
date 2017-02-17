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
#include <string.h>
#define TIMES 1000000
/*
 * next : next 
 * p	: patten string
 *
 *
 */
int get_next(char *p, int *next)
{
	if (NULL == p || NULL == next){
		return -1;
	}
	int tmp;
	int index;
	index = 0;
	tmp = next[0] = -1;
	while (p[index+1] != '\0'){
		if (tmp == -1 || p[index] == p[tmp]){
			tmp++;
			index++;
			next[index] = tmp;
		}else{ // not match,next time just give the value zero
			tmp = -1;
		}
	}
	return -1;
}
/*
 * s : source string
 * p : patten string
 *
 */
int kmp_match(char *s,char *p)
{
    int next[100];
    int i , j;
	size_t s_len;
	size_t p_len;
    i = 0;
    j = 0;
    get_next(p, next);
//	s_len = strlen(s);
//	p_len = strlen(p);
    while(s[i]!='\0'){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }else{
            j = next[j];       //消除了指针i的回溯
        }
        if(j == 18){
            return (i - j);// offset of *p in *s;great than zero means have found *p
		}
    }
    return -1;	// not found *p
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
	while (s[index] != '\0'){
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
int main(int argc,char **argv)
{
	int tick=0;
	char *patten="abdfggdjsksjdhfklg";
	//char *patten_test="abcabcda";
	char *patten_test="abacabdaba";
	char *source2="zzzzzzzzz";
	int next1[30]={0xff};
	int next2[30]={0xff};
	char *source="dfgdfdfkj;dkfjasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahsduchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqasduahsdasjndasuah;akjshjhasahd;asjhas;jdhwihejka;sh;ajkhwe89u1ij;akdjjssssssssssssssssssssssssssncdjhurhfvs;djh;ajkshd;asjhsahsja;sh;asjha;sjha;djahs    duchhhhhhhujkdha;dha;sjhidhqwkdha;sjnha;xn;h;udcha;h;j;sdcf;sjd;hahoihadwqabdfggdjsksjdhfklg";
	#if 1
	for(tick=0; tick<TIMES; tick++){
	//for(tick=0; tick<1; tick++){
		//printf("kmp_match %d\n",kmp_match(source,patten));
		//printf("match %d\n",match(source,patten));
		
		kmp_match(source,patten);
		match(source,patten);
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
