#include <stdio.h>
/*
FILE *fp;

FILE *fp fopen(const char *filename, const char *mode);
int fscanf(FILE *fp, const char *mode, ...);
int *p;
void *p1;

int fgetc(FILE *fp);
int fputc(int c, FILE *fp);
*/
int main(){
	FILE *fp;
	//DIR *dp;
	int a;
	char arr[1000];

	fp = fopen("text1.txt" , "r");

	//while((a = fgetc(fp)) != EOF){

	//}
	//fprintf(fp , "text asdf");
	fscanf(fp , "r" , arr);

	int i;
	for(i = 0; i <= 1000; i++){
		printf("%c",arr[i]);
	}
	//fp = fopen("text.txt", "w"); //w open for read, create if not exist
	//fp = fopen("text.txt", "a"); //a append
	//fp = fopen("text.txt", "r"); //r read
	//fp = fopen("text.txt", "r+"); //r+ read and write from the beginning of the file
	//fp = fopen("text.txt", "w+"); //w+ delete existing file and open
	//fp = fopen("text.txt", "a+"); //a+ append only if the file exists

	// fread = for binary files read byte by byte
	// fwrite = for binary files read byte by byte
	// wb rb ab

	fclose(fp);

	return 0;
}
