#include <stdio.h>
#include <stdlib.h>

int IsDigit(char c){
	if((c <= '9')&&(c >= 0)){
		return 1;
	}
	return 0;
}

char* GetNumber(FILE* fp){
	char* enternumber;
	int ch;
	size_t len = 0;
	size_t size = 1;
	enternumber = realloc(NULL,sizeof(char));
	
	while((ch = fgetc(fp))!=EOF && ch != '\n'){
		if(IsDigit(ch)){
			enternumber[len++]=ch;
			enternumber = realloc(enternumber,sizeof(char)*(++size));
		}
	}
	enternumber[len] = '\0';
	return enternumber;
}

void PrintNumber(char* number){
	int i;
	for(i = 0;number[i]!='\0';i++){
		printf("%c",number[i]);
	}
	printf("\n");
}

char* CopyMyNumber(char* numbertocopy){
	int i;
	char* myCopiedNumber;
	int size = 1;
	myCopiedNumber = realloc(NULL,sizeof(char));
	for(i = 0;numbertocopy[i]!='\0';++i){
		myCopiedNumber[i] = numbertocopy[i];
		myCopiedNumber = realloc(myCopiedNumber,sizeof(char)*(++size));
	}
	return myCopiedNumber;
}

void ShiftLeftWholeArrayAndRealloc(char* number){
	int i;
	for(i = 0;number[i]!='\0';++i){
		number[i]=number[i+1];
	}
	number[--i] = '\0';
	number = realloc(number,sizeof(char)*++i);
}

int DivideByTwoAndReturnIfCarry(char* number){
	int i;
	int CarryOrNot;
	for(i = 0;number[i]!='\0';++i);
	i--;
	CarryOrNot = (((number[i]-'0')%2)!=0);
	
	while(i >= 0){
		if((number[i]-'0')%2!=0){
			number[i]--;
			if(number[i+1]!='\0'){
				number[i+1]+=5;
			}
		}
		number[i] = ((number[i]-'0')/2)+'0';
		i--;
	}
	if(number[0]=='0'){
		ShiftLeftWholeArrayAndRealloc(number);
	}
	return CarryOrNot;
}

void ReverseMyArray(char* array){
	int i;
	for(i = 0;array[i]!='\0';++i);
	i--;
	int k = 0;
	while(k<i){
		array[k] += array[i];
		array[i] = array[k]-array[i];
		array[k] = array[k]-array[i];
		k++;
		i--;
	}
}

char* ReturnTransformedToBinary(char* number){
	char* bin;
	size_t len = 0;
	size_t size = 1;
	char* copiednumber = CopyMyNumber(number);
	bin = realloc(NULL,sizeof(char));
	while(copiednumber[0]!='\0'){
		bin[len++] = '0'+DivideByTwoAndReturnIfCarry(copiednumber);
		bin = realloc(bin,sizeof(char)*(++size));
	}
	bin[len] = '\0';
	
	free(copiednumber);
	return bin;
}

int is_prime(long long int num){
	long long int i;
	if (num <= 1) return 0;
	if (num % 2 == 0 && num > 2) return 0;
	for(i = 3; i < num / 2; i+= 2){
		if (num % i == 0)
			return 0;
	}
	return 1;
}

long long int FindNextPrimeNumber(long long int currentnumber){
	currentnumber++;
	while(!is_prime(currentnumber)){
		currentnumber++;
	}
	return currentnumber;
}

void PrintPrimeArray(long long int* primearray){
	int i;
	for(i = 0;primearray[i]!='\0';++i){
		printf("%lld,",primearray[i]);
	}
	printf("\n");
}

void SumArrayWithNumber(char* array,long long int number){
	ReverseMyArray(array);
	int i;
	int temp;
	int size = 1;
	int len = 0;
	while(number>0){
		if(number>10){
			temp = number%10;
		}else{
			temp = number;
		}
		number/=10;
		temp = array[len]-'0'+temp;
		array[len++] = temp%10;
		temp/=10;
		array = realloc(array,sizeof(long long int)*(++size));
		if(temp!=0){
			array[len] = temp;
		}
	}
	if(temp!=0){
		array[len+1]='\0';
	}else{
		array[len]='\0';
	}
	ReverseMyArray(array);
}

char* MultiplyGiantNumberByInteger(char* giantnum,long long int myinteger){
	ReverseMyArray(giantnum);
	char* SummedGiantNumber = realloc(NULL,sizeof(char)*2);
	SummedGiantNumber[0] = '0';
	SummedGiantNumber[1] = '\0';
	
	int i;
	long long int mulpart;
	for(i = 0;giantnum[i]!='\0';++i){
		mulpart = (giantnum[i]-'0')*myinteger;
		mulpart*=10^i;
		SumArrayWithNumber(SummedGiantNumber,mulpart);
	}
	
	
	free(giantnum);
	return SummedGiantNumber;
}

char* ReturnMultiplicatedGiantNumber(long long int* primesarray){
	char* multiplicatedGiantNumber;
	multiplicatedGiantNumber = realloc(NULL,sizeof(char)*2);
	multiplicatedGiantNumber[0] = '1';
	multiplicatedGiantNumber[1] = '\0';
	int i;
	for(i = 0;primesarray[i]!='\0';++i){
		multiplicatedGiantNumber = MultiplyGiantNumberByInteger(multiplicatedGiantNumber,primesarray[i]);
	}
	
	
	
	return multiplicatedGiantNumber;
}

long long int* ConvertBinaryToPrimeArray(char* bin){
	long long int* primaryarray;
	size_t size = 1;
	primaryarray = realloc(NULL,sizeof(long long int));
	int lastindex;
	for(lastindex = 0;bin[lastindex]!='\0';++lastindex);
	lastindex--;
	
	long long int currentprimenumber = 0;
	int indexprimenumbersarray = 0;
	int i = 0;
	for(i = lastindex;i>=0;--i){
		currentprimenumber = FindNextPrimeNumber(currentprimenumber);
		if(bin[i]=='1'){
			primaryarray[indexprimenumbersarray++]=currentprimenumber;
			primaryarray = realloc(primaryarray,sizeof(long long int)*(++size));
		}
	}
	primaryarray[indexprimenumbersarray] = '\0';
	return primaryarray;
}


char* CalculateData(char* StartNumber, char* Steps){
	char* CalculatedData;
	char* BinNum = ReturnTransformedToBinary(StartNumber);
	ReverseMyArray(BinNum);
	PrintNumber(BinNum);
	long long int* primearray = ConvertBinaryToPrimeArray(BinNum);
	PrintPrimeArray(primearray);
	char* multiplicatedGiantNumber = ReturnMultiplicatedGiantNumber(primearray);
	PrintNumber(multiplicatedGiantNumber);
	
	free(multiplicatedGiantNumber);
	free(primearray);
	free(BinNum);
	return CalculatedData;
}



int main(){
	char* StartNumber;
	printf("Enter the start number here: ");
	StartNumber = GetNumber(stdin);
	//PrintNumber(StartNumber);
	char* Steps;
	printf("Enter the number of the steps here: ");
	Steps = GetNumber(stdin);
	//PrintNumber(Steps);
	char* Data;
	Data = CalculateData(StartNumber,Steps);
	free(StartNumber);
	free(Steps);
	return 0;
}
