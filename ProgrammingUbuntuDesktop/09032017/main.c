//Дадени са средномесечните температури за всеки месец, да се прочетат данните и да се определи средната температура за годината (средна за тримесечие), да се прочетат данните, да се изкарат на екрана и да се принтират във файл средната температура за тримесечие и средната температура за годината.
/*void qsort(void *base, size_t nmemb, size_t size, int(*compar)(const void *, const void *));
compar
 0 if a = b
 1 if a > b
-1 if a < b
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 12

void print(double* temperatures);
int readTextFile(char* fileName,double* temperature);
char* nameOfMonth(int id);
int minTemp(double *temp);
int maxTemp(double *temp);



int main(){
	double temperature[SIZE];
	int minTempIndex,maxTempIndex;
	if(readTextFile("months.txt",temperature)==-1){
		exit(-1);
	}
	print(temperature);
	minTempIndex = minTemp(temperature);
	maxTempIndex = maxTemp(temperature);
	printf("Max temperature: %s = %lf\n",nameOfMonth(minTempIndex),temperature[minTempIndex]);
	printf("Min temperature: %s = %lf\n",nameOfMonth(maxTempIndex),temperature[maxTempIndex]);
	return 0;
}

void print(double* temperature){
	int i;
	printf("Month\ttemperature\n");
	for(i = 0;i < SIZE;++i){
		printf("%s\t%g\n",nameOfMonth(i),temperature[i]);
	}
}

int readTextFile(char* fileName,double* temperature){
	FILE* fin;
	int i = 0;
	fin = fopen(fileName,"r");
	if(fin == NULL){
		perror(NULL);
		return -1;
	}
	while(!feof(fin)){
		fscanf(fin,"%lf",&temperature[i++]);
		if(i==SIZE){
			break;
		}
	}
	fclose(fin);
	return 0;
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

int minTemp(double *temp){
	int min  = 0;
	int i;
	for(i = 1; i<SIZE;++i){
		if(*(temp+i)<temp[min]){
			min=i;
		}
	}
	return min;
}
int maxTemp(double *temp){
	int max  = 0;
	int i;
	for(i = 1; i<SIZE;++i){
		if(*(temp+i)>temp[max]){
			max=i;
		}
	}
	return max;
}
