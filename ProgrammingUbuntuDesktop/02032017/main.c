//Lecture 02 03 2017
#include <stdio.h>
#include <stdlib.h>

void WriteBinaryFile(const char* filename,int * arr,unsigned int len);
void WriteFile(char* filename, int *arr,unsigned int len);

void UpdateArray(int* arr,int len){
	int i;
	
	for(i = 0;i<len;++i){
		printf("Enter arr[%d] ",i);
		scanf(" %d",&arr[i]);
	}
}

int main(){
	int array[10];
	UpdateArray(array,10);
	WriteBinaryFile("bin.bin",array,10);
	WriteFile("txt.txt",array,10);
	return 0;
}

void WriteBinaryFile(const char* filename,int * arr,unsigned int len){
	FILE* fout;
	fout = fopen(filename,"wb");
	if(fout == NULL){
		printf("File IO error\n");
		return;
	}
	fwrite(arr,sizeof(int),len,fout);
	fclose(fout);
}

void WriteFile(char* filename, int *arr,unsigned int len){
	FILE* fout;
	int i;
	fout = fopen(filename, "w");
	if(fout == NULL){
		printf("Error in text file\n");
		return;
	}
	for(i = 0;i<len;++i){
		fprintf(fout,"%d,",arr[i]);
	}
	fclose(fout);
}
