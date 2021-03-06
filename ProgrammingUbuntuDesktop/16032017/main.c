#include <stdio.h>
#include <stdlib.h>
#define SIZE 12

typedef struct {
	double temp;
	int month;
} TTemp;

void readTemp(TTemp* temp,char* filename);
void printTemp(TTemp *temp);
char* nameOfMonth(int id);

int main(){
	/*TTemp temperature;
	printf("Input temperature: ");
	scanf("%lf",&temperature.temp);
	printf("Input month: ");
	scanf("%d",&temperature.month);
	
	printf("Temp: %g\tfor %d\n",temperature.temp,temperature.month);
	*/
	
	TTemp temps[SIZE];
	readTemp(temps,"months.txt");
	
	return 0;
}

void printTemp(TTemp *temp){
	int i;
	for(i = 0;i < SIZE; ++i){
		printf("%s\t%g\n",nameOfMonth(temp[i].month),temp[i].temp);
	}
}

char* nameOfMonth(int id){
	switch(id){
		case 0:return "JAN";
		case 1:return "FEB";
		case 2:return "MAR";
		case 3:return "APR";
		case 4:return "MAY";
		case 5:return "JUN";
		case 6:return "JUL";
		case 7:return "AUG";
		case 8:return "SEP";
		case 9:return "OCT";
		case 10:return "NOV";
		case 11:return "DEC";
		default:return "No such month";
	}
	return " ";
}

void readTemp(TTemp* temp,char* filename){
	FILE* fin;
	int i = 0;
	fin = fopen(filename,"r");
	if(fin == NULL){
		perror(NULL);
		exit(1);
	}
	while(!feof(fin)){
		fscanf(fin,"%lf",&(temp[i].temp));
		temp[i].month=i;
		++i;
		if(i==SIZE){
			break;
		}
		
		//fclose(fin);
	}
}
