#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "bin.bin"

char* GetNewIntAndReturnAddress(){
	int* n = (int*)malloc(sizeof(int));
	scanf(" %d",n);
	getchar();
	return (char*)n;
}

char* GetNewStringAndReturnAddress(){
	char* mem = NULL;
	char c;
	int len = 0;
	
	while((c = getchar())!='\n'){
		mem = (char*)realloc(mem,sizeof(char)*(++len));
		mem[len-1] = c;
	}
	mem = (char*)realloc(mem,sizeof(char)*(++len));
	mem[len-1] = '\0';
	return mem;
}

char** AddNewIntToMemoryMap(char** memoryMap,int* len){
	memoryMap = realloc(memoryMap,sizeof(void*)*(++(*len)));
	memoryMap[*len-1] = GetNewIntAndReturnAddress();
	return memoryMap;
}

char** AddNewStringToMemoryMap(char** memoryMap,int* len){
	memoryMap = realloc(memoryMap,sizeof(void*)*(++(*len)));
	memoryMap[*len-1] = GetNewStringAndReturnAddress();
	return memoryMap;
}

void PrintMemoryMap(char** memoryMap,int* len){
	int i;
	for(i = 0;i<*len;){
		printf("%s\n",(char*)(memoryMap[i]));i++;
		printf("%d\n",*(int*)(memoryMap[i]));i++;
		printf("%s\n",(char*)(memoryMap[i]));i++;
	}
}

void AppendDataToFile(char** memoryMap,int* len){
	FILE* fp = fopen(FILENAME,"rb");
	if(fp == NULL){
		fp = fopen(FILENAME,"wb");
	}else{
		fclose(fp);
		fp = fopen(FILENAME,"ab");
	}
	int i;
	for(i = 0;i<*len;){
		fwrite((char*)(memoryMap[i]),sizeof(char),(int)strlen((char*)(memoryMap[i])),fp);i++;
		fwrite((int*)(memoryMap[i]),sizeof(int),1,fp);i++;
		fwrite((char*)(memoryMap[i]),sizeof(char),(int)strlen((char*)(memoryMap[i])),fp);i++;
	}
	
	fclose(fp);
}



char** TryToLoadMemoryFromFile(char** memoryMap,int* len){
	FILE* fp = fopen(FILENAME,"rb");
	char* allData = NULL;
	int index = 0;
	char byte;
	int lendata = 0;
	int i;
	if(fp != NULL){
		while(fread(&byte,sizeof(char),1,fp)!=1){
			allData = (char*)realloc(allData,++lendata);
			allData[lendata-1] = byte;
		}
		while(index+1<lendata){
		
			memoryMap = realloc(memoryMap,sizeof(void*)*(++(*len)));
			memoryMap[*len-1] = allData+index;
			while(*(allData+index)!='\0'){
				index++;
			}
			index++;
		
			memoryMap = realloc(memoryMap,sizeof(void*)*(++(*len)));
			memoryMap[*len-1] = allData+index;
		
			index+=sizeof(int);
		
			memoryMap = realloc(memoryMap,sizeof(void*)*(++(*len)));
			memoryMap[*len-1] = allData+index;
			
			while(*(allData+index)!='\0'){
				index++;
			}
			index++;
			
		}
		fclose(fp);
	}
	return memoryMap;
}

int main(){
	char** memoryMap = NULL;//pointer to memory of the addresses of data
	int len = 0;
	char c;
	/*do{
		printf("enter name\n");
		memoryMap = AddNewStringToMemoryMap(memoryMap,&len);
		printf("enter group\n");
		memoryMap = AddNewIntToMemoryMap(memoryMap,&len);
		printf("enter fac num\n");
		memoryMap = AddNewStringToMemoryMap(memoryMap,&len);
		printf("type 0 for exit or 1 to enter another record\n");
	}while(((c = getchar())!='0')&&(getchar()));
	AppendDataToFile(memoryMap,&len);*/
	memoryMap = TryToLoadMemoryFromFile(memoryMap,&len);
	
	PrintMemoryMap(memoryMap,&len);
	return 0;
}
