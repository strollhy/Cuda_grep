
#include<fstream>
#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int main(int argc, char* argv[])
{
	char* word = argv[1];
	char* file = argv[2];
	
	int word_len = strlen(word);

	/* Read file line by line */	
	ifstream infile(file);
	string sLine;
	
	while(!infile.eof())
	{	
		// Load line
		getline(infile, sLine);
			
		// Naive search of word
		for(int i=0; i<sLine.length(); i++) 
		{
			bool find = true;

			for(int j=0; j<word_len; j++)
			{
				if(sLine[i+j] != word[j])
				{
					find = false;
					break;
				}	
			}
			
			if(find) 
			{
				//cout<<sLine<<endl;
				break;
			}
		}

	}

	infile.close();
}
