#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BINFILENAME "data.bin"

struct FileStruct{
	char path[256];
	char filename[256];
	long int sizeInBytes;
	char dateCreated[11];
	char dateModified[11];
	char Flags[128];
};
typedef struct FileStruct TypeFile;
struct Node{
	TypeFile* fileObj;
	char* nextNode;
};
typedef struct Node TypeNode;
TypeNode head;
void INIT(){
	head.fileObj = NULL;
	head.nextNode = NULL;
}
int menu(void){
	printf("============================================\n");
	printf("MENU\n");
	printf("____________________________________________\n");
	printf("1. Add new file\n");
	printf("2. Search file by name and print information\n");
	printf("3. Count files in directory and print size\n");
	printf("4. Exit\n");
	printf("--------------------------------------------\n");
	int n;
	printf("OPTION = ");
	scanf(" %d",&n);
	printf("============================================\n");
	if(n == 2121){return n;}//2121 is a cheat code for printing all nodes
	if((n >= 1)&&(n <= 3)){
		return n;
	}else{
		return -1;
	}
}
long int ReturnSizeOfFile(char* filename){
	FILE* fp = fopen(filename,"rb");
	if(fp !=NULL){
		fseek(fp, 0L, SEEK_END);
		long int sz = ftell(fp);
		fclose(fp);
		return sz;
	}else{
		return -1;
	}
}
TypeNode* CreateNode(void){
	TypeNode* node = (TypeNode*)malloc(sizeof(TypeNode));
	TypeFile* file = (TypeFile*)malloc(sizeof(TypeFile));
	node->fileObj = file;
	node->nextNode = NULL;
	return node;
}

void AppendFileToBinFile(TypeFile* FileObjP,char* BinFileName){
	FILE* bfp = fopen(BinFileName,"rb");
	int numberOfWrittenFiles = 0;
	if(bfp!=NULL){
		fread(&numberOfWrittenFiles,sizeof(int),1,bfp);
		fclose(bfp);
		bfp = fopen(BinFileName,"r+b");
		numberOfWrittenFiles++;
		fseek(bfp, 0, SEEK_SET);
		fwrite(&numberOfWrittenFiles,sizeof(int),1,bfp);
		fclose(bfp);
		bfp = fopen(BinFileName,"ab");
	}else{
		bfp = fopen(BinFileName,"wb");
		numberOfWrittenFiles = 1;
		fwrite(&numberOfWrittenFiles,sizeof(int),1,bfp);
	}
	
	printf("num of indexed files %d\n",numberOfWrittenFiles);
	fwrite(FileObjP,sizeof(TypeFile),1,bfp);
	
	fclose(bfp);
}

void ReadBinFileToMemory(char* BinFileName){
	FILE* bfp = fopen(BinFileName,"rb");
	int numberOfWrittenFiles = 0;
	int i;
	TypeNode* node;
	if(bfp!=NULL){
		fread(&numberOfWrittenFiles,sizeof(int),1,bfp);
		//numberOfWrittenFiles = 3;
		TypeNode* temp = &head;
		while(temp->nextNode != NULL){
			//printf("!=NULL;\n");
			temp = (TypeNode*)(temp->nextNode);
		}
		//printf("num of indexed files %d\n",numberOfWrittenFiles);
		for(i = 0; i < numberOfWrittenFiles; i++){
			//printf("%d,",i);
			node = CreateNode();
			temp->nextNode = (char*)node;
			
			free(((TypeNode*)(temp->nextNode))->fileObj);
			((TypeNode*)(temp->nextNode))->fileObj = (TypeFile*)malloc(sizeof(TypeFile));
			fread(((TypeNode*)(temp->nextNode))->fileObj,sizeof(TypeFile),1,bfp);
			temp = (TypeNode*)(temp->nextNode);
		}
		fclose(bfp);
	}else{
		printf("Bin file may not exists yet!\n");
	}
}

