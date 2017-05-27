#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MyMenu(void);
void RunOption(int option_id,FILE** table_file_pointer,FILE** codec_file_pointer);
int CreateNewDbTable(void);
void OpenADbTableFileForAppend(char* filename,FILE** PointerToTableFilePointer,FILE** PointerToCodecFilePointer);
void OpenADbTableFileForRead(char* filename,FILE** PointerToTableFilePointer,FILE** PointerToCodecFilePointer);
void OpenCodecFileForRead(char* filename,FILE** PointerToCodecFilePointer);
int AddNewRecord(FILE** PointerToTableFilePointer,FILE** PointerToCodecFilePointer);
int ListAllDataFromOpenedFile(FILE** PointerToTableFilePointer,FILE** PointerToCodecFilePointer);
char* GetInputString(void);
char* AppendCodecExt(char* filename);

int main(){
	FILE* dbTableFile;
	FILE** dbTableFilePointer = &dbTableFile;
	FILE* codecFile;
	FILE** codecFilePointer = &codecFile;
	int option_id;
	while((option_id = MyMenu()) != 6){
		RunOption(option_id,dbTableFilePointer,codecFilePointer);
	}
	return 0;
}

int MyMenu(void){
	printf("\nMENU\n");
	printf("1. Create new file\n");
	printf("2. Open a file for append\n");
	printf("3. Open a file for read\n");
	printf("4. Add a new record to opened file\n");
	printf("5. List all data from opened file\n");
	printf("6. Exit :(\n\n");
	int your_choice;
	scanf(" %d",&your_choice);
	if((your_choice <= 6)&&(your_choice >= 1))
		return your_choice;
	else
		return -1;
}

void RunOption(int option_id,FILE** table_file_pointer,FILE** codec_file_pointer){
	char* filename;
	switch(option_id){
		case 1:
			CreateNewDbTable();
			break;
		case 2:
			printf("Enter the name of the file to open for append\n");
			filename = GetInputString();
			OpenADbTableFileForAppend(filename,table_file_pointer,codec_file_pointer);
			if(filename != NULL){
				free(filename);
				filename = NULL;
			}
			break;
		case 3:
			printf("Enter the name of the file to open for read\n");
			filename = GetInputString();
			OpenADbTableFileForRead(filename,table_file_pointer,codec_file_pointer);
			if(filename != NULL){
				free(filename);
				filename = NULL;
			}
			break;
		case 4:
			AddNewRecord(table_file_pointer,codec_file_pointer);
			break;
		case 5:
			ListAllDataFromOpenedFile(table_file_pointer,codec_file_pointer);
			break;
	}
}

int CreateNewDbTable(void){
	char* filename;
	char* codec_filename;
	printf("\nEnter a dbtable filename\n");
	filename = GetInputString();
	FILE* fp;
	if(!(fp = fopen(filename,"wb"))){
		printf("Error creating data table file\n");
	}
	fclose(fp);
	
	codec_filename = AppendCodecExt(filename);
	if(!(fp = fopen(codec_filename,"w"))){
		printf("Error creating codec file\n");
	}
	fclose(fp);
	if(filename != NULL){
		//free(filename);
		filename = NULL;
	}
	
	char* user_codec;
	
	printf("Enter your fields here for example: name char(30),age int,grade float\n");
	user_codec = GetInputString();
	
	if(!(fp = fopen(codec_filename,"wb"))){
		printf("Error opening codec file\n");
	}
	
	if(fwrite(user_codec,1,strlen(user_codec),fp)!=strlen(user_codec)){
		printf("Can't save user codec :(\n");
	}
	
	if(user_codec != NULL){
		free(user_codec);
		user_codec = NULL;
	}
	if(codec_filename != NULL){
		free(codec_filename);
		codec_filename = NULL;
	}
	
	fclose(fp);
}
void OpenADbTableFileForAppend(char* filename,FILE** PointerToTableFilePointer,FILE** PointerToCodecFilePointer){
	
	FILE* fin;
	if(!(*PointerToTableFilePointer = fopen(filename,"ab"))){
		printf("Can\'t open data table file for append\n");
	}
	OpenCodecFileForRead(filename,PointerToCodecFilePointer);
}
void OpenADbTableFileForRead(char* filename,FILE** PointerToTableFilePointer,FILE** PointerToCodecFilePointer){
	if(!(*PointerToTableFilePointer = fopen(filename,"rb"))){
		printf("Can\'t open data table file for read\n");
	}
	OpenCodecFileForRead(filename,PointerToCodecFilePointer);
}

void OpenCodecFileForRead(char* filename,FILE** PointerToCodecFilePointer){
	char* codec_filename = AppendCodecExt(filename);
	if(!(*PointerToCodecFilePointer = fopen(codec_filename,"rb"))){
		printf("Can\'t open codec file\n");
	}
	if(codec_filename != NULL){
		free(codec_filename);
		codec_filename = NULL;
	}
}

int AddNewRecord(FILE** PointerToTableFilePointer,FILE** PointerToCodecFilePointer){
	
}
int ListAllDataFromOpenedFile(FILE** PointerToTableFilePointer,FILE** PointerToCodecFilePointer){
	
}

char* GetInputString(void){
	char* filename;
	char* temp_string;
	char current_char;
	int length = 1;
	filename = (char*)malloc(length);
	fgetc(stdin);
	while((current_char = fgetc(stdin))!='\n'){
		temp_string = (char*)realloc(filename,++length);
		if(temp_string != NULL){
			if(filename != temp_string){
				if(filename != NULL){
					free(filename);
					filename = NULL;
				}
				filename = temp_string;
			}
			filename[length-2] = current_char;
		}
	}
	filename[length-1] = '\0';
	return filename;
}

char* AppendCodecExt(char* filename){
	char* result;
	result = (char*)malloc(strlen(filename));
	strcpy(result, filename);
    result = strcat(result, ".codec");
	
	return result;
}
