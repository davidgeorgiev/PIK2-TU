#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

int readBinaryFile(const char*filename,int* arr);
void OutputData(int *arr,unsigned int len);

int main(){
	int data[SIZE];
	int len = readBinaryFile("bin.bin",data);
	OutputData(data,len);
	return 0;
}

int readBinaryFile(const char*filename,int* arr){
	FILE* fin = fopen(filename,"rb");
	int size;
	if(!fin){
		printf("Error opening file\n");
		return 0;
	}
	size = fread(arr,sizeof(int),SIZE,fin);
	
	fclose(fin);
	return size;
}

void OutputData(int *arr,unsigned int len){
	int i;
	for(i = 0;i<SIZE;++i){
		printf("%d,",arr[i]);
	}
}

