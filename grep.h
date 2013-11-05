// grep.h
#ifndef _GREP_H_
#define _GREP_h_

#define MAXNUM 3276800			//Maximum number of lines to be loaded everytime

extern unsigned long NUM; 		//Number of lines
extern unsigned long buff_len;		//Buffer length
extern unsigned int word_len; 		//Word length
extern unsigned long segm_no;		//Segment number

void grep(char* buffer, char* word, 
	  int* line_pos, int* line_len);

#endif // _GREP_H_
