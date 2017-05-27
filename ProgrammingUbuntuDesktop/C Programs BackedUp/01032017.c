#include <stdio.h>
#include <stdlib.h>

void EnterString(char* mystring, FILE* fp){
	size_t size = 1;
	int pos = 0;
	char tempc;
	mystring = realloc(NULL,sizeof(char));
	while((tempc = fgetc(fp))!='\n'){
		mystring[pos++] = tempc;
		//printf("%c",tempc);
		mystring = realloc(mystring,sizeof(char)*(++size));
		//printf("%c",mystring[pos-1]);
	}
	mystring[pos] = '\0';
}

void PrintString(char* mystring){
	int i = 0;
	while(mystring[i]!='\0'){
		printf("%c, ",mystring[i]);
		i++;
	}
}

int main(){
	char* mystring;
	
	int i = 0;
	char* arraychars;
	int* arraynumber;
	size_t sizechars = 0;
	size_t sizenumber = 0;
	arraychars = realloc(NULL,sizeof(char));
	arraynumber = realloc(NULL,sizeof(char));
	
	EnterString(mystring,stdin);
	PrintString(mystring);
	
	free(mystring);
	return 0;
}
