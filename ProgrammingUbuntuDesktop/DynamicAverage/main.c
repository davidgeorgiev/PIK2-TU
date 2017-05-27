#include <stdio.h>
#include <stdlib.h>
#define INPUTFILENAME "numbers.txt"
#define OUTPUTFILENAME "result.txt"


int CloseArray(int** DynamicArray,int len){
	int* CheckUpdateMemory = (int*)realloc(*DynamicArray,sizeof(int)*(++len));
	if(CheckUpdateMemory != NULL){
		free(*DynamicArray);
		*DynamicArray = CheckUpdateMemory;
		*DynamicArray[len-1] = '\0';
		printf("Successfuly appended \\0 to array on index %d\n",len-1);
		return 0;
	}else{
		return -1;
	}
}

int AppendNumberToArray(int** DynamicArray,int NumberToAppend,int len){
	//printf("before %p\n",*DynamicArray);
	int* CheckUpdateMemory = (int*)realloc(*DynamicArray,sizeof(int)*(++len));
	if(CheckUpdateMemory != NULL){
		free(*DynamicArray);
		*DynamicArray = CheckUpdateMemory;
		*DynamicArray[len-1] = NumberToAppend;
		//printf("after %p\n",*DynamicArray);
		printf("Successfuly appended %d to array on index %d\n",*DynamicArray[len-1],len-1);
		return len;
	}else{
		return -1;
	}
}

int GetNextNumberFromTheFile(FILE* fp){
	int ch;
	int tempnumber = 0;
	char negative = 0;
	char LastWasDigit = 0;
	while((ch = fgetc(fp))!=EOF){
		if(ch == '-'){
			negative = 1;
		}
		if((ch <= '9')&&(ch >= '0')){
			tempnumber *= 10;
			tempnumber += ch-'0';
			LastWasDigit = 1;
		}else{
			if(LastWasDigit){
				if(ch != '-'){
					if(negative){tempnumber*=-1;negative = 0;}
				}
				return tempnumber;
			}
			tempnumber = 0;
			LastWasDigit = 0;
		}
	}
	return EOF;
}

int GetNumbersFromTheFileAndSaveThemInArray(char* filename,int** DynamicArray){
	FILE* fp = fopen(filename,"r");
	int current_number;
	int len = 0;
	while((current_number = GetNextNumberFromTheFile(fp))!=EOF){
		printf("%p\n",DynamicArray);
		printf("%p\n",*DynamicArray);
		if((len = AppendNumberToArray(DynamicArray,current_number,len))==-1){
			printf("Can\'t append number to array! Allocation memory error!!!\n");
		}
	}
	fclose(fp);
	CloseArray(DynamicArray,len);
	return len;
}

int PrintDynamicArray(int** DynamicArray, int len){
	int i;
	//for(i = 0; i<len; ++i){
		printf("%p\n",*DynamicArray);
	//}
}

int main(){
	int* DynamicArray = NULL;
	int** PointerToDynamicArray = &DynamicArray;
	int len = GetNumbersFromTheFileAndSaveThemInArray(INPUTFILENAME,PointerToDynamicArray);
	PrintDynamicArray(PointerToDynamicArray,len);
	free(DynamicArray);
	return 0;
}
