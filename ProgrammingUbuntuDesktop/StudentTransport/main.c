#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define NUMBER_OF_TRANSPORTS 5
#define MAX_KILOMETERS 5000

struct Transport {
	char _name[30];
    float _start_price;
    float _night_price;
    float _day_price;
    int _min_kilometers;

};

typedef struct Transport Transport;

void CopyName(Transport* transport,const char name[30]){
    	int i = 0;
    	while(name[i]!='\0'){
    		(*transport)._name[i] = name[i];
    		i++;
    	}
    	(*transport)._name[i]='\0';
    }
void initialize(Transport* transport,const char name[30],float start_price,float night_price,float day_price,int min_kilometers){
    (*transport)._start_price = start_price;
    (*transport)._night_price = night_price;
    (*transport)._day_price = day_price;
    (*transport)._min_kilometers = min_kilometers;
    CopyName(transport,name);
}

void GetNumericalString(char* outString){
	char userString[10];
	scanf(" %s",userString);
	
	
	int i = 0;
	int k = 0;
	while(userString[i]!='\0'){
		if((userString[i]<='9')&&(userString[i]>='0')){
			outString[k] = userString[i];
			k++;
		}
		i++;
	}
	if(k==0){
		outString[k] = '0';
		k++;
	}
	outString[k] = '\0';
}

int GetKilometers(int* kilometers){
	char StringInput[10];
	printf("Enter kilometers: ");
	GetNumericalString(StringInput);
	if(sscanf(StringInput,"%d",kilometers)){
		return 0;
	}else{
		return -1;
	}
}

int GetTime(int* dayOrNight,char* userInput){
	*dayOrNight = -1;
	printf("Enter time: ");
	scanf("%s",userInput);
	
	if(strcmp(userInput,"day")==0){
		*dayOrNight = 0;
	}else if(strcmp(userInput,"night")==0){
		*dayOrNight = 1;
	}
	return *dayOrNight;
}

void PrintErrorTime(char* userInput){
	printf("The time must be \"day\" or \"night\", but your input is \"%s\"!\n",userInput);
}
void PrintErrorKm(int userInput){
	printf("The kilometers must be a value between 0 and 5000, but your value is \"%d\"!\n",userInput);
}

void PrintTransports(Transport* available_transports,int len){
	int i = 0;
	while(i<len){
		printf("\nTransport %d:\nname:\t\t%s\nstart price:\t%.2f BGN\nnight price:\t%.2f BGN\nday price:\t%.2f BGN\nmin kilometers:\t%d\n",i+1,available_transports[i]._name,available_transports[i]._start_price,available_transports[i]._night_price,available_transports[i]._day_price,available_transports[i]._min_kilometers);
		i++;
	}
}

int FindBestPriceByIndex(float* prices){
	int i = 0;
	float bestPrice;
	int BestPriceIndex = -1;
	while(prices[i]!='\0'){
		if(prices[i]>0){
			if(i == 0){
				bestPrice = prices[i];
				BestPriceIndex = i;
			}
			if(bestPrice>prices[i]){
				bestPrice = prices[i];
				BestPriceIndex = i;
			}
		}
		i++;
	}
	return BestPriceIndex;
}

void PrintAllPriceInformation(float* prices,Transport* transports,int len,int kilometers,int dayOrNight){
	printf("Look at this data and you will believe\n");
	int i = 0;
	char day[4] = "day";
	char night[6] = "night";
	while(i<len){
		if(prices[i]>0){
			if(dayOrNight==0){// 0 for day and 1 for night
				printf("%s for %d kilometers at %s costs %.2f\n",transports[i]._name,kilometers,day,prices[i]);
			}else{
				printf("%s for %d kilometers at %s costs %.2f\n",transports[i]._name,kilometers,night,prices[i]);
			}
		}else{
			printf("%s is UNAVAILABLE for %d kilometers, because the min kilometers are %d\n",transports[i]._name,kilometers,transports[i]._min_kilometers);
		}
		
		i++;
	}
	printf("\n");
}

void PrintTheBestPriceTransport(int kilometers,int dayOrNight,Transport* transports,int* transportIndex,int len){
	int i = 0;
	float* prices = (float*)malloc(sizeof(float)*len+1);
	int BestTransportIndex;
	prices[len] = '\0';
	while(i < len){
		if(transports[i]._min_kilometers<=kilometers){
			prices[i] = transports[i]._start_price;
			if(dayOrNight==0){ // 0 for day and 1 for night
				prices[i] += transports[i]._day_price*kilometers;
			}else{
				prices[i] += transports[i]._night_price*kilometers;
			}
		}else{
			prices[i] = -1;
		}
		i++;
	}
	BestTransportIndex = FindBestPriceByIndex(prices);
	printf("\nThe best price transport is %s, because min kilometers are %d which is less than %d and costs %.2f BGN which is cheaper than the other transports in this case\n\n",transports[BestTransportIndex]._name,transports[BestTransportIndex]._min_kilometers,kilometers,prices[BestTransportIndex]);
	PrintAllPriceInformation(prices,transports,len,kilometers,dayOrNight);
	free(prices);
}

int main(){
	printf("\n");
	int mykm = 0;
	int dayOrNight; // 0 for day and 1 for night
	char dayOrNightUserInput[5];
	int transportIndex;
	
	while((GetKilometers(&mykm)==-1)||((mykm>MAX_KILOMETERS)||(mykm<=0))){
		PrintErrorKm(mykm);
	}
	
	while(GetTime(&dayOrNight,dayOrNightUserInput)==-1){
		PrintErrorTime(dayOrNightUserInput);
	}
	
	Transport available_transports[NUMBER_OF_TRANSPORTS];
	initialize(&available_transports[0],"TAXI",0.7,0.79,0.9,0);
	initialize(&available_transports[1],"BUS",0,0.9,0.9,20);
	initialize(&available_transports[2],"TRAIN",0,0.06,0.06,100);
	initialize(&available_transports[3],"AIRPLANE",0,0.21,0.15,200);
	initialize(&available_transports[4],"HELICOPTER",0,0.11,0.10,200);
	PrintTransports(available_transports,NUMBER_OF_TRANSPORTS);
	
	PrintTheBestPriceTransport(mykm,dayOrNight,available_transports,&transportIndex, NUMBER_OF_TRANSPORTS);
	
	return 0;
}
