#include <stdio.h>
#include <stdlib.h>
//NE RABOTI KAKTO TRYABVA
//sizeofstring(int)name(string) group(int) sizeofstring(int)fn(string)

void AddInt(char** PointerToPointerMemory,int* size){
	//printf("size %d\n",*size);
	fflush(stdin);
	int old_size = *size;
	(*size) += sizeof(int);
	//printf("size %d\n",*size);
	*PointerToPointerMemory = (char*)realloc(*PointerToPointerMemory,*size);
	//printf("%d\n",old_size);
	scanf(" %d",(int*)(*PointerToPointerMemory+old_size));
}

void AddString(char** PointerToPointerMemory,int* size){
	fflush(stdin);
	char ch;
	int char_counter = 0;
	int old_size = *size;
	*size+=sizeof(int);
	*PointerToPointerMemory = (char*)realloc(*PointerToPointerMemory,*size);
	
	while((ch = fgetc(stdin))!='\n'){
		(*size)++;
		char_counter++;
		*PointerToPointerMemory = (char*)realloc(*PointerToPointerMemory,*size);
		//printf(" %d",*size-1);
		*(*PointerToPointerMemory+*size-1)=ch;
		
	}
	//printf(" %d",old_size);
	*(int*)(*PointerToPointerMemory+old_size)=char_counter;
	//printf("\n");
}

void SaveToFile(char** PointerToPointerMemory,int* size,char* filename){
	FILE* fp = fopen(filename,"wb");
	
	if(fwrite(*PointerToPointerMemory,1,*size,fp)!=*size){
		exit(-1);
	}
	
	fclose(fp);
}

void NewRecord(char** PointerToPointerMemory,int* SizeOfMemory){
	printf("Enter name\n");
	AddString(PointerToPointerMemory,SizeOfMemory);
	printf("Enter group\n");
	AddInt(PointerToPointerMemory,SizeOfMemory);
	printf("Enter fn\n");
	AddString(PointerToPointerMemory,SizeOfMemory);
}

void PrintMemory(char** PointerToPointerMemory,int* SizeOfMemory){
	int index;
	
}

int main(){
	char* MyMemory = NULL;
	char** PointerToPointerMemory = &MyMemory;
	int SizeOfMemory = 0;
	
	char ch;
	do{
		NewRecord(PointerToPointerMemory,&SizeOfMemory);
		printf("Type 1 to add a new record\n");
		ch = getchar();
	}while(ch == '1');
	

	free(MyMemory);
	
}

