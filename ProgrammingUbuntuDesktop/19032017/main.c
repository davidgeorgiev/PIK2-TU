#include <stdio.h>
#include <stdlib.h>
//char int type char int type
#define FILENAME "bin.bin"
int menu(){
	printf("1.append int\n2.append float\n3.append double\n4.append string\n5.print memory\n6.Load memory from file\n7.Save memory to file\n8.exit\n");
	int option;
	scanf(" %d",&option);
	return option;
}

void AppendInt(char** PointerToMemoryPointer,int* PointerToSizeOfMemoryInBytes){
	printf("Enter some integer: ");
	int oldSize = *PointerToSizeOfMemoryInBytes;
	*PointerToSizeOfMemoryInBytes += sizeof(char)+sizeof(int);
	if(*PointerToMemoryPointer == NULL){		
		*PointerToMemoryPointer = (char*)malloc(*PointerToSizeOfMemoryInBytes);
	}else{
		*PointerToMemoryPointer = (char*)realloc(*PointerToMemoryPointer,*PointerToSizeOfMemoryInBytes);
	}
	*(*PointerToMemoryPointer+oldSize) = 'i';
	scanf(" %d",(int*)(*PointerToMemoryPointer+oldSize+sizeof(char)));
	
}

void AppendFloat(char** PointerToMemoryPointer,int* PointerToSizeOfMemoryInBytes){
	printf("Enter some float: ");
	int oldSize = *PointerToSizeOfMemoryInBytes;
	*PointerToSizeOfMemoryInBytes += sizeof(char)+sizeof(float);
	if(*PointerToMemoryPointer == NULL){		
		*PointerToMemoryPointer = (char*)malloc(*PointerToSizeOfMemoryInBytes);
	}else{
		*PointerToMemoryPointer = (char*)realloc(*PointerToMemoryPointer,*PointerToSizeOfMemoryInBytes);
	}
	*(*PointerToMemoryPointer+oldSize) = 'f';
	scanf(" %f",(float*)(*PointerToMemoryPointer+oldSize+sizeof(char)));
	
}

void AppendDouble(char** PointerToMemoryPointer,int* PointerToSizeOfMemoryInBytes){
	printf("Enter some double: ");
	int oldSize = *PointerToSizeOfMemoryInBytes;
	*PointerToSizeOfMemoryInBytes += sizeof(char)+sizeof(double);
	if(*PointerToMemoryPointer == NULL){		
		*PointerToMemoryPointer = (char*)malloc(*PointerToSizeOfMemoryInBytes);
	}else{
		*PointerToMemoryPointer = (char*)realloc(*PointerToMemoryPointer,*PointerToSizeOfMemoryInBytes);
	}
	*(*PointerToMemoryPointer+oldSize) = 'd';
	scanf(" %lf",(double*)(*PointerToMemoryPointer+oldSize+sizeof(char)));
	
}

void AppendString(char** PointerToMemoryPointer,int* PointerToSizeOfMemoryInBytes){
	printf("Enter some string: ");
	int oldSize = *PointerToSizeOfMemoryInBytes;
	*PointerToSizeOfMemoryInBytes += sizeof(char)+sizeof(int);
	if(*PointerToMemoryPointer == NULL){		
		*PointerToMemoryPointer = (char*)malloc(*PointerToSizeOfMemoryInBytes);
	}else{
		*PointerToMemoryPointer = (char*)realloc(*PointerToMemoryPointer,*PointerToSizeOfMemoryInBytes);
	}
	*(*PointerToMemoryPointer+oldSize) = 's';
	int CurrentIdentation = oldSize+sizeof(int);
	fgetc(stdin);
	char tempchar;
	int counterOfChars = 0;
	while((tempchar = fgetc(stdin))!='\n'){
		*PointerToSizeOfMemoryInBytes+=sizeof(char);
		*PointerToMemoryPointer = (char*)realloc(*PointerToMemoryPointer,*PointerToSizeOfMemoryInBytes);
		CurrentIdentation+=sizeof(char);
		*(*PointerToMemoryPointer+CurrentIdentation)=tempchar;
		counterOfChars++;
	}
	*(int*)(*PointerToMemoryPointer+oldSize+1)=counterOfChars;
}

