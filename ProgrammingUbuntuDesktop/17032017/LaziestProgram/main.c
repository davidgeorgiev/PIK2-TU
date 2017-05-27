#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CODING "int*5 int*2 float*3 char*5 double*8"
#define BINFILE "bin.bin"

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


char* GiveMeNextField(int* index){
	if(*index-1 == (int)strlen(CODING)){
		return NULL;
	}
	int size = 1;
	char* FieldInfo = (char*)malloc(size);
	while((CODING[*index]!=' ')&&(CODING[*index]!='\0')){
		FieldInfo = (char*)realloc(FieldInfo,++size);
		FieldInfo[size-2] = CODING[*index];
		(*index)++;
	}
	(*index)++;
	FieldInfo[size-1] = '\0';
	return FieldInfo;
}

int GiveMeTheSize(char* DataType){
	if(strcmp(DataType,"int")){
		return sizeof(int);
	}else if(strcmp(DataType,"char")){
		return 1;
	}else if(strcmp(DataType,"float")){
		return sizeof(float);
	}else if(strcmp(DataType,"double")){
		return 8;
	}
	return 1;
}
void CastAndScan(char* DataType,void* AllocatedMemory,int indexToScan){
	int* IntPointer;
	char* CharPointer;
	float* FloatPointer;
	double* DoublePointer;
	char* tempUserInput;
	if(strcmp(DataType,"int")){
		IntPointer = (int*)AllocatedMemory;
		tempUserInput = GetInputString();
		IntPointer[indexToScan] = atoi(tempUserInput);
		free(tempUserInput);
		tempUserInput = NULL;
	}else if(strcmp(DataType,"char")){
		CharPointer = (char*)AllocatedMemory;
		tempUserInput = GetInputString();
		CharPointer[indexToScan] = tempUserInput[0];
		//scanf("%c",&CharPointer[indexToScan]);
	}else if(strcmp(DataType,"float")){
		FloatPointer = (float*)AllocatedMemory;
		tempUserInput = GetInputString();
		FloatPointer[indexToScan] = atof(tempUserInput);
		//scanf("%f",&FloatPointer[indexToScan]);
	}else if(strcmp(DataType,"double")){
		DoublePointer = (double*)AllocatedMemory;
		tempUserInput = GetInputString();
		DoublePointer[indexToScan] = atof(tempUserInput);
		//scanf("%lf",&DoublePointer[indexToScan]);
	}
}

int ReturnNumberOfElements(char* Field){
	char* copiedField = (char*)malloc(strlen(Field));
	strcpy(copiedField,Field);
	char* DataType = strtok(copiedField, "*");
	char* DataAmount = strtok(NULL, "*");
	int AmountOfData;
	sscanf(DataAmount,"%d",&AmountOfData);
	return AmountOfData;
}
char* ReturnDataType(char* Field){
	char* copiedField = (char*)malloc(strlen(Field));
	strcpy(copiedField,Field);
	char* DataType = strtok(copiedField, "*");
	return DataType;
}

char* GetNeededData(char* Field){
	char* DataType = ReturnDataType(Field);
	int AmountOfData = ReturnNumberOfElements(Field);
	int size = GiveMeTheSize(DataType);
	int len = 0;
	
	
	
	void* PointerToReturn;
	PointerToReturn = malloc(0);
	int i;
	for(i = 0;i < AmountOfData;++i){
		PointerToReturn = realloc(PointerToReturn,size*(++len));
		printf("enter index %d here ",len-1);
		CastAndScan(DataType,PointerToReturn,len-1);
	}
	return (char*)PointerToReturn;
}

int FileExists(char* filename){
	FILE* fp;
	fp = fopen(filename,"r");
	if(fp!=NULL){
		fclose(fp);
		return 0;
	}else{
		return -1;
	}
}

int AppendDataToFile(FILE* fin,char* DataPointer,int NumberOfElements){
	if(fwrite(DataPointer,1,NumberOfElements,fin)==NumberOfElements){
		return 0;
	}else{
		return -1;
	}
}

void AppendNewRecord(char* filename){
	FILE* fin;
	if(FileExists(filename)!=0){
		fin = fopen(filename,"wb");
	}else{
		fin = fopen(filename,"ab");
	}
	int index = 0;
	char* CurrentField;
	char* DataToAppendInFile;
	while((CurrentField = GiveMeNextField(&index))!=NULL){
		printf("%s\n",CurrentField);
		DataToAppendInFile = GetNeededData(CurrentField);
		AppendDataToFile(fin,DataToAppendInFile,ReturnNumberOfElements(CurrentField)*GiveMeTheSize(ReturnDataType(CurrentField)));
		free(CurrentField);
		CurrentField = NULL;
	}
	fclose(fin);
}

