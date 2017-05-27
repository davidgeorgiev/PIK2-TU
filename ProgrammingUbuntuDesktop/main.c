#include <stdio.h>
#include <stdlib.h>
void selectionSort(TTemp *temp);

int main(){
	return 0;
}



void selectionSort(TTemp *temp){
	TTemp TempValue;
	int minIndex;
	int i,j;
	
	
	
	for(i=0;i<SIZE;i++){
		minIndex = i;
		for(j=i+1;j<Size;j++){
			if(temp[minIndex]>temp[j]){
				minIndex = j;
			}
		}
		tempValue = temp[i];
		tamp[i] = temp[minIndex];
		tempMinValue = tempValue;
	}
}