char* PrintMemoryByIndexAndReturnPointer(char** PointerToMemoryPointer,int* PointerToSizeOfMemoryInBytes,int indexToPrint){
	printf("MEMORY[%d]: ",indexToPrint);
	char* CurrentPointer = *PointerToMemoryPointer;
	char* EndPointer = CurrentPointer + *PointerToSizeOfMemoryInBytes;
	int IndexCounter = 0;
	int i;
	int sizeOfString;
	char* PointerToReturn;
	while(CurrentPointer<EndPointer){
		switch(*CurrentPointer){
			case 'i':
				PointerToReturn = CurrentPointer;
				CurrentPointer++;
				if(IndexCounter == indexToPrint){
					printf("int    %d\n",*(int*)CurrentPointer);
					return PointerToReturn;
				}
				CurrentPointer+=sizeof(int);
				IndexCounter++;
				break;
			case 'f':
				PointerToReturn = CurrentPointer;
				CurrentPointer++;
				if(IndexCounter == indexToPrint){
					printf("float  %f\n",*(float*)CurrentPointer);
					return PointerToReturn;
				}
				CurrentPointer+=sizeof(float);
				IndexCounter++;
				break;
			case 'd':
				PointerToReturn = CurrentPointer;
				CurrentPointer++;
				if(IndexCounter == indexToPrint){
					printf("double %lf\n",*(double*)CurrentPointer);
					return PointerToReturn;
				}
				CurrentPointer+=sizeof(double);
				IndexCounter++;
				break;
			case 's':
				PointerToReturn = CurrentPointer;
				CurrentPointer++;
				sizeOfString = *(int*)CurrentPointer;
				CurrentPointer+=sizeof(int);
				
				if(IndexCounter == indexToPrint){
					printf("string ");
					for(i = 0;i < sizeOfString;++i){
						printf("%c",*(CurrentPointer+i));
					}
					printf("\n");
					return PointerToReturn;
				}
				CurrentPointer+=sizeOfString;
				
				IndexCounter++;
				break;	
		}
	}
	printf("NO SUCH INDEX\n");
	return NULL;
}

void PrintAllMemory(char** PointerToMemoryPointer,int* PointerToSizeOfMemoryInBytes){
	int i = 0;
	while(PrintMemoryByIndexAndReturnPointer(PointerToMemoryPointer,PointerToSizeOfMemoryInBytes,i)!=NULL){
		i++;
	}
}

int ReturnSizeOfFile(char* filename){
	int sz;
	FILE* fp = fopen(filename,"rb");
	if(fp!=NULL){
		fseek(fp, 0L, SEEK_END);
		sz = (int)ftell(fp);
		fclose(fp);
		return sz;
	}else{
		printf("Can not open file %s\n",filename);
		return -1;
	}
}

void LoadMemoryFromFile(char** PointerToMemoryPointer,int* PointerToSizeOfMemoryInBytes,char* filename){
	int MemorySize = ReturnSizeOfFile(filename);
	int i;
	FILE* fout;
	if(MemorySize > 0){
		if(*PointerToMemoryPointer != NULL){
			free(*PointerToMemoryPointer);
			*PointerToMemoryPointer = NULL;
		}
		*PointerToMemoryPointer = (char*)malloc(MemorySize);
		if((fout = fopen(filename,"rb"))!=NULL){
			if(fread(*PointerToMemoryPointer,sizeof(char),MemorySize,fout)!=MemorySize){
				printf("Can not read memory from file %s\n",filename);
			}else{
				*PointerToSizeOfMemoryInBytes = MemorySize;
			}
			fclose(fout);
		}else{
			printf("Can not open file %s\n",filename);
		}
	}
}

void SaveMemoryToFile(char** PointerToMemoryPointer,int* PointerToSizeOfMemoryInBytes,char* filename){
	FILE* fin = fopen(filename,"wb");
	if(fin!=NULL){
		if(fwrite(*PointerToMemoryPointer,sizeof(char),*PointerToSizeOfMemoryInBytes,fin)
		    !=*PointerToSizeOfMemoryInBytes){
			printf("Can not write data to file %s\n",filename);	
		}else{
			printf("Memory is successfuly written to file %s\n",filename);
		}
		fclose(fin);
	}else{
		printf("Can not create file %s\n",filename);
	}
	
}

void RunOption(int option,char** PointerToMemoryPointer,int* PointerToSizeOfMemoryInBytes){
	switch(option){
		case 1:AppendInt(PointerToMemoryPointer,PointerToSizeOfMemoryInBytes);break;
		case 2:AppendFloat(PointerToMemoryPointer,PointerToSizeOfMemoryInBytes);break;
		case 3:AppendDouble(PointerToMemoryPointer,PointerToSizeOfMemoryInBytes);break;
		case 4:AppendString(PointerToMemoryPointer,PointerToSizeOfMemoryInBytes);break;
		case 5:PrintAllMemory(PointerToMemoryPointer,PointerToSizeOfMemoryInBytes);break;
		case 6:LoadMemoryFromFile(PointerToMemoryPointer,PointerToSizeOfMemoryInBytes,FILENAME);break;
		case 7:SaveMemoryToFile(PointerToMemoryPointer,PointerToSizeOfMemoryInBytes,FILENAME);break;
	}
}

int main(){
	char* MemoryPoiter = NULL;
	char** PointerToMemoryPointer = &MemoryPoiter;
	int SizeOfMemoryInBytes = 0;
	int* PointerToSizeOfMemoryInBytes = &SizeOfMemoryInBytes;
	int chosenOption;
	
	while((chosenOption=menu())<8){
		RunOption(chosenOption,PointerToMemoryPointer,PointerToSizeOfMemoryInBytes);
	}
	
	return 0;
}