void AddNewFile(){
	char filename[512];
	printf("\tEnter the full path of the file including the filename\n");
	scanf(" %s",filename);
	long int sizeOfFile;
	if((sizeOfFile = ReturnSizeOfFile(filename))!=-1){
		int indexOfLastSlash;
		for(indexOfLastSlash = 1;filename[indexOfLastSlash-1]!='\0';indexOfLastSlash++);
		for(;filename[indexOfLastSlash]!='/';){indexOfLastSlash--;}
		filename[indexOfLastSlash] = '\0';
	
		TypeNode* temp = &head;
		while(temp->nextNode != NULL){
			//printf("!=NULL;\n");
			temp = (TypeNode*)(temp->nextNode);
		}
	
		TypeNode* node = CreateNode();
		temp->nextNode = (char*)node;
	
		TypeFile* WorkingOnFile = ((TypeNode*)(temp->nextNode))->fileObj;
		int i = 0;
		while(filename[i]!='\0'){
			(WorkingOnFile->path)[i] = filename[i];
			i++;
			(WorkingOnFile->path)[i] = '/';
			(WorkingOnFile->path)[i+1] = '\0';
		}
		i++;
		int k = 0;
		while(filename[i]!='\0'){
			(WorkingOnFile->filename)[k] = filename[i];
			i++;
			k++;
			(WorkingOnFile->filename)[k] = '\0';
		}
		WorkingOnFile->sizeInBytes = sizeOfFile;
		//printf("%s\n",WorkingOnFile->path);
		//scanf(" %s",WorkingOnFile->path);
		//printf("%s\n",WorkingOnFile->path);
	
		AppendFileToBinFile(WorkingOnFile,BINFILENAME);
	}else{
		printf("\tfile not exists\n");
	}
}
void PrintSingleNode(TypeNode* node,int index){
	printf("\t____________________________________________\n\n");
	if(index!=-1){
		printf("\tINDEX %d\n",index);
	}
	printf("\t--------------------------------------------\n");
	printf("\tPATH = %s\n",node->fileObj->path);
	printf("\tFILENAME = %s\n",node->fileObj->filename);
	printf("\tSIZE IN BYTES = %ld\n",node->fileObj->sizeInBytes);
	printf("\tDATE OF CREATION = %s\n",node->fileObj->dateCreated);
	printf("\tDATE OF MODIFICATION = %s\n",node->fileObj->dateModified);
	printf("\tFLAGS = %s\n",node->fileObj->Flags);
	printf("\t____________________________________________\n");
}
void SearchFile(){
	printf("\t============================================\n");
	printf("\tSEARCHING FOR A FILE...\n");
	printf("\t--------------------------------------------\n");
	char search_for[256];
	int index = 0;
	int if_exists = 0;
	printf("\tEnter filename to search for!\n\t");
	scanf("%s",search_for);
	TypeNode* temp = &head;
	while(temp->nextNode != NULL){
		index++;
		temp = (TypeNode*)(temp->nextNode);
		if(strcmp(search_for,temp->fileObj->filename)==0){
			PrintSingleNode(temp,index);
			if_exists = 1;
		}
	}
	if(!if_exists){
		printf("\t--------------------------------------------\n");
		printf("\tNO SUCH FILE!\n");
		printf("\t--------------------------------------------\n");
	}
	printf("\t============================================\n\n");
}
int CheckIfStringStartsWith(char* mystring,char* startwith){
	int i = 0;
	int ifStartsWith = 1;
	while(startwith[i]!='\0'){
		if(startwith[i] != mystring[i]){
			ifStartsWith = 0;
		}
		i++;
	}
	//if((mystring[i-2]!='/')&&(mystring[i-2]!='\\')){
		//ifStartsWith = 0;
	//}
	return ifStartsWith;
}
void CountFiles(){
	printf("\t============================================\n");
	printf("\tCOUNTING FILES IN CUSTOM DIRECTORY...\n");
	printf("\t--------------------------------------------\n");
	char search_in_dir[256];
	int index = 0;
	int if_exists = 0;
	int counter = 0;
	long int SummedSize = 0;
	printf("\tEnter directory to count in!\n\t");
	scanf("%s",search_in_dir);
	TypeNode* temp = &head;
	while(temp->nextNode != NULL){
		index++;
		temp = (TypeNode*)(temp->nextNode);
		if(CheckIfStringStartsWith(temp->fileObj->path,search_in_dir)){
			counter++;
			SummedSize+=temp->fileObj->sizeInBytes;
			if_exists = 1;
		}
	}
	if(!if_exists){
		printf("\t--------------------------------------------\n");
		printf("\tNO SUCH FILE!\n");
		printf("\t--------------------------------------------\n");
	}else{
		printf("\t--------------------------------------------\n");
		printf("\tCOUNTED FILES: %d\n",counter);
		printf("\tSIZE OF ALL FILES: %ld\n",SummedSize);
		printf("\t--------------------------------------------\n");
	}
	printf("\t============================================\n\n");
}
void PrintAllNodes(){
	printf("\n\tPrinting nodes...\n");
	TypeNode* temp = &head;
	int counter = 0;
	while(temp->nextNode != NULL){
		counter++;
		temp = (TypeNode*)(temp->nextNode);
		PrintSingleNode(temp,counter);
	}
}

void RunOption(int optionID){
	switch(optionID){
		case 1:AddNewFile();break;
		case 2:SearchFile();break;
		case 3:CountFiles();break;
		case 2121:PrintAllNodes();
	}
}

int main(){
	INIT();
	ReadBinFileToMemory(BINFILENAME);
	int option;
	
	
	for(;;){
		if((option = menu())==-1){return 0;}
		RunOption(option);
	}
	
	return 0;	
}
