// Kernel definition
__global__ void vecGrep(char* buffer, 
			int* word_len, char* word, 
		        int* line_pos, int* line_len, 
		        int* find)
{
        // threadIdx.x is a built-in variable provided by CUDA at runtime
        int indx = threadIdx.x;
	int pos = line_pos[indx];
	int len = line_len[indx];
	
	for(int i=0; i<len; i++)
	{
		find[indx] = 1;

		for(int j=0; j<*word_len; j++) 
		{
        		if (buffer[pos+i+j] != word[j]) 
			{
        	        	find[indx] = 0;
				break;
			}
        	
		}
		
		if(find[indx] == 1)
			break;
	}
}


#include"grep.h"
#include<stdio.h>
#include<string.h>

void grep (char* buffer, char* word,
           int* line_pos, int* line_len)
{
        char *devPtrLine;
        char *devPtrWord;
	int *devPtrPos;
	int *devPtrLen;
	int *devPtrWlen;

        int *devPtrFind;
	int result[NUM];
	
	int buffer_size = buff_len * sizeof(char);
	int word_size = word_len * sizeof(char);
	int list_size = NUM * sizeof(int);
	
        cudaMalloc((void**)&devPtrLine, buffer_size);
	cudaMalloc((void**)&devPtrWlen, sizeof(int));
        cudaMalloc((void**)&devPtrWord, word_size);
        cudaMalloc((void**)&devPtrFind, list_size);
	cudaMalloc((void**)&devPtrPos, list_size);
	cudaMalloc((void**)&devPtrLen, list_size);

        cudaMemcpy(devPtrLine, buffer, buffer_size, cudaMemcpyHostToDevice);
	cudaMemcpy(devPtrWlen, &word_len, sizeof(int), cudaMemcpyHostToDevice);
        cudaMemcpy(devPtrWord, word, word_size, cudaMemcpyHostToDevice);
	cudaMemcpy(devPtrPos, line_pos, list_size, cudaMemcpyHostToDevice);
	cudaMemcpy(devPtrLen, line_len, list_size, cudaMemcpyHostToDevice);

        // __global__ functions are called: Fun<<< Dg, Db, Ns >>>(parameter);
        vecGrep<<<1, NUM>>> (devPtrLine, 
				devPtrWlen, devPtrWord, 
				devPtrPos, devPtrLen, devPtrFind);
        cudaMemcpy(result, devPtrFind, list_size, cudaMemcpyDeviceToHost);

	// For display
	//for(int i=0; i<NUM; i++) printf("%d,", result[i]);
	//printf("\b \b\n");
      	
	/*	
	for(int i=0; i<NUM; i++)
		if(result[i])
		{ 
			int p = line_pos[i];
			int l = line_len[i];
			for(int j=0; j<l; j++)
				printf("%c", buffer[p+j]);
			printf("\n");
		}
	*/
	//printf(" %d ###################\n", segm_no);
	
        cudaFree(devPtrLine);
	cudaFree(devPtrWlen);
        cudaFree(devPtrWord);
        cudaFree(devPtrFind);
	cudaFree(devPtrPos);
	cudaFree(devPtrLen);
}

