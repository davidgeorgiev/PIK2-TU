#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

int FindMinEvenNumber(int arr*,int len){
	int i;
	int min;
	int firsttime = 1;
	for(i = 0;i< len;i++){
		if(!arr[i]%2){
			if(firsttime){
				min = i;
				firsttime = 0;
			}
			if(min>arr[i]){
				min = arr[i];
			}
		}
	}
	return min;
}

void UpdateArray(int* arr, int len){
	int i;
	for(i = 0;i<len;i++){
		printf("Please enter arr[%d] ",i);
		scanf(" %d",&arr[i]);
		printf("%d remaining\n ",MAX_SIZE-i-1);
	}
}

int main(){
	int arr[MAX_SIZE];
	UpdateArray(arr, MAX_SIZE);
	return 0;
}
