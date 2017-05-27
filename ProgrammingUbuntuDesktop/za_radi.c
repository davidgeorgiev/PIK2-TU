#include <stdio.h>
#define MAXSIZEOFARRAY 100
#define FIRSTDIGITTOSEARCH 3
#define SECONDDIGITTOSEARCH 8

int MyMenu();
void ArrayInit(int* myarr,int from_user_or_not);
void RunOption(int optionid,int* myarr,int* arrtocopy);
void PrintArray(int* myarr);
void CopyValuesWithSelectedDigitToTheAnotherArray(int* myarr, int* arrtocopy, int mydigit);
int CountADigitInNumber(int number, int digit);
void SortArrayDecreasing(int* myarray);
int CountDigitInArray(int* myarr, int digit);

int main(){
	int option = 0;
	int myarr1[MAXSIZEOFARRAY];
	int myarr2[MAXSIZEOFARRAY];
	while((option = MyMenu())&&(option!=8)){
		RunOption(option,myarr1,myarr2);
	}
	return 0;
}

int MyMenu(){
	int option = 0;
	printf("1. Use existing array\n");
	printf("2. Input your own array\n");
	printf("3. Print the first array\n");
	printf("4. Copy all numbers including %d in them to a second array\n",FIRSTDIGITTOSEARCH);
	printf("5. Sort the second array decreasing\n");
	printf("6. Print the second array\n");
	printf("7. Count how much %d appears in the second array and print result\n",SECONDDIGITTOSEARCH);
	printf("8. Exit\n");
	scanf("%d",&option);
	
	if((option <= 8)&&(option >= 1)){
		return option;
	}else{
		return 0;
	}
}

void ArrayInit(int* myarr,int from_user_or_not){
	int i = 0;
	if(from_user_or_not){

		for(i = 0; i < MAXSIZEOFARRAY; i++){
			printf("myarr[%d]=",i);
			scanf("%d",&myarr[i]);
		}
	}else{
		for(i = 0; i < MAXSIZEOFARRAY; i++){
			myarr[i] = rand() % 100;
		}
	}
}

void RunOption(int optionid,int* myarr,int* arrtocopy){
	if(optionid == 1){
		ArrayInit(myarr,0);
	}else if(optionid == 2){
		ArrayInit(myarr,1);
	}else if(optionid == 3){
		PrintArray(myarr);
	}else if(optionid == 4){
		CopyValuesWithSelectedDigitToTheAnotherArray(myarr, arrtocopy, FIRSTDIGITTOSEARCH);
	}else if(optionid == 5){
		SortArrayDecreasing(arrtocopy);
	}else if(optionid == 6){
		PrintArray(arrtocopy);
	}else if(optionid == 7){
		printf("The digit %d appearing in the second array %d times\n",SECONDDIGITTOSEARCH,CountDigitInArray(arrtocopy, SECONDDIGITTOSEARCH));
	}
	
}
void PrintArray(int* myarr){
	int i = 0;
	printf("Array(");
	for(i = 0; i < MAXSIZEOFARRAY; i++){
		if(i!=0){
			printf(",");
		}
		printf("%d",myarr[i]);
	}
	printf(")\n");
}

void CopyValuesWithSelectedDigitToTheAnotherArray(int* myarr, int* arrtocopy, int mydigit){
	int i = 0;
	int k = 0;
	for(i = 0; i < MAXSIZEOFARRAY; i++){
		if(CountADigitInNumber(myarr[i], FIRSTDIGITTOSEARCH)){
			arrtocopy[k] = myarr[i];
			k++;
		}
	}
	while(k < MAXSIZEOFARRAY){
		arrtocopy[k] = 0;
		k++;
	}
}

int CountADigitInNumber(int number, int digit){
	int currentdigit = 0;
	int counter = 0;
	while(number > 0){
		currentdigit = number % 10;
		number/=10;
		if(currentdigit == digit){
			counter++;
		}
	}
	return counter;
}

void SortArrayDecreasing(int* array){
	int c,d,n,swap;
	n = MAXSIZEOFARRAY;
	for (c = 0 ; c < ( n - 1 ); c++)
		{
		for (d = 0 ; d < n - c - 1; d++)
			{
			if (array[d] < array[d+1])
			{
				swap = array[d];
				array[d] = array[d+1];
				array[d+1] = swap;
			}
		}
	}
}

int CountDigitInArray(int* myarr, int digit){
	int i = 0;
	int counter = 0;
	for(i = 0; i < MAXSIZEOFARRAY; i++){
		counter+= CountADigitInNumber(myarr[i],digit);
	}
	return counter;
}

