// grep.h
#ifndef _GREP_H_
#define _GREP_h_

#define MAXNUM 1000	//Maximum number of lines to be loaded everytime

extern int NUM; 	//Number of lines
extern int buff_len;	//Buffer length
extern int word_len; 	//Word length
extern int segm_no;	//Segment number

void grep(char* buffer, char* word, 
	  int* line_pos, int* line_len);

#endif // _GREP_H_
