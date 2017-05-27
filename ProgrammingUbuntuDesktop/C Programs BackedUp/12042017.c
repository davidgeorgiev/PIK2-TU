#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//potrebitelqt vuvezhda 12.04.2017 trqbva da se oburne taka 20170412 i da se izkarat dannite za knigite predi datata

struct MyStruct{
	int id;
	char name[30];
	char date[30];
};
typedef struct MyStruct MyStruct;

MyStruct* AddRecord(MyStruct* objects,int* len){
	objects = (MyStruct*)realloc(objects,sizeof(MyStruct)*(++(*len)));
	printf("\nENTER NEW BOOK\n");
	printf("enter id ");
	scanf(" %d",&(objects[(*len)-1].id));
	printf("enter name ");
	scanf("%s",&(objects[(*len)-1].name));
	printf("enter date ");
	scanf("%s",&(objects[(*len)-1].date));
	return objects;
}
char* FixDate(char* mystr){
	char* fixedstring;
	fixedstring = (char*)malloc(30);
	fixedstring[6] = mystr[0];
	fixedstring[7] = mystr[1];
	fixedstring[4] = mystr[3];
	fixedstring[5] = mystr[4];
	fixedstring[0] = mystr[6];
	fixedstring[1] = mystr[7];
	fixedstring[2] = mystr[8];
	fixedstring[3] = mystr[9];
	fixedstring[8] = '\0';
	return fixedstring;
}
void PrintAllBooksBydate(MyStruct* objects,int* len,char* date){
	char* myfixeddate;
	char* currentdate;
	myfixeddate = FixDate(date);
	//printf("Fixed date = %s\n",myfixeddate);
	printf("\nPRINTING ALL BOOKS BEFORE %s\n",date);
	int i;
	int is_some_book = 0;
	for(i = 0;i < *len;++i){
		
		currentdate = FixDate(objects[i].date);
		if(strcmp(currentdate,myfixeddate)<1){
			printf("\n");
			printf("id = %d\n",objects[i].id);
			printf("name = %s\n",objects[i].name);
			printf("date = %s\n",objects[i].date);
			is_some_book = 1;
		}
		free(currentdate);
	}
	if(is_some_book == 0){
		printf("sorry there is not books before %s\n",date);
	}
	free(myfixeddate);
}
int main(){
	int len = 0;
	MyStruct* TestStruct = NULL;
	char c = 'y';
	char* mydate = (char*)malloc(30);
	
	while(c=='y'){
		TestStruct = AddRecord(TestStruct,&len);
		printf("\nAdd new record? y/n\n");
		scanf(" %c",&c);
	}
	c = 'y';
	while(c=='y'){
		printf("\nEnter an date in format dd.mm.yyyy\n");
		scanf("%s",mydate);
		PrintAllBooksBydate(TestStruct,&len,mydate);
		printf("\nCheck with another date? y/n\n");
		scanf(" %c",&c);
	}
	free(mydate);
	
	
	
	return 0;
}
