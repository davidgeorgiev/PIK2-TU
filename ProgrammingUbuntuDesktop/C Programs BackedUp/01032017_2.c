#include <stdio.h>
#include <stdlib.h>

void MakeAllZero(int* results){
	int i = 0;
	while(i<=26){
		results[i]=0;
		i++;
	}
	
}

int IdentificatAndCount(int* results,char c){
	int i;
	int diff = 'A'-'a';
	for(i = 'a';i<='z';i++){
		if((c==i)||(c-diff==i)){
			results[i-'a']++;
		}
	}
	
	return 0;
}

void PrintResults(int* results){
	int i;
	for(i='a';i<='z';i++){
		if(results[i-'a']!=0){
			printf("%c: %d\n",i,results[i-'a']);
		}
	}
}

int main(){
	char c;
	int results[26];
	MakeAllZero(results);
	while((c=getchar())!='\n'){
		IdentificatAndCount(results,c);
	}
	PrintResults(results);
}
