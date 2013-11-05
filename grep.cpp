
/**
 * Performance test 1
 * pre-allocate GPU memory
 * load large chunks of data to GPU, and process everytime
 * 	
 */


#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
#include<stdlib.h>
#include"grep.h"

#define SIZE 1000

unsigned long NUM;
unsigned long buff_len;
unsigned int word_len;
unsigned long segm_no;

using namespace std;

int main(int argc, char* argv[])
{
	char* buffer = (char*) malloc((long) MAXNUM * SIZE * sizeof(char));
	char* word = argv[1];
	char* file = argv[2];
	
	// For lines
	buff_len = 0;
	word_len = strlen(word);

	int line_indx = 0;
	int line_pos[MAXNUM];
	int line_len[MAXNUM];

	/* Read file line by line */	
	ifstream infile(file);
	string sLine;
	
	while(!infile.eof())
	{	
		// Load line
		getline(infile, sLine);

		// Line start point & length
		unsigned int slen = sLine.length(); // not including null terminator
		
		line_len[line_indx] = slen;
		line_pos[line_indx] = buff_len;

			
		//Append line to buffer, using strcat is very time consuming
		memmove(buffer+buff_len, (char*) sLine.c_str(), sizeof(char) * slen);
		buff_len += slen;
		line_indx++;
		NUM++;


		// If bUffer full
		if(NUM >= MAXNUM | infile.eof())
		{
			// Dump buffer to GPU for processing
			grep(buffer, word, line_pos, line_len);

			// Reset all parameters
			NUM = 0;
			buff_len = 0;
			line_indx = 0;
			segm_no++;
		}
	}

	infile.close();
}
