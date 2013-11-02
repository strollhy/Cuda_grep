
#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
#include<stdlib.h>
#include"grep.h"

#define SIZE 1000

int NUM;
int buff_len;
int word_len;
int segm_no;

using namespace std;

int main(int argc, char* argv[])
{
	char* buffer = (char*) malloc(MAXNUM * SIZE * sizeof(char));	
	char* word = argv[1];
	
	// For lines
	buff_len = 0;
	word_len = strlen(word);

	int line_indx = 0;
	int line_pos[MAXNUM];
	int line_len[MAXNUM];

	/* Read file line by line */	
	ifstream infile("./data/test.xml");
	string sLine;
	
	while(!infile.eof())
	{	
		// Load line
		getline(infile, sLine);
		NUM++;

		// Line start point & length
		line_len[line_indx] = sLine.length();
		line_pos[line_indx] = buff_len;
		buff_len += sLine.length();
		line_indx++;

		// Append line to buffer
		strcat(buffer, (char*) sLine.c_str()); 
	
		// If bUffer full
		if(NUM >= MAXNUM)
		{
			// Dump buffer to GPU for processing
			grep(buffer, word, line_pos, line_len);

			// Reset all parameters
			NUM = 0;
			buff_len = 0;
			line_indx = 0;
			segm_no++;

			// Flush buffer
			free(buffer);
			buffer = (char*) malloc(MAXNUM * SIZE * sizeof(char));	
		}
	}

	infile.close();
}