int GetTheFullSizeOfARecordInBytes(){
	int SizeOfARecordInBytes = 0;
	int index = 0;
	char* CurrentField;
	char* DataToAppendInFile;
	while((CurrentField = GiveMeNextField(&index))!=NULL){
		SizeOfARecordInBytes += ReturnNumberOfElements(CurrentField)*GiveMeTheSize(ReturnDataType(CurrentField));
		free(CurrentField);
		CurrentField = NULL;
	}
	return SizeOfARecordInBytes;
}

char* ReturnPointerToTheNextRecord(FILE* fout){
	int SizeOfRecord = GetTheFullSizeOfARecordInBytes();
	char* CurrentRecordData = (char*)malloc(SizeOfRecord);
	if(fread(CurrentRecordData,1,SizeOfRecord,fout)==SizeOfRecord){
		return CurrentRecordData;
	}else{
		return NULL;
	}
}

void PrintADataByIndex(char* PointerToTheBigArray,int ArrayIndex){
	int* TempIntPointer;
	char* TempCharPointer;
	float* TempFloatPointer;
	double* TempDoublePointer;
	char* CurrentType;
	int numberOfElements;

	int SizeOfRecord = GetTheFullSizeOfARecordInBytes();
	PointerToTheBigArray += SizeOfRecord*ArrayIndex;
	int index = 0;
	char* CurrentField;
	printf("Printing the data for record on index %d\n",ArrayIndex);
	while((CurrentField = GiveMeNextField(&index))!=NULL){
		CurrentType = ReturnDataType(CurrentField);
		numberOfElements = ReturnNumberOfElements(CurrentField);
		int i;
		printf("\nType of data [%s]; amount [%d]\n",CurrentType,numberOfElements);
		if(strcmp(CurrentType,"int")){
			TempIntPointer = (int*)PointerToTheBigArray;
			for(i = 0;i<numberOfElements;++i){
				printf("%d,",TempIntPointer[i]);
			}
			PointerToTheBigArray += numberOfElements*GiveMeTheSize(CurrentType);
		}else if(strcmp(CurrentType,"char")){
			TempCharPointer = (char*)PointerToTheBigArray;
			for(i = 0;i<numberOfElements;++i){
				printf("%c,",TempCharPointer[i]);
			}
			PointerToTheBigArray += numberOfElements*GiveMeTheSize(CurrentType);
		}else if(strcmp(CurrentType,"float")){
			TempFloatPointer = (float*)PointerToTheBigArray;
			for(i = 0;i<numberOfElements;++i){
				printf("%f,",TempFloatPointer[i]);
			}
			PointerToTheBigArray += numberOfElements*GiveMeTheSize(CurrentType);
		}else if(strcmp(CurrentType,"double")){
			TempDoublePointer = (double*)PointerToTheBigArray;
			for(i = 0;i<numberOfElements;++i){
				printf("%lf,",TempDoublePointer[i]);
			}
			PointerToTheBigArray += numberOfElements*GiveMeTheSize(CurrentType);
		}
	}
	printf("\n");
}

char* AppendARecordToTheBigArrayAndReturnPointerToIt(char* PointerToTheRecord,char* PointerToTheBigArray,int* index){
	int SizeOfRecord = GetTheFullSizeOfARecordInBytes();
	if(PointerToTheBigArray == NULL){
		PointerToTheBigArray = (char*)malloc(SizeOfRecord*(++(*index)));
	}else{
		PointerToTheBigArray = (char*)realloc(PointerToTheBigArray,SizeOfRecord*(++(*index)));
	}
	int indexOfRecord;
	int indexOfBigArray = SizeOfRecord*((*index)-1);
	for(indexOfRecord = 0;indexOfRecord<SizeOfRecord;++indexOfRecord){
		PointerToTheBigArray[++indexOfBigArray]=PointerToTheRecord[indexOfRecord];
	}
	return PointerToTheBigArray;
}

char* LoadAllRecordsToMemoryAndReturnPointerToAllocatedMemoryIfFileExists(char* filename){

	char* currentData;
	char* BigDataArray = NULL;
	int BigDataArrayIndex = 0;
	FILE* fin;
	if(FileExists(filename)==0){
		fin = fopen(filename,"rb");
		while((currentData = ReturnPointerToTheNextRecord(fin))!=NULL){
			BigDataArray = AppendARecordToTheBigArrayAndReturnPointerToIt(currentData,BigDataArray,&BigDataArrayIndex);
			free(currentData);
		}
		fclose(fin);
		return BigDataArray;
	}else{
		printf("File not exists\n");
		return NULL;
	}
}



int main(){
	char* BigMemoryArray;
	//AppendNewRecord(BINFILE);
	BigMemoryArray = LoadAllRecordsToMemoryAndReturnPointerToAllocatedMemoryIfFileExists(BINFILE);
	PrintADataByIndex(BigMemoryArray,0);
	free(BigMemoryArray);
	return 0;
}
